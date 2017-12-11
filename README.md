# Sonoff

Custom firmware for an Itead SONOFF which enables control over MQTT and OTA updates.
Additionally, the built-in button and LED have been set to toggle and display the state of the relay, respectively.


## Requirements
* Arduino IDE with [support for ESP8266](https://github.com/esp8266/Arduino)
* [Async MQTT client](https://github.com/marvinroger/async-mqtt-client)
* [ESPAsyncTCP](https://github.com/me-no-dev/ESPAsyncTCP)

## Arduino flashing settings

* Type of board: Generic ESP8266
* Flash Mode: DIO
* Flash Frequency: 40MHz
* CPU Frequency: 80MHz
* Flash Size: **1M (64K SPIFFS)**
* Debug Port: Disabled
* Debug Level: None
* Reset Method: ck
* Upload Speed: 115200

In other words, only the flash size needs to be changed

Note: Newer SONOFFs require the flash mode to be changed to DOUT.


