// lowest and highest sensor readings: 
const int sensorMin = 0;     // sensor minimum 
const int sensorMax = 1024;  // sensor maximum 
 
void setup() { 
  // initialize serial communication @ 9600 baud: 
  Serial.begin(9600);   
} 
void loop() { 
  // read the sensor on analog A0: 
  // zie: https://www.arduino.cc/reference 
  int sensorReading = analogRead(A0); 
  int digiSensorReading = digitalRead(8);
  // map the sensor range (four options): 
  // zie: https://www.arduino.cc/reference/en/language/functions/math/map/  
  int range = map(sensorReading, sensorMin, sensorMax, 0, 3); 
   
   //range value: 
  switch (range) { 
  case 0:    // A fire closer than 1.5 feet away. 
    Serial.println("** Close Fire **"); 
    break; 
  case 1:    // A fire between 1-3 fee t away. 
    Serial.println("** Distant Fire **"); 
    break; 
  case 2:    // No fire detected. 
    Serial.println("No Fire"); 
    break; 
  } 
  delay(1);
//    Serial.println(digiSensorReading);
}
