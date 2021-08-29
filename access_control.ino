#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN); 

int relay =8;
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

const byte ROWS = 4;  
const byte COLS = 4; 

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {A0, A1, A2, A3}; 
byte colPins[COLS] = {4,5,6,7}; 
char password[4] = {'5','1','7','3'};
char aux[4];
int c=0;


Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
#include <Adafruit_Fingerprint.h>

SoftwareSerial mySerial(2, 3);

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);


void setup(){
   Serial.begin(9600);
    lcd.init();
    lcd.backlight();
 pinMode(relay , OUTPUT);
lcd.print("pass finger card");
lcd.setCursor(0, 1);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  finger.begin(57600);
  
   }
  
void loop(){
  char key = keypad.getKey();
  getFingerprintIDez(); 
  
  if(finger.fingerID==1){
  lcd.setCursor(0,1);
  lcd.print("finger authorised");
  digitalWrite(relay , 1);
  delay (500);
  digitalWrite(relay , 0);
  delay(500);
  lcd.clear();
      lcd.home();
      lcd.print("pass finger card");
      lcd.setCursor(0, 1);
      finger.fingerID=2;
  }

  
  
  
  if (key){

    
    if(key !='D'){aux[c]=key; lcd.print('#'); c++;}
    else{
      if(c==4)
      {lcd.clear();
      for(int i=0;i<4;i++)
      {if(aux[i]==password[i])
      digitalWrite(relay , 1);
  delay (500);
  digitalWrite(relay , 0);
  delay(500);
      {if(aux[i]!=password[i])
      {break;}
      else
      {if(i==3)
      {digitalWrite(13,HIGH);
      delay(500);
      }}}}}
       else{lcd.home();for(int i=0;i<4;i++)
       {lcd.print("Enter rghit pass");
       delay(300);
       lcd.clear();
       delay(300);}
       }
        lcd.clear();
      lcd.home();
      lcd.print("pass finger card");
      lcd.setCursor(0, 1);
      digitalWrite(13,LOW);
      c=0;
    }
      
      }
      else if(! mfrc522.PICC_ReadCardSerial()) { 
        if ( ! mfrc522.PICC_IsNewCardPresent()) 
  { return;}
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
    if(mfrc522.uid.uidByte[i] < 0x10 ){
        Serial.print(" 0");
        content.concat( " 0" );
      }
      else{
          Serial.print(" ");
          content.concat( " ");
        }
     
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }  
Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "B4 3A DE 28") 
//change here the UID of the
//card/cards that you want to give access
  {
    lcd.setCursor(0,1);
    lcd.print("Authorized access");
    digitalWrite(relay , 1);
  delay (500);
  digitalWrite(relay , 0);
  delay(500);
    delay(3000);
  }
else   {
  lcd.setCursor(0,1);
    lcd.print(" Access denied");
    delay(1500);
  }
  mfrc522.PICC_HaltA();
  
        lcd.clear();
      lcd.home();
      lcd.print("pass finger card");
      lcd.setCursor(0, 1);
} 
 
  
  
}


      uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 

  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID; 
}
    
