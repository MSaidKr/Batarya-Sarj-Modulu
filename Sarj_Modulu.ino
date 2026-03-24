#include <Wire.h>
#include <Adafruit_INA219.h>
#include <LiquidCrystal_I2C.h>

Adafruit_INA219 ina219;
// LCD Adresi genelde 0x27'dir, olmazsa 0x3F dene
LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup(void) {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0, 0);
  lcd.print("Sistem Kontrol..");
  delay(1000);

  // INA219 Kontrolü
  if (!ina219.begin()) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("INA219: HATA!");
    lcd.setCursor(0, 1);
    lcd.print("Kablolari SIKISTIR");
    Serial.println("INA219 bulunamadi. Baglantilari kontrol et!");
    while (1) { delay(10); } 
  } else {
    // İşte aradığın o onay mesajı!
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("INA219: OK!");
    lcd.setCursor(0, 1);
    lcd.print("Veri Bekleniyor..");
    Serial.println("INA219 Basariyla Baglandi.");
    delay(2000);
  }
  lcd.clear();
}

void loop(void) {
  float busvoltage = 0;
  float current_mA = 0;
  float power_mW = 0;

  // Verileri Oku
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  power_mW = ina219.getPower_mW();

  // LCD Yazdırma
  lcd.setCursor(0, 0);
  lcd.print("V: "); lcd.print(busvoltage); lcd.print(" V   ");
  
  lcd.setCursor(0, 1);
  lcd.print("A: "); lcd.print(current_mA); lcd.print(" mA   ");

  // Seri Port Yazdırma (Yedek takip için)
  Serial.print("Voltaj: "); Serial.print(busvoltage); Serial.println(" V");
  Serial.print("Akim: "); Serial.print(current_mA); Serial.println(" mA");
  Serial.println("--------------------");

  delay(1000); // 1 saniyede bir güncelle
}