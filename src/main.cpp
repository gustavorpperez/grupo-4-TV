#include <Arduino.h>
#include <ArduinoJson.h>

#include "debugManager.h"
#include "mqttManager.h"
#include "WiFiManager.h"



const char TOPICO_COMANDO[] = "senai134/mbolas/televisao";
void tratarJsonComando(const String& mensagem);

#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <IRrecv.h>
#include <IRutils.h>

#define IR_LED_PIN 4
#define RECV_PIN 14

IRsend irsend(IR_LED_PIN);
IRrecv irrecv(RECV_PIN);
decode_results results;


const char TOPICO_COMANDO[] = "senai134/sala09/televisao/publicar";
void tratarJsonComando(const String& mensagem);
void conectarTelevisao();



void setup() {
  Serial.begin(9600);
  irsend.begin();         
  irrecv.enableIRIn();
  conectarWiFi();
  configurarMQTT();
  conectarMQTT();
  debugInfo("Pronto! Aguardando comandos MQTT...");
}


void loop() {
  garantirWifiConectado();
  garantirMQTTConectado();
  loopMQTT();
  receberSinalInfraRed();
}

struct ComandoIR {
  const char* nome;
  uint32_t    codigo;
};
 
const ComandoIR tabelaComandos[] = {
  { "power",           0x20DF10EF },
  { "baixar_volume",   0x20DF40BF },
  { "aumentar_volume", 0x20DFC03F },
  {"botao_ok",         0x20DF22DD },
  { "mute",            0x20DF906F },
  { "hdmi1",           0x20DF738C },
  { "hdmi2",           0x20DFB34C },
  { "botão_cima",       0x20DF02FD },
  { "botão_baixo",      0x20DF827D },
  { "botão_esquerda",   0x20DFE01F },
  { "botão_direita",    0x20DF609F },
  { "1",                0x20DF8877 },
  { "2",                0x20DF48B7 },
  { "3",                0x20DFC837 },
  { "4",                0x20DF28D7 },
  { "5",                0x20DFA857 },
  { "6",                0x20DF6897 },
  { "7",                0x20DFE817 },
  { "8",                0x20DF18E7 },
  { "9",                0x20DF9867 },
  { "0",                0x20DF08F7 },
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

  if (strcmp(topico, TOPICO_COMANDO) == 0)
  {
    tratarJsonComando(mensagem);
    return;
  }

  debugErro("Topico não tratado: " + String(topico));
} 


void conectarTelevisao(uint32_t codigo)
{
  debugInfo("Enviando sinal IR...");

  irrecv.pause();               // Pausa o receptor para não capturar o próprio sinal
  irsend.sendNEC(codigo, 32);   // Envia o código recebido via JSON
  delay(100);
  irrecv.resume();              // Reativa o receptor após o envio

    Serial.println("Sinal enviado!");
    delay(200);  // debounce do botão

  debugInfo("Sinal IR enviado: 0x" + String(codigo, HEX));
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
  //TODO quando realizar uma ação, retornar uma mensagem para o IHM.
}
