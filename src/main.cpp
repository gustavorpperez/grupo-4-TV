#include <Arduino.h>
#include <ArduinoJson.h>

#include "debugManager.h"
#include "mqttManager.h"
#include "WiFiManager.h"

#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <IRrecv.h>
#include <IRutils.h>

#define IR_LED_PIN 4
#define RECV_PIN 14

IRsend irsend(IR_LED_PIN);
IRrecv irrecv(RECV_PIN);
decode_results results;


const char TOPICO_COMANDO[] = "senai134/mbolas/televisao";
void tratarJsonComando(const String& mensagem);
void conectarTelevisao();

void setup() {

  Serial.begin(9600);
  conectarWiFi();
  configurarMQTT();
  conectarMQTT();
  irrecv.enableIRIn();
  Serial.println("Pronto! Pressione o botão BOOT para ligar/desligar a TV.");
}

void loop() {
   garantirWifiConectado();
   void garantirMQTTConectado();
   loopMQTT();
}

void tratarMensagemRecebida(const char *topico, const String &mensagem)
{
  debugInfo("=============================");
  debugInfo("Mensagem recebida na aplicação");
  debugInfo("=============================");

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

void conectarTelevisao()
{
  //!PRECISA DA CONFIRMAÇÃO PARA SER ENVIADO (COM UM IF)
  Serial.println("Botão pressionado! Enviando sinal IR...");

    irrecv.pause();                      //Pausa o receptor para não capturar o próprio sinal
    irsend.sendNEC(0x20DF40BF, 32);   //! SUBSTITUIR PELO JSON  
    delay(100);
    irrecv.resume();                     //Reativa o receptor após o envio

    Serial.println("Sinal enviado!");
    delay(200);  // debounce do botão
  
}

void receberSinalInfraRed() //* Se apontar o controle e dar o sinal, ira apareecer no terminal
{
    if (irrecv.decode(&results)) {
    Serial.print("Sinal recebido: 0x");
    Serial.println(results.value, HEX);
    irrecv.resume();
  }
}