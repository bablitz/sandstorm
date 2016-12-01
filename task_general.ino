void taskGeneral() {
  //Move to wall bottom
  followPath(wallBottom, WALL_BOTTOM);
  sendf(&rf, "***REACHED WALL BOTTOM***");
  
  //rotate to 0 theta
  taskTurn(E_ROT, 0);
  
  //detected obstacle?
  if (isWallPresent(PIN_TRIGL, PIN_ECHOL)) {
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

void taskManipulation() {
  //Adjust orientation to face obstacle
  while(!isWallPresent(PIN_TRIGL, PIN_ECHOL)) {
    turnLeft(255);
    delay(750);
    stopMotors();
  }
  turnLeft(-255);
  delay(750);
  
  

  //Drive forward until --> debris detected or time out

  //Debris not detected?
    //Drive back
    //Reorient
    //Drive forward

  //Lift

  //Transmit material
  
  
  driveForward(255);
  delay(5000);
  stopMotors();
  raiseLift(LIFT_TIME);
}

