#include <LiquidCrystal.h>

LiquidCrystal lcd (2, 3, 4, 5, 6, 7);

int inputPin = 8;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
int timer = 0;
int contador = 0;

void setup() {
  lcd.begin(16,2);
  pinMode(inputPin, INPUT);     // declare sensor as input
  Serial.begin(9600);
}

void loop() {
  val = digitalRead(inputPin);  // read input value
    while (val == HIGH){
      timer++;
      lcd.print("Motion detected!");
      lcd.setCursor(0,1);
      lcd.print("Elapsed time: " + String(timer));
      pirState = HIGH;
      delay(1000);
      val = digitalRead(inputPin);  // read input value
      lcd.clear();
    }
    
    if (pirState == HIGH){
      timer = 0;
      contador++;
      lcd.print("Motion ended!");
      lcd.setCursor(0,1);
      lcd.print("Objects: " + String(contador));
      delay(1000);
      lcd.clear();
      pirState = LOW;
    }
}
