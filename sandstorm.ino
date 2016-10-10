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

//The following are multiplied by the current error to determine
//  motor power, acting as a "gain" a pseudo-pid approach
const float rotKp = 300, //Rotational porportionality constant
            linKp = 1000; //Linear porportionality constant

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

void turnToNode(float xNode, float yNode, float xPrev, float yPrev, float margin) {
  
  //Calculate the desired turn angle
  float thetaTarget = atan((yNode - yPrev) / (xNode - xPrev));
  
  //Set motor to power proportional to error with constraints
  float errorTheta = getRotationError(thetaTarget);
  tank.setLeftMotorPWM(constrain(rotKp * errorTheta, -255, 255));
  tank.setRightMotorPWM(constrain(-rotKp * errorTheta, -255, 255));
  
  //Turn to target while error is not within margin
  while (abs(getRotationError(thetaTarget)) >= margin) {
    delay(10);
  }
  
  //Reset motor power to zero
  tank.setLeftMotorPWM(0);
  tank.setRightMotorPWM(0);
}

void driveToNode(float xNode, float yNode, float xPrev, float yPrev, float margin) {

  //Calculate the absolute distance to target (vector length)
  float distTarget = sqrt(pow(xNode - xPrev, 2) + pow(yNode - yPrev, 2));
  
  //Set motor to power proportional to error with constraints
  float errorLine = getLinearError(distTarget, xPrev, yPrev);
  tank.setLeftMotorPWM(constrain(linKp * errorLine, -255, 255));
  tank.setRightMotorPWM(constrain(linKp * errorLine, -255, 255));
  
  //Drive to target while error is not within margin
  while (getLinearError(distTarget, xPrev, yPrev) >= margin) {
    delay(10);
  }
  
  //Reset motor power to zero
  tank.setLeftMotorPWM(0);
  tank.setRightMotorPWM(0);
}

float getLinearError(float distTarget, float xPrev, float yPrev) {

  updateMarker();
  
  //TODO: add function to account for height of scanned image
  
  sendf(&rf, "- ~ x: ", marker.x);
  sendf(&rf, "- ~ y: ", marker.y);
  
  //Calculate linear error from target node
  float errorLine = distTarget - sqrt(pow(marker.x - xPrev, 2) + 
                                      pow(marker.y - yPrev, 2));
  sendf(&rf, "- ~ Linear Error: ", errorLine);
  
  return errorLine;
  
}

float getRotationError(float thetaTarget) {
  
  updateMarker();
  
  //Get current orientation from RF readings (TODO: try finding avg)
  
  sendf(&rf, "-- ~ Theta: ", marker.theta);
  
  //Calculate rotational error
  float errorTheta = thetaTarget - marker.theta;
  sendf(&rf, "-- ~ Theta Error: ", errorTheta);

  return errorTheta;

}

void updateMarker() {
  
  while (!rf.receiveMarker(&marker, MARKER)) {
    sendf(&rf, "Failed to receive marker");
  }
  
  
}
