

/*
 *  This sketch demonstrates how to scan WiFi networks.
 *  The API is almost the same as with the WiFi Shield library,
 *  the most obvious difference being the different file you need to include:
 */
#include "WiFi.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>

int LED17 = 17;


const char* ssid = "EUSKALTEL_D0011768";
const char* password = "HGWMUUWJ";

//sensor DHT1 gpio34
DHT dht1(34,DHT11); 
float ten1 = 00.0;

String scanTenperature1(){
  float tenperature = dht1.readTemperature();
  if(!isnan(tenperature)){
      if(ten1 != tenperature){
           ten1 = tenperature;
           return String(ten1);
      }
  }else{
     return String("none");
  }
}
//
//sensor DHT2 gpio35
DHT dht2(35,DHT11); 
float ten2 = 00.0;

String scanTenperature2(){
  float tenperature = dht2.readTemperature();
  if(!isnan(tenperature)){
      if(ten2 != tenperature){
           ten2 = tenperature;
           return String(ten2);
      }
  }else{
     return String("none");
  }
}
//
//sensor DHT3 gpio32
DHT dht3(32,DHT11); 
float ten3 = 00.0;

String scanTenperature3(){
  float tenperature = dht3.readTemperature();
  if(!isnan(tenperature)){
      if(ten3 != tenperature){
           ten3 = tenperature;
           return String(ten3);
      }
  }else{
     return String("none");
  }
}
//
//sensor DHT4 gpio33
DHT dht4(33,DHT11); 
float ten4 = 00.0;

String scanTenperature4(){
  float tenperature = dht4.readTemperature();
  if(!isnan(tenperature)){
      if(ten4 != tenperature){
           ten4 = tenperature;
           return String(ten4);
      }
  }else{
     return String("none");
  }
}
//
//sensor DHT5 gpio25
DHT dht5(25,DHT11); 
float ten5 = 00.0;

String scanTenperature5(){
  float tenperature = dht5.readTemperature();
  if(!isnan(tenperature)){
      if(ten5 != tenperature){
           ten5 = tenperature;
           return String(ten5);
      }
  }else{
     return String("none");
  }
}
//



//wifiConectfucn
void wifiConect(){
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    //confirmar conexion
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    if(WiFi.status() == WL_CONNECTED){
      digitalWrite(LED17, HIGH);
    }
}
//
void setup()
{
    Serial.begin(115200);
    pinMode(LED17, OUTPUT); 
    delay(10);
    //conesionWifi
   // wifiConect();
}

void loop()
{
    delay(500);
    String tempe1 = scanTenperature1();
    if(tempe1 != "none"){
      Serial.println("DHT1: "+tempe1);
    }
  /*digitalWrite(LED, HIGH); 
  Serial.println("led on");
  delay(1000);                          
  digitalWrite(LED, LOW);  
  Serial.println("led off");  
  delay(2000);*/  
}
