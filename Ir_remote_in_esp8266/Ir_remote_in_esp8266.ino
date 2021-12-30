
#include <Arduino.h>      //This library for use Arduino function like pinMode(), etc.
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <ESP_EEPROM.h>  //esp8266 not have any EEPROM. This library use little flash memory as like a EEPROM.


const uint16_t kRecvPin = 14; //Ir sensor pin (GPIO14)

IRrecv irrecv(kRecvPin);  //Initialize the ir sensor pin

decode_results results;
int tem;
          //All out put pins  
const int l0=16;      
const int l1=12;
const int l2=11;
const int fan=13;
const int d_led = 2;  //This is the data recive output led

void setup(){
  pinMode(l0,OUTPUT);
  pinMode(l1,OUTPUT);
  pinMode(l2,OUTPUT);
  pinMode(fan,OUTPUT);
  pinMode(d_led,OUTPUT);
  EEPROM.begin(20);       //Initialize the EEPROM. I need just 20bit. 
  Serial.begin(115200);
  irrecv.enableIRIn();  
  while (!Serial) 
    delay(50);
  Serial.println();
  Serial.print("IRrecvDemo is now running and waiting for IR message on Pin "); //just for debuging
  Serial.println(kRecvPin);
  }

void loop(){
  int l0s,l1s,l2s,fan_s;
  EEPROM.get(0,l0s);
  EEPROM.get(4,l1s);     //Recive data from EEPROM
  EEPROM.get(8,l2s);
  EEPROM.get(12,fan_s);
  digitalWrite(l0,l0s);
  digitalWrite(l1,l1s);
  digitalWrite(l2,l2s);
  digitalWrite(fan,fan_s);
 
  while (irrecv.decode(&results)) {
    serialPrintUint64(results.value,DEC);   //DEC for showing data in decimal. You can use BIN or HEX.
    Serial.println("");

          /*(results.value) return remote recive data.
             all decimal values are remote button short press code.*/
    if(results.value == 33441975){
      EEPROM.put(0,0);
      EEPROM.put(4,0);  //put function for insert data
      EEPROM.put(8,0);
      EEPROM.put(12,0);
      }
    else if(results.value == 33444015){
      EEPROM.get(0,tem);
      tem = ~tem;     //~ this is not oparetor
      EEPROM.put(0,tem);
        digitalWrite(d_led,HIGH);
        delay(5);
        digitalWrite(d_led,LOW);
        delay(5);
        digitalWrite(d_led,HIGH);
        delay(5);
        digitalWrite(d_led,LOW);
      }

    else if(results.value == 33478695){
      EEPROM.get(4,tem);    //get function for recive data
      tem = ~tem;
      EEPROM.put(4,tem);
        digitalWrite(d_led,HIGH);
        delay(5);
        digitalWrite(d_led,LOW);
        delay(5);
        digitalWrite(d_led,HIGH);
        delay(5);
        digitalWrite(d_led,LOW);
      }

   else if(results.value == 33486855){
      EEPROM.get(8,tem);
      tem = ~tem;
      EEPROM.put(8,tem);
        digitalWrite(d_led,HIGH);
        delay(5);
        digitalWrite(d_led,LOW);
        delay(5);
        digitalWrite(d_led,HIGH);
        delay(5);
        digitalWrite(d_led,LOW);
      }
   else if(results.value == 33435855){
      EEPROM.get(12,tem);
      tem = ~tem;
      EEPROM.put(12,tem);
        digitalWrite(d_led,HIGH);
        delay(5);
        digitalWrite(d_led,LOW);
        delay(5);
        digitalWrite(d_led,HIGH);
        delay(5);
        digitalWrite(d_led,LOW);
      }
    boolean r=EEPROM.commit();    // commit for save all EEPROM data permanently.
    irrecv.resume();
    delay(50);      //for run code slowly
  }
  
  }
