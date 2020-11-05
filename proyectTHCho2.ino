



/*
 *  This sketch demonstrates how to scan WiFi networks.
 *  The API is almost the same as with the WiFi Shield library,
 *  the most obvious difference being the different file you need to include:
 */
#include "WiFi.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <ArduinoJson.h>

int LED17 = 17;


const char* ssid = "EUSKALTEL_D0011768";
const char* password = "HGWMUUWJ";

//json
char json[] = "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";

//pins func 17,


//sensor DHT1 gpio34
DHT dht1(17,DHT11); 
float ten1 = 00.0;
float humi1 = 00.0;

String scanTenperature1(){
  dht1.begin();
  float tenperature = dht1.readTemperature();
  if(!isnan(tenperature)){
      ten1 = tenperature;
      return String(ten1);

  }else{
     return String("none");
  }
}

String scanHumidity1(){
  dht1.begin();
  float humidity = dht1.readHumidity();
  if(!isnan(humidity)){
      humi1 = humidity;
      return String(humi1);
  }else{
     return String("none");
  }
}





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
//gpio egiaztatzeko funtzioa
void led(String led,boolean metode){
  if(metode == true){
      digitalWrite(17, HIGH);
  }else{
      digitalWrite(17, LOW);
   }
}
void setup()
{
    Serial.begin(115200);
    //pinMode(17, OUTPUT); 
    DynamicJsonDocument doc(1024);
    
    doc["sensor"] = "gps";
    doc["time"]   = 1351824120;
    doc["data"][0] = 48.756080;
    doc["data"][1] = 2.302038;
    
    serializeJson(doc, Serial);;
    //conesionWifi
   // wifiConect();
}

void loop()
{
    delay(5000);
    String tempe1 = scanTenperature1();
    delay(5000);
    String humi1 = scanHumidity1();
   
    //Serial.println("bai");
    Serial.println("DHT1 tenperature: "+tempe1);
    Serial.println("DHT1 humidity: "+humi1);
  //digitalWrite(17, HIGH); 
    delay(5000);
  //Serial.println("bai");                          
  //digitalWrite(17, LOW);  
  //delay(500);
}
