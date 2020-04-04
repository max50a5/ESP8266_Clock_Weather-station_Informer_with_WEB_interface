const char P_help[] PROGMEM =  R"=====(
<html>
    <head>
        <!--meta name = "viewport" content = "width=device-width, initial-scale=1.0"-->
        <meta http-equiv = "Content-type" content = "text/html; charset=utf-8">
        <title>Уличный датчик вер.04.2020 (By IvanUA & MAX)</title>
        <link rel="shortcut icon" href="#" />
        <link rel = "stylesheet" type = "text/css" href = "/style.css">
        <script type = "text/javascript" src = "/function.js"></script>
        <script type = "text/javascript">
//            function set_printCom(submit) {
//                server = "/printCom?printCom=" + val_sw('printCom');
//                send_request(submit, server);
//            }
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
            <titles><span class="opt_cn">Если что-то пошло не так...</span></titles>
            <div class="informer"><span class="opt_cn">ВНИМАНИЕ!!! Некоторые изменения могут быть необратимыми!!!</span>
            </div>            
            <center>
                <div>
                    <b><span class="opt_cn">Обновление: выберите и загрузите прошивку(bin)</span></b>
                    <form method="POST" action="/update" enctype="multipart/form-data">
                        <div>
                            <input type="file"  name="update" style="height: 33px;">
                            <input type="submit" class="save_booton" value="загрузить" onclick="this.value='Подождите...';">
                        </div>
                    </form>
                </div>
            </center>
            <div class="menu_unit">
                <a class="link__img" href="#"><span class="ico__text" onclick="restart(this,'Перезагрузить?');">Перезагрузить устройство</span></a>
            </div>
            <div class="informer">
                    <span class="opt_cn">Если вы ввели что-то не так и не можете изменить это, верните устройство к заводским настройкам. Устройство перезагрузиться!</span>
            </div>
            <div class="menu_unit">
                <a class="center" href="#"><span class="ico__text" onclick="resetConfig(this,'Сбросить настройки?');">Сброс настроек по умолчанию</span></a>
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
