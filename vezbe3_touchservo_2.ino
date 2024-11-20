//2. Napisati program koji proverava reflekse korisnika. U prozvoljnom trenutku potrebno je da se
//upali LED dioda koja je ugrađena na ploči, nakon čega korisnik treba što pre da odreaguje i
//pritisne senzor dodira. Postupak je potrebno izvršiti ukupno 10 puta, nakon čega se kao rezultat
//ispisuje prosečno vreme reakcije korisnika. 

#define TOUCH_PIN 4
#define PALJENJE 0
#define DODIR 1
#define KRAJ 2

unsigned long time_new, time_old;
unsigned long vreme_paljenja;
int vreme_dodira[11];
int touch_new, touch_old;
int counter, i;
float average, sum;
int stanje;

unsigned long vreme_pocetak, vreme_kraj;

void setup() {
  Serial.begin(9600);

  pinMode(TOUCH_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  randomSeed(2);

  touch_new = 0;
  touch_old = 0;
  counter = 0;
  time_new = millis();
  time_old = millis();
  i = 1;
  average = 0;
  sum = 0;
  stanje = PALJENJE;

  vreme_paljenja = random(1000, 5001);
}

void loop() {
  switch(stanje) {
    case PALJENJE:
      time_new = millis();
      vreme_paljenja = random(3000, 6000);
      
      if (time_new - time_old >= vreme_paljenja) {
        digitalWrite(LED_BUILTIN, HIGH);
        stanje = DODIR;
        time_old = time_new;
        vreme_pocetak = millis();
      }
    break;

    case DODIR: 
      touch_new = digitalRead(TOUCH_PIN);
    
      if (touch_new != touch_old && touch_new) {
        vreme_kraj = millis();
        vreme_dodira[i] = vreme_kraj - vreme_pocetak;
        
        Serial.println("Zavrseno merenje ");
        Serial.print(i);
        Serial.println();
        i++;
        digitalWrite(LED_BUILTIN, LOW);
        stanje = PALJENJE;
      }
      touch_old = touch_new;
      
      if (i > 10) {
        for (int i = 1; i < 11; i++) {
          sum += vreme_dodira[i];
        }
        average = sum/10;
        Serial.println("Merenja zavrsena");
        Serial.print(average);
        Serial.print("ms");
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
