
float getLinearError(float xNode, float yNode) {

  updateMarker();
  
  //TODO: add function to account for height of scanned image
  
  sendf(&rf, "- ~ x: ", marker.x);
  sendf(&rf, "- ~ y: ", marker.y);
  
  //Calculate linear error from target node
  float errorLine = sqrt(pow(xNode - marker.x, 2) + 
                         pow(yNode - marker.y, 2));
  sendf(&rf, "- ~ Linear Error: ", errorLine);
  
  return errorLine;
  
}

float getRotationError(float xNode, float yNode) {
  
  updateMarker();

  //Calculate target angle
  float thetaTarget = atan((yNode - marker.y) / 
                           (xNode - marker.x));
  
  //Get current orientation from RF readings (TODO: try finding avg)
  
  sendf(&rf, "-- ~ Theta: ", marker.theta);
  
  //Calculate rotational error
  float errorTheta = thetaTarget - marker.theta;
  sendf(&rf, "-- ~ Theta Error: ", errorTheta);

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
