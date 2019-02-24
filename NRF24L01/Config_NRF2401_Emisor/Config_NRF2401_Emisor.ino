#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//Conexiones de los pines:
//Vcc->3.3V
//GND->GND
//CSN->Pin8
//CE->Pin7
//MOSI->Pin11
//SCK->Pin13
//IRQ->Desconectado
//MISO->Pin12
// Load in the libraries

// Set the CE & CSN pins
#define CE_PIN   7
#define CSN_PIN 8

// This is the address used to send/receive
const byte rxAddr[6] = "00001";

// Create a Radio
RF24 radio(CE_PIN, CSN_PIN); 

void setup() {
  
  // Start up the Serial connection
  while (!Serial);
  Serial.begin(9600);
  
  // Start the Radio!
  radio.begin();
  radio.setAutoAck(false);
  
  // Power setting. Due to likelihood of close proximity of the devices, set as RF24_PA_MIN (RF24_PA_MAX is default)
  radio.setPALevel(RF24_PA_MIN); // RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  
  // Slower data rate for better range
  radio.setDataRate( RF24_250KBPS ); // RF24_250KBPS, RF24_1MBPS, RF24_2MBPS
  
  // Number of retries and set tx/rx address
  radio.setRetries(15, 15);
  radio.openWritingPipe(rxAddr);

  // Stop listening, so we can send!
  radio.stopListening();
}

void loop() {

  // Set up a message and a timestamp to it using millis()
  String str = "Hello world! "; 
  str += String( millis() );
  
  // http://stackoverflow.com/questions/7383606/converting-an-int-or-string-to-a-char-array-on-arduino
  // Length (with one extra character for the null terminator)
  int str_len = str.length() + 1; 
  
  // Prepare the character array (the buffer) 
  char char_array[str_len];
  
  // Copy it over 
  str.toCharArray(char_array, str_len);


  bool ok = radio.write(&char_array, sizeof(char_array));
  //reportamos por el puerto serial los datos enviados 
  if(ok)
  {
     // Let the ourside world know..
  Serial.print("Sent Message: ");
  Serial.print( char_array );
  Serial.println("");
   
  }
  else
  {
     Serial.println("no se ha podido enviar");
  }
  
  // Wait a short while before sending the other one
  delay(2000);
}
