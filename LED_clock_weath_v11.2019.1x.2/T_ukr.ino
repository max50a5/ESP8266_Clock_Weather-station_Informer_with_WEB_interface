void ukrText(){
  tNow = "Зараз";
  tPress = "ммРс";
  tSpeed = "м/с";
  tMin = "хв.";
  tCurr = "Сьогодні";
  tTom = "Завтра";
  tYour = "Ваш";
  tPoint = "Підключіться до мережі ESP-Info, та введіть адрес: 192.168.4.1       ";
  tJanuary = "січня";
  tFebruary = "лютого";
  tMarch = "березня";
  tApril = "квітня";
  tMay = "травня";
  tJune = "червня";
  tJuly = "липня";
  tAugust = "серпня";
  tSeptember = "вересня";
  tOctober = "жовтня";
  tNovember = "листопада";
  tDecember = "грудня";
  tMonday = "Понеділок";
  tTuesday = "Вівторок";
  tWednesday = "Середа";
  tThursday = "Четвер";
  tFriday = "П'ятниця";
  tSaturday = "Субота";
  tSunday = "Неділя";
  tYear = "року";

  tWeatrNot = "   Немає оновлень погоди більше 6 годин!!!   ";
  tWeatrTN = "немає оновлень погоди - ";
    if(printCom) {
    printTime();
    Serial.println("Text UKR.");
  }
  weatherLang = "uk";
}
