// Includes the Servo library
#include <Servo.h>. 
/////the Ultrasonic Sensor to detect the object//////////
// Defines Tirg and Echo pins of the Ultrasonic Sensor
const int trigPin = 10;
const int echoPin = 11;
// Variables for the duration and the distance
long duration;
int distance;
int ObjRedled=2;
int buzz=7;
Servo myServo; // Creates a servo object for controlling the servo motor
Servo myServo2;


/////////////////////////////////////////////////////////////////////
//OPEN GATE FOR CARS
Servo GateServo; 
int GateBuzzer = 9; //connects buzzer to digital pin 12
int GateIr = 3; // connect ir sensor  to digital pin 2
int GateGreenLed = 8;


///////////////////////////////////////

//Gas detection//

int GasYellowLed = 6;
//7
int Gasbuzzer = 5;
int smokeA0 = A5;
// Your threshold value
int sensorThres = 30;

/////////////////////////////////////

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(ObjRedled,OUTPUT);//red led as output
  pinMode(GateGreenLed,OUTPUT);
  pinMode(GasYellowLed,OUTPUT);
  pinMode(buzz,OUTPUT);// buzz as output
  pinMode(GateBuzzer, OUTPUT);// define buzzer(piezo) as a output device
  pinMode(Gasbuzzer, OUTPUT);// define buzzer(piezo) as a output device
  pinMode(GateIr, INPUT); // defines ir sensor as a input device
  
  
  myServo.attach(12); // Defines on which pin is the servo motor attached
  myServo2.attach(4);
  GateServo.attach(13); // attaches the servo to digital pin
  
  
}
void loop() {
 //openGate();
 detectobj();
//gasDetect();
}
// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance(){ 
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;
  return distance;
}

void detectobj(){
  
  // rotates the servo motor from 15 to 165 degrees
  for(int i=0;i<=180;i++){  
  myServo.write(i);
  myServo2.write(i);
  delay(30);
  distance = calculateDistance();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
  
  Serial.print(i); // Sends the current degree into the Serial Port
  Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  Serial.print(distance); // Sends the distance value into the Serial Port
  Serial.print("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  
 if(distance>=2 and distance<=15 and i<=90) {
   myServo2.write(i);
      digitalWrite(ObjRedled, HIGH);//turns off green led
      digitalWrite( buzz, HIGH);//turns on buzzer
      

    }
    else{
       myServo2.write(0);
      digitalWrite(ObjRedled, LOW);//turns off green led
      digitalWrite( buzz, LOW);//turns on buzzer
     

      }
  }
  // Repeats the previous lines from 165 to 15 degrees
  for(int i=180;i>0;i--){  
  myServo.write(i);
  myServo2.write(i);
  
  delay(30);
  distance = calculateDistance();
  Serial.print(i);
  Serial.print(",");
  Serial.print(distance);
  Serial.print(".");
   if(distance>=2 and distance<=15 and i<=90){
    myServo2.write(i);
      digitalWrite(ObjRedled, HIGH);//turns off green led
      digitalWrite( buzz, HIGH);//turns on buzzer
      

    }
    else{
      myServo2.write(0);
      digitalWrite(ObjRedled, LOW);//turns off green led
      digitalWrite( buzz, LOW);//turns on buzzer
      

      }
  }
  }

void openGate(){
  int irValue=digitalRead(GateIr);
  if (irValue == 0) {
    digitalWrite(GateBuzzer, HIGH);
    digitalWrite(GateGreenLed, HIGH);
    GateServo.write(90);
    delay(15); 
    Serial.print("irValue: ");
   Serial.println(irValue);
     //delay(1000);
  }
    
  else {
    digitalWrite(GateBuzzer, LOW);
    digitalWrite(GateGreenLed, LOW);
    GateServo.write(0);
    delay(15); 
    //delay(100);
  }
}

void gasDetect(){
  int analogSensor = analogRead(smokeA0);

  Serial.print("Pin A0: ");
  Serial.println(analogSensor);
  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres)
  {
    digitalWrite(GasYellowLed, HIGH);
    Serial.println("Gas detected..."); 
    digitalWrite(Gasbuzzer, HIGH);
    
  }
  else
  {
    digitalWrite(GasYellowLed, LOW);
  //  digitalWrite(greenLed, HIGH);
    Serial.println("No Gas detected..."); 
    digitalWrite(Gasbuzzer, LOW);
    
  }
  delay(1000);
  }
    
