
const int trigPin = 2;
const int echoPin = 3;
const int irSensorPin = 4;
const int heartRateSensorPin = A1; //heart rate sensor
const int temperaturePin = 5;  //temperature sensor
const int ldrPin = A0;          //light sensor
const int buzzerPin = 9;       //speaker
const int waterSensorPin = 8;        //water sensor

const float temperatureThreshold = 30.0; // Adjust this value based on desired temperature threshold
const int ldrThreshold = 300; // Adjust this value based on desired light threshold
const int distanceThreshold = 60; // Adjust this value based on desired distance threshold
const int distanceThreshold1 = 30;  //Distance threshold when it is very close


void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(irSensorPin, INPUT);
  pinMode(heartRateSensorPin, INPUT);
//  pinMode(temperaturePin, INPUT);
  pinMode(ldrPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(waterSensorPin, INPUT);
  
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

  // Determine whether the buzzer should be on and delay based on distance
  bool buzzerShouldBeOn = false;
  int buzzDuration = 0;

  if (distance <= distanceThreshold1) {
    Serial.println("US: Obstacle Detected!");
    buzzerShouldBeOn = true;
    buzzDuration = 50;  // Shorter buzz duration
  } else if (distance <= distanceThreshold) {
    Serial.println("US: Obstacle Detected!");
    buzzerShouldBeOn = true;
    buzzDuration = 500;  // Longer buzz duration
  }

  // Control the buzzer based on buzzerShouldBeOn and buzzDuration
  if (buzzerShouldBeOn) {
    digitalWrite(buzzerPin, HIGH);
    delay(buzzDuration);
    digitalWrite(buzzerPin, LOW);
    delay(buzzDuration);  // Add delay for the pause between buzzes
  } else {
    digitalWrite(buzzerPin, LOW);
  }

  //IR sensor
  int irSensorValue = digitalRead(irSensorPin);
  if (irSensorValue == LOW) {
    Serial.println("IR: Obstacle Detected!");
    digitalWrite(buzzerPin, HIGH);
    delay(500);
  } else {
    Serial.println("IR: Obstacle not Detected!");
    digitalWrite(buzzerPin, LOW);
  }
  
  // heart rate sensor
  int heartRate = analogRead(heartRateSensorPin) ;
  Serial.print("Heart Rate: ");
  Serial.println(heartRate);
   // Check if heart rate is outside the normal range
  if (heartRate < 60 || heartRate > 100) {
    Serial.println("Heart rate sensor is detecting out of range of 60 and 100");
//    digitalWrite(buzzerPin, HIGH);
  }

  //Temperature sensor
//  int temperatureValue = analogRead(temperaturePin);
//  float temperature = temperatureValue * 0.48828125;
//  Serial.print("Temperature: ");
//  Serial.print(temperature);
//  Serial.println("C");
  
  
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
  
  delay(200);
}
