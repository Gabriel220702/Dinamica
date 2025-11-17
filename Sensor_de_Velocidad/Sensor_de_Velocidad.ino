#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // RS,E,D4,D5,D6,D7
// defines pins numbers
const int trigPin = 8;
const int echoPin = 9;

// defines variables
long duration;
int distance1 = 0;
int distance2 = 0;
double Speed = 0;
int distance = 0;

void setup()
{
  lcd.begin(16, 2); // LCD 16X2
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(7, OUTPUT);
  Serial.begin(9600); // Starts the serial communication

  lcd.setCursor(0, 0);
  lcd.print("   HC-SR04 ON");
  lcd.setCursor(0, 1);
  lcd.print("  Calibrando...");
  delay(2000);
  lcd.clear();
}

void loop()
{
  // Calculating Speed
  distance1 = ultrasonicRead(); // Calls ultrasonicRead() function below

  delay(1000); // Giving a time gap of 1 sec

  distance2 = ultrasonicRead(); // Calls ultrasonicRead() function below

  // Formula: change in distance divided by change in time
  Speed = (distance2 - distance1) / 1.0; // As the time gap is 1 sec, we divide it by 1.

  // Displaying Speed
  Serial.print("v in cm/s: ");
  Serial.println(Speed);
  lcd.setCursor(0, 1);
  lcd.print("v cm/s:  ");
  lcd.print(Speed, 2); // Display with 2 decimal places

  // LED indicator
  if (distance > 0 && distance < 5)
  {
    digitalWrite(7, HIGH);
    delay(50);
  }
  else if (distance >= 5 && distance < 10)
  {
    digitalWrite(7, HIGH);
    delay(50);
    digitalWrite(7, LOW);
    delay(50);
  }
  else if (distance >= 10 && distance < 20)
  {
    digitalWrite(7, HIGH);
    delay(210);
    digitalWrite(7, LOW);
    delay(210);
  }
  else if (distance >= 20 && distance < 35)
  {
    digitalWrite(7, HIGH);
    delay(610);
    digitalWrite(7, LOW);
    delay(610);
  }
}

float ultrasonicRead()
{
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating distance
  distance = duration * 0.034 / 2;

  // Prints the distance on the Serial Monitor
  Serial.print("d in cm: ");
  Serial.println(distance);
  lcd.setCursor(0, 0);
  lcd.print("d cm:    ");
  lcd.print(distance);
  lcd.print("   ");
  return distance;
}
