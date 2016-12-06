long duration;
float cm, meters;

bool isWallPresent(int trig, int echo)
{
  // Wall is at distance 1 meter from left edge of grid
  if (getAvgDistance(10, trig, echo) < 1.0) {
    return true;
  }
  else {
    return false;    
  }
}



// getDistance returns a number in meters
float getDistance(int trig,int echo)
{
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echo, INPUT);
  duration = pulseIn(echo, HIGH);
  
  // convert the time into a distance
  cm = 0.5 * duration / 29.1;
  meters = cm / 100.0;
  //sendf(&rf, "Detected distance of ", meters);
  
  return meters;
  Serial.println();
  delay(250);
}

float getAvgDistance(int count, int trig, int echo) {
  float total = 0;
  for (int i = 0; i < count; i++) {
    total += getDistance(trig, echo);
    delay(100);
  }

  return total / count;
}

