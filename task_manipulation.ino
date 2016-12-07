void taskManipulation() {
  //Adjust orientation to face obstacle

//  float avgDist = 3.0;
//  short int i = 0;
//  short int j = 1;
//  avgDist = getAvgDistance(10, PIN_TRIGR, PIN_ECHOR);
//  while(avgDist > 0.3) {
//    //turnToNode(800.0F, getRotationError(2.3F, 0.6F));
//    turnLeft(j * 255);
//    delay(200);
//    stopMotors();
//    delay(400);
//    avgDist = getAvgDistance(10, PIN_TRIGR, PIN_ECHOR);
//    //Serial.println(avgDist);
//    i += j;
//    if ( i >= 7) j = -1;
//    if ( i <= -7) j = 1;
//  }
  

  //Drive forward until --> debris detected or time out
  driveForward(255);
  delay(5000);
  stopMotors();
  //Debris not detected?
  while (getAvgDistance(10, PIN_TRIGR, PIN_ECHOR) > 0.1) {
    driveForward(-255);
    delay(4000);
    stopMotors();
    turnToNode(300.0F, getRotationError(2.3F, 0.6F));
    driveForward(255);
    delay(4000);
    stopMotors();
    
  }
    //Drive back
    //Reorient
    //Drive forward

  //Lift
  raiseLift(LIFT_TIME);

  //Transmit material
  int total = 0;
  for (int i = 0; i < 10; i++) {
    total += analogRead(PIN_CONDUCT);
  }
  if (total / 10 > 4) {
    sendf(&rf, "-(STEEL)-");
  }
  else {
    sendf(&rf, "-(COPPER)-");
  }
}
