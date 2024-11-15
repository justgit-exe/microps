#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10
#define CLIENTS_NUM 16 //recimo

char clientNames[CLIENTS_NUM][36] = {"Milan Marinkovic", "Djordje Djordjevic"};
char clientUids[CLIENTS_NUM][12] = {"00 8B 9C 1E", "33 9C CB 95"}; //XX_XX_XX_XX plus terminator
int clientPins[CLIENTS_NUM] = {1389, 1804}; //pin kartice coveka
float clientMoney[CLIENTS_NUM] = {4500.00, 12000.00}; 

MFRC522 rc522(SS_PIN, RST_PIN); //kreiranje klase

char userUid[12]; //XX_XX_XX_XX plus terminator
float iznos;
bool found;
bool pinNeeded;
int pin;
int i;

int stanje;

void setup()
{
   Serial.begin(9600);
   SPI.begin();
   rc522.PCD_Init();
   stanje = 0;
}
void loop()
{
    switch(stanje) {
      case 0: //cekamo da neko unese neki 
        if (Serial.available()) { //nesto je uneseno
          delay(15);
          iznos = Serial.parseFloat();
          Serial.print("Iznos: ");
          Serial.println(iznos);
          Serial.println("Prislonite karticu: ");
          
          stanje = 1;
        }
        break;

      case 1: //cekamo da korisnik prisloni karticu
          if (rc522.PICC_IsNewCardPresent() && rc522.PICC_ReadCardSerial()){ //da li smo prislonili karticu i dal je netso procitano
            readUid(rc522);
            rc522.PICC_HaltA(); //neophodna kako bi se pripremio senzor za dalje ocitavanje
            //Serial.println(userUid); //ne moramo bas odmah da pisemo liniju

            if (iznos >= 3000.00) {
              Serial.println("Unesite PIN: ");
              pinNeeded = true;
              stanje = 2;
            }
            else {
              pinNeeded = false;
              stanje = 3;
            }
          }
        break;

      case 2: //cekamo da se unese pin
        if (Serial.available()) {
          delay(15);
          pin = Serial.parseInt();
          stanje = 3;
        }
        break;

      case 3: //proveravamo da li je uid pronadjen i da li je pin tacan
        found = false;
        for (i = 0; i < 2; i++) {
          if (stringsCheck(clientUids[i], userUid)) {
            found = true;
            break;
          }
        }

        if (!found) {
          Serial.println("NEVAZECA KARTICA");
          stanje = 0;
        }

        else if (pinNeeded) { //ulazimo ako je pin bio potreban
          if (pin == clientPins[i]) { //i-ti korisnikov PIN
            stanje = 4;
          }
          else {
            Serial.println("POGRESAN PIN");
            stanje = 0;
          }
        }

        else {
          stanje = 4;
        }
        break;

      case 4:
        if (clientMoney[i] >= iznos) {
          clientMoney[i] -= iznos;
          Serial.println("PRIHVACENO");
        }

        else {
          Serial.println("ODBIJENO");
        }

        stanje = 0;
        Serial.print(clientNames[i]);
        Serial.print(" | ");
        Serial.println(clientMoney[i]);
        break;

      default:
        break;
      
    }
}

void readUid(MFRC522 &rc522)
{
   String uidStr;
   String tmpStr;
  
   uidStr = "";
   for (byte i = 0; i < rc522.uid.size; i++)
   {
     tmpStr = String(rc522.uid.uidByte[i], HEX);
     tmpStr.toUpperCase();
     if (i)
     uidStr = String(uidStr + " ");
     if (rc522.uid.uidByte[i] < 0x10)
     uidStr = String(uidStr + "0");
    
     uidStr = String(uidStr + tmpStr);
   }
   strcpy(userUid, uidStr.c_str());
}

bool stringsCheck(char str1[], char str2[]) {
  int i = 0;

  while (str1[i] != 0 && str2[i] != 0) {//null terminator
    if (str1[i] != str2[i]) {
      return false;
    }
    i++;
  }

  return (str1[i] == str2[i]); //za poredjenje null terminatora (na kraju) sarma i sarmac situacija
}
