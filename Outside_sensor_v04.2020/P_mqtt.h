const char P_mqtt[] PROGMEM =  R"=====(
<html>
    <head>
        <meta http-equiv = "Content-type" content = "text/html; charset=utf-8">
        <title>Уличный датчик вер.04.2020 (By IvanUA & MAX)</title>
        <link rel="shortcut icon" href="#" />
        <link rel = "stylesheet" type = "text/css" href = "/style.css">
        <script type = "text/javascript" src = "/function.js"></script>
        <script type = "text/javascript">
            function set_mqtt_ust(submit) {
                server = "/mqttUst?mqttOn=" + val('mqttOn') + "&mqtt_server=" + val('mqtt_server') + "&mqtt_port=" + (val('mqtt_port')) + "&mqtt_user=" + (val('mqtt_user')) + "&mqtt_pass=" + (val('mqtt_pass'));
                server += "&mqtt_name=" + val('mqtt_name')+ "&mqtt_pub_temp=" + val('mqtt_pub_temp') + "&mqtt_pub_hum=" + val('mqtt_pub_hum') + "&mqtt_pub_press=" + val('mqtt_pub_press');
                send_request(submit,server);
            }
            function set_mqtt_on(submit) {
                server = "/mqttOn?mqttOn=" + val_sw("mqttOn");
                send_request(submit, server);
            }
        </script>
    </head>
    <body onload = "load_mqtt();">
        <header>
            <span class="opt_cn">Уличный датчик вер.04.2020 (By IvanUA & MAX)</span><br>
        </header>       
        <central-unit>
            <div class="menu_unit">
                <a class="link__img" href="/index.html"><span class="ico__text">Wifi</span></a>
                <a class="link__img" href="/thing.html"><span class="ico__text">thingspeak</span></a>                  
                <a class="link__img" href="/mqtt.html"><span class="ico__text">Mqtt</span></a>
                <a class="link__img" href="/setup.html"><span class="ico__text">Настройки</span></a>
                <a class="link__img" href="/help.html"><span class="ico__text">Помощь</span></a>
            </div>
            <titles>
                <span class="opt_cn">Настройки MQTT</span>
            </titles>
            <div class="informer">
                <span class="opt_cn">Настройки MQTT-сервера. Вы можете использовать любой сервер, например, </span>
                <a href="https://www.cloudmqtt.com" align="center" target="_blank"> cloudmqtt.com</a>
            </div>        
            <br>    
            <div id="main_unit">
                <hr>
                <label class="switch">
                    <span class="opt_cn">Использовать MQTT-сервер</span>
                    <input type="checkbox" class="checkbox" id="mqttOn" name="switch-btn" onclick="set_mqtt_on(this);">
                    <span class="switch-btn"></span>
                 </label>
                 <hr>
                 <br>
                <paragraph><span class="opt_cn">Параметры MQTT-сервера</span></paragraph>
                <center>
                <table>
                    <tr>
                        <td align = "right"><span class="opt_cn">Адрес сервера</span></td>
                        <td><input type="text" class="field form-control" id="mqtt_server" value="{{mqtt_server}}" pattern="[- 0-9a-zA-Z._/]{1,20}"></td>
                    </tr>
                    <tr>
                        <td align = "right"><span class="opt_cn">Порт сервера</span></td>
                        <td><input type="text" class="field form-control" id="mqtt_port" value="{{mqtt_port}}" pattern="[\d]{4,5}"><br>
                    </tr>
                    <tr>
                        <td align = "right"><span class="opt_cn">Имя пользователя</span></td>
                        <td><input class="field form-control" id="mqtt_user" value="{{mqtt_user}}" pattern="[-\w\s#@/]{0,20}" onfocus="this.type='text'" type="password"></td>
                    </tr>
                    <tr>
                        <td align = "right"><span class="opt_cn">Пароль пользователя</span></td>
                        <td><input class="field form-control" id="mqtt_pass" value="{{mqtt_pass}}" pattern="[-\w\s#@/]{0,20}" onfocus="this.type='text'" type="password"></td>
                    </tr>
                    <tr>
                        <td align = "right"><span class="opt_cn">Имя устройства (ESP)</span></td>
                        <td><input type="text" class="field form-control" id="mqtt_name" value="{{mqtt_name}}" pattern="[-\w\s#@/]{1,24}"></td>
                    </tr>
                </table>
                </center> 
                <paragraph><span class="opt_cn">Топики исходящих сообщений</span></paragraph>
                <center>
                <table>                    
                    <tr>
                        <td align = "right"><span class="opt_cn">Публикация температуры</span></td>
                        <td><input type="text" class="field form-control" id="mqtt_pub_temp" value="{{mqtt_pub_temp}}" pattern="[-\w\s#@/]{1,24}"></td>
                    </tr>
                    <tr>
                        <td align = "right"><span class="opt_cn">Публикация влажности</span></td>
                        <td><input type="text" class="field form-control" id="mqtt_pub_hum" value="{{mqtt_pub_hum}}" pattern="[-\w\s#@/]{1,24}"></td>
                    </tr>
                    <tr>
                        <td align = "right"><span class="opt_cn">Публикация давления</span></td>
                        <td><input type="text" class="field form-control" id="mqtt_pub_press" value="{{mqtt_pub_press}}" pattern="[-\w\s#@/]{1,24}"></td>
                    </tr>
                </table>
                </center>
                <br>        
                <span class="save_booton" onclick="set_mqtt_ust(this);">Сохранить настройки</span>
                <br>
            </div>
            <div>
                <a href="http://forum.amperka.ru/threads/%D0%A7%D0%B0%D1%81%D1%8B-%D0%BD%D0%B0-esp-01-nodemcu-max7219-web-%D0%B8%D0%BD%D1%82%D0%B5%D1%80%D1%84%D0%B5%D0%B9%D1%81.12767/">Форум</a>
                <a href="https://github.com/IZ76/ESP8266_Clock_Weather-station_Informer_with_WEB_interface">GitHub</a>
                <a href="https://www.youtube.com/channel/UCGkErLs3cwCeTj5mcsObgVA">YouTube</a>
                <a href="https://github.com/max50a5/ESP8266_Clock_Weather-station_Informer_with_WEB_interface" class = "right">Мой Форк</a>
            </div>
        </central-unit>
    </body>           
</html>
)=====";
