/*_______By IvanUA_____________________________
 Кнопка________________________D3/GPIO0        |
 Зуммер________________________D6/GPIO12       |
 DS18B20_______________________D4/GPIO2        |
 Si7021/BMP/BME280/DS3231 SDA__D2/GPIO4        | 
 Si7021/BMP/BME280/DS3231 SCL__D1/GPIO5        |
 GND - FotoRezistor ___________A0              |
 +3,3 - rezistor 2-100k _______A0              |
______________________________________________ |
  Wemos battery shield, measure Vbat           |
   add 100k between Vbat and ADC               |
   Voltage divider of 100k+220k over 100k      |
   gives 100/420k                              |
   ergo 4.2V -> 1Volt                          |
   Max input on A0=1Volt ->1023                |
   4.2*(Raw/1023)=Vbat                         |
______________________________________________*/

#include <Wire.h>
#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <ArduinoJson.h>
#include <WiFiUdp.h>
#include <OneWire.h>
#include <PubSubClient.h>
#include <ArduinoOTA.h>
#include <ESP8266HTTPUpdateServer.h>
#include "Adafruit_Si7021.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_BMP085.h>
#include "BlueDot_BME280.h"
#include <Ticker.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
Ticker blinker;
ESP8266HTTPUpdateServer httpUpdater;
WiFiClient ESPclient;
PubSubClient MQTTclient(ESPclient);
ESP8266WebServer server(80);
File fsUploadFile;
IPAddress apIP(192, 168, 4, 1);
#include "P_js.h"
#include "P_css.h"
#include "P_index.h"
#include "P_thing.h"
#include "P_Setup.h"
#include "P_help.h"
#include "P_mqtt.h"

