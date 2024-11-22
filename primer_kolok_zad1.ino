//unsoi se string i zatim operacija M - sve mala V - sve velika O - velika u mala i obrnuto

#define UNOS 0
#define M 1
#define V 2
#define O 3
#define ISPIS 4

char unos[64];
char izlaz[64];
char operacija;
int duzinaUnosa;
int stanje;

void setup() {
  Serial.begin(9600);
  stanje = UNOS;
  Serial.println("Unesite string: ");
}

void loop() {

  switch(stanje) {
    case UNOS:
      while(Serial.available() == 0);
      delay(50);
    
      duzinaUnosa = Serial.available();
    
      Serial.readBytes(unos, duzinaUnosa);
      unos[duzinaUnosa] = 0;
    
      Serial.println("Unesena poruka je ");
      Serial.print(unos);
      Serial.println();
      
      Serial.println("Koja je zeljena operacija? M/V/O");
      while(Serial.available() == 0);
      delay(50);
      operacija = Serial.read();

      if (operacija == 'M') {
        stanje = M;
      }
      else if (operacija == 'V') {
        stanje = V;
      }
      else if (operacija == 'O') {
        stanje = O;
      }
      Serial.println(operacija);
    break;

    case M:
      for (int i = 0; i < duzinaUnosa; i++) {
        if (unos[i] >= 'A' && unos[i] <= 'Z') {
          unos[i] = unos[i] + 32;
        }
      }
      stanje = ISPIS;
    break;

    case V:
      for (int i = 0; i < duzinaUnosa; i++) {
        if (unos[i] >= 'a' && unos[i] <= 'z') {
          unos[i] = unos[i] - 32;
        }
      }
      stanje = ISPIS;
    break;

    case O:
      for (int i = 0; i < duzinaUnosa; i++) {
        if (unos[i] >= 'a' && unos[i] <= 'z') {
          unos[i] = unos[i] - 32;
        }
        else if (unos[i] >= 'A' && unos[i] <= 'Z') {
          unos[i] = unos[i] + 32;
        }
      }
      stanje = ISPIS;
    break;

    case ISPIS:
      Serial.println("Rezultat operacije je string: ");
      Serial.println(unos);
      Serial.println("Unesite string: ");
      stanje = UNOS;
    break;

    default:
    break;
  }


  

}
