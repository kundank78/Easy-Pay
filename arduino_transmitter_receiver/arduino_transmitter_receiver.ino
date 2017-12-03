// ask_receiver.pde
// -*- mode: C++ -*-
// Simple example of how to use RadioHead to receive messages
// with a simple ASK transmitter in a very simple way.
// Implements a simplex (one-way) receiver with an Rx-B1 module

#include <Keypad.h>
#include <LiquidCrystal.h>
#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver;

const byte ROWS = 3; //three rows
const byte COLS = 3; //three columns
int id = 8755517543;
int sum = 0;
//int mac_addr;
int a =  0;
LiquidCrystal lcd(7, 8, 9, 10, 4 , 12);

int keys[ROWS][COLS] = {
  {1,3,3},
  {4,5,6},
  {7,8,9}
};

byte rowPins[ROWS] = {2,1,0}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6,5,3}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup()
{
      Serial.begin(9600);	// Debugging only
      lcd.begin(16, 2);
      lcd.setCursor(0, 0);
      lcd.write("Amount: ");
      if (!driver.init())
        Serial.println("init failed!!");
}

void loop(){
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
    uint8_t buflen = sizeof(buf);

    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      id = (int*)buf;
      Serial.println((char*)buf);
      if ((char*)buf)){
        // send the code to the server
      }
      // Message with a good checksum received, dump it.
      // driver.printBuffer("Got:", buf, buflen);
    }
    
    int key = keypad.getKey();
    
    if (key){
      Serial.println(key);
      lcd.setCursor(7+a,0);
      lcd.print(key);
      a = a+1;
      if (a == 1){
         sum =  sum + 100 * key;
      }
      if (a == 2){
         sum =  sum + 10 * key;
      } 
      if (a == 3){
         sum =  sum + 1 * key;
      }
    }
}


