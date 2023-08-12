#include "DHT.h"
#define DHTPIN 5
#define DHTTYPE DHT11

const int trigPin = 2;
const int echoPin = 3;
const int irSensorPin = 4;
const int heartRateSensorPin = A1; //heart rate sensor
const int temperaturePin = 5;  //temperature sensor
const int ldrPin = A0;          //light sensor
const int buzzerPin = 9;       //speaker
const int waterSensorPin = 8;        //water sensor

const float temperatureThreshold = 30.0; // Adjust this value based on desired temperature threshold
const int ldrThreshold = 500; // Adjust this value based on desired light threshold
const int distanceThreshold = 50; // Adjust this value based on desired distance threshold

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(irSensorPin, INPUT);
  pinMode(heartRateSensorPin, INPUT);
  pinMode(temperaturePin, INPUT);
  pinMode(ldrPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(waterSensorPin, INPUT);
  dht.begin(); // initialize the temperature sensor
  
  Serial.begin(9600);
}

void loop() {
  // Ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;

  // Output distance to serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println("cm");

  if (distance <= distanceThreshold) {
    Serial.println("Obstacle Detected!");
    digitalWrite(buzzerPin, HIGH);
    delay(500);
  } else {
    digitalWrite(buzzerPin, LOW);
  }

  //IR sensor
  int irSensorValue = digitalRead(irSensorPin);
  if (irSensorValue == LOW) {
    Serial.println("Obstacle Detected!");
    digitalWrite(buzzerPin, HIGH);
    delay(500);
  } else {
    Serial.println("Obstacle not Detected!");
    digitalWrite(buzzerPin, LOW);
  }
  
  // heart rate sensor
  int heartRate = analogRead(heartRateSensorPin) ;
  Serial.print("Heart Rate: ");
  Serial.println(heartRate);
  
  //Temperature sensor
  int temperatureValue = analogRead(temperaturePin);
  float temperature = temperatureValue * 0.48828125;
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("C");

  float tempC = dht.readTemperature();
  Serial.print("Temperature new: ");
  Serial.print(tempC);
  Serial.println("C");

//  if (temperature > temperatureThreshold) {
//    Serial.println("High Temperature Detected!");
//    digitalWrite(buzzerPin, HIGH);
//    digitalWrite(vibratorPin, HIGH);
//    delay(500);
//  } else {
//    digitalWrite(buzzerPin, LOW);
//    digitalWrite(vibratorPin, LOW);
//  }
  
  // LDR (Light Dependent Resistor)
  int ldrValue = analogRead(ldrPin);
  Serial.print("LDRValue: ");
  Serial.println(ldrValue);
  
  if (ldrValue < ldrThreshold) {
    Serial.println("Low Light Detected!");
    digitalWrite(buzzerPin, HIGH);
    delay(500);
  } else {
    Serial.println("Enough Light Detected!");
    digitalWrite(buzzerPin, LOW);
  }

  // Water Sensor
  int waterValue = digitalRead(waterSensorPin);  // Read the sensor value

  if (waterValue == HIGH) {
      Serial.println("Water detected!");  // Water is detected
      digitalWrite(buzzerPin, HIGH);
      delay(500);
  } else {
      Serial.println("No water.");  // No water detected
      digitalWrite(buzzerPin, LOW);
  }
  
  delay(1000);
}
