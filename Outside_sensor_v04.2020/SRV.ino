void serverInit(void) {
  server.on("/", [](){server.send_P(200, "text/html", P_index);});
  server.on("/index.html", [](){server.send_P(200, "text/html", P_index);});
  server.on("/thing.html", [](){server.send_P(200, "text/html", P_thing);}); 
  server.on("/mqtt.html", [](){server.send_P(200, "text/html", P_mqtt);});
  server.on("/setup.html", [](){server.send_P(200, "text/html", P_setup);});
  server.on("/help.html", [](){server.send_P(200, "text/html", P_help);});
  server.on("/style.css", [](){server.send_P ( 200, "text/css", P_css);});
  server.on("/function.js", [](){server.send_P ( 200, "text/plain", P_js);});
  server.on("/favicon.ico", [](){server.send(200, "text/html", "");});
  server.onNotFound([]() {(404, "text/plain", "FileNotFound");});
  server.on("/configs_wifi.json", handle_ConfigWifiJson);
  server.on("/configs_thing.json", handle_ConfigThingJson);
  server.on("/configs_mqtt.json", handle_ConfigMqttJson);
  server.on("/configs_setup.json", handle_ConfigSetupJson);
  server.on("/ssid", handle_Set_Ssid);
  server.on("/thingUst", handle_thing_ust);
  server.on("/thingOn", handle_thing_on);
  server.on("/mqttUst", handle_mqtt_ust);
  server.on("/mqttOn", handle_mqtt_on);
  server.on("/setup", handle_setup);
  server.on("/restart", handle_Restart);            // перезавантаження можуля по запиту типу http://192.168.1.11/restart?device=ok
  server.on("/resetConfig", handle_resetConfig);
  httpUpdater.setup(&server);
  server.begin();
}
//======================================================================================================
void handle_ConfigWifiJson() {
  String json = "{";
  json += "\"ssid\":\"";
  json += ssid;
  json += "\",\"password\":\"";
  json += password;
  json += "\",\"ssidAP\":\"";
  json += ssidAP;
  json += "\",\"passwordAP\":\"";
  json += passwordAP;
  json += "\"}";
  server.send(200, "text/json", json);
}
//======================================================================================================
void handle_ConfigThingJson() {
  String json = "{";
  json += "\"thingOn\":\"";
  json += (thingOn==1?"checked":"");
  json += "\",\"writeapikey\":\"";
  json += writeapikey;
  json += "\"}";
  server.send(200, "text/json", json);
}
//====================================================================================================== 
void handle_ConfigMqttJson() {
  String json = "{";
  json += "\"mqttOn\":\"";
  json += (mqttOn==1?"checked":"");
  json += "\",\"mqtt_server\":\"";
  json += mqtt_server;
  json += "\",\"mqtt_port\":\"";
  json += mqtt_port;
  json += "\",\"mqtt_user\":\"";
  json += mqtt_user;
  json += "\",\"mqtt_pass\":\"";
  json += mqtt_pass;
  json += "\",\"mqtt_name\":\"";
  json += mqtt_name;
  json += "\",\"mqtt_pub_temp\":\"";
  json += mqtt_pub_temp;
  json += "\",\"mqtt_pub_hum\":\"";
  json += mqtt_pub_hum;
  json += "\",\"mqtt_pub_press\":\"";
  json += mqtt_pub_press;
  json += "\"}";
  server.send(200, "text/json", json);
}
//======================================================================================================
void handle_ConfigSetupJson() {
  String json = "{";
  json += "\"buzzerOnOff\":\"";
  json += (buzzerOnOff==1?"checked":"");
  json += "\",\"akbOnOff\":\"";
  json += (akbOnOff==1?"checked":"");
  json += "\",\"buzzerSet\":\"";
  json += (buzzerSet==1?"checked":"");
  json += "\",\"sensorTemp\":\"";
  json += (sensorTemp==0?"NONE":sensorTemp==1?"DS18B20":sensorTemp==2?"SI7021":sensorTemp==3?"BMP280":sensorTemp==4?"BME280":"NONE");
  json += "\",\"corrTemp\":\"";
  json += corrTemp;
  json += "\",\"Tu\":\"";
  json += t3;
  json += "\",\"sensorHumi\":\"";
  json += (sensorHumi==0?"NONE":sensorHumi==2?"SI7021":sensorHumi==4?"BME280":"NONE");
  json += "\",\"corrHumi\":\"";
  json += corrHumi;
  json += "\",\"Hd\":\"";
  json += h0;
  json += "\",\"sensorPrAl\":\"";
  json += (sensorPrAl==0?"NONE":sensorPrAl==3?"BMP280":sensorPrAl==4?"BME280":"NONE");
  json += "\",\"corrPress\":\"";
  json += corrPress;
  json += "\",\"Pu\":\"";
  json += p0;
  json += "\",\"pressSys\":\"";
  json += pressSys;
  json += "\"}";
  server.send(200, "text/json", json);
}
//======================================================================================================
void handle_Set_Ssid() {
  ssid = server.arg("ssid").c_str();
  password = server.arg("password").c_str();
  ssidAP = server.arg("ssidAP").c_str();
  passwordAP = server.arg("passwordAP").c_str();
  saveConfig();
  server.send(200, "text/plain", "OK");
  ESP.reset();
}
//======================================================================================================
void handle_thing_ust() {
  writeapikey = server.arg("writeapikey").c_str();
  saveConfig(); 
  server.send(200, "text/plain", "OK");
}
//======================================================================================================
void handle_thing_on() {
  thingOn = server.arg("thingOn").toInt(); 
  saveConfig(); 
  server.send(200, "text/plain", "OK");
}
//======================================================================================================
void handle_setup(){
  buzzerOnOff = server.arg("buzzerOnOff").toInt();
  akbOnOff = server.arg("akbOnOff").toInt();
  buzzerSet = server.arg("buzzerSet").toInt();
  String sT = server.arg("sensorTemp");
  String sH = server.arg("sensorHumi");
  String sP = server.arg("sensorPrAl");
  if(sT=="NONE") sensorTemp = 0;
  else if(sT=="DS18B20") sensorTemp = 1;
  else if(sT=="SI7021") sensorTemp = 2;
  else if(sT=="BMP280") sensorTemp = 3;
  else if(sT=="BME280") sensorTemp = 4;
  if(sH=="NONE") sensorHumi = 0;
  else if(sH=="SI7021") sensorHumi = 2;
  else if(sH=="BME280") sensorHumi = 4;
  if(sP=="NONE") sensorPrAl = 0;
  else if(sP=="BMP280") sensorPrAl = 3;
  else if(sP=="BME280") sensorPrAl = 4;
  pressSys = server.arg("pressSys").toInt();
  corrTemp = server.arg("corrTemp").toFloat();
  corrHumi = server.arg("corrHumi").toFloat();
  corrPress = server.arg("corrPress").toInt();
  saveConfig();
  sensors();
  server.send(200, "text/plain", "OK");
}
//======================================================================================================
void handle_mqtt_ust() {
  snprintf(mqtt_server, 24, "%s", server.arg("mqtt_server").c_str());
  mqtt_port = server.arg("mqtt_port").toInt();
  snprintf(mqtt_user, 24, "%s", server.arg("mqtt_user").c_str());
  snprintf(mqtt_pass, 24, "%s", server.arg("mqtt_pass").c_str());
  snprintf(mqtt_name, 24, "%s", server.arg("mqtt_name").c_str());
  snprintf(mqtt_pub_temp, 24, "%s", server.arg("mqtt_pub_temp").c_str());
  snprintf(mqtt_pub_hum, 24, "%s", server.arg("mqtt_pub_hum").c_str());
  snprintf(mqtt_pub_press, 24, "%s", server.arg("mqtt_pub_press").c_str());
  saveConfig(); 
  server.send(200, "text/plain", "OK");
  if(mqttOn) reconnect();
}
//======================================================================================================
void handle_mqtt_on() {
  mqttOn = server.arg("mqttOn").toInt(); 
  if(mqttOn) reconnect();
  saveConfig(); 
  server.send(200, "text/plain", "OK");
}
//======================================================================================================
void handle_resetConfig() {
  String restart = server.arg("device");
  if(restart == "ok"){
    //SPIFFS.format();
    SPIFFS.remove("/config.json");
    delay(3000);
    server.send(200, "text/plain", "OK");
    delay(3000);
    bip();
    ESP.reset();
  }
}
//======================================================================================================
void handle_Restart() {
  String restart = server.arg("device");
  if(restart == "ok"){
    server.send(200, "text/plain", "OK"); 
    ESP.reset();
  }
}
//====================================== Тут функції для роботи з файловою системою
String getContentType(String filename){
  if (server.hasArg("download")) return "application/octet-stream";
  else if (filename.endsWith(".htm")) return "text/html";
  else if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".json")) return "application/json";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".png")) return "image/png";
  else if (filename.endsWith(".gif")) return "image/gif";
  else if (filename.endsWith(".jpg")) return "image/jpeg";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  else if (filename.endsWith(".xml")) return "text/xml";
  else if (filename.endsWith(".pdf")) return "application/x-pdf";
  else if (filename.endsWith(".zip")) return "application/x-zip";
  else if (filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}
