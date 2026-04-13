# ProjetoFinalAME
Sistema embarcado com Edge AI para detecção precoce de incêndios em ambientes internos utilizando sensores ambientais e aprendizado de máquina.
#  Fire Detection with Edge AI

Sistema embarcado inteligente para detecção precoce de incêndios em ambientes internos utilizando Edge AI e sensores ambientais.

---

##  Descrição

Este projeto propõe o desenvolvimento de um sistema capaz de identificar anomalias ambientais indicativas de incêndio por meio da análise de dados de sensores em tempo real.

A solução utiliza técnicas de aprendizado de máquina embarcado (Edge AI), permitindo processamento local no dispositivo, reduzindo latência e eliminando a dependência de conexão com a internet.

---

##  Objetivo

Detectar precocemente possíveis situações de incêndio a partir de padrões ambientais, aumentando a segurança e permitindo respostas rápidas antes que o problema se agrave.

---

##  Como funciona

1. Sensores coletam dados ambientais:
   - Temperatura
   - Umidade
   - Concentração de gases/fumaça

2. Os dados são enviados ao Raspberry Pi

3. Um modelo de Machine Learning analisa os dados

4. O sistema classifica o ambiente como:
   - Normal (0)
   - Risco de incêndio (1)

5. Em caso de risco:
   - LEDs de alerta são ativados
   - Buzzer é acionado
   - Interface web exibe o status

---

##  Tecnologias Utilizadas

- Python
- Scikit-learn
- TensorFlow (opcional)
- Raspberry Pi
- Sensores AHT10 e MQ-2
- Flask (dashboard web)

---

##  Hardware

- Raspberry Pi 3 (ou superior)
- Sensor AHT10 (temperatura e umidade)
- Sensor MQ-2 (gases e fumaça)
- LEDs (verde, amarelo, vermelho)
- Buzzer
- Protoboard e jumpers

---

