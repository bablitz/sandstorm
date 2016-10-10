

void turnToNode(float xNode, float yNode, float xPrev, float yPrev, float margin) {
  
  //Calculate the desired turn angle
  float thetaTarget = atan((yNode - yPrev) / (xNode - xPrev));
  
  //Set motor to power proportional to error with constraints
  float errorTheta = getRotationError(thetaTarget);
  tank.setLeftMotorPWM(constrain(ROT_KP * errorTheta, -255, 255));
  tank.setRightMotorPWM(constrain(-ROT_KP * errorTheta, -255, 255));
  
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
  tank.setLeftMotorPWM(constrain(LIN_KP * errorLine, -255, 255));
  tank.setRightMotorPWM(constrain(LIN_KP * errorLine, -255, 255));
  
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
