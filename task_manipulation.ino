//task_manipulation.ino
//Authors: Bennett Blitz, Tom Condrom
//ENES100-0602

//Description: Code that operates the debris manipulation/transmission algorithm

void taskManipulation() {

  //Drive forward until --> debris detected or time out
  driveForward(255);
  delay(5000);
  stopMotors();
  //Debris not detected?
  int attempts = 0;
  while (getAvgDistance(10, PIN_TRIGR, PIN_ECHOR) > 0.1 && attempts < 5) {
    driveForward(-255);
    delay(4000 + attempts * 500);
    stopMotors();
    turnToNode(300.0F, getRotationError(2.3F, 0.6F));
    driveForward(255);
    delay(4000 + attempts * 500);
    stopMotors();
    attempts++;
    
  }

  //Lift
  if (attempts < 5)
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
