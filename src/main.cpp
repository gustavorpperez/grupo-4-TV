#include <Arduino.h>
#include <ArduinoJson.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <IRrecv.h>
#include <IRutils.h>

#include "debugManager.h"
#include "mqttManager.h"
#include "WiFiManager.h"

#define IR_LED_PIN 4
#define RECV_PIN 14

IRsend irsend(IR_LED_PIN);
IRrecv irrecv(RECV_PIN);
decode_results results;

void tratarJsonComando(const String &mensagem);
void conectarTelevisao(uint32_t codigo);
void receberSinalInfraRed();
void tratarMensagemRecebida(const char *topico, const String &mensagem);
<<<<<<< HEAD
void retornarIHM();
=======
>>>>>>> eaadc3d7d421a569f67a6e8330c1d236eab018cd

bool MQTTrecebido = false;

void setup()
{
  Serial.begin(9600);
  irsend.begin();
  irrecv.enableIRIn();
  conectarWiFi();
  configurarMQTT();
  registrarCallbackMensagem(tratarMensagemRecebida);
  conectarMQTT();
  debugInfo("Pronto! Aguardando comandos MQTT...");
}

void loop()
{
  garantirWifiConectado();
  garantirMQTTConectado();
  loopMQTT();
  receberSinalInfraRed();
<<<<<<< HEAD
  retornarIHM(); // ✅ estava faltando
} 

struct ComandoIR
{
  const char *nome;
  uint32_t codigo;
};

const ComandoIR tabelaComandos[] = {
  { "1",                 0x20DF10EF }, //*LIGAR
  { "2",                 0x20DFC03F }, //*abaixar volume
  { "3",                 0x20DF40BF }, //*aumentar volume
  { "4",                 0x20DF22DD }, //*botao OK
  { "5",                 0x20DF906F }, //*mute
  { "6",                 0x20DF738C }, //*hmdi1
  { "7",                 0x20DF33CC }, //*hdm2
  { "8",                 0x20DF9768 }, //*hdmi3
  { "9",                 0x20DF5BA4 }, //*hdmi4
  { "10",                0x20DF02FD }, //*botao cimaa
  { "11",                0x20DF827D }, //*botao baixo
  { "12",                0x20DFE01F }, //*botao esquerdo
  { "13",                0x20DF609F }, //*botao direito
  { "14",                0x20DF8877 }, //*1
  { "15",                0x20DF48B7 }, //*2 
  { "16",                0x20DFC837 }, //*3 
  { "17",                0x20DF28D7 }, //*4 
  { "18",                0x20DFA857 }, //*5 
  { "19",                0x20DF6897 }, //*6 
  { "20",                0x20DFE817 }, //*7 
  { "21",                0x20DF18E7 }, //*8 
  { "22",                0x20DF9867 }, //*9 
  { "23",                0x20DF08F7 }, //*0
};

const int totalComandos = sizeof(tabelaComandos) / sizeof(tabelaComandos[0]);
=======
}
>>>>>>> eaadc3d7d421a569f67a6e8330c1d236eab018cd

struct ComandoIR
{
  const char *nome;
  uint32_t codigo;
};

const ComandoIR tabelaComandos[] = {
    {"power", 0x20DF10EF},
    {"baixar_volume", 0x20DF40BF},
    {"aumentar_volume", 0x20DFC03F},
    {"botao_ok", 0x20DF22DD},
    {"mute", 0x20DF906F},
    {"hdmi1", 0x20DF738C},
    {"hdmi2", 0x20DFB34C},
    {"botão_cima", 0x20DF02FD},
    {"botão_baixo", 0x20DF827D},
    {"botão_esquerda", 0x20DFE01F},
    {"botão_direita", 0x20DF609F},
    {"1", 0x20DF8877},
    {"2", 0x20DF48B7},
    {"3", 0x20DFC837},
    {"4", 0x20DF28D7},
    {"5", 0x20DFA857},
    {"6", 0x20DF6897},
    {"7", 0x20DFE817},
    {"8", 0x20DF18E7},
    {"9", 0x20DF9867},
    {"0", 0x20DF08F7},
};

void tratarMensagemRecebida(const char *topico, const String &mensagem)
{
  debugInfo("==============================");
  debugInfo("Mensagem recebida na aplicação");
  debugInfo("==============================");

  if (topico == nullptr)
  {
    debugErro("Topico MQTT invalido");
    return;
  }
  debugInfo("Topico: " + String(topico));
  debugInfo("Mensagem: " + mensagem);

<<<<<<< HEAD
if (strncmp(topico, "senai134/equipe/yoshi/devices/", 30) == 0)
=======
  if (strcmp(topico, "senai134/equipe/yoshi/devices/#") == 0)
>>>>>>> eaadc3d7d421a569f67a6e8330c1d236eab018cd
  {
    tratarJsonComando(mensagem);
    return;
  }

  debugErro("Topico não tratado: " + String(topico));
}

void tratarJsonComando(const String &mensagem)
{
  JsonDocument doc;

  DeserializationError erro = deserializeJson(doc, mensagem);
  if (erro)
  {
    debugErro("Erro ao interpretar JSON");
    debugErro(erro.c_str());
    return;
  }

<<<<<<< HEAD
  if (!doc["tv"]["comando"].is<const char *>())
  {
    debugErro("JSON inválido. Use tv.comando (ex: power, mute...)");
    return;
  }
=======
    if (!doc["tv"]["comando"].is<const char *>())
    {
      debugErro("JSON inválido. Use tv.comando (ex: power, volume_up, mute...)");
      return;
    }
>>>>>>> eaadc3d7d421a569f67a6e8330c1d236eab018cd

  String comando = doc["tv"]["comando"].as<String>();
  comando.toLowerCase();
  debugInfo("Comando recebido: " + comando);

<<<<<<< HEAD
  for (int i = 0; i < totalComandos; i++)
  {
    if (comando == tabelaComandos[i].nome)
    {
      conectarTelevisao(tabelaComandos[i].codigo);
      MQTTrecebido = true;
      return;
    }
  }

  debugErro("Comando desconhecido: " + comando);
=======
  MQTTrecebido = true;
>>>>>>> eaadc3d7d421a569f67a6e8330c1d236eab018cd
}

void conectarTelevisao(uint32_t codigo)
{
  debugInfo("Enviando sinal IR...");

  irrecv.pause();             // Pausa o receptor para não capturar o próprio sinal
  irsend.sendNEC(codigo, 32); // Envia o código recebido via JSON
  delay(100);
  irrecv.resume(); // Reativa o receptor após o envio

  Serial.println("Sinal enviado!");
<<<<<<< HEAD
=======
  delay(200); // debounce do botão
>>>>>>> eaadc3d7d421a569f67a6e8330c1d236eab018cd

  debugInfo("Sinal IR enviado: 0x" + String(codigo, HEX));
 // publicarMensagem(TOPICO_STATUS, "{\"tv\":{\"status\":\"comando_enviado\"}}");
}

void receberSinalInfraRed() //* Se apontar o controle e dar o sinal, ira aparecer dentro do terminal
{
  if (irrecv.decode(&results))
  {
    Serial.print("Sinal recebido: 0x");
    Serial.println(results.value, HEX);
    irrecv.resume();
  }
}

void retornarIHM()
{
  if (MQTTrecebido)
  {
    String mensagem = "MQTT recebido";
    
    publicarMensagemNoTopico(0, mensagem.c_str());

    MQTTrecebido = false;
  }
}
