//Sandstorm.ino
//Authors: Bennett Blitz, Tom Condrom
//ENES100-0602

#include <dfr_tank.h>
#include <SoftwareSerial.h>
#include "enes100.h"
#include "rf_util.h"

//---------------------------Definitions--------------------------

//Pin Definitions
#define PIN_RX 8
#define PIN_TX 9

#define MARKER 18 //Number of RF Marker Board

#define PATH_LENGTH 3 //Number of nodes in path
#define X 0 //The x coordinate of a node
#define Y 1 //The y coordinate of a node
#define E 2 //The margin of linear error when driving to a node

#define MAX_TURNS 2 //Maximum number of times osv corrects its rotation
#define MAX_DRIVE 1 //Maximum number of times osv corrects its position

//path: a list of nodes for the robot to follow (x, y, error margin)
//                               X     Y     E
float path[PATH_LENGTH][3] = {{ 2.3,  0.6, 0.10 },
                              { 2.3,  0.6, 0.10 },
                              { 2.3,  0.6, 0.10 }};

const float E_ROT = 0.3; //Margin of error for all rotations

//The following are multiplied by the current error to determine
//  motor power, acting as a "gain" a pseudo-pid approach
const float ROT_KP = 300, //Rotational porportionality constant
            LIN_KP = 1000; //Linear porportionality constant
            
const float DRIVE_TIME = 1000, //Amount of time(ms)the robot will drive
            TURN_TIME = 500; //Amount of time(ms)the robot will turn

const float RF_LATENCY = 1500; //Approximate latency of marker receiver
            
SoftwareSerial sSerial(PIN_RX, PIN_TX);
enes100::RfClient<SoftwareSerial> rf(&sSerial);
enes100::Marker marker;

DFRTank tank;

//----------------------------------------------------------------

void setup() {
  
  sSerial.begin(9600);
  Serial.begin(9600);
  pinMode(PIN_RX, INPUT);
  pinMode(PIN_TX, OUTPUT);
  
  delay(1000);
  
  rf.resetServer();

  sendf(&rf, "Team Sandstorm is Connected");
  Serial.println("Team Sandstorm is Connected");

  delay(500);
  
  followPath(path, PATH_LENGTH);
}

void loop() {}
