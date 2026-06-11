<div align="center">

# 📡 ESP32 IoT Smart Control System

**Biblioteca Arduino/ESP32 para gerenciamento não-bloqueante de WiFi e MQTT, com controle infrared e integração AWS IoT Core.**

[![Platform](https://img.shields.io/badge/platform-ESP32-blue?style=flat-square&logo=espressif&logoColor=white)](https://www.espressif.com/)
[![Framework](https://img.shields.io/badge/framework-Arduino-00979D?style=flat-square&logo=arduino&logoColor=white)](https://www.arduino.cc/)
[![MQTT](https://img.shields.io/badge/broker-MQTT%20%7C%20AWS%20IoT-FF9900?style=flat-square&logo=amazonaws)](https://aws.amazon.com/iot-core/)
[![PlatformIO](https://img.shields.io/badge/build-PlatformIO-orange?style=flat-square&logo=platformio)](https://platformio.org/)
[![License](https://img.shields.io/badge/license-Acadêmico-lightgrey?style=flat-square)](./LICENSE)

</div>

---

## 👨‍💻 Equipe

| Integrante |
|---|
| Narcizo Silvério de Almeida |
| Giovanna Mafra Zau |
| Gustavo Ayres Lima |
| Gustavo Rodrigues Padovan Perez |
| Luiz Antônio Uchoa Lacerda |
| Pedro Stain Furtado |

---

## 📋 Sumário

- [Visão Geral](#-visão-geral)
- [Por que não-bloqueante?](#-por-que-não-bloqueante)
- [Arquitetura](#️-arquitetura-do-sistema)
- [Conectividade WiFi](#-conectividade-wifi)
- [Comunicação MQTT](#️-comunicação-mqtt)
- [Controle Infrared](#-controle-infrared-ir)
- [Reconexão Automática](#-sistema-de-reconexão)
- [Sistema de Debug](#-sistema-de-debug)
- [AWS IoT Core](#️-aws-iot-core)
- [Tecnologias](#-tecnologias-utilizadas)
- [Melhorias Futuras](#-melhorias-futuras)

---

## 🚀 Visão Geral

O sistema foi projetado para atuar como um **gateway IoT inteligente**, capaz de:

- 📶 Conectar-se automaticamente a redes WiFi
- ☁️ Comunicar-se com brokers MQTT (HiveMQ / Mosquitto / AWS IoT Core)
- 📡 Receber comandos remotos estruturados em JSON
- 📺 Controlar dispositivos via infravermelho (TVs e eletrônicos)
- 🔄 Garantir reconexão automática em caso de falhas
- 🧠 Registrar logs inteligentes com níveis de debug configuráveis

---

## 🧠 Por que não-bloqueante?

A abordagem tradicional **trava o microcontrolador** com `while()`, impedindo qualquer execução paralela:

```cpp
// ❌ Bloqueante — trava o setup() por até 15 segundos
while (WiFi.status() != WL_CONNECTED) {
  delay(500);
}
```

Este projeto usa **máquinas de estado processadas no `loop()`**:

```cpp
// ✅ Não-bloqueante — setup() retorna imediatamente
void loop() {
  garantirWifiConectado();   // verifica estado, reconecta se necessário
  garantirMQTTConectado();   // idem para o broker MQTT
  loopMQTT();                // processa mensagens recebidas
  receberSinalInfraRed();    // captura IR em paralelo
}
```

**Resultado direto:**

- ✅ Sem travamento do ESP32
- ✅ Execução paralela de tarefas
- ✅ Maior estabilidade em produção

---

## ⚙️ Arquitetura do Sistema

O projeto é organizado em **módulos independentes e desacoplados**:

```
src/
├── main.cpp           → Fluxo principal (setup e loop)
├── WiFiManager.cpp    → Conexão e reconexão WiFi
├── mqttManager.cpp    → Comunicação MQTT (Pub/Sub)
├── debugManager.cpp   → Sistema de logs e diagnóstico
└── secrets.cpp        → Configurações (WiFi, MQTT, AWS)
```

---

## 🌐 Conectividade WiFi

O gerenciador WiFi realiza todo o ciclo de vida da conexão:

- ✅ Configuração em modo `WIFI_STA`
- ✅ Tentativas automáticas com controle de número máximo
- ✅ Logs detalhados de status em cada etapa
- ✅ Recuperação automática de falhas de rede

> **Reconnect inteligente:** se a conexão cair, o sistema detecta automaticamente, reinicia o processo de conexão e mantém o microcontrolador operacional — sem intervenção externa.

---

## ☁️ Comunicação MQTT

Implementação baseada em `PubSubClient` com suporte a três modos de segurança:

| Modo | Enum | Quando usar |
|------|------|-------------|
| 🔓 **SIMPLES** | `ModoConexao::SIMPLES` | Redes locais confiáveis, testes |
| 🔐 **TLS** | `ModoConexao::TLS` | Ambientes de produção |
| ☁️ **AWS IoT Core** | `ModoConexao::AWS` | Comunicação corporativa com mTLS |

### 📥 Tópicos MQTT

| Direção | Tópico |
|---------|--------|
| 🔽 Recebimento | `senai134/equipe/yoshi/devices/#` |
| 🔼 Status | `senai134/esp32/status` |
| 🔼 Log | `senai134/esp32/log` |
| 🔼 Resposta | `senai134/esp32/resposta` |

### 🔄 Fluxo de Mensagem

```
ESP32 → conecta ao broker
      → assina tópicos
      → recebe JSON
      → processa comando
      → executa ação IR
      → publica status
```

### 🧾 Estrutura do JSON

```json
{
  "tv": {
    "comando": "power"
  }
}
```

O payload passa por conversão com `ArduinoJson`, validação de estrutura, normalização via `tolower()` e busca na tabela de comandos antes de ser executado.

---

## 📺 Controle Infrared (IR)

O sistema suporta envio (`IRsend`) e leitura (`IRrecv`) de sinais infravermelhos com uma tabela de comandos mapeados:

| Comando | Código HEX |
|---------|-----------|
| `power` | `0x20DF10EF` |
| `mute` | `0x20DF906F` |
| `1` | `0x20DF8877` |
| `2` | `0x20DF48B7` |
| `...` | `...` |

**Funcionalidades suportadas:**

- ✅ Ligar/desligar TV
- ✅ Controle de volume
- ✅ Navegação direcional
- ✅ Seleção de entrada HDMI
- ✅ Teclado numérico completo
- ✅ Captura de sinais do controle original

### 📡 Fluxo IR

```
MQTT → JSON recebido
     ↓
Parser identifica comando
     ↓
Busca código na tabela IR
     ↓
ESP32 envia sinal infravermelho
     ↓
TV executa a ação
```

---

## 🔄 Sistema de Reconexão

| Componente | Comportamento |
|------------|--------------|
| 📶 **WiFi** | Detecção automática de queda, reconexão contínua e reinicialização segura |
| ☁️ **MQTT** | Tentativas com backoff entre reconexões e reinscrição automática nos tópicos |

---

## 🧠 Sistema de Debug

Sistema avançado com **quatro níveis configuráveis**:

| Nível | Nome | Descrição |
|:-----:|------|-----------|
| `0` | `NONE` | Sem saída de logs |
| `1` | `ERROR` | Apenas erros críticos |
| `2` | `INFO` | Fluxo geral do sistema |
| `3` | `FULL` | Diagnóstico completo |

**Recursos inclusos:**

- 📝 Logs formatados por categoria
- 🔌 Saída via Serial
- 🎛️ Controle por GPIO
- 🔍 Diagnóstico detalhado de WiFi e MQTT com dicas de solução

---

## ☁️ AWS IoT Core

Suporte completo à integração com AWS IoT via **mTLS** (autenticação mútua com certificados):

- Certificado CA da Amazon
- Certificado individual do dispositivo
- Chave privada RSA
- Endpoint configurável por projeto

```
a2uwr88uek3twk-ats.iot.us-east-1.amazonaws.com
```

---

## 🔧 Tecnologias Utilizadas

| Tecnologia | Função |
|------------|--------|
| 🟢 **Arduino Framework** | Base de desenvolvimento para o ESP32 |
| 📡 **PubSubClient** | Comunicação MQTT (Pub/Sub) |
| 🌐 **WiFi / WiFiClientSecure** | Conectividade e comunicação segura TLS |
| 📦 **ArduinoJson** | Parsing e validação de mensagens JSON |
| 📺 **IRremoteESP8266** | Envio e recepção de sinais infravermelhos |
| ☁️ **AWS IoT Core** | Broker MQTT gerenciado na nuvem com mTLS |
| 🧠 **DebugManager** | Sistema de logs customizado por nível |

---

## ⚡ Características Técnicas

- ✔ Execução não-bloqueante no `loop()`
- ✔ Arquitetura modular e de fácil extensão
- ✔ Compatível com múltiplos brokers MQTT
- ✔ Suporte a TLS e certificados mTLS
- ✔ Controle IR de alta precisão
- ✔ Reconexão automática WiFi e MQTT
- ✔ Sistema de logs por nível de severidade
- ✔ Escalável para múltiplos dispositivos

---

## 📈 Melhorias Futuras

- 📱 App mobile para controle remoto
- 🧠 Integração com Alexa / Google Assistant
- 📊 Dashboard web em tempo real
- 🔋 Monitoramento de consumo de energia
- 📡 Suporte a múltiplos dispositivos IR
- ☁️ Persistência em banco de dados na nuvem

---

## 📄 Licença

Projeto acadêmico desenvolvido para fins educacionais.

---

<div align="center">

*Sistema IoT embarcado real — conectividade em rede, automação IR, segurança TLS/AWS e arquitetura não-bloqueante otimizada para microcontroladores.*

</div>
