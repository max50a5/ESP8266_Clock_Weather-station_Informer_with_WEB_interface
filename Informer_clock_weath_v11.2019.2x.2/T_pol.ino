void polText(){
  tNow = "Teraz";
  tPress = "mmHg";
  tSpeed = "m/s";
  tMin = "min.";
  tCurr = "Dzisiaj";
  tTom = "Jutro";
  tYour = "Twój";
  tPoint = "Polacz sie z punktem dostępu ESP-Info i wprowadz w przeglądarce adres: 192.168.4.1         ";
  tJanuary = "stycznia";
  tFebruary = "lutego";
  tMarch = "marzca";
  tApril = "kwiecnia";
  tMay = "maja";
  tJune = "czerwca";
  tJuly = "lipca";
  tAugust = "sierpnia";
  tSeptember = "wrzesnia";
  tOctober = "pazdziernika";
  tNovember = "listopada";
  tDecember = "grudznia";
  tMonday = "Poniedzialek";
  tTuesday = "Wtorek";
  tWednesday = "Środa";
  tThursday = "Czwartek";
  tFriday = "Piątek";
  tSaturday = "Sobota";
  tSunday = "Niedziela";
  tYear = "roku";

  tWeatrNot = "   Brak aktualizacji pogody przez ponad 6 godzin!!!   ";
  tWeatrTN = "brak aktualizacji pogody - ";
  if(printCom) {
    printTime();
    Serial.println("Text POL.");
  }
  weatherLang = "pl";
}
