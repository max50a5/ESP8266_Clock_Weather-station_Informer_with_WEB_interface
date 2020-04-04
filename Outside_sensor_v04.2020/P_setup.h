const char P_setup[] PROGMEM =  R"=====(
<html>
    <head>
        <!--meta name = "viewport" content = "width=device-width, initial-scale=1.0"-->
        <meta http-equiv = "Content-type" content = "text/html; charset=utf-8">
        <title>Уличный датчик вер.04.2020 (By IvanUA & MAX)</title>
        <link rel="shortcut icon" href="#" />
        <link rel = "stylesheet" type = "text/css" href = "/style.css">
        <script type = "text/javascript" src = "/function.js"></script>
        <script type = "text/javascript">
            function set_setup(submit) {
                server = "/setup?sensorTemp=" + val('sensorTemp') + "&sensorHumi=" + val('sensorHumi') + "&sensorPrAl=" + val('sensorPrAl') + "&pressSys=" + val('pressSys') + "&akbOnOff=" + val_sw('akbOnOff');
                server += "&corrTemp=" + val('corrTemp') + "&corrHumi=" + val('corrHumi') + "&corrPress=" + val('corrPress') + "&buzzerOnOff=" + val_sw('buzzerOnOff') + "&buzzerSet=" + val_sw('buzzerSet');
                send_request(submit,server);
            }
        </script>
    </head>
    <body onload = "load_setup();">
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
            <div class="informer">
                <span class="opt_cn">Здесь можно настроить параметры и используемые датчики.</a>
            </div> 
            <div id="main_unit">
                <center>
                    <paragraph><span class="opt_cn">Настройки параметров</span></paragraph>
                     <label class="switch"><span class="opt_cn">Использовать АКБ (Да/Нет)</span>
                        <input type="checkbox" id="akbOnOff">
                        <span class="switch-btn"></span>
                    </label>   
                    <br>                 
                    <label class="switch"><span class="opt_cn">Зуммер (Вкл./Выкл.)</span>
                        <input type="checkbox" id="buzzerOnOff">
                        <span class="switch-btn"></span>
                    </label>   
                    <br>                    
                    <label class="switch"><span class="opt_cn">Активный зуммер (Да/Нет)</span>
                        <input type="checkbox" id="buzzerSet">
                        <span class="switch-btn"></span>
                    </label>
                </center>                        
                <center>
                    <paragraph><span class="opt_cn">Настройки датчиков</span></paragraph>             
                    <table id="table__font" class = "table">
                        <tr>
                            <td></td>
                            <td><span class="opt_cn"><b> Датчик </b></span></td>
                            <td><span class="opt_cn"><b> Коррекция </b></span></td>
                            <td><span class="opt_cn"><b> Данные </b></span></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">T</span></td>
                            <td><select id = "sensorTemp">
                              <option value = "NONE"> НЕТ </option>
                              <option value = "DS18B20"> DS18B20 </option>
                              <option value = "SI7021"> SI7021 </option>
                              <option value = "BMP280"> BMP180/280 </option>
                              <option value = "BME280"> BME280 </option>
                            </select></td>
                            <td><input type="text" class="field form-control" id="corrTemp" value="{{corrTemp}}" pattern="\- \d+(\.\d{2})?"></td>
                            <td><span class="opt_cn"> {{Tu}} </span></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">H</span></td>
                            <td><select id = "sensorHumi">
                              <option value = "NONE"> НЕТ </option>
                              <option value = "SI7021"> SI7021 </option>
                              <option value = "BME280"> BME280 </option>
                            </select></td>
                            <td><input type="text" class="field form-control" id="corrHumi" value="{{corrHumi}}" pattern="\- \d+(\.\d{2})?"></td>
                            <td><span class="opt_cn"> {{Hd}} </span></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">P</span></td>
                            <td><select id = "sensorPrAl">
                              <option value = "NONE"> НЕТ </option>
                              <option value = "BMP280"> BMP180/280 </option>
                              <option value = "BME280"> BME280 </option>
                            </select></td>
                            <td><input type="text" class="field form-control" id="corrPress" value="{{corrPress}}" pattern="\- [0-9]{0,3}"></td>
                            <td><span class="opt_cn"> {{Pu}} </span></td>
                        </tr>
                        <tr>
                            <td></td>
                            <td><select id = "pressSys">
                              <option value = "0"> гПа </option>
                              <option value = "1"> ммРс </option>
                            </select></td>
                            <td></td>
                            <td></td>
                        </tr>
                    </table>
                    <br>
                    <span class="save_booton" onclick="set_setup(this);">Сохранить настройки</span>
                    <br>
                </center>
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
