void websocket_setup(){
  Serial.println(F("[WS] WS setup"));
  ws_server.begin();
  ws_server.onEvent(webSocketEvent);
}

void ws_update_state(){
  Serial.println(F("[WS] update of relay state"));
  ws_server.broadcastTXT(relay_state);
}
