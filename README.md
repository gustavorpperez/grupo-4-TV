📡 ESP32 IoT Smart Control System
WiFi + MQTT + Infrared + AWS IoT Core (Non-blocking Architecture)

Sistema embarcado desenvolvido para o ESP32, com foco em conectividade IoT robusta, comunicação MQTT segura e controle de dispositivos via infravermelho (IR).

Este projeto implementa uma arquitetura não-bloqueante baseada em máquina de estados, permitindo que o microcontrolador mantenha múltiplas operações simultâneas sem travamentos no loop().

👨‍💻 Membros da equipe
Narcizo Silvério de Almeida
Giovanna Mafra Zau
Gustavo Ayres Lima
Gustavo Rodrigues Padovan Perez
Luiz Antônio Uchoa Lacerda
Pedro Stain Furtado
🚀 Visão Geral do Projeto

O sistema foi projetado para atuar como um gateway IoT inteligente, capaz de:

📶 Conectar-se automaticamente a redes WiFi
☁️ Comunicar-se com brokers MQTT (HiveMQ / Mosquitto / AWS IoT Core)
📡 Receber comandos remotos estruturados em JSON
📺 Controlar dispositivos via infravermelho (TVs e eletrônicos)
🔄 Garantir reconexão automática em caso de falhas
🧠 Registrar logs inteligentes com níveis de debug

⚙️ Arquitetura do Sistema

O projeto é dividido em módulos independentes:

src/
├── main.cpp           → Fluxo principal (setup e loop)
├── WiFiManager.cpp    → Conexão e reconexão WiFi
├── mqttManager.cpp    → Comunicação MQTT (Pub/Sub)
├── debugManager.cpp   → Sistema de logs e diagnóstico
├── secrets.cpp        → Configurações (WiFi, MQTT, AWS)
🧠 Arquitetura Não-Bloqueante

Diferente de abordagens tradicionais que travam o microcontrolador com while(), este projeto utiliza execução contínua baseada em estado.

❌ Modelo bloqueante (ruim)
while (WiFi.status() != WL_CONNECTED) {
  delay(500);
}
✅ Modelo usado no projeto
void loop() {
  garantirWifiConectado();
  garantirMQTTConectado();
  loopMQTT();
}

📌 Resultado:

Sem travamento do ESP32
Execução paralela de tarefas
Maior estabilidade em produção
🌐 Conectividade WiFi

O sistema realiza:

Configuração em modo WIFI_STA
Tentativas automáticas de conexão
Controle de número máximo de tentativas
Logs detalhados de status
Recuperação automática de falhas
🔄 Reconnect inteligente

Se a conexão cair:

O sistema detecta automaticamente
Reinicia o processo de conexão
Mantém o sistema operacional
☁️ Comunicação MQTT

Implementação baseada em PubSubClient, com suporte a:

MQTT padrão (sem TLS)
MQTT com TLS
AWS IoT Core (mTLS)
📡 Fluxo MQTT
ESP32 → conecta ao broker
ESP32 → assina tópicos
ESP32 → recebe JSON
ESP32 → processa comando
ESP32 → executa ação IR
ESP32 → publica status
📥 Tópicos MQTT
🔽 Recebimento
senai134/equipe/yoshi/devices/#
🔼 Publicação
senai134/esp32/status
senai134/esp32/log
senai134/esp32/resposta
🔐 Modos MQTT suportados
Modo	Descrição
🔓 SIMPLES	MQTT sem criptografia
🔐 TLS	MQTT com certificado CA
☁️ AWS IoT Core	Comunicação segura com mTLS
📺 Controle Infrared (IR)

O sistema utiliza:

📡 IRsend (envio de comandos)
📥 IRrecv (leitura de sinais)
🧠 Tabela de comandos mapeados
📊 Exemplo de tabela IR
{ "power", 0x20DF10EF },
{ "mute",  0x20DF906F },
{ "1",      0x20DF8877 },
{ "2",      0x20DF48B7 },
📺 Funcionalidades IR
Ligar/desligar TV
Controle de volume
Navegação direcional
Entrada HDMI
Teclado numérico
Captura de sinais do controle original
📡 Fluxo IR
MQTT → JSON recebido
     ↓
Parser identifica comando
     ↓
Busca código na tabela
     ↓
ESP32 envia sinal IR
     ↓
TV executa ação
📄 Estrutura de Mensagem MQTT
🧾 Exemplo JSON
{
  "tv": {
    "comando": 1
  }
}
🔎 Processamento
Conversão com ArduinoJson
Validação de estrutura
Normalização (tolower)
Busca em tabela de comandos
Execução via IRsend
🔄 Sistema de Reconexão

O sistema possui recuperação automática para:

📶 WiFi
Reconexão contínua
Detecção de queda
Reinitialização segura
☁️ MQTT
Tentativas limitadas
Backoff entre tentativas
Reinscrição automática em tópicos
🧠 Sistema de Debug

Sistema avançado com níveis configuráveis:

Nível	Nome	Descrição
0	NONE	Sem logs
1	ERROR	Apenas erros
2	INFO	Fluxo geral
3	FULL	Diagnóstico completo
📌 Recursos do debug
Logs formatados
Separação por tipo
Saída via Serial
Controle por GPIO
Diagnóstico de MQTT e WiFi
☁️ AWS IoT Core (Opcional)

O sistema suporta integração completa com AWS IoT:

Certificado CA
Certificado do dispositivo
Chave privada RSA
Conexão segura mTLS

📡 Endpoint configurável:

a2uwr88uek3twk-ats.iot.us-east-1.amazonaws.com
🔧 Tecnologias Utilizadas
🟢 Arduino Framework (ESP32)
📡 PubSubClient (MQTT)
🌐 WiFi / WiFiClientSecure
📦 ArduinoJson
📺 IRremoteESP8266
☁️ AWS IoT Core
🧠 DebugManager customizado
⚡ Características Técnicas

✔ Execução não-bloqueante
✔ Arquitetura modular
✔ Compatível com múltiplos brokers MQTT
✔ Suporte a TLS e certificados
✔ Controle IR de alta precisão
✔ Reconexão automática WiFi/MQTT
✔ Sistema de logs avançado
✔ Escalável para múltiplos dispositivos

📦 Exemplo de Uso
void loop() {
  garantirWifiConectado();
  garantirMQTTConectado();
  loopMQTT();
  receberSinalInfraRed();
}
📈 Possíveis melhorias futuras
📱 App mobile para controle remoto
🧠 Integração com Alexa / Google Assistant
📊 Dashboard web em tempo real
🔋 Monitoramento de energia
📡 Suporte a múltiplos dispositivos IR
☁️ Banco de dados na nuvem
📄 Licença

Projeto acadêmico desenvolvido para fins educacionais.

🏁 Conclusão

Este projeto demonstra um sistema completo de IoT embarcado real, integrando:

comunicação em rede
automação IR
segurança com TLS/AWS
arquitetura escalável
execução otimizada para microcontroladores 
