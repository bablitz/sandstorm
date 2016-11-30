void raiseLift(int liftTime) {
  setMotorPWM(M_LIFT, 255);
  delay(liftTime);
  setMotorPWM(M_LIFT, 0);
}

