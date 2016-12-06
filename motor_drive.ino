//motor_drive.ino
//Authors: Bennett Blitz, Tom Condrom
//ENES100-0602

//Description: Uses motor_control.ino for basic drive/lift functions

void drive(float left, float right) {
  //Set motor to power with constraints
  setMotorPWM(M_LEFT, left);
  setMotorPWM(M_RIGHT, right);
}

void driveForward(float pwm) {
  drive(pwm, pwm);
}

void turnLeft(float pwm) {
  drive(-pwm, pwm);
}

void stopMotors() {
  drive(0, 0);
}

void turnToNode(float duration, float rotationError) {
  
  //Set motor to power proportional to error
  turnLeft(ROT_KP * rotationError);
  
  //Turn to target for set amount of time
  delay(duration);
  
  //Reset motor power to zero
  stopMotors();
}

void driveToNode(float duration, float linearError) {

  //Set motor to power proportional to error
  driveForward(LIN_KP * linearError);

  //Drive to target for set amount of time
  delay(duration);
  
  //Reset motor power to zero
  stopMotors();
}

void raiseLift(int liftTime) {
  setMotorPWM(M_LIFT, 255);
  delay(liftTime);
  setMotorPWM(M_LIFT, 0);
}
