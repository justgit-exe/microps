/*
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  lcd.begin(16, 2); //16 kolona, 2 reda
  //lcd.setCursor(0,1); // x od 0 do 15, y od 0 do 1
  //lcd.home(); //postavlja na 0,0
  //lcd.clear();
  //lcd.write(65); - ascii tabelan a 65 poziciji 'a'
  //lcd.print("); - nije ascii
  //lcd.Cursor() - pojavi se kursor
  //lcd.blink(); - blinka cursor
}

void loop() {
  // put your main code here, to run repeatedly:

}
*/
#include  <LiquidCrystal.h>
LiquidCrystal lcd (8 , 9 , 4 , 5 , 6 , 7) ;
byte srce [8] = {
B00000 , // oznacava paljenje i gasenje piksela
B01010 ,
B11111 ,
B11111 ,
B01110 ,
B00100 ,
B00000 ,
};
void setup () {
lcd.begin (16 , 2) ;
lcd.createChar (0 , srce ) ; //definisanje simbola srca - adresa mu je 0
}
void loop () {
lcd.setCursor (0 , 0) ;
lcd.write ( byte (0) ) ; //jer je srce na adersi 0
delay (1000) ;
lcd.setCursor (0 , 0) ;
lcd.write(' ');
delay(1000);
}
