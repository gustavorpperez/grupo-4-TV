#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H

#include <Arduino.h>

void configurarMQTT();
void conectarMQTT();
void garantirMQTTconectado();
void loopMQTT();
void publicarMensagemNoTopico(int indiceTopico, const char* mensagem);

void publicarMensagem(const char *topico, const char *mensagem);

bool mqttEstaConectado();

const char *obterTopicoPublicacao();
const char *obterTopicoRecebimnto();
int obterTotalTopicosRecebimento();

typedef void (*CallbackMensagemMQTT)(const char *topico, const String &mensagem);

void registrarCallbackMensagem(CallbackMensagemMQTT callback);

#endif