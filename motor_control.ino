
void setMotorPWM(int motor, int pwm) {
  int in1 = 0,
      in2 = 0;
  if (pwm < 0) {
    in1 = 1;
  }
  if (pwm > 0) {
    in2 = 1;
  }
  digitalWrite(motorPin[motor][CTRL_IN1], in1);
  digitalWrite(motorPin[motor][CTRL_IN2], in2);
  digitalWrite(motorPin[motor][CTRL_PWM], pwm);
}

void stopMotorSoft(int motor) {
  setMotorPWM(motor, 0);
}

void stopMotorHard(int motor) {
  digitalWrite(motorPin[motor][CTRL_IN1], 1);
  digitalWrite(motorPin[motor][CTRL_IN2], 0);
  digitalWrite(motorPin[motor][CTRL_PWM], 0);
}

