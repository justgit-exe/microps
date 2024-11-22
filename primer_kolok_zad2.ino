//drugi zadatak nesto sa sahom idk

#include  <LiquidCrystal.h>
#define SELECT 1
#define LEFT 2
#define UP 3
#define DOWN 4
#define RIGHT 5

#define GENERISANJE 6
#define KRETANJE_KRALJA 7
#define ZIVEO_ENDING 8
#define PAO_ENDING 9
#define BUKEFALOV_GAMBIT 10

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int kraljX, kraljY, konjX, konjY, pijunX, pijunY;
int button_new, button_old;
bool gambit;

unsigned long time_new, time_old;

int stanje, gameStanje;

byte kralj[8] {
  B11011,
  B10001,
  B11011,
  B10001,
  B10001,
  B00000,
  B00000,
  B10001,
};
byte konj[8] {
  B11101,
  B10000,
  B00000,
  B01100,
  B11001,
  B10001,
  B00000,
  B10001,
};
byte pijun[8] {
  B11111,
  B10011,
  B11011,
  B10001,
  B10001,
  B00000,
  B10001,
  B11111,
};

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(2));

  lcd.begin(16, 2);
  lcd.createChar(0, kralj);
  lcd.createChar(1, konj);
  lcd.createChar(2, pijun); //lcd.createChar(PIJUN, pijun); a gore #define PIJUN 2

  button_new = 0;
  button_old = 0; 

  time_new = millis();
  time_old = millis();

  gameStanje = GENERISANJE;
  gambit = false;
}

void loop() {
  switch(gameStanje) {
    case GENERISANJE:
      kraljX = 0;
      kraljY = 0;
      lcd.setCursor(kraljX, kraljY);
      lcd.write(byte(0));

      konjX = random(5, 14);
      konjY = random(0, 2);
      lcd.setCursor(konjX, konjY);
      lcd.write(byte(1));

      pijunX = konjX + 2;
      pijunY = konjY;
      lcd.setCursor(pijunX, pijunY);
      lcd.write(byte(2));

      gameStanje = KRETANJE_KRALJA;
      gambit = false;
    break;

    case KRETANJE_KRALJA:
      button_new = ocitaj_taster();

      if (button_new != button_old && button_new != 0) {
        stanje = button_new;
      }
      button_old = button_new;

      switch(stanje) {
        case UP:
          if (kraljY == 1 && (pijunX != kraljX)) {
            kraljY = 0;
            lcd.setCursor(kraljX, 1);
            lcd.write(" ");
          }
          
          else if (kraljY == 1 && (pijunX == kraljX)) {
            kraljY = 1;
          }
        break;

        case DOWN:
          if (kraljY == 0 && (pijunX != kraljX)) {
            kraljY = 1;
            lcd.setCursor(kraljX, 0);
            lcd.write(" ");
          }        

          else if (kraljY == 0 && (pijunX == kraljX)) {
            kraljY = 0;
          }
        break;

        case RIGHT:
          if (kraljX + 1 == pijunX && pijunY == kraljY) {
            kraljX == kraljX;
          }

          else {
              lcd.setCursor(kraljX, kraljY);
              lcd.write(" ");
              kraljX += 1;
          }
        break;

        case LEFT:
          if (kraljX > 0 && (pijunX == kraljX - 1) && (pijunY == kraljY)) {
            kraljX = kraljX;
          }
          else if (kraljX > 0) {
              lcd.setCursor(kraljX, kraljY);
              lcd.write(" ");
              kraljX -= 1;
          }
        break;

        default:
        break;
      }
      lcd.setCursor(kraljX, kraljY);
      Serial.println(kraljX);
      lcd.write(byte(0));

      if (kraljX >= 16) {
        gameStanje = ZIVEO_ENDING;
        lcd.clear();
        lcd.print("ZIVEO KRALJ!");
        time_old = millis();
      }

      if (((kraljX == konjX - 2) || (kraljX == konjX + 2)) && (kraljY != konjY) && gambit == false) {
        lcd.setCursor(konjX, konjY);
        lcd.write(" ");
        lcd.setCursor(kraljX, kraljY);
        lcd.write(byte(1));
        delay(1500);
        
        gameStanje = PAO_ENDING;
        lcd.clear();
        lcd.print("KRALJ JE PAO!");
        time_old = millis();
      }

      if (((kraljX == konjX - 1) || (kraljX == konjX + 1)) && (stanje == SELECT)) {
        lcd.setCursor(konjX, konjY);
        lcd.write(byte(0));
        lcd.setCursor(kraljX, kraljY);
        lcd.write(" ");
        delay(1500);

        lcd.clear();
        lcd.print("BUKEFALOV GAMBIT!");
        delay(3000);
        lcd.clear();

        kraljX = konjX;
        kraljY = konjY;
        lcd.setCursor(kraljX, kraljY);
        lcd.write(byte(0));
        lcd.setCursor(pijunX, pijunY);
        lcd.write(byte(2));
        gambit = true;
      }

      stanje = 0;
    break;

    case ZIVEO_ENDING:
      time_new = millis();
      if (time_new - time_old >= 3000) {
        gameStanje = GENERISANJE;
        lcd.clear();
      }
    break;

    case PAO_ENDING:
      time_new = millis();
      if (time_new - time_old >= 3000) {
        gameStanje = GENERISANJE;
        lcd.clear();
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
