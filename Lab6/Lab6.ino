#include <Stepper.h>

int Pin1 = 8;                                               
int Pin2 = 9;
int Pin3 = 10;
int Pin4 = 11;
int FinalStepCount = 0;                           
int stepcount = 0;
const int StepPerRevolution = 200;
const int trigPin = 22;
const int echoPin = 23;
int pushStart = A1;
int pushStop = A2;
long Distance;
long TotalTime;
int FinalDistance = 0;
Stepper stepper(StepPerRevolution, Pin1, Pin2, Pin3, Pin4);

void setup() {
  Serial.begin(9600);
  pinMode(pushStart, INPUT);
  pinMode(pushStop, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(Pin1, OUTPUT);
  pinMode(Pin2, OUTPUT);
  pinMode(Pin3, OUTPUT);
  pinMode(Pin4, OUTPUT);
}

void loop() {
    int Start = digitalRead(pushStart);        
      if(Start == 1)                          //Only if the button is pressed the stepper will begin its rotation.
      {
        Inicio();
      }
      delay(50);     
}

void Inicio() {
  int End = digitalRead(pushStop);            
    do{
      if(End == 1)                            //If in any case the second botton is pressed the stepper will stoped in any position it is.
      {
          Serial.println("Finalizado");
          break;
      }
      stepper.setSpeed(50);                   //Define the stepper speed.
      stepper.step(10);                       //Define how much steps it its going to make each "step". Once step on the code is equal to 10 of the stepper. The stepper (28BYJ-48) needs aproximately 2000 steps to make one turn
      digitalWrite(trigPin,LOW);              //** 
      delayMicroseconds(5);                   //**This section is used to control and
      digitalWrite(trigPin, HIGH);            //**activate the ultrasonic sensor in order 
      delayMicroseconds(10);                  //**to take samples of how long it take to the 
      digitalWrite(trigPin, LOW);             //**wave to return to the sensor.
      TotalTime=pulseIn(echoPin, HIGH);       //*
      Distance = int(0.017*TotalTime);        //Operation to obtain the distance from the sensor to 'x' object in cm, all this based on time.
      
      if(stepcount == 1)
      {
            FinalDistance = Distance;         //As soon as the stepper begin to move it will save the distance obtained by the ultrasonic sensor in this variable.
      }
      if(Distance<FinalDistance)              
      {
            FinalDistance = Distance;         //If the previpus condition is fulfilled this will update the nearest distance,
            FinalStepCount = stepcount;       //and also how many steps it will take to reach that position again
      }
      
      Serial.println("Distance ");            //Printing the results on serial screen
      Serial.print(Distance);
      Serial.println(" cm");
      stepcount++;                            //Condition to limit the amount of steps (one turn)
      delay(100);
    } 
  while(stepcount<StepPerRevolution);         //*Condition in which once the step limit is reached this will reset the
  stepcount = 0;                              //*variable stepcount so another lap can be done once the button is pressed again.
  stepper.step(FinalStepCount*10);            //This will move the stepper to the point where the closest object was detected.                                              
 }                                            //The multlipication of the variable is done due to the condition previously done to the amount of steps by "step"
