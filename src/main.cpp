#include <Servo.h>
#include <Arduino.h>
#define Rpos 5
#define Rneg 3
#define Lpos 6
#define Lneg 11

#define Lside 8
#define LSensor 2
#define Rside 4
#define RSensor 7
#define StartMod 10
#define servo 9

void lineLeftt();
void lineRightt();
Servo myServo;  // Create Servo object
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myServo.attach(servo);
  pinMode(Rpos, OUTPUT);
  pinMode(Rneg, OUTPUT);
  pinMode(Lpos, OUTPUT);
  pinMode(Lneg, OUTPUT);
  pinMode(StartMod, INPUT);
  pinMode(Rside, INPUT);
  pinMode(Lside, INPUT);
  pinMode(LSensor, INPUT);
  pinMode(RSensor, INPUT);


  pinMode(A1, INPUT);
  pinMode(A0, INPUT);
  pinMode(A3, OUTPUT);

  pinMode(A6, INPUT); // DIPSWITCH 1
  pinMode(A7, INPUT); // DIPSWITCH 2
  myServo.write(10);   // Set servo to 170 70

  while(!digitalRead(StartMod)){}
  delay(5000);
}
enum RunMode {
  fightMode,
  startMode,
  stopMode,
  blindMode
};
void loop() {
  myServo.write(80);
  Serial.println(analogRead(A0));

  RunMode mode;
  if(analogRead(A6) > 500 && analogRead(A7) > 500)
    mode = fightMode;
  else if(analogRead(A6) < 500 && analogRead(A7) < 500)
    mode = startMode;
  else if(analogRead(A6) < 500 && analogRead(A7) > 500)
    mode = blindMode;
  else
    mode = stopMode;

  switch (mode){
    case fightMode:
      fight();
      break;
    case startMode:
      start();
      break;
    case stopMode:
      stop();
      break;
    case blindMode:
      blindSearch();
      break;
  }
}
void blindSearch() {
  if(digitalRead(StartMod)) {
    forwardRamp(250, 10, 10);
  }
  else
    stop();

  // if(analogRead(A0) < 100)
  //   lineRightt();
  // if(analogRead(A1) < 100)
  //   lineLeftt();
  // else
  //   forward(55);
}
void fight() {
  if(analogRead(A0) < 100)
    lineRightt();
  if(analogRead(A1) < 100)
    lineLeftt();
  if(digitalRead(LSensor) && digitalRead(RSensor))
    forward(255);
  else if (digitalRead(Rside)) {
    rotateRight(240); // Use rotateRight
    delay(60);
  }
  else if (digitalRead(Lside)) {
    rotateLeft(240);  // Use rotateLeft
    delay(60);
  }
  else if (digitalRead(RSensor))
    turnRight(240); // Use rotateRight
  else if (digitalRead(LSensor))
    turnLeft(240);  // Use rotateLeft
  else
    forward(53); // Or forward(0) if you want it to stop by default
}
void start() {
 if(digitalRead(StartMod)) {
    if(analogRead(A0) < 100)
        lineRightt();
      if(analogRead(A1) < 100)
        lineLeftt();
      if(digitalRead(LSensor) && digitalRead(RSensor))
        forward(255);
      else if (digitalRead(Rside)) {
        rotateRight(240); // Use rotateRight
        delay(60);
      }
      else if (digitalRead(Lside)) {
        rotateLeft(240);  // Use rotateLeft
        delay(60);
      }
      else if (digitalRead(RSensor))
        turnRight(240); // Use rotateRight
      else if (digitalRead(LSensor))
        turnLeft(240);  // Use rotateLeft
      else
        forward(63); // Or forward(0) if you want it to stop by defaul
 }
 else
   forward(0);
}
void lineRightt() {
  back(140);
  delay(180);
  rotateRight(130);
  delay(100);
  forward(0);
}
void lineLeftt() {
  back(140);
  delay(180);
  rotateLeft(120);
  delay(100);
  forward(0);
}
void stop() {
  analogWrite(Rpos, 0);
  analogWrite(Rneg, 0);
  analogWrite(Lpos, 0);
  analogWrite(Lneg, 0);
}
void forward(double speed) {
  analogWrite(Rpos, speed);
  analogWrite(Rneg, 0);
  analogWrite(Lpos, speed);
  analogWrite(Lneg, 0);
}
void forwardRamp(double targetSpeed, int rampStep, int rampDelay) {
  for (int currentSpeed = 0; currentSpeed <= targetSpeed; currentSpeed += rampStep) {
    analogWrite(Rpos, currentSpeed);
    analogWrite(Rneg, 0);
    analogWrite(Lpos, currentSpeed);
    analogWrite(Lneg, 0);

    delay(rampDelay); // Control how fast it ramps up
  }
}
void back(double speed) {
  analogWrite(Rpos, 0);
  analogWrite(Rneg, speed);
  analogWrite(Lpos, 0);
  analogWrite(Lneg, speed);
}
void rotateRight(double speed) {
  analogWrite(Rpos, 0);
  analogWrite(Rneg, speed);
  analogWrite(Lpos, speed);
  analogWrite(Lneg, 0);
}
void rotateLeft(double speed) {
  analogWrite(Rpos, speed);
  analogWrite(Rneg, 0);
  analogWrite(Lpos, 0);
  analogWrite(Lneg, speed);
}
void turnRight(double speed) {
  analogWrite(Rpos, 0);
  analogWrite(Rneg, 0);
  analogWrite(Lpos, speed);
  analogWrite(Lneg, 0);
}
void turnLeft(double speed) {
  analogWrite(Rpos, speed);
  analogWrite(Rneg, 0);
  analogWrite(Lpos, 0);
  analogWrite(Lneg, 0);
}