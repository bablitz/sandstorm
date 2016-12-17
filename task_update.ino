//task_update.ino
//Authors: Bennett Blitz, Tom Condrom
//ENES100-0602

//Description: Code involving receiving data from rf and error calculation

//Get the positive distance from the given node coordinates
float getLinearError(float xNode, float yNode) {

  updateMarker();
  
  //Calculate linear error from target node
  float errorLine = sqrt(pow(xNode - marker.x, 2) + 
                         pow(yNode - marker.y, 2));
  sendf(&rf, "- ~ Linear Error: ", errorLine);
  
  return errorLine;
  
}

//Gets rotation error from node; requires update
float getRotationError(float xNode, float yNode) {
  
  updateMarker();

  //Calculate target angle
  float thetaTarget = atan2((yNode - marker.y), 
                            (xNode - marker.x));
  
  return getRotationError(thetaTarget, false);

}

//Gets rotation error from target rotation
float getRotationError(float target) {

  return getRotationError(target, true);
}

//Get rotation error from a target angle
//  if refreshMarker flag is true, updateMarker is called
float getRotationError(float target, bool refreshMarker) {

  if (refreshMarker) updateMarker();
  
  //Calculate rotational error
  float errorTheta = target - marker.theta;

  //Adjust error value to be withing -PI and PI
  if (errorTheta > PI)
    errorTheta -= 2 * PI;
  if (errorTheta < -PI)
    errorTheta += 2 * PI;

  return errorTheta;
}

//Update maker data after a constant delay
void updateMarker() {

  //Account for latency of RF sensor
  delay(RF_LATENCY);
  
  while (!rf.receiveMarker(&marker, MARKER)) {
    sendf(&rf, "Failed to receive marker");
    delay(100);
  }
}
