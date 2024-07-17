#include <Servo.h>

const int trigPin = 7;
const int echoPin = 8;
const int servoPin = 10;
const int buzzerPin = 6;

Servo myServo;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  myServo.attach(servoPin);
}

void loop() {
  long duration, cm;
  unsigned long currentMillis = millis();
  static unsigned long previousMillis = 0;
  const long intervalOn = 1000; // 2 segundos ligado
  const long intervalOff = 2000; // 4 segundos desligado
  static bool buzzerState = false;

  // Mover servo motor de 0 a 180 graus e medir a distância
  for (int angle = 0; angle <= 180; angle += 1) {
    myServo.write(angle);
    delay(15);

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    cm = microsecondsToCentimeters(duration);

    Serial.print(angle);
    Serial.print(",");
    Serial.print(cm);
    Serial.println(".");

    // Controle do buzzer
    currentMillis = millis();
    if (buzzerState && (currentMillis - previousMillis >= intervalOn)) {
      noTone(buzzerPin);
      buzzerState = false;
      previousMillis = currentMillis;
    } else if (!buzzerState && (currentMillis - previousMillis >= intervalOff)) {
      tone(buzzerPin, 880);
      buzzerState = true;
      previousMillis = currentMillis;
    }

    delay(100);
  }

  // Mover servo motor de 180 a 0 graus e medir a distância
  for (int angle = 180; angle >= 0; angle -= 1) {
    myServo.write(angle);
    delay(15);

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    cm = microsecondsToCentimeters(duration);

    Serial.print(angle);
    Serial.print(",");
    Serial.print(cm);
    Serial.println(".");

    // Controle do buzzer
    currentMillis = millis();
    if (buzzerState && (currentMillis - previousMillis >= intervalOn)) {
      noTone(buzzerPin);
      buzzerState = false;
      previousMillis = currentMillis;
    } else if (!buzzerState && (currentMillis - previousMillis >= intervalOff)) {
      tone(buzzerPin, 880);
      buzzerState = true;
      previousMillis = currentMillis;
    }

    delay(100);
  }
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