//======================================= Читання файлу
bool handleFileRead(String path){
  if (path.endsWith("/")) path += "index.htm";
  String contentType = getContentType(path);
  String pathWithGz = path + ".gz";
  if (SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)) {
    if (SPIFFS.exists(pathWithGz))
      path += ".gz";
    File file = SPIFFS.open(path, "r");
    size_t sent = server.streamFile(file, contentType);
    file.close();
    return true;
  }
  return false;
}
//======================================== Завантаження файлу
void handleFileUpload(){
  if (server.uri() != "/edit") return;
  HTTPUpload& upload = server.upload();
  if (upload.status == UPLOAD_FILE_START) {
    String filename = upload.filename;
    if (!filename.startsWith("/")) filename = "/" + filename;
    fsUploadFile = SPIFFS.open(filename, "w");
    filename = String();
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    if (fsUploadFile)
      fsUploadFile.write(upload.buf, upload.currentSize);
  } else if (upload.status == UPLOAD_FILE_END) {
    if (fsUploadFile)
      fsUploadFile.close();
  }
}
//======================================== Видалення файлу
void handleFileDelete(){
  if (server.args() == 0) return server.send(500, "text/plain", "BAD ARGS");
  String path = server.arg(0);
  if (path == "/")
    return server.send(500, "text/plain", "BAD PATH");
  if (!SPIFFS.exists(path))
    return server.send(404, "text/plain", "FileNotFound");
  SPIFFS.remove(path);
  server.send(200, "text/plain", "");
  path = String();
}
//========================================= Створення файлу
void handleFileCreate(){
  if (server.args() == 0)
    return server.send(500, "text/plain", "BAD ARGS");
  String path = server.arg(0);
  if (path == "/")
    return server.send(500, "text/plain", "BAD PATH");
  if (SPIFFS.exists(path))
    return server.send(500, "text/plain", "FILE EXISTS");
  File file = SPIFFS.open(path, "w");
  if (file)
    file.close();
  else
    return server.send(500, "text/plain", "CREATE FAILED");
  server.send(200, "text/plain", "");
  path = String();
}
//========================================== Список файлів 
void handleFileList(){
  if (!server.hasArg("dir")){
    server.send(500, "text/plain", "BAD ARGS");
    return;
  }
  String path = server.arg("dir");
  Dir dir = SPIFFS.openDir(path);
  path = String();
  String output = "[";
  while (dir.next()) {
    File entry = dir.openFile("r");
    if (output != "[") output += ',';
    bool isDir = false;
    output += "{\"type\":\"";
    output += (isDir) ? "dir" : "file";
    output += "\",\"name\":\"";
    output += String(entry.name()).substring(1);
    output += "\"}";
    entry.close();
  }
  output += "]";
  server.send(200, "text/json", output);
}
