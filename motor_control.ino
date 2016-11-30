const float PWM_MAX = 255;
const float PWM_MIN = -255;

void setMotorPWM(int motor, int pwm) {
  int in1 = 0,
      in2 = 0;
  pwm = constrain(pwm, PWM_MIN, PWM_MAX);
  
  if (pwm < 0) {
    in1 = 1;
  }
  if (pwm > 0) {
    in2 = 1;
  }
  
  digitalWrite(motorPin[motor][CTRL_IN1], in1);
  digitalWrite(motorPin[motor][CTRL_IN2], in2);

  if (motorPin[motor][CTRL_PWM] >= 0)
    digitalWrite(motorPin[motor][CTRL_PWM], pwm);
}

void stopMotorSoft(int motor) {
  setMotorPWM(motor, 0);
}

//NOT NECESSARY FOR OUR MOTORS
//void stopMotorHard(int motor) {
//  digitalWrite(motorPin[motor][CTRL_IN1], 1);
//  digitalWrite(motorPin[motor][CTRL_IN2], 0);
//  if (motorPin[motor][CTRL_PWM] >= 0)
//    digitalWrite(motorPin[motor][CTRL_PWM], 0);
//}

