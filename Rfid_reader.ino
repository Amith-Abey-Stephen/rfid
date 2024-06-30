// CONNECT ALL PINSS REFER THE LINK
// https://youtu.be/pdBrvLGH0PE
/************************************************************************************
 * Created By: Tauseef Ahmad
 * Created On: December 31, 2021
 * 
 * Tutorial: https://youtu.be/pdBrvLGH0PE
 *
 * ****************************************************************************
 * Download Resources
 * **************************************************************************** 
 *  Download RFID library:
 *  https://github.com/miguelbalboa/rfid
 **********************************************************************************/

#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 21
#define RST_PIN 22
byte readCard[4];
String MasterTag = "22 98 73 21 ";
String tagID = "22 98 73 21";
// Create instances
MFRC522 mfrc522(SS_PIN, RST_PIN);



setup() function
void setup() 
{
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  delay(4);
  //Show details of PCD - MFRC522 Card Reader
  mfrc522.PCD_DumpVersionToSerial();
  Serial.println("--------------------------");
  Serial.println(" Access Control ");
  Serial.println("Scan Your Card>>");
}

 * loop() function
void loop() 
{
  getID();
  //Wait until new tag is available
  while (getID()) {
    if (tagID == MasterTag){
      Serial.println(" Access Granted!");
      Serial.println("--------------------------");
       //You can write any code here like, opening doors, 
       //switching ON a relay, lighting up an LED etc...
    }
    else{
      Serial.println(" Access Denied!");
      Serial.println("--------------------------");
    }
    delay(2000);
    Serial.println(" Access Control ");
    Serial.println("Scan Your Card>>");
  }
}


boolean getID() 
{
  // Getting ready for Reading PICCs
  //If a new PICC placed to RFID reader continue
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return false;
  }

  //Since a PICC placed get Serial and continue
  if ( ! mfrc522.PICC_ReadCardSerial()) {
  return false;
  }

  tagID = "";
  for ( uint8_t i = 0; i < 4; i++) {
  //readCard[i] = mfrc522.uid.uidByte[i];
  // Adds the 4 bytes in a single String variable
  tagID.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  tagID.toUpperCase();
  mfrc522.PICC_HaltA(); // Stop reading
  return true;
}
