#include <Servo.h>

#define TOUCH_PIN 7
#define SERVO_PIN 9
#define STEP_DELAY 25

Servo servo;
int pos;

bool touch_new, touch_old;
bool first_time;

int stanje;

void setup() {
  Serial.begin(9600);
  pinMode(TOUCH_PIN, INPUT);
  servo.attach(SERVO_PIN);
  pos = 0;
  servo.write(pos);
  stanje = 0;

  touch_new = false;
  touch_old = false;
  first_time = true;

}

void loop() {
  switch(stanje) {
    case 0:
      touch_new = digitalRead(TOUCH_PIN);
        if (touch_new) { //ako dryim
          pos++;
          servo.write(pos);
          delay(STEP_DELAY);
  
          if (pos >= 180) {
            stanje = 1;
             }
          }

          if (touch_old == true && touch_new == false && first_time == true) { //silazni takt
            stanje = 2;
            first_time = false;
          }
        touch_old = touch_new;
    break;

    case 1:
      touch_new = digitalRead(TOUCH_PIN);
        if (touch_new) { //ako dryim
          pos--;
          servo.write(pos);
          delay(STEP_DELAY);
  
          if (pos <= 0) {
            stanje = 0;
          }
          }

          if (touch_old == true && touch_new == false && first_time == true) { //silazni takt
            stanje = 2;
            first_time = false;
          }
        touch_old = touch_new;
    break;

    case 2:
    Serial.println(2);
    break;

    default:
    break;
  }

}
