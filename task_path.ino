//task_path.ino
//Authors: Bennett Blitz, Tom Condrom
//ENES100-0602

//Description: Navigation algorithm, taskPathing is the main function

//Manages the pathing algorithm
void taskPathing() {
  //Move to wall bottom
  followPath(wallBottom, WALL_BOTTOM);
  sendf(&rf, "***REACHED WALL BOTTOM***");
  
  //rotate to 0 theta
  taskTurn(E_ROT, 0);
  
  //detected obstacle?
  if (isWallPresent(PIN_TRIGR, PIN_ECHOR)) {
    sendf(&rf, "***OBSTACLE DETECTED***");
    //yes - move around wall to destination
    followPath(aroundObstacle, AROUND_OBSTACLE);
  } else {
    sendf(&rf, "***OBSTACLE NOT DETECTED***");
    //no - move past wall to destination
    followPath(throughObstacle, THROUGH_OBSTACLE);
  }
  sendf(&rf, "***REACHED MATERIAL SITE***");
  //lift obstacle
  //transmit material/mass
}

//Follow a given path with <pathLength> nodes
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

// Repeatedly turn to the specified node in path within a margin of error (in rads)
void taskTurn(float margin, float path[][3], int node) {
  float rotationError = getRotationError(path[node][X], path[node][Y]);
  while ((rotationError >= margin || rotationError <= -margin)) {
    
    //Execute turn
    sendf(&rf, "--Starting Turn with error of ", rotationError);
    turnToNode(TURN_TIME, rotationError);

    //Update rotation error
    rotationError = getRotationError(path[node][X], path[node][Y]);
  }
}

//Repeatedly turn to the specified target angle within a margin of error (in rads)
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

