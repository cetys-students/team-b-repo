int ft = 2;
int hall = 3;
int temp = A0;

int led1 = 5;
int led2 = 6;

int vft = 0;
int vhall = 0;
int vtemp = 0;

int count = 0;
int timer = 0;

void setup() {
  pinMode(ft, INPUT);
  pinMode(hall, INPUT);
  pinMode(temp, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  
  vft = digitalRead(ft);
  vhall = digitalRead(hall);
//vtemp = analogRead(temp);
  //CONVERSION VOLTAJE A TEMP REAL
vtemp = analogRead(temp);

  if(vft == 1){
   count++;
  }
   if(vhall == 1){
    count++;
  }
 if (vtemp > 30){
  count++;
}

if(count == 2 || count == 3){
 digitalWrite(led1, HIGH);
 digitalWrite(led2, HIGH);
}

else if(count == 1 && timer<=10){
      timer++;
      digitalWrite(led1, HIGH);
      digitalWrite(led2,LOW);
      delay(500);
      digitalWrite(led1,LOW);
      digitalWrite(led2,HIGH);
      delay(500);
      if(timer == 10){
  digitalWrite(led1, HIGH);
  digitalWrite(led2,HIGH);
  
  }
else if (count == 0){
  timer = 0;
}


  }
  

  
Serial.print("count: ");
Serial.print(count);
Serial.print("   timer: ");
Serial.print(timer);
Serial.print("Photo: ");
Serial.print(vft);
Serial.print("   HALL: ");
Serial.print(vhall);
Serial.print("   Temp: ");
Serial.println(vtemp);
count = 0;
delay(10);

  
  }



