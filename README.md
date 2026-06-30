# 🔥 Detecção de Anomalias Indicativas de Incêndio em Ambientes Internos utilizando Edge AI

Projeto desenvolvido para a disciplina de **Aprendizado de Máquina Embarcado (AME)** da **Universidade Federal do Ceará (UFC) – Campus Quixadá**.

O sistema utiliza **Inteligência Artificial embarcada (Edge AI)** para identificar condições indicativas de incêndio a partir de sensores ambientais, permitindo a execução do modelo diretamente em uma **Raspberry Pi Pico**.

---

## 👩‍💻 Autoras

- **Beatriz de Sousa Alves**
- **Vitória das Graças Silva**

Universidade Federal do Ceará – Campus Quixadá

---

# 📌 Objetivo

Desenvolver um sistema inteligente capaz de detectar anomalias indicativas de incêndio em ambientes internos utilizando um modelo de aprendizado de máquina de baixo custo computacional.

O projeto combina sensores ambientais e um modelo **Multi-Layer Perceptron (MLP)** treinado para classificar o ambiente como:

- ✅ Ambiente seguro
- 🔥 Risco de incêndio

O objetivo final é executar toda a inferência diretamente em um dispositivo embarcado utilizando conceitos de **TinyML**.

---

# 🚀 Demonstração

Durante a execução, a Raspberry Pi Pico realiza continuamente:

- leitura dos sensores;
- pré-processamento dos dados;
- inferência utilizando o modelo treinado;
- acionamento dos dispositivos de alerta.

Exemplo de saída:

```text
✅ Ambiente seguro (99.61%)

📊 T: 32.78°C
📊 H: 65.69%
📊 Gás: 1977
📊 Fire: 0.39%
```

Quando há risco:

```text
🔥 ALERTA! Incêndio detectado! (97.66%)
```

---

# 🖥️ Arquitetura do Sistema

```text
                Sensores
        ┌────────┬────────┐
        │        │        │
     Temperatura Umidade  Gás
        │        │        │
        └────────┴────────┘
                 │
                 ▼
        Pré-processamento
                 │
                 ▼
        Modelo MLP (Edge AI)
                 │
                 ▼
      Probabilidade de Incêndio
                 │
      ┌──────────┴──────────┐
      ▼                     ▼
 Ambiente Seguro      Alerta de Incêndio
```

---

# 🧠 Modelo de IA

Modelo utilizado:

- Multi-Layer Perceptron (MLP)

Arquitetura:

```text
Entrada (3 atributos)

↓

Dense (32 neurônios)

↓

Dense (16 neurônios)

↓

Dense (8 neurônio)

↓

Sigmoid
```

Funções utilizadas:

- ReLU
- Sigmoid
- Binary Crossentropy
- Adam Optimizer

---

# 📊 Dataset

Foi utilizado o **Manual Fire Dataset**, disponível publicamente no Kaggle.

Características:

- 6122 amostras
- Temperatura
- Umidade
- Concentração de gases
- Classe (Normal / Fire)

Divisão dos dados:

| Conjunto | Percentual |
|-----------|-----------:|
| Treino | 70% |
| Validação | 15% |
| Teste | 15% |

---

# 📈 Resultados

| Métrica | Valor |
|---------|-------|
| Accuracy | **97.61%** |
| Precision | **97.25%** |
| Recall | **97.70%** |
| F1-Score | **97.47%** |

O modelo apresentou excelente capacidade de generalização e baixo índice de falsos alarmes.

---

# ⚙️ Hardware Utilizado

- Raspberry Pi Pico
- Sensor AHT10
- Sensor MQ-2
- LED verde
- LED vermelho
- Buzzer

---

# 💻 Software

- Python
- TensorFlow
- TensorFlow Lite
- Edge Impulse
- Pico SDK
- CMake
- VS Code

---

# 📂 Estrutura do Projeto

```text
ProjetoFinalAME/

├── README.md
├── requirements.txt
├── notebook/
├── model/
├── pico/
├── data/
```

---

# ▶️ Como Executar

## 1. Clone o projeto

```bash
git clone 



(https://github.com/bea00518/ProjetoFinalAME/tree/master#)
```

---

## 2. Instale as dependências

```bash
pip install -r requirements.txt
```

---

## 3. Execute o notebook

Abra:

```
notebook/Fire_Detection_MLP.ipynb
```

Execute todas as células para reproduzir o treinamento.

---

## 4. Compile o projeto da Raspberry Pi Pico

Entre na pasta:

```
pico/
```

Compile utilizando o Pico SDK.

Após a compilação, copie o arquivo `.uf2` para a Raspberry Pi Pico.

---

# 📁 Dataset

O conjunto de dados pode ser obtido em:

https://www.kaggle.com/datasets/bahasurunayanakantha/manual-fire-dataset

Após o download, coloque o arquivo na pasta indicada pelo notebook.

---

# 📄 Artigo

Artigo desenvolvido para a disciplina de Aprendizado de Máquina Embarcado.

**PDF:**

https://drive.google.com/file/d/182xsusvowmiHVy68SBrIEDXJBlNbkA6z/view?usp=sharing

---

# 🔮 Trabalhos Futuros

- Utilização de dados coletados em ambiente real.
- Conversão otimizada para TensorFlow Lite.
- Redução do consumo de memória.
- Aplicativo para monitoramento remoto.
- Integração com sistemas IoT.
- Avaliação em diferentes cenários de incêndio.

---

# 📚 Referências

- TensorFlow
- Edge Impulse
- Manual Fire Dataset (Kaggle)
- Raspberry Pi Pico SDK

---

# 📜 Licença

Este projeto foi desenvolvido exclusivamente para fins acadêmicos.
