// Head partials
// Style
const String styles = "<style>"
  ".main{"
  "padding: 25px;"
  "text-align: center;"
  "}"
  ".status_container{"
  "display:flex;"
  "justify-content:center;"
  "}"
  ".status{"
  "width: 35vmin;"
  "height: 35vmin;"
  "border-radius: 50%;"
  "border: 10px solid #ce0000;"
  "padding: 5px;"
  "background: white;"
  "background-clip: content-box;"
  "transition: background-color 0.5s;"
  "}"
  "</style>";

// Body partials
const String header = "<div class='header'>"
  + String(HOSTNAME) +
  "</div>";

const String nav = "<div class='nav'>"
  "<a href='/'>Status</a>"
  "<a href='/update_form'>Firmware update</a>"
  "</div>";
  
const String footer= "<div class='footer'>"
  "<img src='https://maximemoreillon.com/images/logo/logo.png'>"
  "  <div>"
  "    <div>SONOFF firmware v1.3</div>"
  "    <div>Maxime Moreillon</div>"
  "  </div>"
  "</div>";

// Update form
String update_form = "<h2>Firmware update</h2>"
  "<form method='POST' action='/update' enctype='multipart/form-data'>"
  "<input type='file' name='update'>"
  "<input type='submit' value='Update'>"
  "</form>";

// Combinations
String head ="<head>"
  "<title>" + String(HOSTNAME) +"</title>"
  + styles +
  "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
  "<link rel='icon' href='https://webcomponents.maximemoreillon.com/logo/logo.png'>"
  "<link rel='stylesheet' type='text/css' href='https://webcomponents.maximemoreillon.com/master_css/master.css'>"
  "<link rel='stylesheet' type='text/css' href='https://webcomponents.maximemoreillon.com/modals/modals.css'>"
  "<link rel='stylesheet' type='text/css' href='https://webcomponents.maximemoreillon.com/loader/loader.css'>"
  "<script src='https://webcomponents.maximemoreillon.com/loader/loader.js'></script>"
  "<script src='https://webcomponents.maximemoreillon.com/modals/modals.js'></script>"
  "</head>";

String pre_main = "<html>"
  + head + 
  "<body>"
  "<div class='wrapper'>"
  + header + nav +
  "<div class='main'>";
  
String post_main = "</div>"
  + footer +
  "</div>"
  "</body>"
  "</html>";

// Root
String root_main = ""
  "<div class='status_container'>"
  "  <div class='status' id='status' onclick='toggle()'></div>"
  "</div>"
  "<div id='disconnected_modal' class='modal_wrapper'>"
  "  <div class='modal_container'>"
  "    NO CONNECTION"
  "  </div>"
  "</div>"
  "<div id='loader' class='loader_wrapper'>"
  "  <div id='loader_loading' class='loader_loading'></div>"
  "  <div id='loader_success' class='loader_success'>OK</div>"
  "  <div id='loader_error' class='loader_error'>ERROR</div>"
  "</div>"
  "<script>"
  "websock = new WebSocket('ws://' + window.location.hostname + ':81/');"
  "websock.onopen = function(evt) { close_modal_by_ID('disconnected_modal'); };"
  "websock.onclose = function(evt) { open_modal_by_ID('disconnected_modal'); };"
  "websock.onerror = function(evt) { console.log(evt); };"
  "websock.onmessage = function(evt) {"
  "  var status = document.getElementById('status');"
  "  if(evt.data == 'ON'){"
  "    status.style.backgroundColor = '#ce0000';"
  "  }"
  " else if(evt.data == 'OFF'){"
  "    status.style.backgroundColor = '#ffffff';"
  "  }"
  "};"
  ""
  "function toggle(){"
  "  open_loader();"
  "  var xhttp = new XMLHttpRequest();"
  "  xhttp.open('GET','/toggle',true);"
  "  xhttp.onreadystatechange = function () {"
  "    if(xhttp.readyState === 4){"
  "      if(xhttp.status === 200) close_loader_success();"
  "      else close_loader_error();"
  "    }"
  "  };"
  "  xhttp.send();"
  "}"
  "</script>";

// Not found
String not_found = "<h2>Not found</h2>";
