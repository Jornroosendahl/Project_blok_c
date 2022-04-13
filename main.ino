// library importeren
#include <FastLED.h>
#include <arduino-timer.h>

//pins voor de ledstrip defineren
#define NUM_LEDS 8
#define DATA_PIN 4
#define CLOCK_PIN 5

//pins aanwijzen en variabelen maken
auto timer = timer_create_default(); // create timer with default settings
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
int toeter = 3;
CRGB leds[NUM_LEDS];





void setup() { 
  // initialize serial communication @ 9600 baud: 
  Serial.begin(9600);
  LEDS.addLeds<APA102,DATA_PIN, CLOCK_PIN,RGB>(leds,NUM_LEDS);
  
  // de verschillende pins als output zettten
  pinMode(TIP120pin, OUTPUT); // Set pin for output to control TIP120 Base pin
  pinMode(sleepPin, OUTPUT);
  pinMode(toeter, OUTPUT);
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


void fanLeds(){
  // functie om de ledstrip te laten knipperen als de auto bij de vlam staat
    leds[0] = CRGB(255,0,0);
    leds[1] = CRGB(0,255,0);
    leds[2] = CRGB(0,255,0);
    leds[3] = CRGB(0,0,255);
    leds[4] = CRGB(255,255,0);
    leds[5] = CRGB(255,255,0);
    leds[6] = CRGB(255,255,0);
    leds[7] = CRGB(255,255,0);
    FastLED.show();
    delay(50);
    leds[0] = CRGB(0,255,0);
    leds[1] = CRGB(0,0,255);
    leds[2] = CRGB(255,0,0);
    leds[3] = CRGB(0,255,0);
    leds[4] = CRGB(0,255,0);
    leds[5] = CRGB(255,0,0);
    leds[6] = CRGB(0,255,0);
    leds[7] = CRGB(255,0,0);
    FastLED.show();
    delay(50);
}

void slowLeds() {
  // functie om de leds 1 kleur (rood) te laten branden terwijl de auto rijdt
  leds[0] = CRGB(0,0,255);
    leds[1] = CRGB(0,0,255);
    leds[2] = CRGB(0,0,255);
    leds[3] = CRGB(0,0,255);
    leds[4] = CRGB(0,0,255);
    leds[5] = CRGB(0,0,255);
    leds[6] = CRGB(0,0,255);
    leds[7] = CRGB(0,0,255);
    FastLED.show();    
}

long readDistance(){
  // functie om de afstand te meten en in de serial monitor te printen
  // Afstand wordt opgeslagen in variabele distance
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
  // functie om de fan te laten draaien en ledjes meerdere keren te laten knipperen en een kort piepsignaal te laten horen
  digitalWrite(toeter,HIGH);
    delay(50);
    digitalWrite(toeter,LOW);
    delay(50);
    digitalWrite(toeter,HIGH);
    delay(50);
    digitalWrite(toeter,LOW);
    delay(50);
  fanLeds();
  fanLeds();
  fanLeds();
  fanLeds();
  fanLeds();
  fanLeds();
  fanLeds();
  fanLeds();
  fanLeds();
  fanLeds();
  digitalWrite(TIP120pin,HIGH);
  Serial.print("AAAAAAAAAAAAAAAANNNNNN");
  delay(2500);
  digitalWrite(TIP120pin,LOW);
}

void go(){
  // functie om de auto vooruit te laten rijden
  digitalWrite(sleepPin, HIGH); 
  digitalWrite(motorForward1Pin, HIGH);
  digitalWrite(motorReverse1Pin, LOW);
  digitalWrite(motorForward2Pin, HIGH); 
  digitalWrite(motorReverse2Pin, LOW);
  slowLeds();
  }

void reverse(){
  // functie om de auto achteruit te laten rijden
  digitalWrite(sleepPin, HIGH); 
  digitalWrite(motorForward1Pin, LOW);
  digitalWrite(motorReverse1Pin, HIGH);
  digitalWrite(motorForward2Pin, LOW); 
  digitalWrite(motorReverse2Pin, HIGH);
  delay(1000);
  }
void stop(){
  // functie om de auto te laten stoppen
  digitalWrite(sleepPin, HIGH); 
  digitalWrite(motorForward1Pin, LOW);
  digitalWrite(motorReverse1Pin, LOW);
  digitalWrite(motorForward2Pin, LOW); 
  digitalWrite(motorReverse2Pin, LOW);
}

void rightwheel(){
  // functe om de auto een stukje achteruit te laten rijden en vervolgens het rechterwiel te laten draaien
  int digiSensorReading = digitalRead(6);
  digitalWrite(sleepPin, HIGH); 
  // eerst klein stukje achteruit
  digitalWrite(motorForward1Pin, LOW);
  digitalWrite(motorReverse1Pin,HIGH);
  digitalWrite(motorForward2Pin,LOW);
  digitalWrite(motorReverse2Pin,HIGH);
  delay(1000);


  
   for(int i = 0; i < 10; i++){
 digitalWrite(motorForward1Pin, HIGH); 
 digitalWrite(motorReverse1Pin, LOW);
 digitalWrite(motorForward2Pin, LOW); 
 digitalWrite(motorReverse2Pin, LOW);
 delay(100);
 digitalWrite(motorForward1Pin, LOW); 
 digitalWrite(motorReverse1Pin, LOW);
 digitalWrite(motorForward2Pin, LOW); 
 digitalWrite(motorReverse2Pin, LOW);
 delay(300);
 if(digitalRead(6) == 1){

 break;
 }else{
  continue;
  }
 }



 

  digitalWrite(motorForward1Pin, LOW); 
  digitalWrite(motorReverse1Pin, LOW);
  digitalWrite(motorForward2Pin, LOW); 
  digitalWrite(motorReverse2Pin, LOW);
  delay(1000);
  }
void leftwheel(){
  // functie om de auto eerst een stukje achteruit te laten rijden, om vervolgens het linkerwiel te laten draaien
  int digiSensorReading = digitalRead(6);
 digitalWrite(sleepPin, HIGH); 
   // eerst klein stukje achteruit
  digitalWrite(motorForward1Pin, LOW);
  digitalWrite(motorReverse1Pin,HIGH);
  digitalWrite(motorForward2Pin,LOW);
  digitalWrite(motorReverse2Pin,HIGH);
  delay(800);


 for(int i = 0; i < 5; i++){
 digitalWrite(motorForward1Pin, LOW); 
 digitalWrite(motorReverse1Pin, LOW);
 digitalWrite(motorForward2Pin, HIGH); 
 digitalWrite(motorReverse2Pin, LOW);
 delay(100);
 digitalWrite(motorForward1Pin, LOW); 
 digitalWrite(motorReverse1Pin, LOW);
 digitalWrite(motorForward2Pin, LOW); 
 digitalWrite(motorReverse2Pin, LOW);
 delay(300);
 if(digitalRead(6) == 1){

 break;
 }else{
  continue;
  }
 }



 digitalWrite(motorForward1Pin, LOW); 
 digitalWrite(motorReverse1Pin, LOW);
 digitalWrite(motorForward2Pin, LOW); 
 digitalWrite(motorReverse2Pin, LOW);
 delay(1000);
 }  



void loop() {
  // de main loop waar alle functies worden aangeroepen 
  int digiSensorReading = digitalRead(6);  
  readDistance();
  if (distance >  20){
    go();
   } else if (distance <= 15 and digiSensorReading){
    Serial.print(digiSensorReading);
    stop();
     fan();
     delay(1000);
   }
   
   else if(distance <= 20){
    stop();
    delay(1000);
    leftwheel();
    delay(500);
    readDistance();
   }
   if (distance <= 20 and digiSensorReading){
    return;
   }
   if (distance <= 20) {
    rightwheel();
    delay(500);
    readDistance();
   }
   if (distance <= 20 and digiSensorReading){
    return;
   }
   if (distance <= 20){
    reverse();
   }
}
