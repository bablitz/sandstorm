void taskGeneral() {
  //Move to wall bottom
  followPath(wallBottom, WALL_BOTTOM);
  
  //rotate to 0 theta
  taskTurn(E_ROT, 0);
  
  //detected obstacle?
  if (isWallPresent()) {
    //yes - move around wall to destination
    followPath(aroundObstacle, AROUND_OBSTACLE);
  } else {
    //no - move past wall to destination
    followPath(throughObstacle, THROUGH_OBSTACLE);
  }
  //lift obstacle
  //transmit material/mass
}

