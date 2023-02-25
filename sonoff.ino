/*
 * CUSTOM SONOFF FIRMWARE
 * Maxime MOREILLON
 * 
 * Board type: Generic ESP8266
 * Flash mode: DOUT
 * Flash size: 1M (64 SPIFFS)
 */

// Libraries
#include <ESP8266WiFi.h> // Main ESP8266 library
#include <ArduinoOTA.h> // OTA update library
#include <WiFiUdp.h> // Required for OTA
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>

#include "credentials.h";
//#include "sonoff_kitchen_light_nagoya.h";
#include "sonoff_living_light_nagoya.h";
//#include "sonoff_bedroom_light_nagoya.h";
//#include "sonoff_test.h";

// MQTT
#define MQTT_BROKER_ADDRESS IPAddress(192, 168, 1, 2)
#define MQTT_PORT 1883
#define MQTT_LAST_WILL "{'state':'disconnected'}"
#define MQTT_QOS 1
#define MQTT_RETAIN true

// Pin mapping
#define RELAY_PIN 12
#define LED_PIN 13
#define BUTTON_PIN 0

// Web server
#define WWW_PORT 80
#define WS_PORT 81


// Global variables
WiFiClient wifi_client;
PubSubClient MQTT_client(wifi_client);

// Web server
ESP8266WebServer web_server(WWW_PORT);
WebSocketsServer ws_server = WebSocketsServer(WS_PORT);
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght);

// Global variables
char* relay_state = INITIAL_STATE;

void setup() {
  // Mandatory initial delay
  delay(10);

  // Serial init
  Serial.begin(115200);
  Serial.println(); // Separate serial stream from initial gibberish

  IO_setup();
  wifi_setup();
  MQTT_setup();
  OTA_setup();
  web_server_setup();
  websocket_setup();
}


void loop() {
  ArduinoOTA.handle();
  MQTT_client.loop();
  web_server.handleClient();
  ws_server.loop();
  read_button();
  wifi_connection_manager();
  MQTT_connection_manager();

  
}

// I wish I could put this in the "websockets" tab
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght){
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.println(F("[WS] A client disconnected"));
      break;
    case WStype_CONNECTED:
      Serial.println(F("[WS] A client connected"));
      ws_update_state();
      break;
    case WStype_TEXT:
      Serial.println(F("[WS] Message from client"));
      break;
  }
}
