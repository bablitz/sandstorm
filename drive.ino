//#include <dfr_tank.h>


const float PWM_MAX = 255;
const float PWM_MIN = -256;

//DFRTank tank;


void setSpeedRight(float pwm) {
  //TODO: Add code to set motor speed within proper range
}

void setSpeedLeft(float pwm) {
  //TODO: Add code to set motor speed within proper range
}

void drive(float left, float right) {
  setSpeedLeft(left);
  setSpeedRight(right);
}

void driveForward(float pwm) {
  drive(pwm, pwm);
}

void turnRight(float pwm) {
  drive(pwm, -pwm);
}

void driveStop() {
  drive(0, 0);
}

