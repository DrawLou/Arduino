#include <SoftwareSerial.h>
SoftwareSerial ArduinoMaster(2,3);
String msg;
void setup(){
   Serial.begin(9600);
  ArduinoMaster.begin(9600);      
}
void loop(){
  readSerialPort();
  
  // Send answer to master
  if(msg!=""){
      Serial.print("Master sent : " );
      Serial.println(msg);
      ArduinoMaster.print(msg);
      msg="";
  }
}
void readSerialPort(){
 while (ArduinoMaster.available()) {
    delay(10);
    if (ArduinoMaster.available() >0) {
        char c = ArduinoMaster.read();  //gets one byte from serial buffer
        msg += c; //makes the string readString
    }
 }
 ArduinoMaster.flush();
}
