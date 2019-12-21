const char P_help[] PROGMEM =  R"=====(
<html>
    <head>
        <!--meta name = "viewport" content = "width=device-width, initial-scale=1.0"-->
        <meta http-equiv = "Content-type" content = "text/html; charset=utf-8">
        <title>Informer_clock_weath на ESP8266 ver:11.2019.2x.2 (By IvanUA)</title>
        <link rel="shortcut icon" href="#" />
        <link rel = "stylesheet" type = "text/css" href = "/style.css">
        <script type = "text/javascript" src = "/function.js"></script>
        <script type = "text/javascript">
            function set_printCom(submit) {
                server = "/printCom?printCom=" + val_sw('printCom');
                send_request(submit, server);
            }
            function resetConfig(submit,texts) {
                if(confirm(texts)) {
                    server = "/resetConfig?device=ok";
                    send_request(submit, server);
                    return true;
                } else {
                    return false;
                }
            }
        </script>
    </head>
    <body onload = "load();">
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
                <a class="link__img" href="#"><span class="ico__text" onclick="resetConfig(this,'Сбросить к заводским настройкам?');">Сброс</span></a>
            </div>
            <titles><span class="opt_cn">Если что-то пошло не так ...</span></titles>
            <div class="informer"><span class="opt_cn">ВНИМАНИЕ!!! Некоторые изменения могут быть необратимыми !!!</span>
            </div>            
            <div id="main_unit">
                <div class="informer">
                    <span class="opt_cn">Если вы ввели что-то не так и не можете изменить это, верните устройство к заводским настройкам. Файл конфигурации будет удален. Устройство перезагрузиться!</span>
                </div>  
                <a class = "btn btn-block btn-default" href = "/configs.json">Открыть файл конфигурации</a>
                <hr>
                <label class="switch">
                    <span class="opt_cn">Отображать информацию в COM порт</span>
                    <input class="checkbox" type="checkbox" id="printCom" name="switch-btn" onclick="set_printCom(this);">
                    <span class="switch-btn"></span>
                </label>
            </div>
            <hr>
            <center>
                <div>
                    <b><span class="opt_cn">Обновление: выберите и загрузите прошивку (bin)</span></b>
                    <form method="POST" action="/update" enctype="multipart/form-data">
                        <div>
                            <input type="file"  name="update" style="height: 33px;">
                            <input type="submit" class="save_booton" value="загрузить" onclick="this.value='Подождите...';">
                        </div>
                    </form>
                </div>
            </center>
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
