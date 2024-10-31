//automat sa stanjima 0 - 1 - 2 sa prisikom touch
// u 0 servo da miruje, u 1 rotiranje u jednu stranu, u 2 rotiranje u drugu stranu

#include <Servo.h>
#define TOUCH_PIN 5
#define SERVO_PIN 9

Servo servo;
int polozaj;

int touch_new, touch_old;
int stanje;

void setup() {
  Serial.begin(9600);
  pinMode(TOUCH_PIN, INPUT);

  servo.attach(SERVO_PIN);
  polozaj = 0;
  servo.write(polozaj);
}

void loop() {
  touch_new = digitalRead(TOUCH_PIN);

  if (touch_new != touch_old && touch_new == 1) { //logika za prelazak iz stanja u stanje
    if (stanje == 0) {
      stanje = 1;
    }
    else if (stanje == 1) {
      stanje = 2;
    }
    else {
      stanje = 0;
    }
  }

  touch_old = touch_new; //nalazi se van ifa zbog uslova touch_new == 1, otherwise se ne bi nikad ispunilo

  switch(stanje) {
    case 0:
    break;

    case 1: 
    if (polozaj < 180) {
      polozaj++;
      servo.write(polozaj);
    }
    delay(15);
    break;

    case 2:
    if (polozaj > 0) {
      polozaj--;
      servo.write(polozaj);
    }
    delay(15);
    break;

    default:
    break;
  }

}
