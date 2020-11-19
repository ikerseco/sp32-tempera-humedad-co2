/*
 *  This sketch demonstrates how to scan WiFi networks.
 *  The API is almost the same as with the WiFi Shield library,
 *  the most obvious difference being the different file you need to include:
 */
#include  <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <EspMQTTClient.h>



//pin LED digital pin 0
int PIN0 = 0;
//pin DTH11 digital pin 17,
int PIN17 = 17;
//pin buzzer digital pin 16
int PIN16 = 16;
//pin MQ-2 analog pin 36
int PIN36 = 36;


//mqtt
EspMQTTClient client(
  "EUSKALTEL_D0011768",
  "HGWMUUWJ",
  "192.168.0.14",  // MQTT Broker server ip
  "TestClient",// Client name that uniquely identify your device
  1883
  );





//sensor DHT1 gpio17
DHT dht1(PIN17,DHT11); 
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
/*
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
      digitalWrite(PIN0, HIGH);
    }
}


*/
//gpio egiaztatzeko led funtzioa
void led(int led,boolean metode){
  if(metode == true){
      digitalWrite(led, HIGH);
  }else{
      digitalWrite(led, LOW);
   }
}

//buzzer korreonte actiboaren alarma funtzioa, pin analog 1
void buzzerAc(int pin,boolean metodo){
    if(metodo == true){
      digitalWrite(pin, HIGH);
  }else{
      digitalWrite(pin, LOW);
   }
} 


//buzzer korreonte alternoaren alarma funtzioa, pin analog 16
void buzzerAL(int pin,boolean metodo,int Max,int Min){
  if(metodo == true){
    ledcSetup(0, Max, Min); // setup beeper
    ledcAttachPin(pin, 0); // attach beeper
    ledcWriteTone(0, 200); // play tone 
  }else{
    ledcAttachPin(pin, 1);
  }
} 


//MQ-2 funtzioa
boolean MQ2(int Media,int buzzer,int analog){
   int analogSensor = analogRead(analog);
   delay(500);
   if (analogSensor > Media){
      Serial.println("GAS:"+ String(analogSensor));
      buzzerAL(buzzer,true,100,10);
      return boolean(true);
    }
    else{
      Serial.println("GAS:"+ String(analogSensor));
      buzzerAL(buzzer,false,100,10); 
      return boolean(false);
    }
}



void setup()
{
    Serial.begin(115200);
     client.enableDebuggingMessages();//
    //led digital
    pinMode(PIN0,OUTPUT);
    //buzzer corriente activa Digital OUTPUT
    pinMode(PIN16,OUTPUT);
    //MQ-2 sensor Analogic INPUT
    pinMode(36,INPUT);
    //pinMode(PIN4,OUTPUT);
    //conesionWifi
    delay(5000);
    client.loop();
}


void onConnectionEstablished() {
  client.subscribe("test", [] (const String &payload)  {
    Serial.println(payload);
  });
}



void loop()
{
    client.loop();
    long now = millis();
    if (now - 0 > 15000) {
        Serial.println("procesing...");
        String tempe1 = scanTenperature1();
        delay(2000);
        String humi1 = scanHumidity1();
        delay(2000);
        boolean datMq1 = MQ2(1100,PIN16,PIN36);
        delay(2000);
        Serial.println("DHT1 tenperature: "+tempe1);
        Serial.println("DHT1 humidity: "+humi1);
        String DatTotal = tempe1+"/"+humi1+"/"+datMq1;
        Serial.println(DatTotal);
    }
}
