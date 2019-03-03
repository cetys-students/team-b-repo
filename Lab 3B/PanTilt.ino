#include <Servo.h>
Servo horiz;
Servo vert;
//Sensors
int S_UP = 2;
int S_DOWN = 3;
int S_RIGHT = 4;
int S_LEFT = 5;
//Data
int UP = 0;
int DOWN = 0;
int RIGHT = 0;
int LEFT = 0;
//Degrees
int ContadorH = 90;
int ContadorV = 90;

void setup() {
Serial.begin(9600);
pinMode(S_UP,INPUT);
pinMode(S_DOWN,INPUT);
pinMode(S_RIGHT,INPUT);
pinMode(S_LEFT,INPUT);
//Servos
horiz.attach(6);
vert.attach(7);
}
void loop() {
UP = digitalRead(S_UP);
DOWN = digitalRead(S_DOWN);
RIGHT = digitalRead(S_RIGHT);
LEFT = digitalRead(S_LEFT);

if(UP == 1 && DOWN == 0&& ContadorV != 180 && ContadorV != 0){
//Move up
  ContadorV++;
  vert.write(ContadorV);
  delay(500);
}
else if(UP == 0 && DOWN == 1 && ContadorV != 180 && ContadorV != 0){
//Mover down
  ContadorV--;
  vert.write(ContadorV);
  delay(500);
}
if(RIGHT == 1 && LEFT == 0 && ContadorH != 180 && ContadorH != 0){
//Move to the right
  ContadorH++;
  horiz.write(ContadorH);
  delay(500);
}
else if(RIGHT == 0 && LEFT == 1 && ContadorH != 180 && ContadorH != 0){
//Move to the left
  ContadorH--;
  horiz.write(ContadorH);
  delay(500);
}

Serial.print("UP: ");
Serial.print(UP);
Serial.print("   DOWN: ");
Serial.print(DOWN);
Serial.print("   LEFT: ");
Serial.print(LEFT);
Serial.print("   RIGHT: ");
Serial.print(RIGHT);
Serial.print("   ContadorV: ");
Serial.print(ContadorV);
Serial.print("   ContadorH: ");
Serial.println(ContadorH);

delay(50);
}

