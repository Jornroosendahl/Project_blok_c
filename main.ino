int TIP120pin = 11; //TIP120pin connected to pin 11 of the Arduino 
const int sensorMin = 0;     // sensor minimum 
const int sensorMax = 1024;  // sensor maximum
const int echoPin = 8; 
const int trigPin = 2;
long duration; // variable for the duration of sound wave travel 
int distance; // variable for the distance measurement 
int sleepPin = 7;    // select the output pin for enabeling motordriver 
int motorForward1Pin = 12;
int motorReverse1Pin = 13;
int motorForward2Pin = 9;
int motorReverse2Pin = 10;
 
void setup() { 
  // initialize serial communication @ 9600 baud: 
  Serial.begin(9600);
  pinMode(TIP120pin, OUTPUT); // Set pin for output to control TIP120 Base pin
  pinMode(sleepPin, OUTPUT); 
  pinMode(motorForward1Pin, OUTPUT); 
  pinMode(motorReverse1Pin, OUTPUT); 
  pinMode(motorForward2Pin, OUTPUT);
  pinMode(motorReverse2Pin, OUTPUT); 
  digitalWrite(sleepPin, HIGH);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.println("Ultrasonic Sensor HC-SR04 Test");
  Serial.println("with Arduino UNO");
}

long readDistance(){
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); 
  duration = pulseIn(echoPin, HIGH); 
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 
  Serial.print("Distance: "); 
  Serial.print(distance); 
  Serial.println(" cm");
  return distance; 
}

void fan(){
  digitalWrite(TIP120pin,HIGH);
  delay(2500);
  digitalWrite(TIP120pin,LOW);
}

void go(){
  digitalWrite(sleepPin, HIGH); 
  digitalWrite(motorForward1Pin, HIGH);
  digitalWrite(motorReverse1Pin, LOW);
  digitalWrite(motorForward2Pin, HIGH); 
  digitalWrite(motorReverse2Pin, LOW);
  delay(6);
  }

void reverse(){
  digitalWrite(sleepPin, HIGH); 
  digitalWrite(motorForward1Pin, LOW);
  digitalWrite(motorReverse1Pin, HIGH);
  digitalWrite(motorForward2Pin, LOW); 
  digitalWrite(motorReverse2Pin, HIGH);
  delay(1000);
  }
void stop(){
  digitalWrite(sleepPin, HIGH); 
  digitalWrite(motorForward1Pin, LOW);
  digitalWrite(motorReverse1Pin, LOW);
  digitalWrite(motorForward2Pin, LOW); 
  digitalWrite(motorReverse2Pin, LOW);
}

void rightwheel(){
  digitalWrite(sleepPin, HIGH); 
  // eerst klein stukje achteruit
  digitalWrite(motorForward1Pin, LOW);
  digitalWrite(motorReverse1Pin,HIGH);
  digitalWrite(motorForward2Pin,LOW);
  digitalWrite(motorReverse2Pin,HIGH);
  delay(500);
  
  digitalWrite(motorForward1Pin, HIGH); 
  digitalWrite(motorReverse1Pin, LOW);
  digitalWrite(motorForward2Pin, LOW); 
  digitalWrite(motorReverse2Pin, LOW);
  delay(1000);

  digitalWrite(motorForward1Pin, LOW); 
  digitalWrite(motorReverse1Pin, LOW);
  digitalWrite(motorForward2Pin, LOW); 
  digitalWrite(motorReverse2Pin, LOW);
  delay(1000);
  }
void leftwheel(){
 digitalWrite(sleepPin, HIGH); 
   // eerst klein stukje achteruit
  digitalWrite(motorForward1Pin, LOW);
  digitalWrite(motorReverse1Pin,HIGH);
  digitalWrite(motorForward2Pin,LOW);
  digitalWrite(motorReverse2Pin,HIGH);
  delay(500);
  
 digitalWrite(motorForward1Pin, LOW); 
 digitalWrite(motorReverse1Pin, LOW);
 digitalWrite(motorForward2Pin, HIGH); 
 digitalWrite(motorReverse2Pin, LOW);
 delay(500);

 digitalWrite(motorForward1Pin, LOW); 
 digitalWrite(motorReverse1Pin, LOW);
 digitalWrite(motorForward2Pin, LOW); 
 digitalWrite(motorReverse2Pin, LOW);
 delay(1000);
 }  
 
void loop() { 
  int digiSensorReading = digitalRead(6);  
  readDistance();
  if (distance >  25){
    go();
   } else if (distance <= 25 and digiSensorReading){
    stop();
     fan();
     delay(1000);
   }
   
   else if(distance <= 25){
    stop();
    delay(1000);
    leftwheel();
    delay(500);
    readDistance();
   }
   if (distance <= 25) {
    rightwheel();
    delay(500);
    readDistance();
   }
   if (distance <= 25){
    reverse();
   }
}
