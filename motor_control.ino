//motor_control.ino
//Authors: Bennett Blitz, Tom Condrom
//ENES100-0602

//Description: Operates the motor controller logic on the lowest level

const float PWM_MAX = 255;
const float PWM_MIN = -255;

//Set directional PWM for motor (operates logic)
void setMotorPWM(int motor, int pwm) {
  int in1 = 0,
      in2 = 0;
  pwm = constrain(pwm, PWM_MIN, PWM_MAX);

  //Set direction
  if (pwm < 0) {
    in1 = 1;
  }
  if (pwm > 0) {
    in2 = 1;
  }
  
  digitalWrite(motorPin[motor][CTRL_IN1], in1);
  digitalWrite(motorPin[motor][CTRL_IN2], in2);

  //Set PWM if motor has a PWM pin
  if (motorPin[motor][CTRL_PWM] >= 0)
    digitalWrite(motorPin[motor][CTRL_PWM], pwm);
}


//Stops motors by deactivating logic pins
void stopMotorSoft(int motor) {
  setMotorPWM(motor, 0);
}

