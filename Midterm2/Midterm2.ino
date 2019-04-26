//Including libraries
#include <Wire.h>
#include <LSM303.h>
#include <L3G.h>

LSM303 compass;
L3G gyro;

char report[80];
//Accel data to display
float x_value = 0;
float y_value = 0;
float z_value = 0;
float magnitude_a = 0;

//Gyro to display in Serial
float x_valueg = 0;
float y_valueg = 0;
float z_valueg = 0;
float magnitude_g = 0;

int ledPin = 2;

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  //ACCEL
  compass.init();
  compass.enableDefault();
  pinMode(ledPin, OUTPUT);

  //GYRO REGISTER
  if (!gyro.init())
  {
    Serial.println("Failed to autodetect gyro type!");
    while (1);
  }

  gyro.enableDefault();
  gyro.writeReg(gyro.CTRL_REG4, 0x10); //Changing data registers in FS to 500 dps
  gyro.writeReg(gyro.CTRL_REG1, 0xEF); //default ODR
}

void loop()
{
  compass.read();
  x_value = (int)compass.a.x * 0.061 / 1000; //Respective conversions
  y_value = (int)compass.a.y * 0.061 / 1000;
  z_value = (int)compass.a.z * 0.061 / 1000;
  magnitude_a = sqrt((pow(x_value, 2)) + (pow(y_value, 2)) + (pow(z_value, 2)));

  gyro.read();
  x_valueg = (int)gyro.g.x * 17.5 / 1000; 
  y_valueg = (int)gyro.g.y * 17.5 / 1000;
  z_valueg = (int)gyro.g.z * 17.5 / 1000;
  magnitude_g = sqrt((pow(x_valueg, 2)) + (pow(y_valueg, 2)) + (pow(z_valueg, 2)));

  if (magnitude_a <= 0.25 ) { //IMPACT
    digitalWrite(ledPin, HIGH);
    delay(1000);
  }  
  else {
    digitalWrite(ledPin, LOW);
  }

  Serial.print("Accel = ");
  Serial.print("X: ");
  Serial.print(x_value);
  Serial.print(" Y: ");
  Serial.print(y_value);
  Serial.print(" Z: ");
  Serial.print(z_value);
  Serial.print("    Magnitude A: ");
  Serial.println(magnitude_a);

  delay(200);
}


