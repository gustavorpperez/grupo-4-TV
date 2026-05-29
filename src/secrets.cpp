#include "secrets.h"
#include <Arduino.h>

//Configurações do WiFi

const char* WIFI_SSID = "SALA 09";
const char* WIFI_SENHA = "info@134";

// ===================================
// MQTT 
// ===================================

const char *MQTT_BROKER = "b750b6be1c664ede873e0c265a3493bb.s1.eu.hivemq.cloud";
const int MQTT_PORTA = 8883;

const char* MQTT_CLIENT_ID = "esp32_grupo4_TV";

const char* MQTT_USUARIO = "grupo4";
const char* MQTT_SENHA = "Senai@134";

const bool MQTT_TLS = true;

const char MQTT_CERTIFICADO_CA[] PROGMEM = "";

//=============================================
//AWS
//=============================================

const bool USAR_AWS_IOT = true;

const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

const char AWS_CERT_CRT[] PROGMEM = R"CRT(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUSBGUc5CLVKVN79hntialiOibXC8wDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTI2MDUyNzEyNDI0
NloXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAKU/sdxT/1WpjVUf6IK9
0cFn0vFem5kd+zJNl2+lOvyIsHbbdy/2VCKKsISakmVQka3BCF0716Ymb5AoVv66
GtGBcnjm/Z5QgKtXMKXAZOdc1MyjeRzY5OrsQ0juAZnl4/pQOx2AEWXTLVfEkNE2
hsxJXiGAEYiJj0pJ6XsC8LR68JOQ5lVIKnrTQF7jo0YGYjy6CyWOqkS/ZVJwRCrG
O5MOtU7/VhpwZf1HClJsYDFUiVE2Akn9jld8uz7ylL7oq9i3YjgZjfhDm2DDSzst
wP7XxggJ17JPH4vAesITdI4vWybpX/jkPL3LqrYpAkq7x6NHLue718S6eLYHSc4X
rI8CAwEAAaNgMF4wHwYDVR0jBBgwFoAUikZ0FHTQ2ZATYhPHXtUajXgQpdMwHQYD
VR0OBBYEFE3fgMOM+zCNW78yZJK1iyADOKccMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQAAx8Ukw06QLgQavzRzNnNJCZrX
4QGY7WX/w8ztZ6nyVvRCGaZ7TbpBOmDd0GfgeU53GGynMmXMozzOm18csr5sIIq+
dGEsJHUo/6wsEjDl85wnS+/Y+H5ur8w5jn4zUJp4p6BJ6hLm0cHRfYVbak+r+Tqo
dnfxHaCi9cfNKYrNpvidUzgbnaKk93WOKpO/n+Oa0yFo2UCNAAu+QsFAcK7x6zc5
md9QjdGbkjCcGrul2M2vD+WKHhZNrqf+wd21igMU1TRUer9U1PdRLfhxdUogtzOc
pZXb36bJTPau8UXDdJPWtzflsl/+ZmSA00wuE2Vmu/F33QC92fLsruYsF9y1
-----END CERTIFICATE-----
)CRT";

