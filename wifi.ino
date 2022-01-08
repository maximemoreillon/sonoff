void wifi_setup() {

  Serial.println(F("[WiFi] Wifi starting"));

  WiFi.hostname(HOSTNAME);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}


void wifi_connection_manager(){

  static int wifi_connected = -1; // 1: connected, 0: disconnected, -1: unknown
  
  if(WiFi.status() != WL_CONNECTED) {
    // Wifi currently disconnected
    if(wifi_connected != 0){
      // Wifi connection status changed to "disconnected"
      wifi_connected = 0;
      Serial.println(F("[WiFi] Disconnected"));
    }

    // LED management: Blink LED if disconnected
    if( (millis()/500)%2 == 0) digitalWrite(LED_PIN, LOW); // LED is active LOW
    else digitalWrite(LED_PIN, HIGH); // LED is active LOW
    
  }
  else {
    if(wifi_connected != 1){
      // Wifi connection status changed to "connected"
      wifi_connected = 1;
      Serial.print(F("[WiFi] Connected, IP: "));
      Serial.println(WiFi.localIP());

      // Set LED the right state if connected
      set_LED();
    }
  }
  
}
