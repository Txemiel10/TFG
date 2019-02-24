const int baudRate = 9600;

#include "SoftwareSerial.h"
SoftwareSerial softSerial(2, 3); // RX, TX

void setup()
{
  Serial.begin(baudRate);
  softSerial.begin(baudRate);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
// enviar los datos de la consola serial al ESP-01,
// y mostrar lo enviado por el ESP-01 a nuestra consola
{
  
  if (softSerial.available())
  {
    Serial.print((char)softSerial.read());
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(200);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(200); 
  }
  if (Serial.available())
  {
    softSerial.print((char)Serial.read());
  }
}
