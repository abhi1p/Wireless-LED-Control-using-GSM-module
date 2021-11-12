/*
In numcheck function add your mobile number
*/

#include<SoftwareSerial.h>

int relayLED=6;
char msgArr[60];
char num[20];
String buff;
int msgLen=0;

SoftwareSerial sim(2,3 );

void setup() {
  Serial.begin(9600);

  //initializing gsm module
  sim.begin(9600);
  delay(2000);
  sim.println("AT");
  updates();
  sim.println("AT+CMGF=1");
  updates();
  sim.println("AT+CNMI=1,2,0,0,0");
  updates();
  sim.println("AT+CSQ");
  updates();
  delay(2000);

  //relay configure
  pinMode(relayLED,OUTPUT);
  digitalWrite(relayLED,HIGH);



}

void loop() {
  // put your main code here, to run repeatedly:
  readMsg();
}

void updates()
{
  delay(500);
    while(Serial.available())
  {
    sim.write(Serial.read());
  }
  while(sim.available())
  {
    Serial.write(sim.read());
  }

}

void readMsg()
{
  if(sim.available())
  {
    buff=sim.readString();  //received buffer
    String f=buff.substring(2,6);
    if(f=="+CMT")
    {
      String msg=buff.substring(51); //message from string buffer after 51
      msgLen=msg.length()-2;
      String Msg=msg.substring(0,msgLen); //removing 2 symbol character from message
      String mobileNum=buff.substring(9,22); //mobile number from 9,22
      ledOn(mobileNum,Msg);

  }
  }

}

void ledOn(String mobNum,String Msg)
{
  Serial.println(mobNum);
  Serial.println(Msg);
  if(numCheck(mobNum)&&(Msg=="ledon")) //turn on led
  {
    digitalWrite(relayLED,LOW);
    
  }
  else if(numCheck(mobNum)&&(Msg=="ledoff")) //turn of led
  {
    digitalWrite(relayLED,HIGH);
  }
}
bool numCheck(String num)
{
  if(num=="") //Add your mob number with country code
  {                                              //for ex- num=="+911234567890"
    return true;                                 //here country code is +91
  }
  else
  {
    return false;
  }
}
