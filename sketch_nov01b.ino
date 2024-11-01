#include  <LiquidCrystal.h>
#define SELECT 1
#define LEFT 2
#define UP 3
#define DOWN 4
#define RIGHT 5

LiquidCrystal lcd (8, 9, 4, 5, 6, 7) ;

int counter;
int button_new, button_old;

void setup() {
  lcd.begin(16, 2);

  counter = 0;
  button_new = 0;
  button_old = 0;

  lcd.setCursor(0, 0);
  lcd.print(counter);
}

void loop() {
  button_new = ocitaj_taster();
  if (button_new != button_old) {
    delay(30);
    if (button_new == UP) {
      counter++;
    }

    else if (button_new == DOWN) {
      counter--;
    }

    else if (button_new == SELECT) {
      counter = 0;
    }

    lcd.clear(); //za svaki novi ispis se proslo izbrise
    lcd.setCursor(0, 0);
    lcd.print(counter);
    
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
