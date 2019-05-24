#include <Wire.h>
#include <L3G.h>
#include <LSM303.h>

int ledPin_1 = 2;
int ledPin_2 = 3;
int ledPin_3 = 4;
int ledPin_4 = 5;
int ledPin_5 = 6;

// A c c e l e r o m e t e r
LSM303 compass;
char report[80];
float x_value = 0;
float y_value = 0;
float z_value = 0;
float magnitudeAccel = 0;

// G y r o s c o p e
L3G gyro;
float gyroY = 0;
float lastGyroY = 0;
float angleY = 0;
float scalingFactor_y = 17.5 / 1000;
float calibrationBias_y = 0;
// Sampling period with a frequency of 100 Hz in ms
float samplingPeriod_y = 10.0;
float delta_y = 0;

float gyroZ = 0;
float lastGyroZ = 0;
float angleZ = 0;
float scalingFactor_z = 17.5 / 1000;
float calibrationBias_z = 0;
// Sampling period with a frequency of 100 Hz in ms
float samplingPeriod_z = 10.0;
float delta_z = 0;

//  Variables
int state = 0;
int cal_count = 0;
int count = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  pinMode(ledPin_1, OUTPUT);
  pinMode(ledPin_2, OUTPUT);
  pinMode(ledPin_3, OUTPUT);
  pinMode(ledPin_4, OUTPUT);
  pinMode(ledPin_5, OUTPUT);

  // Gyro setup
  if (!gyro.init()) {
    Serial.println("Failed to autodetect gyro type!");
    while (1);
  }
  gyro.enableDefault();
  gyro.writeReg(gyro.CTRL_REG4, 0x10);
  gyro.writeReg(gyro.CTRL_REG1, 0xEF); // Full scale 500 dps
  compass.init();
  compass.enableDefault();

  //Calibration for Angle Z
  while (cal_count < 1000) {
    Serial.println("Calibrating...");
    gyro.read();

    gyroY = gyro.g.y * scalingFactor_y;
    calibrationBias_y += gyroY;
    gyroZ = gyro.g.z * scalingFactor_z;
    calibrationBias_z += gyroZ;
    cal_count++;
  }
  calibrationBias_y /= 1000;
  calibrationBias_z /= 1000;
  Serial.print(calibrationBias_y);
  Serial.print(calibrationBias_z);

}

void loop() {
  gyro.read();
  compass.read();
  x_value = (int)compass.a.x * 0.061 / 1000;
  y_value = (int)compass.a.y * 0.061 / 1000;
  z_value = (int)compass.a.z * 0.061 / 1000;
  magnitudeAccel = sqrt((pow(x_value, 2)) + (pow(y_value, 2)) + (pow(z_value, 2)));

  // I N T E G R A L   A N G L E   Y
  lastGyroY = gyroY;
  gyroY = gyro.g.y * scalingFactor_y;
  gyroY -= calibrationBias_y;
  // Calculate integral
  float delta_y = (samplingPeriod_y / 1000.0);
  angleY += (gyroY + lastGyroY) * delta_y * 3.5;

  // I N T E G R A L   A N G L E   Z
  lastGyroZ = gyroZ;
  gyroZ = gyro.g.z * scalingFactor_z;
  gyroZ -= calibrationBias_z;
  // Calculate integral
  float delta_z = (samplingPeriod_z / 1000.0);
  angleZ += (gyroZ + lastGyroZ) * delta_z * 3.5;

  if (count >= 50) {
    state = 0;
    count = 0;
    angleZ = 0;
    angleY = 0;
    digitalWrite(ledPin_1, LOW);
    digitalWrite(ledPin_2, LOW);
    digitalWrite(ledPin_3, LOW);
    digitalWrite(ledPin_4, LOW);
  }
  if ((state == 0) && (y_value >= 1.15)) {
    digitalWrite(ledPin_1, HIGH);
    angleZ = 0;
    count = 0;
    state++;
  }
  if ((state == 1) && (angleZ >= 90.0)) {
    digitalWrite(ledPin_2, HIGH);
    angleZ = 0;
    angleY = 0;
    count = 0;
    state++;
  }
  if ((state == 2) && (angleY >= 90.0)){
    digitalWrite(ledPin_3, HIGH);
    angleZ = 0;
    angleY = 0;
    count = 0;
    state++;
  }
  if ((state == 3) && (magnitudeAccel <= 0.36)){
    digitalWrite(ledPin_4, HIGH);
    angleZ = 0;
    count = 0;
    state++;
  }
  if (state == 4) {
    digitalWrite(ledPin_5, HIGH);
    delay(3000);
    angleZ = 0;
    angleY = 0;
    count = 0;
    state = 0;
    digitalWrite(ledPin_1, LOW);
    digitalWrite(ledPin_2, LOW);
    digitalWrite(ledPin_3, LOW);
    digitalWrite(ledPin_4, LOW);
    digitalWrite(ledPin_5, LOW);
  }
  count++;
}
