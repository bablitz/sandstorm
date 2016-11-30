
void followPath(float path[][3], int pathLength) {

  float linearError;
  //Repeat process to travel to each node
  for (int node = 0; node < pathLength; node++) {
    
    //Repeat turn/drive proces MAX_DRIVE times
    sendf(&rf, "Now traveling to Node ", node, "...");
    linearError = getLinearError(path[node][X], path[node][Y]);
    while (linearError >= path[node][E]) {
      
      //Turn to the next node within margin
      taskTurn(E_ROT, path, node);

      //Execute drive
      sendf(&rf, "-Starting Drive with error of ", linearError);
      driveToNode(DRIVE_TIME, linearError);

      //Update linear error
      linearError = getLinearError(path[node][X], path[node][Y]);
      
    }
  }

  sendf(&rf, "OSV has finished its path of length ", pathLength);
}

void taskTurn(float margin, float path[][3], int node) {
  float rotationError = getRotationError(path[node][X], path[node][Y]);
  while ((rotationError >= margin || rotationError <= -margin)) { //&& (2 * PI - rotationError >= margin || -2 * PI + rotationError <= -margin))  {
    
    //Execute turn
    sendf(&rf, "--Starting Turn with error of ", rotationError);
    turnToNode(TURN_TIME, rotationError);

    //Update rotation error
    rotationError = getRotationError(path[node][X], path[node][Y]);
  }
}

void taskTurn(float margin, float target) {
  float rotationError = getRotationError(target);
  while (rotationError >= margin || rotationError <= -margin) {
    
    //Execute turn
    sendf(&rf, "--Starting Turn with error of ", rotationError);
    turnToNode(TURN_TIME, rotationError);

    //Update rotation error
    rotationError = getRotationError(target);
  }
}

