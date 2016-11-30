
float getLinearError(float xNode, float yNode) {

  updateMarker();
  
  //TODO: add function to account for height of scanned image
  
  //sendf(&rf, "- ~ x: ", marker.x);
  //sendf(&rf, "- ~ y: ", marker.y);
  
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
  //sendf(&rf, "- ~ xNode: ", xNode);
  //sendf(&rf, "- ~ yNode: ", yNode);
  //sendf(&rf, "- ~ Target Angle: ", thetaTarget);
  
  return getRotationError(thetaTarget, false);

}

//Gets rotation error from target rotation
float getRotationError(float target) {

  return getRotationError(target, true);
}

float getRotationError(float target, bool refreshMarker) {

  if (refreshMarker) updateMarker();
  
  //sendf(&rf, "-- ~ Target Angle: ", target);
  
  //Calculate rotational error
  float errorTheta = target - marker.theta;

  //Adjust error value to be withing -PI and PI
  if (errorTheta > PI)
    errorTheta -= 2 * PI;
  if (errorTheta < -PI)
    errorTheta += 2 * PI;
  
  //sendf(&rf, "-- ~ Theta Error: ", errorTheta);

  return errorTheta;
}

void updateMarker() {

  //Account for latency of RF sensor
  delay(RF_LATENCY);
  
  while (!rf.receiveMarker(&marker, MARKER)) {
    sendf(&rf, "Failed to receive marker");
    delay(100);
  }
}
