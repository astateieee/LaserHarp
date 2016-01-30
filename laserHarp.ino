#include <Stepper.h>
const int laser = 6;

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(324, 12, 11, 10, 9);

void setup() {
  myStepper.setSpeed(80);
  Serial.begin(9600);
  pinMode(laser, OUTPUT);
}

void loop() {
  myStepper.setSpeed(analogRead(A1));
  Serial.println(analogRead(A1));
  
  for(int i = 0; i < 12; i++){
    myStepper.step(2, laser);
  }

  for(int i = 0; i < 12; i++){
    myStepper.step(-2, laser);
  }
}
