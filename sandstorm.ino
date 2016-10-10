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

#define PATH_LENGTH 3 //Number of nodes in path
#define X 0 //The x coordinate of a node
#define Y 1 //The y coordinate of a node
#define E 2 //The margin of linear error when driving to a node

#define MAX_TURNS 2 //Maximum number of times osv corrects its rotation
#define MAX_DRIVE 1 //Maximum number of times osv corrects its position

#define MARKER 11 //Number of RF Marker Board

//path: a list of nodes for the robot to follow (x, y, error margin)
//                               X     Y     E
float path[PATH_LENGTH][3] = {{ 2.3,  0.6, 0.10 },
                              { 2.3,  0.6, 0.10 },
                              { 2.3,  0.6, 0.10 }};

const float rotE = 0.2; //Margin of error for all rotations


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

void followPath(float path[][3], int pathLength) {
  
  //Set starting node
  updateMarker();
  float xPrev = marker.x;
  float yPrev = marker.y;
  
  //Repeat process to travel to each node
  for (int node = 0; node < pathLength; node++) {
    
    //Repeat turn/drive proces MAX_DRIVE times
    sendf(&rf, "Now traveling to Node ", node, "...");
    for (int i = 0; i < MAX_DRIVE; i++) {
      
      //Repeat turn MAX_TURN times
      for (int j = 0; j < MAX_TURNS; j++) {
        //Exexute turn
        sendf(&rf, "--Starting Turn ", j, "...");
        turnToNode(path[node][X], path[node][Y], xPrev, yPrev, rotE);
      }

      //Execute drive
      sendf(&rf, "-Starting Drive ", i, "...");
      driveToNode(path[node][X], path[node][Y], xPrev, yPrev, path[node][E]);

      //Reset starting node
      updateMarker();
      xPrev = marker.x;
      yPrev = marker.y;
    }
  }

  sendf(&rf, "OSV has reached its final destination!");
}

void updateMarker() {
  
  while (!rf.receiveMarker(&marker, MARKER)) {
    sendf(&rf, "Failed to receive marker");
  }
}
