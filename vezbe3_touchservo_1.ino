//1. Napisati program koji proverava brzinu korisnika. Od korisnika se očekuje da u roku od 3
//sekunde što više puta pritisne senzor dodira, nakon čega se putem serijske komunikacije ispisuje
//rezultat.

#define TOUCH_PIN 4

#define KRAJ 1
#define UNOS_DODIRA 0

bool touch_new, touch_old;
unsigned long time_new, time_old;
unsigned int counter;

int stanje;

void setup() {
  Serial.begin(9600);
  pinMode(TOUCH_PIN, INPUT);

  touch_new = 0;
  touch_old = 0;
  time_new = millis();
  time_old = millis();
  counter = 0;
}

void loop() {

  switch(stanje) {
    case UNOS_DODIRA:
      time_new = millis();
      touch_new = digitalRead(TOUCH_PIN);
      if (touch_new != touch_old && touch_new) {
        counter++;
      }
      touch_old = touch_new;

      if (time_new - time_old >= 3000) {
        Serial.print("U ove 3 sekunde je senzor bio pritisnut ");
        Serial.print(counter);
        Serial.print(" puta.");
        Serial.println();
        stanje = KRAJ;
      }
    break;

    case KRAJ:
    break;

    default:
    break;
  }
  
}
