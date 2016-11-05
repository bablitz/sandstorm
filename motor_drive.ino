void drive(float left, float right) {
  //Set motor to power with constraints
  //setMotorPWM(M_LEFT, left);
  //setMotorPWM(M_RIGHT, right);
  tank.setLeftMotorPWM(constrain(left, PWM_MIN, PWM_MAX));
  tank.setRightMotorPWM(constrain(right, PWM_MIN, PWM_MAX));
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
