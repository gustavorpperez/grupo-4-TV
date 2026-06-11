# 📺 ESP32 TV IR Control
**WiFi + MQTT + Infrared + AWS IoT Core — Arquitetura Não-Bloqueante**

Sistema embarcado desenvolvido para o ESP32, com foco em conectividade IoT robusta, comunicação MQTT segura via AWS IoT Core e controle de dispositivos via infravermelho (IR). Desenvolvido como projeto acadêmico no SENAI.

## 👨‍💻 Equipe

| Nome |
|---|
| Narcizo Silvério de Almeida |
| Giovanna Mafra Zau |
| Gustavo Ayres Lima |
| Gustavo Rodrigues Padovan Perez |
| Luiz Antônio Uchoa Lacerda |
| Pedro Stain Furtado |

> Depende de: `PubSubClient`, `ArduinoJson`, `IRremoteESP8266` — instalados via PlatformIO.

---


---

## Por que não-bloqueante?

A abordagem tradicional usa `while()` para aguardar conexão, travando o microcontrolador:

```cpp
// ❌ Bloqueante — trava o setup() por até 15 segundos
while (WiFi.status() != WL_CONNECTED) { delay(500); }
```

Este projeto usa verificação contínua de estado processada no `loop()`:

```cpp
// ✅ Não-bloqueante — setup() retorna imediatamente
void loop() {
  garantirWifiConectado();  // avança sem travar
  garantirMQTTConectado();
  loopMQTT();
  // sua lógica continua normalmente
}
```

**Resultado:** sem travamento do ESP32, execução paralela de tarefas e maior estabilidade em produção.

---

## Funcionalidades

- ✅ WiFi e MQTT não-bloqueantes com reconexão automática
- ✅ Três modos de conexão: SIMPLES, TLS e AWS IoT Core
- ✅ Recebimento de comandos estruturados em JSON via MQTT
- ✅ Controle de TV via infravermelho com tabela de comandos mapeados
- ✅ Captura de sinais IR de controles originais via Serial
- ✅ Publicação de status de volta ao broker após cada comando executado
- ✅ Sistema de logs com níveis configuráveis por GPIO
- ✅ Arquitetura modular e escalável para múltiplos dispositivos

---

## Estrutura do Projeto

```
├── include/
│   ├── WiFiManager.h       → Interface de conexão WiFi
│   ├── mqttManager.h       → Interface de comunicação MQTT
│   ├── debugManager.h      → Interface do sistema de logs
│   └── secrets.h           → Credenciais e configurações
├── src/
│   ├── main.cpp            → Fluxo principal (setup e loop)
│   ├── WiFiManager.cpp     → Conexão e reconexão WiFi
│   ├── mqttManager.cpp     → Comunicação MQTT (Pub/Sub)
│   ├── debugManager.cpp    → Sistema de logs e diagnóstico
│   └── secrets.cpp         → Credenciais WiFi, MQTT e AWS
├── platformio.ini          → Configuração do ambiente PlatformIO
└── README.md
```

---

## Instalação

1. Clone o repositório e abra no VS Code com PlatformIO instalado.
2. Configure as credenciais no arquivo `src/secrets.cpp`:

```cpp
const char *WIFI_SSID = "SUA_REDE";
const char *WIFI_SENHA = "SUA_SENHA";
const char *AWS_IOT_ENDPOINT = "seu-endpoint.iot.us-east-1.amazonaws.com";
```

3. Adicione os certificados AWS em `src/secrets.cpp` (`AWS_CERT_CA`, `AWS_CERT_CRT`, `AWS_CERT_PRIVATE`).
4. Compile e grave com **PlatformIO: Upload**.

---

## Modos de Conexão

| Modo | Quando usar |
|---|---|
| `SIMPLES` | Broker local sem criptografia (ex: Mosquitto em rede interna) |
| `TLS` | Broker com certificado CA (ex: HiveMQ Cloud) |
| `AWS IoT Core` | Conexão segura com mTLS — certificado por dispositivo |

Configurado em `secrets.cpp` pela flag:

```cpp
const bool USAR_AWS_IOT = true;  // false para SIMPLES ou TLS
const bool MQTT_TLS     = false;
```

---

## Tópicos MQTT

| Direção | Tópico |
|---|---|
| 🔽 Recebimento | `senai134/equipe/yoshi/devices/#` |
| 🔽 Recebimento | `senai134/shared/projeto/televisao` |
| 🔼 Publicação | `senai134/equipe/yoshi/devices/televisao` |

---

## Formato da Mensagem JSON

```json
{
  "tv": {
    "comando": 1
  }
}
```

O campo `comando` é um número inteiro que mapeia para um botão da TV:

| Número | Ação | Número | Ação |
|---|---|---|---|
| `1` | Power (liga/desliga) | `13` | Botão direito |
| `2` | Abaixar volume | `14` | Tecla 1 |
| `3` | Aumentar volume | `15` | Tecla 2 |
| `4` | OK (confirmar) | `16` | Tecla 3 |
| `5` | Mudo (mute) | `17` | Tecla 4 |
| `6` | HDMI 1 | `18` | Tecla 5 |
| `7` | HDMI 2 | `19` | Tecla 6 |
| `8` | HDMI 3 | `20` | Tecla 7 |
| `9` | HDMI 4 | `21` | Tecla 8 |
| `10` | Botão cima | `22` | Tecla 9 |
| `11` | Botão baixo | `23` | Tecla 0 |
| `12` | Botão esquerdo | | |

---

## Fluxo Completo

```
Broker MQTT → JSON recebido
                   │
                   ▼
      tratarMensagemRecebida()   → valida o tópico
                   │
                   ▼
      tratarJsonComando()        → faz o parse do JSON
                   │
                   ▼
      tabela de comandos IR      → acha o código hex
                   │
                   ▼
      conectarTelevisao()        → envia sinal IR para a TV
                   │
                   ▼
      retornarIHM()              → publica status de volta ao broker
```

---

## Sistema de Debug

Níveis configuráveis em `secrets.cpp`:

| Nível | Constante | Descrição |
|---|---|---|
| `0` | `NONE` | Sem logs |
| `1` | `DEBUG_ERRO` | Apenas erros |
| `2` | `DEBUG_TUDO` | Todas as mensagens |

O pino `PINO_HABILITA_DEBUG_COMPLETO` força o nível máximo quando conectado ao GND — útil para diagnóstico em campo sem recompilar.

---

## Tecnologias

| Tecnologia | Uso |
|---|---|
| Arduino Framework (ESP32) | Base do sistema embarcado |
| PubSubClient | Comunicação MQTT |
| ArduinoJson | Parse de mensagens JSON |
| IRremoteESP8266 | Envio e recepção de sinais IR |
| WiFiClientSecure | Conexão TLS e AWS IoT Core |
| AWS IoT Core | Broker MQTT seguro na nuvem |

---

## Licença

Projeto acadêmico desenvolvido para fins educacionais — SENAI.
