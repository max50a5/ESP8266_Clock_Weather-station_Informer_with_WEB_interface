const char P_thing[] PROGMEM =  R"=====(
<html>
    <head>
        <!--meta name = "viewport" content = "width=device-width, initial-scale=1.0"-->
        <meta http-equiv = "Content-type" content = "text/html; charset=utf-8">
        <title>Уличный датчик вер.04.2020 (By IvanUA & MAX)</title>
        <link rel="shortcut icon" href="#" />
        <link rel = "stylesheet" type = "text/css" href = "/style.css">
        <script type = "text/javascript" src = "/function.js"></script>
        <script type = "text/javascript">
            function set_thing_ust(submit) {
                server = "/thingUst?thingOn=" + val('thingOn') + "&writeapikey=" + val('writeapikey');
                send_request(submit,server);
            }
            function set_thing_on(submit) {
                server = "/thingOn?thingOn=" + val_sw("thingOn");
                send_request(submit, server);
            }
        </script>
    </head>
    <body onload = "load_thing();">
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
                <div class="opt_cn">Настройки ThingSpeak.com</div>
            </titles>
            <div class="informer">
                <span class="opt_cn">Настройки ThingSpeak. Здесь нужно ввести ключ записи (Write API Key)</span>
            </div>        
            <br>                
            <div id="main_unit">
                <hr>
                <label class="switch">
                    <span class="opt_cn">Использовать ThingSpeak.com</span>
                    <input type="checkbox" class="checkbox" id="thingOn" name="switch-btn" onclick="set_thing_on(this);">
                    <span class="switch-btn"></span>
                 </label>
                 <hr>
                 <br>       
                    <tr>
                        <td align = "right"><span class="opt_cn">Write API Key</span></td>
                        <td><input type="text" class="field form-control" id="writeapikey" value="{{writeapikey}}" pattern="[- 0-9a-zA-Z._/]{1,20}"></td>
                    </tr>
                 <br>
                <br>
                <span class="save_booton" onclick="set_thing_ust(this);">Сохранить настройки</span>
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