// ===================================================wifi
String ssid = "Wifi";
String password = "";
String ssidAP      = "Outside_sensor";
String passwordAP  = "12345678";
// ===================================================thingspeak
String writeapikey = "";
bool thingOn = true;
// ===================================================mqtt
char mqtt_server[21] = "m13.cloudmqtt.com";
int  mqtt_port = 13011;
char mqtt_user[25] = "22222222";
char mqtt_pass[25] = "33333333333333";
char mqtt_name[25] = "Informer";
char mqtt_pub_temp[25] = "Informer/temp";
char mqtt_pub_hum[25] = "Informer/hum";
char mqtt_pub_press[25] = "Informer/press";
bool mqttOn = true;
// ===================================================зуммер
#define buzzerPin 12                                                                    //GPIO 12 / D6
bool buzzerOnOff = 0;
bool buzzerSet = 1;
// ===================================================adc
bool akbOnOff = 0;
unsigned int raw = 0;
float uBat = 0.0;
// ===================================================ds18
OneWire  ds(2);                                                                         // DS18B20 подключен к 0 пину (резистор на 4.7к обязателен)
// ===================================================
// ----------
boolean WIFI_connected = false;
String jsonConfig = "{}";
String jsonTime = "{}";
int updateOTA = 1;
float t3 = 0.0; // температура на улице со знаком и плавающей запятой
int t4 = 85;    // температура на улице целая беззнаковая часть
int t5 = 0;     // температура на улице дробная беззнаковая часть
float h0 = 0.0; // влажность на улице со знаком и плавающей запятой
byte h1 = 0;    // влажность на улице целая беззнаковая часть
byte h2 = 0;    // влажность на улице дробная беззнаковая часть
bool pressSys = 1;
int p0;
byte p1;
byte p2;
byte p3;
byte p4;
float tempDs18b20;                    // температура с датчика DS18B20
BlueDot_BME280 bme;
float tempBme = 0;
float humBme = 0;
float pressBme = 0;
float altBme = 0;
Adafruit_BMP280 bmp;
Adafruit_BMP085 bmp180;
float tempBmp = 0;
float pressBmp = 0;
float altBmp = 0;
bool bmp280 = false;
bool BMP180 = false;
bool bme280 = false;
Adafruit_Si7021 sensor = Adafruit_Si7021();
float hum = 0;
float humSi7021 = 0;
float celsiusSi7021 = 0;
bool si7021 = false;
float corrTemp = 0;
float corrHumi  = 0;
int   corrPress = 0;
byte sensorTemp = 0;         //NONE = 0, DS18B20 = 1, Si7021 = 2, BMP280 = 3, BME280 = 4;
byte sensorHumi = 0;         //NONE = 0, NONE    = 1, Si7021 = 2, NONE   = 3, BME280 = 4;
byte sensorPrAl = 0;         //NONE = 0, NONE    = 1, NONE   = 2, BMP280 = 3, BME280 = 4;
//======================================================================================
void setup() {
  Wire.begin(); 
  //pinMode(BUT_PIN, INPUT);
  //digitalWrite(BUT_PIN, !butStat);
  delay(500);
  SPIFFS.begin();
  loadConfig();
  sendToThingSpeak();
  //loadTime();
  //lang();
  pinMode(A0, INPUT);
  raw = analogRead(A0);
  uBat = raw / 1023.0;
  uBat = uBat * 4.2;
  
  // ------------------
  if(bmp.begin()) {
    bmp280 = true;
    sensorsBmp();
  }
  if(bmp180.begin()) {
    BMP180 = true;
    sensorsBmp();
  }
  bme.parameter.communication = 0;                            //Подключение сенсора по I2C 
  bme.parameter.I2CAddress = 0x76;                            //I2C Адрес сенсора или 0x77
  bme.parameter.sensorMode = 0b11;                            //0b00 спящий режим измерения не выполняются, 0b01: выполняется одно измерение, 0b11: датчик постоянно измеряет
  bme.parameter.IIRfilter = 0b100;                            //высокое значение коэффициента означает меньше шума, но измерения также менее чувствительны 0b000-0(off), 0b001-2, 0b010-4, 0b011-8, 0b100-16 (default value)
  bme.parameter.humidOversampling = 0b100;                    //коэффициент избыточной дискретизации для измерений влажности 0b000-0 (фильтр откл), 0b001-1, 0b010-2, 0b011-4, 0b100-8, 0b101-16 (максимум)
  bme.parameter.tempOversampling = 0b101;                     //коэффициент передискретизации для измерения температуры 0b000-0 (фильтр откл), 0b001-1, 0b010-2, 0b011-4, 0b100-8, 0b101-16 (максимум)
  bme.parameter.pressOversampling = 0b101;                    //коэффициент избыточной дискретизации для измерений давления. Для измерений высоты более высокий коэффициент обеспечивает более стабильные значения
  bme.parameter.pressureSeaLevel = 1013.25;                   //текущее давление, скорректированное для уровня моря 1013.25 hPa. Для точных измерений высоты
  bme.parameter.tempOutsideCelsius = 15;                      //средняя температура снаружи 15°C
  bme.parameter.tempOutsideFahrenheit = 59;                   //средняя температура снаружи 59°F
  if(bme.init() == 0x60) {
    bme280 = true;
    sensorsBme();
  }
  if (sensor.begin()) {
    si7021 = true;
    sensorsSi7021();
  }
  sensors();
  serverInit();
// ----------
//  blinker.attach(0.05, showAnimClock);
  //pinMode(buzzerPin, OUTPUT);
// ---------- Підключення до WiFi
  wifiConnect();
// ***********  OTA SETUP
  if(updateOTA) {
    ArduinoOTA.setPort(8266);
    ArduinoOTA.setHostname("Outside_sensor"); 
    ArduinoOTA.onEnd([](){ESP.restart();});
    ArduinoOTA.onError([](ota_error_t error){ESP.restart();});
    ArduinoOTA.begin();
  }
// ---------- MQTT client
  MQTTclient.setServer(mqtt_server, mqtt_port);
  MQTTclient.setCallback(callback);
  MQTTclient.connect(mqtt_name);
}
//==========================================
void callback(char* topic, byte* payload, unsigned int length) { // получаем знаковое число с десятичной плавающей запятой
  if(!mqttOn) return;
  
}

