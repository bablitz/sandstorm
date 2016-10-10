//Sandstorm.ino
//Authors: Bennett Blitz, Tom Condrom
//ENES100-0602

#include <dfr_tank.h>
#include <SoftwareSerial.h>
#include <enes100.h>
#include <enes100_marker.h>
#include <enes100_rf_client.h>
#include <rf_util.h>

//---------------------------Definitions--------------------------

//Pin Definitions
#define PIN_RX 8
#define PIN_TX 9

#define MARKER 11 //Number of RF Marker Board

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

const float E_ROT = 0.2; //Margin of error for all rotations

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

  rf.resetServer();
  sendf(&rf, "Team Sandstorm is Connected");
  Serial.println("Team Sandstorm is Connected");

  delay(1000);
  
  followPath(path, PATH_LENGTH);
}

void loop() {}

void updateMarker() {
  
  while (!rf.receiveMarker(&marker, MARKER)) {
    sendf(&rf, "Failed to receive marker");
  }
}
