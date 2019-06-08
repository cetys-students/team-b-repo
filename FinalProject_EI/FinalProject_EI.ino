#include <Wire.h>
#include <L3G.h>

char report[80];

// G y r o s c o p e
// Sampling period with a frequency of 100 Hz in ms
L3G gyro;

float gyroX = 0;
float lastGyroX = 0;
float angleX = 0;
float scalingFactor_x = 17.5 / 1000;
float calibrationBias_x = 0;
float samplingPeriod_x = 10.0;
float delta_x = 0;

float gyroY = 0;
float lastGyroY = 0;
float angleY = 0;
float scalingFactor_y = 17.5 / 1000;
float calibrationBias_y = 0;
float samplingPeriod_y = 10.0;
float delta_y = 0;

//  Variables
int cal_count = 0;
int buzzer = 6;
int squat_count = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);

  // Gyro setup
  if (!gyro.init()) {
    Serial.print("Failed to autodetect gyro type!");
    while (1);
  }
  gyro.enableDefault();
  gyro.writeReg(gyro.CTRL_REG4, 0x10);// Full scale 500 dps
  gyro.writeReg(gyro.CTRL_REG1, 0xEF); 

  //Calibration for Angle Z
  while (cal_count < 1000) {
    Serial.println("Calibrating...");
    gyro.read();

    gyroX = gyro.g.x * scalingFactor_x;
    calibrationBias_x += gyroX;
    gyroY = gyro.g.y * scalingFactor_y;
    calibrationBias_y += gyroY;
    gyroZ = gyro.g.z * scalingFactor_z;
    calibrationBias_z += gyroZ;
    cal_count++;
  }
  calibrationBias_x /= 1000;
  calibrationBias_y /= 1000;
  calibrationBias_z /= 1000;
  Serial.println("Calibration completed!");
  digitalWrite(buzzer, HIGH);
  delay(1500);
}
 
void loop() {
  gyro.read();
  
  // I N T E G R A L   A N G L E   X
  lastGyroX = gyroX;
  gyroX = gyro.g.x * scalingFactor_x;
  gyroX -= calibrationBias_x;
  // Calculate integral
  float delta_x = (samplingPeriod_x / 1000.0);
  angleX += 0.5 * (gyroX + lastGyroX) * delta_x;
  
  // I N T E G R A L   A N G L E   Y
  lastGyroY = gyroY;
  gyroY = gyro.g.y * scalingFactor_y;
  gyroY -= calibrationBias_y;
  // Calculate integral
  float delta_y = (samplingPeriod_y / 1000.0);
  angleY += 0.5 * (gyroY + lastGyroY) * delta_y;

//CONDITIONS
if (angleX < -70.0){
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  angleX = 0;
  angleY = 0;
}
// Reset in squat
// Values in Gyro Z must be almost zero indicating the stopped movement
if ((angleX >= 50.0) && (gyroZ <= 3.0) && (gyroZ >= -3.0)){
  angleX = 0;
  angleY = 0;
  squat_count++;
  delay(50);
}
// Straight knees -> Knees open -> HIGH SENSITIVITY
if ((angleX > -30.0) && (angleY <= -10.0)){
  Serial.println("Wrong knees!, put them straight");
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  delay(200);
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  angleY = 0;
  angleX = 0;
}
// Bent knees -> Knees open -> MEDIUM SENSITIVITY
if ((angleX <= -30.0) && (angleY <= -8.0)){
  Serial.println("Wrong knees!, put them straight");
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  delay(200);
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  angleY = 0;
}
// Full squat -> Knees open -> LOW SENSITIVITY
if ((angleX < -70.0) && (angleY <= -7.0)){
  Serial.println("Wrong knees!, put them straight");
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  delay(200);
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  angleY = 0;
}
///////////////////////////////////////////////////////////////
// Straight knees -> Knees closed -> HIGH SENSITIVITY
if ((angleX > -30.0) && (angleY > 10.0)){
  Serial.println("Wrong knees!, put them straight");
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  delay(200);
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  angleY = 0;
  angleX = 0;
}
// Bent knees -> Knees closed -> MEDIUM SENSITIVITY
if ((angleX <= -30.0) && (angleY > 8.0)){
  Serial.println("Wrong knees!, put them straight");
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  delay(200);
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  angleY = 0;
}
// Full squat -> Knees closed -> LOW SENSITIVITY
if ((angleX < -65.0) && (angleY > 8.0)){
  Serial.println("Wrong knees!, put them straight");
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  delay(200);
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  angleY = 0;
}
if (squat_count == 8){
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
  delay(300);
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  delay(300);
  digitalWrite(buzzer, HIGH);
  delay(500);
  squat_count = 0;
}
else{
  digitalWrite(buzzer, LOW);
}
}


