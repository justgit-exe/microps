#include  <LiquidCrystal.h>
#define SELECT 1

LiquidCrystal lcd (8, 9, 4, 5, 6, 7) ;

char kar[8];
int state, duzina;
int button_old, button_new;
int stanje;

char pokusaj[64];
int duzina2;
bool pogodak;

void setup() {
  lcd.begin(16, 2);

  Serial.begin(9600);
  randomSeed(analogRead(2));
  stanje = SELECT;

  pogodak = true;
}
//0 - generise se
//1 - pogadjanje
void loop() {
  button_new = ocitaj_taster();

  if (button_new != button_old && button_new != 0) {
    stanje = SELECT;
    lcd.clear();
  }
    
  switch(stanje) {
    case SELECT: //generise kod
    duzina = random(5, 9);

    for(int i = 0; i < duzina; i++) {
      state = random(0, 3);
  
      if (state == 0) { //karakter ce biti veiko slovo
        kar[i] = random(65, 91);
        lcd.setCursor(i, 0);
        lcd.write(kar[i]);
      }
      else if (state == 1) { //karakter ce biti malo slovo
        kar[i] = random(97, 123);
        lcd.setCursor(i, 0);
        lcd.write(kar[i]);
      }
      else if (state == 2) { //karakter ce biti broj
        kar[i] = random(48, 58);
        lcd.setCursor(i, 0);
        lcd.print(kar[i]);
      }
    }
    kar[duzina] = 0;

    stanje = 2;
    break;

    case 2: //pogadjanje koda
      while(Serial.available() == 0);
      delay(50);

      duzina2 = Serial.available();
      Serial.readBytes(pokusaj, duzina2);
      pokusaj[duzina2] = 0;

      for (int i = 0; i < duzina2; i++) {
        Serial.println(pokusaj[i]);
        Serial.println(kar[i]);
        if (pokusaj[i] != kar[i]) {
          pogodak = false;
          break;
        }
      }
      if (pogodak == true) {
        lcd.setCursor(0, 1);
        lcd.write("VERIFIED");
      }
      else {
        lcd.setCursor(0, 1);
        lcd.write("FAILED");
      }
    break;

    default:
    break; 
  }
 
}

byte ocitaj_taster()
{
 int tmp = analogRead(0); //stanje tastera se ocitava preko
 //analognog ulaza 0
 if (tmp > 635 && tmp < 645) //SELECT
  return 1;
 if (tmp > 405 && tmp < 415) //LEFT
  return 2;
 if (tmp > 95 && tmp < 105) //UP
  return 3;
 if (tmp > 252 && tmp < 262) //DOWN
  return 4;
 if (tmp < 5) //RIGHT
  return 5;
 return 0; //nije pritisnut nijedan od tastera
}
