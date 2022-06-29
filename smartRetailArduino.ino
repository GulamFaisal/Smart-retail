

#include <SPI.h>
#include <RFID.h>

#define SS_PIN 10
#define RST_PIN 9
RFID rfid(SS_PIN, RST_PIN);
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <ArduinoJson.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);

String rfidCard;
int a;

String Bill;
double total = 0;
int count_prod = 0;

void setup() {
       // Initiate the serial communication
  Serial.begin(9600);
  Serial.println("Starting the RFID Reader...");
    Serial.println("CLEARDATA");
    Serial.println("Product    Price     Total");
  SPI.begin();
  rfid.init();

  pinMode(9, OUTPUT);
  pinMode(8,INPUT_PULLUP);    //Push Button
  pinMode(5, OUTPUT);         //Green LED
  pinMode(6, OUTPUT);         //BUZZER
  pinMode(7, OUTPUT);         //Red LED
  pinMode(2,OUTPUT);          //NodeMCU
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(A3,OUTPUT);
  pinMode(A7,OUTPUT);
  double total=0;
// Initialization

  
 lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" AUTOMATIC BILL");
  delay (2000);
  lcd.setCursor(0, 1);
  lcd.print("  SHOPPING CART       ");
  delay (2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   Welcome to ");
  lcd.setCursor(0, 1); 
  lcd.print("   MJCET MART  ");

}

void loop() {
  String prod="";
  double price=0.00;
  int a=digitalRead(8);
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      rfidCard = String(rfid.serNum[0]) + " " + String(rfid.serNum[1]) + " " + String(rfid.serNum[2]) + " " + String(rfid.serNum[3]);
      
      if (rfidCard == "211 244 99 151")
      {
        prod="Milk  ";
        price=30.00;
        digitalWrite(4,HIGH);
        delay(1000);
        digitalWrite(4,LOW);

        
        Serial.println(rfidCard);
      } 
    
      
     else if(rfidCard == "178 196 235 25")
      {
        prod="Coca Cola";
        price=39.00;
        digitalWrite(3,HIGH);
        delay(1000);
        digitalWrite(3,LOW);
       
        Serial.println(rfidCard);
      }
 
      else if (rfidCard == "225 192 104 25")
      {
        prod="Trimmer";
        price=400.00;

        digitalWrite(2,HIGH);
        delay(1000);
        digitalWrite(2,LOW);
        Serial.println(rfidCard);
      }
      
      else if (rfidCard == "179 33 94 10")
      {
        prod="Sugar";
        price=50.00;
        digitalWrite(5,HIGH);
        delay(1000);
        digitalWrite(5,LOW);
       
        Serial.println(rfidCard);
      }
    
      else if (rfidCard == "211 58 95 25")
      {
        prod="Battery";
        price=80.00;
        digitalWrite(A3,HIGH);
        delay(1000);
       digitalWrite(A3,LOW);

        Serial.println(rfidCard);
      }
   
      else
      {
      lcd.setCursor(0, 0);
        lcd.print("Product Not Found       ");
      }
       
      
        if(a==1)
        {
        lcd.setCursor(0,0);
        lcd.print((String)prod + " Added       ");
        lcd.setCursor(0, 1);
        lcd.print("Price(Rm): ");
        lcd.print(price);
        digitalWrite(A7,HIGH);
        digitalWrite(6,LOW);
        digitalWrite(7,LOW);
        delay(1000);
        total = total + price;
        
        count_prod++;
        digitalWrite(A7,LOW);
        digitalWrite(6,HIGH);
        digitalWrite(7,HIGH);
        delay(500);
        }
        else if(a==0)
      {
        price=-price;
        lcd.setCursor(0, 0);
        lcd.print((String)prod+" Removed       ");
        digitalWrite(A7,LOW);
        digitalWrite(6,LOW);
        digitalWrite(7,HIGH);
        delay(1000);
        total = total + price;
        count_prod--;
        digitalWrite(A7,HIGH);
        digitalWrite(6,HIGH);
        digitalWrite(7,LOW);
        delay(500);
      }
        lcd.setCursor(0, 1);
        lcd.print("Total price:");
        lcd.print(total);
        digitalWrite(A7,HIGH);
        digitalWrite(6,LOW);
        digitalWrite(7,HIGH);
        delay(2000);
        digitalWrite(A7,LOW);
        digitalWrite(6,LOW);
        digitalWrite(7,LOW);
        delay(1000);
        Bill=((String)prod +  "........"+ "  "  +  price+  "........   " + "   "  +  total);
        Serial.println(Bill);
    
    }
    rfid.halt();
  }
}

