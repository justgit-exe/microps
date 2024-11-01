#include  <LiquidCrystal.h>
#define SELECT 1
#define LEFT 2
#define UP 3
#define DOWN 4
#define RIGHT 5

LiquidCrystal lcd (8, 9, 4, 5, 6, 7) ;

int pozicijaX, pozicijaY;
int button_old, button_new;

byte smajli[8] {
  B00000,
  B01110,
  B10001,
  B11011,
  B10001,
  B11011,
  B10101,
  B01110,
};

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.createChar(0, smajli);
  lcd.setCursor(0, 0);
  lcd.write(byte(0));

  pozicijaX = 0;
  pozicijaY = 0;
}

void loop() {
  button_new = ocitaj_taster();
  if (button_new != button_old) {
    Serial.println(button_new);
    delay(30);
    if (button_new == UP && pozicijaY == 1) {
      pozicijaY = 0;
    }

    else if (button_new == DOWN && pozicijaY == 0) {
      pozicijaY = 1;
    }

    else if (button_new == LEFT && pozicijaX != 0) {
      pozicijaX--;
    }
    
    else if (button_new == RIGHT && pozicijaX != 15) {
      pozicijaX++;
    }

    lcd.clear(); //za svaki novi ispis se proslo izbrise
    lcd.setCursor(pozicijaX, pozicijaY);
    lcd.write(byte(0));
    
    button_old = button_new;
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
