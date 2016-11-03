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
long duration, cm, meters;
 
void setup() {
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
bool isWallPresent()
{
   // getDistance returns a number in meters
   // Wall is at distance 1 meter from left edge of grid
   if((getDistance)<1)
   {
    return(true)
   }
   else
   {
      return(false)    
   }
}



long getDistance()
{
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // convert the time into a distance
  cm = (duration/2) / 29.1;
  meters = cm*100;
  
  return(meters);
  Serial.println();
  delay(250);
}

