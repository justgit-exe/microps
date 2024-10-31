//stoperica

#include <Servo.h>
#define SERVO_PIN 9
#define TOUCH_PIN 5

int touch_new, touch_old;
int broj_s, broj_m, broj_h;
unsigned long time_new, time_old;

Servo servo;
int polozaj;
int stanje;

void setup() {
  Serial.begin(9600);
  servo.attach(SERVO_PIN);

  polozaj = 0;
  servo.write(polozaj);

  touch_new = 0;
  touch_old = 0;

  time_new = millis();
  time_old = millis();

  broj_s = 0;
  broj_m = 0;
  broj_h = 0;

  Serial.println("Trenutno vreme: ");
  Serial.print("00:00:00");
  Serial.println();

  stanje = 1;

}

void loop() {
  time_new = millis();
  touch_new = digitalRead(TOUCH_PIN);

  if (touch_new != touch_old && touch_new == 1) { //ako je pritisnut
    if (stanje == 0) {
      stanje = 1;
    }
    else {
      stanje = 0;
    }
  }
  touch_old = touch_new;

  switch(stanje) {
    case 0:
    break;

    case 1:
    if (time_new  - time_old >=  1000) {
      broj_s++;
      polozaj += 3;
      servo.write(polozaj);

      if (broj_s == 60) {
        broj_m++;
        broj_s = 0;

        polozaj = 0;
        servo.write(polozaj);
      }

      if (broj_m == 60) {
        broj_h++;
        broj_m = 0;
      }
      if (broj_h < 10) {
        Serial.print('0');
      }
      Serial.print(broj_h);
      Serial.print(":");
      if (broj_m < 10) {
        Serial.print('0');
      }
      Serial.print(broj_m);
      Serial.print(":");
      if (broj_s < 10) {
        Serial.print('0');
      }
      Serial.print(broj_s);

      time_old = time_new;
    }
    break;

    default:
    break;
  }

}












