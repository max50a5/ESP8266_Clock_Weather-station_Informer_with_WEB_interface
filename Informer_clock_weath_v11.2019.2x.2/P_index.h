const char P_index[] PROGMEM =  R"=====(
<html>
    <head>
        <!--meta name = "viewport" content = "width=device-width, initial-scale=1.0"-->
        <meta http-equiv = "Content-type" content = "text/html; charset=utf-8">
        <title>Informer_clock_weath на ESP8266 ver:11.2019.2x.2 (By IvanUA)</title>
        <link rel="shortcut icon" href="#" />
        <link rel = "stylesheet" type = "text/css" href = "/style.css">
        <script type = "text/javascript" src = "/function.js"></script>
        <script type = "text/javascript">
            function set_ssid(submit) {
                server = "/ssid?ssid=" + val('ssid') + "&password=" + encodeURIComponent(val('password'))+"&ssidAP=" + val('ssidap') + "&passwordAP=" + encodeURIComponent(val('passwordAp'));
                send_request(submit,server);
                alert("Изменения вступят в силу после перезагрузки. Пожалуйста, перезагрузите устройство.");
            }
        </script>
    </head>
    <body onload = "load_wifi();">
        <header>
            <span class="opt_cn">ИНФОРМАТОР на ESP8266 вер. 11.2019.2X.2 (by IvanZah)</span><br>
            <span class="opt_cn">Время ESP:</span>
            <span id="time">{{time}}</span>
        </header>       
        <central-unit>
            <div class="menu_unit">
                <a class="link__img" href="/index.html"><span class="ico__text">Wifi</span></a>
                <a class="link__img" href="/time.html"><span class="ico__text">Время</span></a>
                <a class="link__img" href="/weather.html"><span class="ico__text">Прогноз</span></a>
                <a class="link__img" href="/setup.html"><span class="ico__text">Настройки</span></a>
                <a class="link__img" href="/help.html"><span class="ico__text">Помощь</span></a>
                <a class="link__img" href="#"><span class="ico__text" onclick="restart(this,'Сбрость ESP?');">Сбросить</span></a>
            </div>
            <div class="body__center">
                <titles>
                    <span class="opt_cn">Настройка WIFI</span>
                </titles>
                <div class="informer">
                    <span class="opt_cn">Подключение к сети Интернет позволит вам синхронизировать время и получать прогноз погоды.</span>
                </div>
                <div id="main_unit">
                    <paragraph>
                        <span class="opt_cn">Подключение к WiFi роутеру</span>
                    </paragraph>
                    <center>
                        <table>
                            <tr>
                                <td align = "right"><span class="opt_cn">Введите название WiFi сети</span></td>
                                <td><input type="text" class="field form-control" id="ssid" value="{{ssid}}" pattern="[-\w\s#@/]{1,15}" placeholder="название WiFi сети"></td>
                            </tr>
                            <tr>  
                                <td align = "right"><span class="opt_cn">Введите пароль WiFi сети</span></td>
                                <td><input class="field form-control" id="password" value="{{password}}" pattern=".{8,15}" onfocus="this.type='text'" type="пароль"></td>
                            </tr>
                        </table>
                    </center>
                    <paragraph>
                        <span class="opt_cn">Параметры точки доступа (IP_192.168.4.1)</span>
                    </paragraph>
                    <center>
                        <table>
                            <tr>
                                <td align = "right"><span class="opt_cn">Введите название точки доступа</span></td>
                                <td><input type="text" class="field" id="ssidap" value="{{ssidAP}}" class="form-control" pattern="[-\w\s#@/]{1,15}" placeholder="имя точки доступа"></td>
                            </tr>
                            <tr>
                                <td align = "right"><span class="opt_cn">Введите пароль точки доступа</span></td>  
                                <td><input class="field" id="passwordAp" value="{{passwordAP}}" class="form-control" pattern=".{0,15}" onfocus="this.type='text'" type="пароль" class="form-control"></td>
                            <tr>
                        </table>
                    </center>
                    <span class="save_booton" onclick="set_ssid(this);">Сохранить</span>
                </div>
            </div>
            <div class="menu_unit" id="langs">
                <a><span class="ico__text" onclick="set_lang_f(this, 'EN');">EN</span></a>
                <a><span class="ico__text" onclick="set_lang_f(this, 'UA');">UA</span></a>
                <a><span class="ico__text" onclick="set_lang_f(this, 'RU');">RU</span></a>
                <a><span class="ico__text" onclick="set_lang_f(this, 'PL');">PL</span></a>
                <a><span class="ico__text" onclick="set_lang_f(this, 'CZ');">CZ</span></a>
                <a><span class="ico__text" onclick="set_lang_f(this, 'DE');">DE</span></a>
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
