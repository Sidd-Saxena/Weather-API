#include <SPI.h>
#include <Ethernet.h>
#include <TextFinder.h>


int preci;
int temp;
int hot = 12;
int cold = 9;
int rain = 6;
int wolv = 8;

byte mac[] = {0x2a, 0x00, 0x00, 0x7e, 0xd7, 0xab};
byte ip[] = {192, 168, 1, 102 };
byte server[] = {38, 102, 136, 138};


String location = "http://api.wunderground.com/api/118b54f2e8ec6b1b/conditions/q/CA/Los_Angeles.xml/ HTTP/1.0";
char inString[32]; // string for incoming serial data
int stringPos = 0; // string index counter
boolean startRead = false; // is reading?
EthernetClient client;
TextFinder finder(client);
 
void setup()
{
 
  Ethernet.begin(mac, ip);
  // Start Serial Port
  Serial.begin(9600);
  delay(6000);
  Serial.println("Setup...");
   Ethernet.begin(mac, ip);
    if (client.connect(server, 80))
  {
    
    
    Serial.println("Connect to Weather Service...");
    client.println("GET http://api.wunderground.com/api/118b54f2e8ec6b1b/conditions/q/CA/Los_Angeles.xml HTTP/1.0");
    client.println("HOST http://www.wunderground.com/weather/api/d/docs?d=index");
    
if (client.connected())
    client.println();
    Serial.println("Connected...");
  } 
  else
  {
    Serial.println(" Connection failed");
  } 
  
  pinMode(hot, OUTPUT);
  pinMode(cold, OUTPUT);
  pinMode(rain, OUTPUT);
  pinMode(wolv, OUTPUT);
}


void loop()
  {digitalWrite(wolv, HIGH);
  if (client.connected())
  finder.find ("temp_f");
  long val = finder.getValue();
  Serial.print ("Temperature  : ");
  Serial.println(val);
  
  finder.find ("relative_humidity");
  long val2 = finder.getValue();
  Serial.print ("Humidity : ");
  Serial.println(val2);
  
  finder.find ("precip_today_metric");
  long val3 = finder.getValue();
  Serial.print ("Rainfall  : ");
  Serial.println(val3);
  
  if (val3 >  0)
  {
     digitalWrite(rain, HIGH);
     delay(1000);
  }
  if(val >= 80)
  {
     digitalWrite(hot, HIGH);
     delay(1000);
  }
  else if (val >= 60)
  {
     digitalWrite(hot, HIGH);
     digitalWrite(cold, HIGH);
     delay(1000);
  }
  else
  {
     digitalWrite(cold, HIGH);
     delay(1000);
  }
}





 
  
  
  
  
  
  
  
  
 
  
  
