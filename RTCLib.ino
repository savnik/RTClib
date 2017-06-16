#include "RTClib.h"
#include "Arduino.h"
RTC_DS1342 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup(){
  Serial.begin(9600);
  while(!Serial){
    ; // wait for serial
  }
  Serial.println("RTC Lib test");

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  Serial.println("Set control register");
  rtc.init();

  Serial.println("RTC found!\nNow set time:");
  Serial.println(__DATE__);
  Serial.println(__TIME__);
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  Serial.println("Set alarm in 30 seconds");
  DateTime now = DateTime(F(__DATE__), F(__TIME__));
  rtc.setAlarm(1, now.second(), now.minute()+1, now.hour(), now.day());
  rtc.setAlarm(2, now.second(), now.minute()+1, now.hour(), now.day());
  rtc.interruptOutputMode(3);
  rtc.clearAlarm(1);
  rtc.clearAlarm(2);
  rtc.enableAlarm(1);
  rtc.enableAlarm(2);
  pinMode(13,INPUT);
  pinMode(12,INPUT_PULLUP);
  
}

void loop(){
  DateTime now = rtc.now();
    
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    
    Serial.print(" since midnight 1/1/1970 = ");
    Serial.print(now.unixtime());
    Serial.print("s = ");
    Serial.print(now.unixtime() / 86400L);
    Serial.println("d");


    if(digitalRead(12) == LOW){
      Serial.println("INTA");
      rtc.clearAlarm(1);
    }
    if(digitalRead(13) == LOW){
      Serial.println("INTB");
      rtc.clearAlarm(2);
    }
    
    Serial.println(rtc.readControlRegister(),BIN);
    Serial.println(rtc.readStatusRegister(),BIN);
    Serial.println(".");
    delay(3000);

}

