void taskGeneral() {
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

