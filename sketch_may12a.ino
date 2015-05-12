#include <Servo.h> 
 
Servo myservo;
Servo myservoToast;

long lastTopMovement = 0;
int goalTopPosition;
int goalTopSpeed;
int currentTopPosition;
const int topAngle = 75;

int pos = 0;


void setup() {
  // put your setup code here, to run once:
  currentTopPosition = 0;
  myservo.attach(9);
  myservoToast.attach(10);
  myservo.write(currentTopPosition);
  myservoToast.write(0);
  goalTopPosition = getRandomTopPosition();
  goalTopSpeed = getRandomTopSpeed();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(goalTopPosition != currentTopPosition && millis() - lastTopMovement > goalTopSpeed) {
    moveTop();
  } else if (millis() - lastTopMovement > 2000) {
    goalTopPosition = getRandomTopPosition();
    goalTopSpeed = getRandomTopSpeed();
  }
  
  // below is just for testing the second servo:
  for(pos = 0; pos <= 60; pos += 1) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservoToast.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(50);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 60; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservoToast.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(50);                       // waits 15ms for the servo to reach the position 
  }
  
  
}

void moveTop() {
  currentTopPosition = currentTopPosition + (goalTopPosition - currentTopPosition)/abs(goalTopPosition - currentTopPosition);
  myservo.write(currentTopPosition);
  lastTopMovement = millis();
}

int getRandomTopPosition() {
  return random(5,topAngle);
}

int getRandomTopSpeed() {
  int randomNum = random(0,20);
  if(abs(goalTopPosition - randomNum) < 10) {
    randomNum = goalTopPosition; // just use this opportunity to "wait"
    lastTopMovement = millis();
  } else if (goalTopPosition - currentTopPosition > 25) {
    randomNum = 25;
  }
  return randomNum;
}