const char AWS_CERT_PRIVATE[] PROGMEM = R"PV(
-----BEGIN RSA PRIVATE KEY-----
MIIEowIBAAKCAQEApT+x3FP/VamNVR/ogr3RwWfS8V6bmR37Mk2Xb6U6/Iiwdtt3
L/ZUIoqwhJqSZVCRrcEIXTvXpiZvkChW/roa0YFyeOb9nlCAq1cwpcBk51zUzKN5
HNjk6uxDSO4BmeXj+lA7HYARZdMtV8SQ0TaGzEleIYARiImPSknpewLwtHrwk5Dm
VUgqetNAXuOjRgZiPLoLJY6qRL9lUnBEKsY7kw61Tv9WGnBl/UcKUmxgMVSJUTYC
Sf2OV3y7PvKUvuir2LdiOBmN+EObYMNLOy3A/tfGCAnXsk8fi8B6whN0ji9bJulf
+OQ8vcuqtikCSrvHo0cu57vXxLp4tgdJzhesjwIDAQABAoIBAE2QBQK+pmVlzQG8
lVzwjciy288RMgV/jg1BYCg2LOalnfZb8qiffUQtRscm6joFxCsDJNLmKMVC2zCV
zqeHYNkfYkSfX0F01cAWj63tDS+PYg6fWFSS9XfS544OsM+0mPo/uE+TchcSNQEy
MSsR5dlzQmyE+TXWI1yiLqXfbm23WW+yTN05ev6FCEOCty5U9FMypbK+pUQv2hW+
cEhgYMQoynfGcZnwbTDzjuFyOZXUTiaZj/YUIbyRIz9vDPyLf7RpKeTywkssWh6c
kAMUZF9YwqEGF8NcNglFzb7U7OQyHogeM32S+ywYSDR48Pv3f6dJRunSdckzXYa2
BhDcPIkCgYEA1+DTPOoQiRJHim/s0mS3iiGF9o1+m1SKMzkkuqsDgH8EzE6lIBJO
nRvDBxndAQS50kNPfg7yp4ZTP/C4qYR0LzDTitkRGRg2zVnAl3cL+rri+KlIoaZS
EmrW9D1MdmRvhHue2ZInhBWXqVMoQPQSPxSxzIi8QGp9AwaqWddsl2MCgYEAw/X+
tkOTX3aLI2QkKHI4xscy+XXUnvSxRx/GEsaV7Ddv08ZlquoMARxuSN6e8UD6YzVq
sZs9CUgpn+sqD7/n/TF/xbXlHky1PGODxlYEZs2pvGclVmzCcV/DU4gK2KMcwAn7
zu5vfB7bkAgffmUyeHJp0vYvZ9ogYDRn6GyxC+UCgYAri+qQixayz8Emp9U5y59K
eeCwD3LOmosWMhy6muyl6vlozSR6B7db8dGxiQIPxohFZdaPMyy3plz8tO5LI7Dc
JBlIFOliCoRjgAtdgmIkPbazOlKwaQB9PpgFxKe76h6kttsgQF9AQarKOUAReiqE
FwSWoa53wANfrOSIIvCAyQKBgQCt6Xzz30dEut1DPJXGe5CeAZ3gvU1FAV7wA2fz
s+DMcmrBpVsHc43R0pyh+UlQTV2qfHbDR0XFHhErBzceIS/PioWePw8nc+aIwLzr
Yd2oKzBPr674Y6+xlM6yLJOLrj9Ow82B2iSBIJW13y+sKj2/nbMDck+iOHjxSLFL
GmOKbQKBgCG2B2vsvk6M8VusDawFtx7XIk37twx84AP8VlFU8LQf4XkZf4axOwtA
FioujVLHXuiMKds+ZWHGkHO8rLJYrXZzbK6vYEX35z6Es7RKG2tJrHxHAtwgsLxl
DhbPE3hJNA/NawFYbM8dHDhAJDeidEO1pLCsc4PuUyONJn1RN9lf
-----END RSA PRIVATE KEY-----
)PV";


const char* AWS_IOT_ENDPOINT = "a2uwr88uek3twk-ats.iot.us-east-1.amazonaws.com";  //Endereço do broker IoT Core

const int AWS_IOT_PORT = 8883;

const char* AWS_IOT_CLIENT_ID = "grupo_YOSHI";

//=============================================
//TÓPICOS
//=============================================

const char* TOPICOS_PUBLICAR[] = {
        "senai134/modulo/televisao"
        "dispositivo/modulo/ihm/comando"
};

const int TOTAL_TOPICOS_PUBLICAR = 4;

const char* TOPICOS_RECEBER[] = {
    "senai134/modulo/televisao",
    "senai134/modulo/ihm/confirmacao"
};

const int TOTAL_TOPICOS_RECEBER = 4;

// ===================================
// DEBUG
// ===================================

// 0 = sem mensagens
// 1 = apenas erros
// 2 = todas as mensagens
const int DEBUG_NIVEL_INICIAL = 2; 

// Pino usado para forçar todas as mensagens
const int PINO_HABILITA_DEBUG_COMPLETO = 4;

