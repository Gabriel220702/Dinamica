#include <Wire.h> // Se incluye la librería Wire
#include <MPU6050_light.h> // Se incluye la librería de comunicación MPU
#include <LiquidCrystal.h> // Se incluye la librería para el Display LCD

MPU6050 mpu(Wire); // Se crea un objeto MPU
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Se dfinen los pines del Display LCD

unsigned long timer = 0;

void setup() {
  Serial.begin(9600); // Se inicia la comunicación Serial

  lcd.begin(16, 2); // Se inicia el Display LCD
  lcd.clear(); // Se limpia el Display LCD
  lcd.setCursor(0, 0);
  lcd.print("   MPU6050 ON");
  lcd.setCursor(0, 1);
  lcd.print("  Calibrando...");
  delay(2000);

  Wire.begin();
  mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcGyroOffsets(); // Se calibra el giroscopio 
  Serial.println("Done!\n");
}

void loop() {
  mpu.update(); // Se obtienen valores del MPU

  if ((millis() - timer) > 100) { // Mostrar los datos cada 100 milisegundos 
    timer = millis();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("    Angulo:");
    lcd.print(int(mpu.getAngleZ())); // Mostrar el valor del angulo Z en el Display LCD 
  }
}
