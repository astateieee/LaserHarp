#include <Stepper.h>

// Pins
int laser = 13;
int sensor = A5;

// Stepper constants and Variables
const int stepsPerRevolution = 100;
Stepper stepper(stepsPerRevolution, 4, 5, 6, 7);
bool clockwise = 0;
int stepCount = 0;

// Beam Constants
const int START_POSITION = 7;         // Number of steps for position calibration
const int BEAMS = 8;                  // Number of beams
const int STEP_DELAY = 10;            // Time between step and turning on laser
const int LASER_ON_TIME = 7;          // Time between laser on and analog read

// Laser Calibaration Array
int threshold[BEAMS]= {0};

void setup() {
  pinMode(laser, OUTPUT);
  Serial.begin(115200); 
  calibratePosition();
  calibrateThreshold();
}

void loop() {
  
  stepperCounter(); // Step through the total amount of steps
  
  delay(20);
  
  digitalWrite(laser, HIGH);
  delay(10);

  int read = analogRead(sensor);
  Serial.println(read);
  
  if(stepCount == 0){
    stepZERO = read;
  }else{
    stepONE = read;
  }
  
  if(stepCount == 0){
    if(read > threshold){
      if (stepZERO > stepONE){
       MIDImessage(noteON, 100, velocity);
       
      }else if(stepZERO < stepONE){
       MIDImessage(noteON, 80, velocity);
      }
    }else{
      MIDImessage(noteOFF, 80, velocity);
      MIDImessage(noteOFF, 100, velocity);
    }
  }
  
  digitalWrite(laser, LOW);
  delay(5);
  
}

// Position Calibration
void calibratePosition(){
  for(int i = 0; i <= 100; i++){
    stepper.step(1);
    delay(4);
  }
  for(int i = 0; i <= START_POSITION; i++){
    stepper.step(-1);
    delay(10);
  }
  delay(1000);
}

// Boot up
void bootUp(){
  
}

// Light level threshold Calibration
void calibrateThreshold(){
  
}

//send MIDI message
void MIDImessage(int command, int MIDInote, int MIDIvelocity) {
  Serial.write(command);//send note on or note off command 
  Serial.write(MIDInote);//send pitch data
  Serial.write(MIDIvelocity);//send velocity data
}

void stepNext(){
  if(clockwise == 1){
    stepper.step(-1);
    stepCount++;
    if(stepCount > BEAMS){
      clockwise = 0;
    }
  }else{
    stepper.step(1);
    stepCount--;
    if(stepCount < 0){
      clockwise = 1;
    }
  }
}
