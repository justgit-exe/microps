#include  <LiquidCrystal.h>
#define SELECT 1
#define LEFT 2
#define UP 3
#define DOWN 4
#define RIGHT 5

#define GENERISANJE 6
#define IGRA 7
#define BAD_ENDING 8
#define STITKO_POLUVREME 9
#define PROTECC_ENDING 10

LiquidCrystal lcd (8, 9, 4, 5, 6, 7) ;

int pozicijaX, pozicijaY;
int button_old, button_new;
unsigned long time_new, time_old;

int zlockoX, zlockoY;
int stitkoX, stitkoY;

int stanje;
int gamesetup;

bool pokupljen_stitko;

byte smesko[8] {
  B00000,
  B01110,
  B10001,
  B11101,
  B11101,
  B10001,
  B10101,
  B01010,
};

byte zlocko[8] {
  B00000,
  B00000,
  B01110,
  B00100,
  B01110,
  B10001,
  B10101,
  B01010,
};

byte stitko[8] {
  B00100,
  B00100,
  B11111,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
};

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(2));
  
  lcd.begin(16, 2);
  lcd.createChar(0, smesko);
  lcd.createChar(1, zlocko);
  lcd.createChar(2, stitko);

  time_new = millis();
  time_old = millis();

  pokupljen_stitko = false;

  gamesetup = GENERISANJE;
}

void loop() {

  switch(gamesetup) {
    case GENERISANJE:
        lcd.clear();
    
        stanje = 0;
        
        pozicijaX = 0;
        pozicijaY = 0;
        lcd.setCursor(0, 0);
        lcd.write(byte(0));
    
        zlockoX = random(8, 16);
        zlockoY = random(0, 2);
        lcd.setCursor(zlockoX, zlockoY);
        lcd.write(byte(1));

        do {
          stitkoX = random(8, 16);
        }while (stitkoX == zlockoX);
        stitkoY = 0;
        lcd.setCursor(stitkoX, stitkoY);
        lcd.write(byte(2));

        pokupljen_stitko = false;
        gamesetup = IGRA;
    break;

    case IGRA:
        time_new = millis();
        button_new = ocitaj_taster();
      
        if (button_new != button_old && button_new != 0) {
          stanje = button_new;
        }
      
        button_old = button_new;
        switch(stanje) {
          case UP:
            if (pozicijaY == 1) {
              pozicijaY = 0;
              lcd.setCursor(pozicijaX, 1);
              lcd.print(" ");
            }
          break;
      
          case DOWN:
            if (pozicijaY == 0) {
              pozicijaY = 1;
              lcd.setCursor(pozicijaX, 0);
              lcd.print(" ");
            }
          break;
      
          case RIGHT:
            lcd.setCursor(pozicijaX, pozicijaY);
            if (time_new - time_old >= 500) {
              if (pozicijaX == 15) {
                pozicijaX = 0;
              }
              else if (pozicijaX < 15) {
                pozicijaX++;
              }
              time_old = time_new;
              lcd.print(" ");
            }
          break;
      
          case LEFT:
            lcd.setCursor(pozicijaX, pozicijaY);
            if (time_new - time_old >= 500) {
              if (pozicijaX == 0) {
                pozicijaX = 15;
              }
              else if (pozicijaX > 0) {
                pozicijaX--;
              }
              time_old = time_new; 
              lcd.print(" ");
            }
          break;
      
          default:
          break;
        }
          
        lcd.setCursor(pozicijaX, pozicijaY);
        lcd.write(byte(0));

        if (pozicijaX == stitkoX && pozicijaY == stitkoY && !pokupljen_stitko) {
          pokupljen_stitko = true;
          lcd.clear();
          lcd.print("AMOGUSE,");
          lcd.setCursor(0, 1);
          lcd.print("VERUJEM TI");
          gamesetup = STITKO_POLUVREME;
        }

        if (pozicijaX == zlockoX && pozicijaY == zlockoY && !pokupljen_stitko) {
          lcd.clear();
          lcd.print("AMOGUSE,");
          lcd.setCursor(0, 1);
          lcd.print("SUMNJIV SI!");
          gamesetup = BAD_ENDING;
        }

        else if (pozicijaX == zlockoX && pozicijaY == zlockoY && pokupljen_stitko) {
          lcd.clear();
          lcd.print("OVU RUNDU...");
          lcd.setCursor(0, 1);
          lcd.print("IMAS POSLA.");

          pokupljen_stitko = false;
          gamesetup = PROTECC_ENDING;
        }
    break;

    case BAD_ENDING:
        time_new = millis();
        if (time_new - time_old >= 3000) {
          gamesetup = GENERISANJE;
          lcd.clear();
        }
    break;

    case STITKO_POLUVREME: 
        time_new = millis();
        if (time_new - time_old >= 1000) {
          lcd.clear();
          lcd.setCursor(zlockoX, zlockoY);
          lcd.write(byte(1));

          lcd.setCursor(pozicijaX, pozicijaY);
          lcd.write(byte(0));
          
          stanje = 0;
          gamesetup = IGRA;
        }
    break;

    case PROTECC_ENDING:
        time_new = millis();
        if (time_new - time_old >= 1500) {
           if (zlockoX <= 14) {
            pozicijaX = zlockoX + 1;
           }
           else {
            pozicijaX = zlockoX - 1;
           }
           lcd.clear();
           lcd.setCursor(zlockoX, zlockoY);
           lcd.write(byte(1));
           lcd.setCursor(pozicijaX, pozicijaY);
           lcd.write(byte(0));

           stanje = 0;
           gamesetup = IGRA;
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
