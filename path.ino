
void followPath(float path[][3], int pathLength) {

  float linearError, rotationError;
  //Repeat process to travel to each node
  for (int node = 0; node < pathLength; node++) {
    
    //Repeat turn/drive proces MAX_DRIVE times
    sendf(&rf, "Now traveling to Node ", node, "...");
    linearError = getLinearError(path[node][X], path[node][Y]);
    while (linearError >= path[node][E]) {
      
      //Repeat turn MAX_TURN times
      rotationError = getRotationError(path[node][X], path[node][Y]);
      while (abs(rotationError) >= E_ROT) {
        
        //Execute turn
        sendf(&rf, "--Starting Turn with error ", rotationError);
        turnToNode(TURN_TIME, rotationError);

        //Update rotation error
        rotationError = getRotationError(path[node][X], path[node][Y]);
      }

      //Execute drive
      sendf(&rf, "-Starting Drive with error ", linearError);
      driveToNode(DRIVE_TIME, linearError);

      //Update linear error
      linearError = getLinearError(path[node][X], path[node][Y]);
      
    }
  }

  sendf(&rf, "OSV has reached its final destination!");
}
