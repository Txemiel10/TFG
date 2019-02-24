#include <SoftwareSerial.h>
//La conexion del modulo con el arduino es la siguiente:
//VCC-Pin 8
//GND-GND
//RXD-Pin 11
//TXD-Pin 10
//EN-Pin 9

//9600 Y NUEVA LINEA

SoftwareSerial BT1(10, 11); // RX | TX
void setup()
  { pinMode(8, OUTPUT);        // Al poner en HIGH forzaremos el modo AT
    pinMode(9, OUTPUT);        // cuando se alimente de aqui
    
    digitalWrite(9, HIGH);     // Activamos la key del modulo
    delay (500) ;              // Espera antes de encender el modulo
    Serial.begin(9600);
    Serial.println("Levantando el modulo HC-06");
    
    digitalWrite (8, HIGH);    //Enciende el modulo
    Serial.println("Esperando comandos AT:");
    BT1.begin(9600); 
    BT1.write("AT?");
  }
 
void loop()
  {  if (BT1.available())
           Serial.write(BT1.read());
     if (Serial.available())
        BT1.write(Serial.read());
  }
