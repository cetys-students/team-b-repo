#include <Wire.h>
#include <L3G.h>
#include <LiquidCrystal.h>

// Gyro
L3G gyro;
float gyroZ = 0;
float lastGyroZ = 0;
float angleZ = 0;
float scalingFactor = 17.5 / 1000;
float calibrationbias = 0;
// Sampling period with a frequency of 100 Hz in ms
float samplingPeriod = 10.0;

// LCD Display
const int RS = 12, EN = 11, D4 = 5, D5 = 4, D6 = 3, D7 = 2;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

int count = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  pinMode(PB, INPUT);
  lcd.begin(16, 2);
  
// Gyro setup
  if (!gyro.init()) {
    Serial.println("Failed to autodetect gyro type!");
    while (1);
  }
  gyro.enableDefault();
  gyro.writeReg(gyro.CTRL_REG4, 0x10);
  gyro.writeReg(gyro.CTRL_REG1, 0xEF); // Full scale 500 dps

  while (count < 1000){
    lcd.setCursor(0, 1);
    lcd.print("Calibrating...");
    gyro.read();
    gyroZ = gyro.g.z * scalingFactor;
    calibrationbias += gyroZ;
    count++;
  }
  calibrationbias /= 1000;
  Serial.println(calibrationbias);
  lcd.clear();
  lcd.print("Started");
  delay(1000);
  lcd.setCursor(2, 1);
  lcd.print("Press to start...");
}

void loop() {
  gyro.read();
  lastGyroZ = gyroZ;
  gyroZ = gyro.g.z * scalingFactor;
  gyroZ -= calibrationbias;
// Calculate integral
  float delta = (samplingPeriod / 1000.0);
  angleZ += (gyroZ + lastGyroZ) * delta;

  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Angle z = ");
  lcd.print(angleZ);
  delay(samplingPeriod);

}



