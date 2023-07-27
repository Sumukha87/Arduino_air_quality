#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTTYPE DHT11 
#include <SoftwareSerial.h>
SoftwareSerial B(10,11);
  // DHT 11
#define DHTPIN 5
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>



int sensorValue;
int digitalValue;
int sensePin = A5;
float outVo=0;
float sigVolt=0;
float dustLevel=0;
int x=100;



void setup()
{
  Serial.begin(9600); // sets the serial port to 9600
  dht.begin();
  B.begin(9600);
  sensor_t sensor;
  delayMS = sensor.min_delay / 1000;
  pinMode(13, OUTPUT);
  pinMode(2, INPUT);
  outVo = analogRead(sensePin);
  sigVolt = outVo*(5.0/1024);
  dustLevel = 0.17 * sigVolt - 0.1;
}

void loop()
{
  sensorValue = analogRead(0); // read analog input pin 0
  digitalValue = digitalRead(3);
  if (sensorValue > 400)
  {
    digitalWrite(13, HIGH);
  }
  else
    digitalWrite(13, LOW);


  Serial.print("-");
  Serial.print("The Quality of air is :");
  Serial.print(sensorValue, DEC);
  Serial.println(" ppm");// prints the value read
  Serial.print("The value of the MQ135 Digital sensor is :");
  Serial.println(digitalValue, DEC);
  if(digitalValue == 0){
    Serial.println("No Harmful Gases Detected");
  }
  else{
    Serial.println("HarmfulGases Detected");
  }
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  Serial.print(F("Temperature: "));
  Serial.print(event.temperature);
  Serial.println(F("°C"));
  dht.humidity().getEvent(&event);
  Serial.print(F("Humidity: "));
  Serial.print(event.relative_humidity);
  Serial.println(F("%"));

  

  Serial.print("The value from the sensor is :");
  Serial.println(outVo);
  Serial.print("The value signal voltage :");
  Serial.println(sigVolt,4);


  Serial.print("The Dust Density is :");
  Serial.println(dustLevel,4);
  B.print(sensorValue);
  B.print(",");
 
 
  B.print(digitalValue);
 
  B.print(",");
  dht.temperature().getEvent(&event);
  B.print(event.temperature);
 
  B.print(",");
  dht.humidity().getEvent(&event);
  B.print(event.relative_humidity);
  
  B.print(",");
  B.print(outVo);
  
  B.print(",");
  B.print(dustLevel);
 
  B.print(";");
 
  
  
  
  
  
  
  
  
  delay(delayMS);
  delay(1000); // wait 100ms for next reading
}