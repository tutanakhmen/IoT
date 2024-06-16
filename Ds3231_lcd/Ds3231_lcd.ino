#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>

RTC_DS3231 rtc;
LiquidCrystal_I2C lcd (0x27,16,2);

char namaHari[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
char namaBulan[12][12]={"Jan","Feb","Mar","Apr","mei","Jun","Jul","Agu","Sep","Okt","Nov","Des"};

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);

  if (!rtc.begin()) {
    Serial.println("RTC tidak terbaca");
    lcd.setCursor(0,0);
    lcd.print("RTC tidak terbaca");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
   rtc.adjust(DateTime(2024, 2, 6, 12, 45, 00));
  }
}

void loop() {
  DateTime now = rtc.now();

lcd.setCursor(0, 1);
  lcd.print("Time: ");
  lcd.print(now.hour(), DEC);
  lcd.print(':');
  lcd.print(now.minute(), DEC);
  lcd.print(':');
  lcd.print(now.second(), DEC);

  // Tampilkan tanggal pada LCD
  lcd.setCursor(0, 0);
  lcd.print("Date: ");
  lcd.print(now.day(), DEC);
  lcd.print('/');
  lcd.print(now.month(), DEC);
  lcd.print('/');
  lcd.print(now.year(), DEC);

  delay(1000);
}
