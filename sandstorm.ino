
//Sandstorm.ino
//Authors: Bennett Blitz, Tom Condrom
//ENES100-0602

#include <dfr_tank.h>
#include <SoftwareSerial.h>
#include <SparkFunISL29125.h>
#include "enes100.h"
#include "rf_util.h"

//---------------------------Definitions--------------------------

//Pin Definitions
#define PIN_RX 8
#define PIN_TX 9
#define PIN_TRIG1 11
#define PIN_ECHO1 10

#define MARKER 104 //Number of RF Marker Board

#define M_LEFT 0
#define M_RIGHT 1
#define M_LIFT 2
#define M_COUNT 3
#define CTRL_IN1 0
#define CTRL_IN2 1
#define CTRL_PWM 2
//motorPin: a list for pins for each motor
//                          IN1  IN2 PWM
int motorPin[M_COUNT][3] = {{7,   8,  9}, // Left Motor
                            {12, 11, 10}, // Right Motor
                            {13,  6,  5}};// Lift Motor

#define X 0 //The x coordinate of a node
#define Y 1 //The y coordinate of a node
#define E 2 //The margin of linear error when driving to a node
//path: a list of nodes for the robot to follow (x, y, error margin)
//                                                X     Y     E
#define WALL_BOTTOM 1 //Number of nodes in path
float wallBottom[WALL_BOTTOM][3]          = {{ 1.50,  0.31, 0.13 }};
#define AROUND_OBSTACLE 4 //Number of nodes in path
float aroundObstacle[AROUND_OBSTACLE][3]    = {{ 1.50,  1.69, 0.13 },
                                               { 2.50,  1.69, 0.13 },
                                               { 2.50,  0.60, 0.13 },
                                               { 3.30,  0.60, 0.15 }};
#define THROUGH_OBSTACLE 2 //Number of nodes in path
float throughObstacle[THROUGH_OBSTACLE][3]  = {{ 2.50,  0.31, 0.15 },
                                               { 3.30,  0.60, 0.15 }};

const float E_ROT = 0.3; //Margin of error for all rotations

//The following are multiplied by the current error to determine
//  motor power, acting as a "gain" a pseudo-pid approach
const float ROT_KP = 300, //Rotational porportionality constant
            LIN_KP = 1000; //Linear porportionality constant
            
const float DRIVE_TIME = 750, //Amount of time(ms)the robot will drive
            TURN_TIME = 500; //Amount of time(ms)the robot will turn

const float RF_LATENCY = 1000; //Approximate latency of marker receiver
            
SoftwareSerial sSerial(PIN_RX, PIN_TX);
enes100::RfClient<SoftwareSerial> rf(&sSerial);
enes100::Marker marker;

DFRTank tank;

SFE_ISL29125 rgb;

//----------------------------------------------------------------

void setup() {
  
  sSerial.begin(9600);
  Serial.begin(9600);
  pinMode(PIN_RX, INPUT);
  pinMode(PIN_TX, OUTPUT);
  pinMode(PIN_TRIG1, OUTPUT);
  pinMode(PIN_ECHO1, INPUT);
  
  delay(1000);
  
  rf.resetServer();

  sendf(&rf, "Team Sandstorm is Connected");
  Serial.println("Team Sandstorm is Connected");

  delay(500);
  
  taskGeneral();
  //rgb.init();
}

void loop() {
  //TEST HERE:

  //unsigned int red = rgb.readRed();
  //Serial.print("Red: "); Serial.println(red);
//  stopMotors();
//  delay(1000);
//  
//  driveForward(-255);
//  delay(1000);
//
//  stopMotors();
//  delay(1000);
//  
//  driveForward(255);
//  delay(5000);
  Serial.println(getAvgDistance(10));
  delay(100);

  
}
