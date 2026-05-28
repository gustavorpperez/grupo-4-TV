#include <Arduino.h>
#include <ArduinoJson.h>

#include "debugManager.h"
#include "mqttManager.h"
#include "WiFiManager.h"


const char TOPICO_COMANDO[] = "senai134/mbolas/televisao";
void tratarJsonComando(const String& mensagem);

void setup() {

  Serial.begin(9600);
  conectarWiFi();
  configurarMQTT();
  conectarMQTT();
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