/*
 * Board type: Generic ESP8266
 */


// Libraries
#include <ESP8266WiFi.h> // Main ESP8266 library
#include <ArduinoOTA.h> // OTA update library
#include <WiFiUdp.h> // Required for OTA
#include <AsyncMqttClient.h> // MQTT library
#include <Ticker.h> // Used when reconecting MQTT upon wifi drop

#include "credentials.h";
//#include "soldering_iron_config.h";
//#include "living_room_light_config.h";
//#include "bedroom_light_config.h";
//#include "bedroom_fan_config.h";
#include "toilet_light_config.h";

// Wifi
Ticker wifi_reconnect_timer;
WiFiEventHandler wifi_connect_handler;
WiFiEventHandler wifi_disconnect_handler;

// MQTT
AsyncMqttClient MQTT_client;
Ticker MQTT_reconnect_timer;
#define MQTT_BROKER_ADDRESS IPAddress(192, 168, 1, 2)
#define MQTT_PORT 1883
#define MQTT_LAST_WILL "OFF"
#define MQTT_QOS 1
#define MQTT_RETAIN true

// Pin mapping
#define RELAY_PIN 12
#define LED_PIN 13
#define BUTTON_PIN 0

// Other variables
char* relay_state = RELAY_INITIAL_STATE;

void setup()
{
  // Mandatory initial delay
  delay(10);

  // Serial init
  Serial.begin(115200);
  Serial.println(); // Separate serial stream from initial gibberish
  Serial.println(F(__FILE__ " " __DATE__ " " __TIME__));

  IO_setup();
  wifi_setup();
  MQTT_setup();
  OTA_setup();

  wifi_connect();
}


void loop() {
  ArduinoOTA.handle();
  read_button();
}
