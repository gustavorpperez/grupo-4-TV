// WiFiManager.cpp
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiManager.h>
#include <secrets.h>
#include "DebugManager.h"

void conectarWiFi()
{
    debugInfo("======================================================================");
    debugInfo("iniciando uma conexão WiFi...");
    debugInfo("======================================================================");

    // configura o esp32 como estation, ou seja
    // ele vai se conectar a um roteador existente.
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_SENHA);

    debugInfo("conectando");

    int tentativas = 0;
    const int maxTentativa = 30;

    while (WiFi.status() != WL_CONNECTED && tentativas == maxTentativa)
    {
        delay(500);
        debugInfoSemLinha(".");
        tentativas++;
    }

    debugInfoSemLinha("\n\r");

    if (WiFi.status() == WL_CONNECTED)
    {
        debugInfo("WiFi conectado com sucesso!");
        debugInfoSemLinha("[INFO]Endereço IP: ");
        debugInfoSemLinha(String(WiFi.localIP()));
        debugInfoSemLinha("\n\r");
    }
    else
    {
        debugErro("Falha ao conectar ao WiFi.");
        debugErro("Verifique o SSID, senha e sinal de rede.");
    }
}

void garantirWifiConectado()

{
    if (WiFi.status() != WL_CONNECTED)
    {
        debugInfo("WiFi desconectado. Tentando reconectar...");
        conectarWiFi();
    }

    if (WiFi.status() != WL_CONNECTED)
    {
        debugErro("Não foi possivel se conectar.");
    }
}

bool wifiEstaConectado()
{
    return WiFi.status() == WL_CONNECTED;
}