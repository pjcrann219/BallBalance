// Ball on surface control project

#include <stdint.h>       // Used in TouchScreen.h
#include "TouchScreen.h"  // Algorithms for touch screen readings
#include <Servo.h>        // Library to com w/ servos

#define YM A0
#define XP A1
#define YP A2
#define XM A3

#define XCENTER 548
#define YCENTER 563

#define xServoPin 8
#define yServoPin 9

#define ARMRADIUS 17.5 // mm
#define XLENGTH 65 //mm
#define YLENGTH 95 //mm

#define XPotPin A4
#define YPotPin A5

// Initiate servo objects
Servo xServo;
Servo yServo;

// Initiate PID objects
ArduPID xPID;
ArduPID yPID;

// Reference Point
double xSetpoint = 0;
double ySetpoint = 0;

// Measured X/Y pos
double X;
double Y;

// PID constants
double Kpx = 16;
double Kix = 0;
double Kdx = 8;

double Kpy = 16;
double Kiy = 0;
double Kdy = 8;

// Units to cm
double XRES = 1023.0 / 15.75;
double YRES = 1023.0 / 9.25;

// used for PD
int lastT = 0;
double lastX = 0;
double lastY = 0;

// Initiate touchscreeen
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 650);

void setup(void) {
  Serial.begin(9600);
  
  xServo.attach(xServoPin);
  yServo.attach(yServoPin);

}

void loop(void) {
// Get points
  TSPoint p = ts.getPoint();

// If Pressure is in correct range, grab X and Y positions

  if (p.z > 50 && p.z < 1000) {
      // Points to mm
     X = -1 * (p.x - XCENTER) / XRES + 2.0;
     Y = (p.y - YCENTER) / YRES + 1;
  }

// Run custom PID function
   myPID();
  
}

void myPID() {
  // Calculate time change
  int dt = millis() - lastT;
  lastT = millis();
  // Calculate proportinal and derrivative errors
  double errorpX = X - xSetpoint;
  double errordX = (X - lastX) *1000 / dt;
  lastX = X;
  double errorpY = Y - ySetpoint;
  double errordY = (Y - lastY) * 1000 / dt;
  lastY = Y;
  // Calculate PD output
  int angleX = Kpx * errorpX + Kdx * errordX;
  int angleY = Kpy * errorpY + Kdx * errordY;
  // Write output to motor
  xServo.write(90 - angleX);
  yServo.write(90 - angleY);
}
