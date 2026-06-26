#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"

// Incluir Edge Impulse
#include "edge-impulse-sdk/classifier/ei_run_classifier.h"
#include "model-parameters/model_metadata.h"

// ==================== CONFIGURAÇÕES ====================

// Pinos do AHT10 (I2C)
#define I2C_PORT i2c0
#define PIN_SDA 4
#define PIN_SCL 5
#define AHT10_ADDR 0x38

// Pino do MQ-2 (ADC)
#define PIN_MQ2 26

// Pinos dos atuadores
#define PIN_LED_VERDE 14
#define PIN_LED_VERMELHO 15
#define PIN_BUZZER 16

// ==================== FUNÇÕES DOS SENSORES ====================

bool read_aht10(float *temp, float *hum) {
    uint8_t cmd[3] = {0xAC, 0x33, 0x00};
    uint8_t data[6];
    
    i2c_write_blocking(I2C_PORT, AHT10_ADDR, cmd, 3, false);
    sleep_ms(80);
    
    if (i2c_read_blocking(I2C_PORT, AHT10_ADDR, data, 6, false) != 6) {
        return false;
    }
    
    if (data[0] & 0x80) {
        return false;
    }
    
    uint32_t raw_temp = ((uint32_t)data[3] & 0x0F) << 16 | 
                        (uint32_t)data[4] << 8 | 
                        (uint32_t)data[5];
    uint32_t raw_hum = ((uint32_t)data[1] << 12) | 
                       ((uint32_t)data[2] << 4) | 
                       ((uint32_t)data[3] >> 4);
    
    *temp = (raw_temp * 200.0f / 1048576.0f) - 50.0f;
    *hum = raw_hum * 100.0f / 1048576.0f;
    
    return true;
}

float read_mq2() {
    adc_select_input(0);
    uint16_t raw = adc_read();
    return (float)raw;
}

// ==================== FUNÇÃO PRINCIPAL ====================

int main() {
    stdio_init_all();
    sleep_ms(2000);
    printf("\n🔥 Fire Detection System - Edge AI\n");
    printf("Features: %d\n", EI_CLASSIFIER_INPUT_WIDTH);
    
    // ========== INICIALIZAR PERIFÉRICOS ==========
    
    // I2C para AHT10
    i2c_init(I2C_PORT, 100000);
    gpio_set_function(PIN_SDA, GPIO_FUNC_I2C);
    gpio_set_function(PIN_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(PIN_SDA);
    gpio_pull_up(PIN_SCL);
    
    // ADC para MQ-2
    adc_init();
    adc_gpio_init(PIN_MQ2);
    adc_select_input(0);
    
    // LEDs e Buzzer
    gpio_init(PIN_LED_VERDE);
    gpio_set_dir(PIN_LED_VERDE, GPIO_OUT);
    gpio_init(PIN_LED_VERMELHO);
    gpio_set_dir(PIN_LED_VERMELHO, GPIO_OUT);
    gpio_init(PIN_BUZZER);
    gpio_set_dir(PIN_BUZZER, GPIO_OUT);
    
    gpio_put(PIN_LED_VERDE, 1);
    gpio_put(PIN_LED_VERMELHO, 0);
    gpio_put(PIN_BUZZER, 0);
    
    // ========== LOOP PRINCIPAL ==========
    
    float temperature = 0, humidity = 0, gas = 0;
    int count = 0;
    
    while (true) {
        // 1. Ler sensores
        if (read_aht10(&temperature, &humidity)) {
            gas = read_mq2();
        } else {
            printf("⚠️ Erro no AHT10\n");
            sleep_ms(1000);
            continue;
        }
        
        // 2. Preparar dados para o classificador
        float features[3] = {temperature, humidity, gas};
        signal_t signal;
        int err = numpy::signal_from_buffer(features, 3, &signal);
        if (err != 0) {
            printf("❌ Erro: numpy::signal_from_buffer %d\n", err);
            sleep_ms(1000);
            continue;
        }
        
        // 3. Executar a classificação (Edge Impulse)
        ei_impulse_result_t result = { 0 };
        err = run_classifier(&signal, &result, false);
        if (err != 0) {
            printf("❌ Erro na classificação: %d\n", err);
            sleep_ms(1000);
            continue;
        }
        
        // 4. Obter as probabilidades
        float prob_safe = 0;
        float prob_fire = 0;
        for (size_t i = 0; i < EI_CLASSIFIER_LABEL_COUNT; i++) {
            if (strcmp(result.classification[i].label, "0") == 0 ||
                strcmp(result.classification[i].label, "safe") == 0) {
                prob_safe = result.classification[i].value;
            } else {
                prob_fire = result.classification[i].value;
            }
        }
        
        // 5. Verificar se é incêndio
        bool is_fire = prob_fire > 0.5;
        
        // 6. Acionar atuadores
        if (is_fire) {
            gpio_put(PIN_LED_VERDE, 0);
            gpio_put(PIN_LED_VERMELHO, 1);
            gpio_put(PIN_BUZZER, 1);
            printf("🔥 ALERTA! Incêndio detectado! (%.2f%%)\n", prob_fire * 100);
        } else {
            gpio_put(PIN_LED_VERDE, 1);
            gpio_put(PIN_LED_VERMELHO, 0);
            gpio_put(PIN_BUZZER, 0);
            if (count % 10 == 0) {
                printf("✅ Ambiente seguro (%.2f%%)\n", prob_safe * 100);
            }
        }
        
        // 7. Mostrar dados a cada 5 segundos
        if (count % 5 == 0) {
            printf("📊 T: %.2f°C | H: %.2f%% | Gás: %.0f | Fire: %.2f%%\n",
                   temperature, humidity, gas, prob_fire * 100);
        }
        
        count++;
        sleep_ms(1000);
    }
    
    return 0;
}
