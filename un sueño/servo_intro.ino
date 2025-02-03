#include <Servo.h>
#define SERVO_PIN 9

Servo servo;
int polozaj;

void setup() {
  Serial.begin(9600);
  servo.attach(SERVO_PIN);

  polozaj = 0;
  servo.write(polozaj);
}

void loop() {
  for (polozaj = 0; polozaj < 180; polozaj++) {
    servo.write(polozaj);
    delay(20);
  }
  for (polozaj = 180; polozaj > 0; polozaj--) {
    servo.write(polozaj);
    delay(20);
  }

}
