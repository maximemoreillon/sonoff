void IO_setup(){

  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);

  // Initial state
  if(strcmp(relay_state,"ON") == 0) {
    digitalWrite(LED_PIN, LOW); // LED is active LOW
    digitalWrite(RELAY_PIN, HIGH);
  }
  else {
    digitalWrite(LED_PIN, HIGH); // LED is active LOW
    digitalWrite(RELAY_PIN, LOW);
  }
}

void read_button()
{
  const long button_debounce_delay = 50;
  static int last_button_reading;
  static long last_button_reading_change_time;
  static int button_state = LOW; // Output
  
  int button_reading = digitalRead(BUTTON_PIN);

  // Check if reading changed
  if(button_reading != last_button_reading)
  {
    // Acknowledge button reading change
    last_button_reading = button_reading;
    
    // Record time of last button reading change
    last_button_reading_change_time = millis();
  }

  // Only acknowledge the button reading if state did not change for long enough
  if(millis()-last_button_reading_change_time > button_debounce_delay)
  {
    
    if(button_reading != button_state)
    {
      // Save reading as button state if state and reading don't match (prevents saving all the time)
      button_state = button_reading;


      // APPLICATION DEPENDENT FROM HERE
      if(button_state == LOW)
      {
        Serial.println("Button pressed");

        if(strcmp(relay_state,"OFF") == 0){
          Serial.println("Relay ON");
          digitalWrite(RELAY_PIN, HIGH);
          digitalWrite(LED_PIN, LOW); // LED is active LOW
          relay_state = "ON";
        }
        else if(strcmp(relay_state,"ON") == 0){
          Serial.println("Relay OFF");
          digitalWrite(RELAY_PIN, LOW);
          digitalWrite(LED_PIN, HIGH); // LED is active LOW
          relay_state = "OFF";
        }
        MQTT_client.publish(MQTT_STATUS_TOPIC, MQTT_QOS, MQTT_RETAIN, relay_state);
      }
    }
  }
}
