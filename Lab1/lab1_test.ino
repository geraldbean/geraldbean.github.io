/**
 * @file PWM-motor-control.ino
 * @author Joshua Marshall (joshua.marshall@queensu.ca)
 * @brief Arduino program to drive one wheel motor through a motor driver.
 * @version 2.0
 * @date 2022-12-05
 *
 * @copyright Copyright (c) 2021-2022
 *
 */

 int EA = 6; // Wheel PWM pin (must be a PWM pin)
 int I1 = 7; // Wheel direction digital pin 1
 int I2 = 4; // Wheel direction digital pin 2

int EB = 10;
int I3 = 12;
int I4 = 11;

//right
int u = 220; // A variable for the motor PWM command [0-255]
//left
int n = 220;

bool run_flag = false;

// unsigned long startTime;
// const unsigned long runDuration = 5000;
// bool running = true;

 void setup()
 {
 // Configure digital pins for output
 pinMode(EA, OUTPUT);
 pinMode(I1, OUTPUT);
 pinMode(I2, OUTPUT);

 pinMode(EB, OUTPUT);
 pinMode(I3, OUTPUT);
 pinMode(I4, OUTPUT);

 //startTime = millis();
 }

void loop(){

//to make sure the loop only runs one time
  if (run_flag) return; 
// Set to true to stop running
run_flag = true;

// if (running && millis() - startTime >= runDuration) {
//   analogWrite(EA, 0);
//   analogWrite(EB, 0);
//   running = false;
// } else {

//right
 //I1 HIGH and I2 LOW is forwards 
 //I1 LOW and I2 HIGH is backwards 
 digitalWrite(I1, HIGH);
 digitalWrite(I2, LOW);
   // left
//I3 LOW and I4 HIGH is forwards
//I3 HIGH and I4 LOW is backwards  
 digitalWrite(I3, LOW);
 digitalWrite(I4, HIGH);

 // PWM command to the motor driver
 analogWrite(EA, u);


 // PWM command to the motor driver
 analogWrite(EB, n);


delay(1000);

analogWrite(EA, 0);
analogWrite(EB, 0);


delay(1000);

//right
 //I1 HIGH and I2 LOW is forwards 
 //I1 LOW and I2 HIGH is backwards 
 digitalWrite(I1, LOW);
 digitalWrite(I2, HIGH);
   // left
//I3 LOW and I4 HIGH is forwards
//I3 HIGH and I4 LOW is backwards  
 digitalWrite(I3, HIGH);
 digitalWrite(I4, LOW);

 // PWM command to the motor driver
 analogWrite(EA, u);


 // PWM command to the motor driver
 analogWrite(EB, n);


delay(1000);

 // PWM command to the motor driver
 analogWrite(EA, 0);


 // PWM command to the motor driver
 analogWrite(EB, 0);



}
