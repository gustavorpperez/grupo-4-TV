//* !SECRETS.H
#include <Arduino.h>
#include "secrets.h"
// configurações do WiFi

const char *WIFI_SSID = "SALA 09";
const char *WIFI_SENHA = "info@134";

//===============================
// MQTT
//===============================



 const char *MQTT_BROKER = "fd20b80b37b543ea9620c3c95585a523.s1.eu.hivemq.cloud";
 const int MQTT_porta = 8883;

const char *MQTT_CLIENT_ID = "esp32_Luiz_Uchoa";
 const char *MQTT_USUARIO = "ucheio";
 const char *MQTT_SENHA = "Senai@134";

 const bool MQTT_TLS = true;

//certificado CA https://letsencrypt.org/certs/isrgrootx1.pem
 const char MQTT_CERTIFICADO_CA[] PROGMEM = "";

 //===============================
// AWS
//===============================
 const bool USAR_AWS_IOT = true;

extern const char* AWS_IOT_ENDPOINT = "a2uwr88uek3twk-ats.iot.us-east-1.amazonaws.com"; //endereço do broker IOT core

extern const char AWS_CERT_CA[] PROGMEM;

extern const char AWS_CERT_CRT[] PROGMEM;

extern const char AWS_CERT_PRIVATE[] PROGMEM;

extern const int AWS_IOT_PORT = 8883;

extern const char* AWS_IOT_CLIENT_ID = " esp32Ucheio1212";


const char *TOPICOS_PUBLICAR[] =
    {
        "senai134/esp32/status",
        "senai134/esp32/log",
        "senai134/esp32/resposta"};

const int TOTAL_TOPICOS_PUBLICAR = 3;
 
const char *TOPICOS_RECEBER[] =
    {
        "senai134/ucheio/esp32/comando",
        "senai134/ucheio/esp32/config",
        "senai134/ucheio/esp32/display"};

const int TOTAL_TOPICOS_RECEBER = 3;

//===============================
// DEBUG
//===============================

// 0 - sem mensagens
// 1 - apenas erros
// 2 - todas as mensagens
const int DEBUG_NIVEL_INICIAL = 2;

// pino usado para forçar todas as mensagens
const int PINO_HABILITA_DEBUG_COMPLETO = 4;