//======================================================================================
void reconnect() {
  if(WiFi.status() == WL_CONNECTED) {  // && !ESPclient.connected()
    if(MQTTclient.connect(mqtt_name, mqtt_user, mqtt_pass)) {
    }
  }
}
//======================================================================================
//======================================================================================
void loop() {
  if(updateOTA) ArduinoOTA.handle();
  server.handleClient();                                                                // дозволяємо HTTP серверу відповідать на запити
  //updateTime();                                                                         // оновлюємо час
  //buttonInter();


  // --------------------------------------------------------------------------------------------------------
//  if(secFr == 0) {
//    if(second == 10 && minute == 1 && hour == 3) {
//      if(rtcStat){
//        getRTCDateTime();
//        hour=hour_rtc;
//        minute=minute_rtc;
//        second=second_rtc;
//        day=day_rtc;
//        month=month_rtc;
//        year=year_rtc;
//        dayOfWeek=dayOfWeek_rtc;
//      }
//    }

    // ---------- 30 перевірка доступності WiFi мережі ---// повторне підк. до WiFi кожну 1, 6, 11, 16...56 хв.
//    if(second>30 && second<38 && !alarm_stat){
//      if(apStart && millis()>1800000) apStart=0;
//      if((WiFi.status() != WL_CONNECTED || !WIFI_connected) && !apStart) {
//        WIFI_connected = false;
//        if(minute % 5 == 1) {
//          wifiConnect();
//          if(WiFi.status() == WL_CONNECTED) WIFI_connected = true;
//        }
//      }
//    }
    // ---------- 50 сек. перевірка доступності MQTT та публікація температури ---------
//    if(second == 50 && mqttOn && !alarm_stat && WIFI_connected) {
//      if(WiFi.status() != WL_CONNECTED) {
//        WIFI_connected = false;
//      }
//      if(!MQTTclient.connected() && WIFI_connected) {
//        reconnect();
//      }
//      if(MQTTclient.connected() && WIFI_connected) {
//        if(sensorTemp  && String(mqtt_pub_temp) != "" && t3 != -85) MQTTclient.publish(mqtt_pub_temp, String(t3).c_str());
//        if(sensorHumi == 2 && String(mqtt_pub_hum) != "" && humSi7021) MQTTclient.publish(mqtt_pub_hum, (String(humSi7021)).c_str());
//        if(sensorHumi == 4 && String(mqtt_pub_hum) != "" && humBme) MQTTclient.publish(mqtt_pub_hum, (String(humBme)).c_str());
//        if(sensorPrAl == 3 && String(mqtt_pub_press) != "" && pressBmp) MQTTclient.publish(mqtt_pub_press, String(pressBmp).c_str());
//        if(sensorPrAl == 4 && String(mqtt_pub_press) != "" && pressBme) MQTTclient.publish(mqtt_pub_press, String(pressBme).c_str());
//      }
//    }
//  }
//  }
  // ---------- якщо мережа WiFi доступна то виконуємо наступні функції ----------------------------
  if(WIFI_connected){
    if(mqttOn) MQTTclient.loop();           // перевіряємо чи намає вхідних повідомлень, як є, то кoлбек функція
  }
}
//======================================================================================
//=========================================================================================================
void wifiConnect(){
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), password.c_str());
  delay (1000);
  for(int i=1; i<21; i++){
    if(WiFi.status()==WL_CONNECTED){
      WIFI_connected=true;
      return;
    }
    delay (1000);
  }
    WiFi.disconnect();
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP(ssidAP.c_str(), passwordAP.c_str());
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void sensors() {
  sensorsDs18b20();
  sensorsSi7021();
  sensorsBmp();
  sensorsBme();
  t3 = (sensorTemp==0?0:sensorTemp==1?tempDs18b20:sensorTemp==2?celsiusSi7021:sensorTemp==3?tempBmp:sensorTemp==4?tempBme:0);
  t3 += corrTemp;
  t4 = int(t3*-1);
  t5 = int(t3*10*(t3>0?1:-1))%10;
  h0 = (sensorHumi==2?humSi7021:sensorHumi==4?humBme:0);
  h0 += corrHumi;
  h1 = int(h0);
  h2 = int(h0*10*(h0>0?1:-1))%10;
  p0 = int(sensorPrAl==3?pressBmp:pressBme);
  p0 += corrPress;
  p1 = p0 / 1000;
  p2 = (p0 - p1*1000) / 100;
  p3 = (p0 - p1*1000 - p2*100) / 10;
  p4 = p0%10;
}
//--------------------------------------------------------------------------
void sensorsDs18b20() {  //1
  byte present = 0;
  byte type_s;
  byte data[12];
  byte addr[8];
  if(!ds.search(addr)) {                                // Стартуємо функцію пошук першого або наступного датчика в addr-возвращаем ответ датчика
    ds.reset_search();                                  // Якщо добігли кінця адресного простору, то скидуємо адрес на початок простору
    delay(250);                                         // Пауза
    return;                                             // Виходимо з підпрограми
  }
  if(OneWire::crc8(addr, 7) != addr[7]) return;           // перевіряємо 7 байт в addr - он содержит crc8 
  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);
  delay(750);
  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);
  for(byte i = 0; i < 9; i++) {
    data[i] = ds.read();
  }
  int16_t raw = (data[1] << 8) | data[0];
  if(type_s) {
    raw = raw << 3;
    if(data[7] == 0x10) {
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    if(cfg == 0x00) raw = raw & ~7;
    else if(cfg == 0x20) raw = raw & ~3;
    else if (cfg == 0x40) raw = raw & ~1;
  }
  tempDs18b20 = (float)raw / 16.00;
}
//--------------------------------------------------------------------------
void sensorsSi7021() {  //2
  if(si7021 == false) return;
  humSi7021 = sensor.readHumidity();
  celsiusSi7021 = sensor.readTemperature();
}
//--------------------------------------------------------------------------
void sensorsBmp() {  //3
  if(bmp280 == true) {
    tempBmp = bmp.readTemperature();
    pressBmp = bmp.readPressure() * (pressSys == 1 ? 0.007500613026439 : 1);
    pressBmp = (int) pressBmp;
    altBmp = bmp.readAltitude(1013.25);
  }
  if(BMP180 == true) {
    tempBmp = bmp180.readTemperature();
    pressBmp = bmp180.readPressure() * (pressSys == 1 ? 0.007500613026439 : 1);
    pressBmp = (int) pressBmp;
    altBmp = bmp180.readAltitude(101500);
  }
}
//--------------------------------------------------------------------------
void sensorsBme() {  //4
  if(bme280 == false) return;
  tempBme = bme.readTempC();          //bme.readTempF()
  humBme = bme.readHumidity();
  pressBme = bme.readPressure() / (pressSys == 1 ? 1.3332239 : 1);
  pressBme = (int) pressBme;
  altBme = bme.readAltitudeFeet();   //bme.readAltitudeMeter()  bme.readAltitudeFeet()
}
//--------------------------------------------------------------------------
void bip(){
  if(buzzerOnOff == 1){
  if(!buzzerSet){
    tone(buzzerPin, 2000, 40);
    delay(250);
    noTone(buzzerPin);
  } else {
    digitalWrite(buzzerPin, HIGH);
    delay(120);
    digitalWrite(buzzerPin, LOW);
    delay(120);
  }
 }
}
//--------------------------------------------------------------------------
void sendToThingSpeak(){ 
    if(thingOn == 1){
  String str="http://api.thingspeak.com/update";
  str+="?api_key=";
  str+=writeapikey;
  if(sensorTemp>0){
    str+="&field1=";
    str+=String(t3);
  }
  if(sensorHumi>0){
    str+="&field2=";
    str+=String(h0);
  }
  if(sensorPrAl>0){
    str+="&field3=";
    str+=String(p0);
  }
  if(akbOnOff == 1){
  str+="&field4=";
  str+=String(uBat);
  } 
  }
 }
//------------ function urlencode for weather parameters --------------------
String urlencode(String str) {    // функция взята от http://forum.amperka.ru/members/benben.19545/
    String encodedString="";
    char c;
    char code0;
    char code1;
    for (int i =0; i < str.length(); i++){
      c=str.charAt(i);
      if (c == ' '){
        encodedString+= '+';
      } else if (isalnum(c)){
        encodedString+=c;
      } else{
        code1=(c & 0xf)+'0';
        if ((c & 0xf) >9){
            code1=(c & 0xf) - 10 + 'A';
        }
        c=(c>>4)&0xf;
        code0=c+'0';
        if (c > 9){
            code0=c - 10 + 'A';
        }
        encodedString+='%';
        encodedString+=code0;
        encodedString+=code1;
      }
      yield();
    }
    return encodedString;
}
//------------ function chr_to_str --------------------
String chr_to_str(String str) {
  String chr_to_str = "";
  for (int i =0; i < str.length(); i++){
    chr_to_str += str.charAt(i);
  }
  return chr_to_str;
}
