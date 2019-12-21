void deText(){
  tNow = "Jetzt";
  tPress = "mmHg";
  tSpeed = "m/s";
  tMin = "min.";
  tCurr = "Heute";
  tTom = "Morgen";
  tYour = "Ihr";
  tPoint = "Stellen Sie die Verbindung mit ESP-Info her, und geben Sie im Browser die Adresse: 192.168.4.1         ";
  tJanuary = "Januar";
  tFebruary = "Februar";
  tMarch = "März";
  tApril = "April";
  tMay = "Mai";
  tJune = "Juni";
  tJuly = "Juli";
  tAugust = "August";
  tSeptember = "September";
  tOctober = "Oktober";
  tNovember = "November";
  tDecember = "Dezember";
  tYear = "des Jahres";
  
  tMonday = "Montag";
  tTuesday = "Dienstag";
  tWednesday = "Mittwoch";
  tThursday = "Donnerstag";
  tFriday = "Freitag";
  tSaturday = "Samstag";
  tSunday = "Sonntag";

  tWeatrNot = "   Keine Wetteraktualisierungen seit 6 Stunden!!!   ";
  tWeatrTN = "Keine Wetteraktualisierungen - ";
  if(printCom) {
    printTime();
    Serial.println("Text DE.");
  }
  weatherLang = "de";
}
