#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <Arduino.h>
#include <PubSubClient.h>

#include "SECRETS.h"
#include "WiFiManager.h"
#include "MqttManager.h"
#include "DebugManager.h"

// *criação de objetos
WiFiClient WiFiCliente;
WiFiClientSecure wifiClientSecure;

PubSubClient mqttClient;

CallbackMensagemMQTT callbackDaAplicacao = nullptr;

void registrarCallbackMensagem(CallbackMensagemMQTT callback)
{
    callbackDaAplicacao = callback;

    if (callbackDaAplicacao != nullptr)
    {
        debugInfo("Callback da aplicação registrado com sucesso.");
    }
    else
    {
        debugErro("callback da aplicação não foi registrado.");
    }
}

const char *obterTopicoPublicacao(int indiceTopico)
{
    if (indiceTopico < 0 || indiceTopico >= TOTAL_TOPICOS_PUBLICAR)
    {
        debugErro("Indice invalido para topico de publicação: " + String(indiceTopico));
        return "";
    }
    return TOPICOS_PUBLICAR[indiceTopico];
}

const char *obterTopicoRecebimnto(int indiceTopico)
{
    if (indiceTopico < 0 || indiceTopico >= TOTAL_TOPICOS_RECEBER)
    {
        debugErro("Indice invalido para topico de publicação: " + String(indiceTopico));
        return "";
    }
    return TOPICOS_RECEBER[indiceTopico];
}

void callbackInternoMQTT(char *topico, byte *payload, unsigned int tamanho)
{
    String mensagem = "";

    for (unsigned int i = 0; i < tamanho; i++)
    {
        mensagem += (char)payload[i];
    }
    debugInfo("==================================");
    debugInfo("mensagem MQTT recebida.");
    debugInfo("==================================");
    debugInfo("topico: " + String(topico));
    debugInfo("Mensagem: " + mensagem);

    if (callbackDaAplicacao != nullptr)
    {
        callbackDaAplicacao(topico, mensagem);
    }
    else
    {
        debugErro("mensagem foi recebida, mas nenhum callback da aplicação registrado. ");
    }
}

void configurarMQTT()
{
    debugInfo("=================================");
    debugInfo("Configuração MQTT...");
    debugInfo("=================================");

   
    if (MQTT_TLS)
    {
        debugInfo("Modo selecionado: MQTT com TLS");

        if(strlen(MQTT_CERTIFICADO_CA) > 100)
        {
          debugInfo("Certificado CA do broker MQTT configurado");
          wifiClientSecure.setCACert(MQTT_CERTIFICADO_CA);
        }
        else
        {
            debugErro("Certificado não configurado, Usando set insecure apenas para teste");
            wifiClientSecure.setInsecure();
        }
        mqttClient.setClient(wifiClientSecure);
        mqttClient.setServer(MQTT_BROKER, MQTT_porta);

        
        debugInfo("Broker MQTT: " + String(MQTT_BROKER));
        debugInfo("Porta MQTT: " + String(MQTT_porta));
    }
    else
    {
        debugInfo("Modo selecionado: MQTT sem TLS");

        mqttClient.setClient(WiFiCliente);
        mqttClient.setServer(MQTT_BROKER, MQTT_porta);

        debugInfo("Broker MQTT: " + String(MQTT_BROKER));
        debugInfo("Porta MQTT: " + String(MQTT_porta));
    }

    mqttClient.setCallback(callbackInternoMQTT);
    debugInfo("Callback interno no MQTT configurado.");
}

void conectarMQTT()
{
    if (!wifiEstaConectado)
    {
        debugErro("MQTT não pode se conectar porqie o WiFi está desconectado.");
        return;
    }

    debugInfo("==================================");
    debugInfo(" Iniciando conexão MQTT");
    debugInfo("==================================");

    int tentativasMQTT = 0;
    const int maxTentativasMQTT = 5;

    while (!mqttClient.connected() && tentativasMQTT < maxTentativasMQTT)
    {
        debugInfo("tentando conectar ao broker MQTT. Tentativa: " + String(tentativasMQTT));

        bool conectado = false;

        /*if (USAR_AWS_IOT)
        {
            conectado = mqttClient.connect(AWS_IOT_CLIENT_ID);
        }

        else
        {
            if (strlen(MQTT_USUARIO) > 0)
            {
                debugInfo("conectando MQTT com usuario e senha.");
                conectado = mqttClient.connect(MQTT_CLIENT_ID, MQTT_USUARIO, MQTT_SENHA);
            }
            else // conexão em modo anonimo
            {
                debugInfo("Conectando MQTT sem usuario e senha");
                conectado = mqttClient.connect(MQTT_CLIENT_ID);
            }
        }
*/
        if (conectado)
        {
            debugInfo("MQTT conectado com sucesso!");

            int totalTopicos = obterTotalTopicosRecebimento();

            debugInfo("Total de topicos para a inscrição: " + String(totalTopicos));

            for (int i = 0; i < totalTopicos; i++)
            {
                const char *topico = obterTopicoRecebimnto(i);

                bool inscrito = mqttClient.subscribe(topico);

                if (inscrito)
                {
                    debugInfo("inscrito no topico: " + String(topico));
                }
                else
                {
                    debugErro("falha ao se inscrever no topico: " + String(topico));
                }
            }
           publicarMensagemNoTopico(0, "ESP32 conectado ao MQTT");
        }
        else
        {
            debugErro("falha ao conectar no MQTT, codigo de erro: " + String(mqttClient.state()));
            tentativasMQTT++;
            delay(2000);
        }
    } // FIM DO WHILE
    if (!mqttClient.connected())
    {
        debugErro("não foi possivel conectar ao broker MQTT após " + String(maxTentativasMQTT) + "tentativas.");
    }
}

int obterTotalTopicosRecebimento()
{
    return TOTAL_TOPICOS_RECEBER;
}

void garantirMQTTConectado()
{
    if (!wifiEstaConectado)
    {
        debugErro("MQTT não reconectado porque o WiFi está conectado.");
        return;
    }
    if (!mqttClient.connected())
    {
        debugErro("MQTT conectado. tentando reconectar...");
        conectarMQTT();
    }
}

void loopMQTT()
{
    mqttClient.loop();
}

void publicarMensagem(const char *topico, const char *mensagem)
{
    if (!mqttClient.connected())
    {
        debugErro("Não foi possivel publicar. MQTT desconectado");
        return;
    }

    bool publicado = mqttClient.publish(topico, mensagem);

    if (publicado)
    {
        debugInfo("Mensagem publicada via MQTT.");
        debugInfo("topico: " + String(topico));
        debugInfo("Mensagem: " + String(mensagem));
    }
    else
    {
        debugErro("Falha ao publicar mensagem no topico: " + String(topico));
    }
}

void publicarMensagemNoTopico(int indiceTopico, const char* mensagem)
{
    const char* topico = obterTopicoPublicacao(indiceTopico);

    if (strlen(topico) == 0)
    {
        debugErro("Não foi possivel publicar. indice de topico invalido: " + String(indiceTopico));
        return;
    }

    publicarMensagem(topico, mensagem);
    
}

bool mqttMensagem()
{
    return mqttClient.connected();
}

