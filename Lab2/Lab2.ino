//Pins
int s_temp = A7;
int buzzer = 2;
//Data
int temp = 0;
int buzz = 0;

void setup() {
  Serial.begin(9600);
  pinMode(s_temp, INPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
temp = analogRead(s_temp);
float voltage = temp*5.0;
voltage /= 1024.0;

//Printing voltage
Serial.print(voltage);
Serial.println(" volts");

float temperature = (voltage) * 100;
Serial.print(temperature);
Serial.println(" °C");
delay(100);
int expectedDelay = 0;

if (temperature >= 110){
  expectedDelay = 100;
}
else if (temperature >= 80){
  expectedDelay = 250;
}
else if (temperature >= 65){
  expectedDelay = 500;
}
else if (temperature >= 28){
  expectedDelay = 1000;
}

digitalWrite(buzzer, HIGH);
delay(expectedDelay);
digitalWrite(buzzer, LOW);
delay(expectedDelay);
}
