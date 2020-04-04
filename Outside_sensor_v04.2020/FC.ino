bool loadConfig() {                                                // Завантаження даних збереженних в файлі config.json
  File configFile = SPIFFS.open("/config.json", "r");              // Відкриваемо файл на читання
  if(!configFile) {                                                // якщо файл не знайдено ствоюємого його та записуємо в ньго данні з наших змінних
    saveConfig();                                                  // Створюємо файл
    configFile.close();
    return false;                                                  // Повернення з помилкою
  }
  size_t size = configFile.size();                                 // Перевіряємо ромір файлу, будемо використовувати файл довжиною в 1024 байта
  if(size > 4496) {
    configFile.close();
    return false;                                                  // Повернення з помилкою
  }
  jsonConfig = configFile.readString();                            // завантажуємо файл конфігурації в глобальну змінну
  DynamicJsonDocument doc(4496);                                   // Резервуємо память для json обекту буфер може розти по мірі необхідності переважно для ESP8266 
  deserializeJson(doc, jsonConfig);
  configFile.close();
  ssidAP = doc["ssidAP"].as<String>();
  passwordAP = doc["passwordAP"].as<String>();                     // Так отримуємо рядок
  ssid = doc["ssid"].as<String>();
  password = doc["password"].as<String>();
  writeapikey = doc["writeapikey"].as<String>();
  thingOn = doc["thingOn"];
  updateOTA = doc["updateOTA"];
  buzzerOnOff = doc["buzzerOnOff"];
  akbOnOff = doc["akbOnOff"];
  buzzerSet = doc["buzzerSet"];
  mqttOn = doc["mqttOn"];
  snprintf(mqtt_server, 24, "%s", (doc["mqtt_server"].as<String>()).c_str());
  mqtt_port = doc["mqtt_port"];
  snprintf(mqtt_user, 24, "%s", (doc["mqtt_user"].as<String>()).c_str());
  snprintf(mqtt_pass, 24, "%s", (doc["mqtt_pass"].as<String>()).c_str());
  snprintf(mqtt_name, 24, "%s", (doc["mqtt_name"].as<String>()).c_str());
  snprintf(mqtt_pub_temp, 24, "%s", (doc["mqtt_pub_temp"].as<String>()).c_str());
  snprintf(mqtt_pub_hum, 24, "%s", (doc["mqtt_pub_hum"].as<String>()).c_str());
  snprintf(mqtt_pub_press, 24, "%s", (doc["mqtt_pub_press"].as<String>()).c_str());
  sensorTemp = doc["sensorTemp"];
  sensorHumi = doc["sensorHumi"];
  sensorPrAl = doc["sensorPrAl"];
  pressSys = doc["pressSys"];
  corrTemp = doc["corrTemp"];
  corrHumi  = doc["corrHumi"];
  corrPress = doc["corrPress"];
  return true;
}
//=================================================================
bool saveConfig() {
  DynamicJsonDocument doc(4496);
  deserializeJson(doc, jsonConfig);
  doc["ssidAP"] = ssidAP;
  doc["passwordAP"] = passwordAP;
  doc["ssid"] = ssid;
  doc["password"] = password;
  doc["writeapikey"] = writeapikey;
  doc["thingOn"] = thingOn;
  doc["buzzerOnOff"] = buzzerOnOff;
  doc["akbOnOff"] = akbOnOff;
  doc["buzzerSet"] = buzzerSet;
  doc["mqttOn"] = mqttOn;
  doc["mqtt_server"] = mqtt_server;
  doc["mqtt_port"] = mqtt_port;
  doc["mqtt_user"] = mqtt_user;
  doc["mqtt_pass"] = mqtt_pass;
  doc["mqtt_name"] = mqtt_name;
  doc["mqtt_pub_temp"] = mqtt_pub_temp;
  doc["mqtt_pub_hum"] = mqtt_pub_hum;
  doc["mqtt_pub_press"] = mqtt_pub_press;
  doc["sensorTemp"] = sensorTemp;
  doc["sensorHumi"] = sensorHumi;
  doc["sensorPrAl"] = sensorPrAl;
  doc["pressSys"] = pressSys;
  doc["corrTemp"] = corrTemp;
  doc["corrHumi"] = corrHumi;
  doc["corrPress"] = corrPress;
  jsonConfig = "";
  if(serializeJson(doc, jsonConfig)==0){
    Serial.println(F("Failed to write to jsonConfig"));
  }  
  File configFile = SPIFFS.open("/config.json", "w");                // Відкриваємо файл для запису
  if(!configFile) {
    configFile.close();
    return false;
  }
  if(serializeJson(doc, configFile)==0){
    Serial.println(F("Failed to write to file"));
  } 
  configFile.close();
  bip();
  return true;
}
