/**
 * @file motor-angular-rate.ino
 * @author Joshua Marshall (joshua.marshall@queensu.ca)
 * @brief Arduino program to estimate motor speed from encoder.
 * @version 2.1
 * @date 2022-12-09
 *
 * @copyright Copyright (c) 2021-2022
 *
 */

// Wheel PWM pin (must be a PWM pin)
int EA = 6;
int EB = 10;

// Wheel direction digital pins for right wheel
int I1 = 7;
int I2 = 5;
int I3 = 12;
int I4 = 11;

// Motor PWM command variable [0-255]
byte u = 0;
byte n = 0;

// left wheel encoder digital pins
const byte SIGNAL_A = 3;
const byte SIGNAL_B = 4;

// left wheel encoder digital pins
const byte SIGNAL_AR = 9;
const byte SIGNAL_BR = 8;

// Encoder ticks per (motor) revolution (TPR)
const int TPR = 3000;

// Wheel radius [m]
const double RHO = 0.0625;

// Counter to keep track of encoder ticks [integer]
volatile long encoder_ticks = 0;
volatile long encoder_ticksr = 0;

// Variable to store estimated angular rate of left wheel [rad/s]
double omega_L = 0.0;
double omega_LR = 0.0;

// Sampling interval for measurements in milliseconds
const int T = 1000;

// Counters for milliseconds during interval
long t_now = 0;
long t_last = 0;

// This function is called when SIGNAL_A goes HIGH when clockwise
void decodeEncoderTicks()
{
    if (digitalRead(SIGNAL_B) == LOW)
    {
        // SIGNAL_A leads SIGNAL_B, so count one way
        encoder_ticks--;
    }
    else
    {
        // SIGNAL_B leads SIGNAL_A, so count the other way
        encoder_ticks++;
    }

    //for other wheel
    if (digitalRead(SIGNAL_BR) == LOW)
    {
        encoder_ticksr--;
    }
    else
    {
        encoder_ticksr++;
    }

}

void setup()
{
    // Open the serial port at 9600 bps
    Serial.begin(9600);

    // Set the pin modes for the motor driver
    pinMode(EA, OUTPUT);
    pinMode(I1, OUTPUT);
    pinMode(I2, OUTPUT);

    pinMode(EB, OUTPUT);
    pinMode(I3, OUTPUT);
    pinMode(I4, OUTPUT);

    // Set the pin modes for the encoders right side
    pinMode(SIGNAL_A, INPUT);
    pinMode(SIGNAL_B, INPUT);

    // left side pin modes
    pinMode(SIGNAL_AR, INPUT);
    pinMode(SIGNAL_BR, INPUT);

    // Every time the pin goes high, this is a pulse
    attachInterrupt( digitalPinToInterrupt(SIGNAL_A), decodeEncoderTicks, RISING);

    // for other wheel
    attachInterrupt( digitalPinToInterrupt(SIGNAL_AR), decodeEncoderTicks, RISING);

    // Print a message
    Serial.print("Program initialized.");
    Serial.print("\n");
}

void loop()
{
    // Get the elapsed time [ms]
    t_now = millis();

    if (t_now - t_last >= T)
    {
        // Estimate the rotational speed [rad/s]
        omega_L = 2.0 * PI * ((double)encoder_ticks / (double)TPR) * 1000.0 / (double)(t_now - t_last);

        //for the other wheel?
        omega_LR = 2.0 * PI * ((double)encoder_ticksr / (double)TPR) * 1000.0 / (double)(t_now - t_last);

        // Print some stuff to the serial monitor
        Serial.print("Encoder ticks: ");
        Serial.print(encoder_ticks);
        Serial.print("\t");
        Serial.print("Estimated right wheel speed: ");
        Serial.print(omega_L);
        Serial.print(" rad/s");

        Serial.print("\t");

        Serial.print("Encoder ticks B: ");
        Serial.print(encoder_ticksr);
        Serial.print("\t");
        Serial.print("Estimated left wheel speed: ");
        Serial.print(omega_LR);
        Serial.print(" rad/s");

        Serial.print("\n");

        // Record the current time [ms]
        t_last = t_now;

        // Reset the encoder ticks counter
        encoder_ticks = 0;

        //reset the other wheel
        encoder_ticksr = 0;
    }

    //Serial.println("reached!");
    // Set the wheel motor PWM command [0-255]
    u = 180;
    n = 180;

    // Select a direction right
    digitalWrite(I1, LOW);
    digitalWrite(I2, HIGH);

    // select a direction left
    digitalWrite(I3, HIGH);
    digitalWrite(I4, LOW);

    // PWM command to the motor driver
    analogWrite(EA, u);
    analogWrite(EB, n);
}
