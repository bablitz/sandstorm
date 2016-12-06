void taskManipulation() {
  //Adjust orientation to face obstacle
//  while(true) {
//    sendf(&rf, "Distance: ", getAvgDistance(10, PIN_TRIGR, PIN_ECHOR));
//    delay(500);
//  }
  float avgDist = 3.0;
  do {
    turnToNode(800.0F, getRotationError(2.3F, 0.6F));
    stopMotors();
    avgDist = getAvgDistance(10, PIN_TRIGR, PIN_ECHOR);
  } while(avgDist < 1.0);
  

  //Drive forward until --> debris detected or time out
  driveForward(255);
  delay(avgDist * 20000);
  stopMotors();
  //Debris not detected?
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
