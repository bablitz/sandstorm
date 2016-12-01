/*
 * created by Rui Santos, http://randomnerdtutorials.com
 * 
 * Complete Guide for Ultrasonic Sensor HC-SR04
 *
    Ultrasonic sensor Pins:
        VCC: +5VDC
        Trig : Trigger (INPUT) - Pin11      Might be different hard for me to see on schematic diagram
        Echo: Echo (OUTPUT) - Analog Pin 0
        GND: GND
 */
 
int trigPin = 11;    //Trig - green Jumper
int echoPin = 0;    //Echo - yellow Jumper   (Analog Pin)
long duration;
float cm, meters;

bool isWallPresent()
{
  // Wall is at distance 1 meter from left edge of grid
  if (getAvgDistance(10) < 1.0) {
    return true;
  }
  else {
    return false;    
  }
}



// getDistance returns a number in meters
float getDistance(Pin_Trig, Pin_Echo) {
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(PIN_ECHO, INPUT);
  duration = pulseIn(PIN_ECHO, HIGH);
  
  // convert the time into a distance
  cm = 0.5 * duration / 29.1;
  meters = cm / 100.0;
  //sendf(&rf, "Detected distance of ", meters);
  
  return meters;
  Serial.println();
  delay(250);
}

float getAvgDistance(int count) {
  float total = 0;
  for (int i = 0; i < count; i++) {
    total += getDistance();
    delay(100);
  }

  return total / count;
}

