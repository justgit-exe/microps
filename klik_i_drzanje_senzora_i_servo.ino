#include <Servo.h>
#define TOUCH_PIN 5
#define SERVO_PIN 9
#define TOUCH_DURATION 500

unsigned long  start_time, end_time;
int touch_new, touch_old;

Servo servo;
int polozaj;

void setup() {
  Serial.begin(9600);
  pinMode(TOUCH_PIN, INPUT);
  servo.attach(SERVO_PIN);

  touch_old = 0;
  touch_new = 0;

  polozaj = 0;
  servo.write(polozaj);
  start_time = millis();
  end_time = millis();

  Serial.println("program je poceo sa radom");

}

void loop() {
  touch_new = digitalRead(TOUCH_PIN);
  if (touch_pin != touch_old) { //trenutak pritiska

    if (touch_new == 1)  {
      start_time - millis();
    }

    else { //kada je drzan + kada je pusten
      end_time = millis();
      if (end_time - start_time < TOUCH_DURATION) { //nije dovoljno dugo zadrzan touch
        if (polozaj <= 165) {
          polozaj += 15;
        }
      }
      else {
        if (polozaj >= 15) {
          polozaj -= 15;
        }
      }
      servo.write(polozaj);
    }

  touch_old = touch_new;

  }
}
