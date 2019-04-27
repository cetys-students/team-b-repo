#include <Wire.h>
#include <LSM303.h>

LSM303 compass;

char report[80];

float x_value = 0;
float y_value = 0;
float z_value = 0;
float magnitude = 0;

int ledPin_1 = 2;
int ledPin_2 = 3;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  compass.init();
  compass.enableDefault();
  pinMode(ledPin_1, OUTPUT);
  pinMode(ledPin_2, OUTPUT);
}

void loop()
{
  compass.read();
  x_value = (int)compass.a.x * 0.061 / 1000;
  y_value = (int)compass.a.y * 0.061 / 1000;
  z_value = (int)compass.a.z * 0.061 / 1000;
  magnitude = sqrt((pow(x_value, 2)) + (pow(y_value, 2)) + (pow(z_value, 2)));

if (magnitude >= 0.89 && magnitude <= 1.05){ //standing still
  digitalWrite(ledPin_1, HIGH);
}
else {
  digitalWrite(ledPin_1, LOW);
}
if ((x_value >= -0.061 && x_value <= 0.061) && (y_value >= -0.025 && y_value <= 0.025) && (z_value >= -0.91 && z_value <= 0.91)){ 
  digitalWrite(ledPin_2, HIGH);
}
else{
  digitalWrite(ledPin_2, LOW);
}


  Serial.print("A    ");
  Serial.print("X: ");
  Serial.print(x_value);
  Serial.print(" Y: ");
  Serial.print(y_value);
  Serial.print(" Z: ");
  Serial.println(z_value);
  Serial.print(" Magnitude: ");
  Serial.println(magnitude);
  

  delay(200);
}
