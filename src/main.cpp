#include <Arduino.h>
/*
* Getting Started example sketch for nRF24L01+ radios
* This is a very basic example of how to send data from one node to another
* Updated: Dec 2014 by TMRh20

    receiver script
*/

#include <SPI.h>
#include "RF24.h"

/****************** User Config ***************************/
/***      Set this radio as radio number 0 or 1         ***/

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(D1,D2); // CE, CSN
/**********************************************************/
int got_data =0;
int last_data =0;
byte addresses[][6] = {"1Node","2Node"};

void setup() {
  Serial.begin(9600);
  pinMode(D8, OUTPUT);

  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
 // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);
  radio.setChannel(120);

  radio.openReadingPipe(1,addresses[1]);

  // Start the radio listening for data
  radio.startListening();
}

void loop() {
    if( radio.available()){                                                        // Variable for the received timestamp
      while (radio.available()) {                                   // While there is data ready
        radio.read( &got_data, sizeof(unsigned long) );             // Get the payload

        if(got_data != last_data)
        {
          if(got_data == 1)
          {
            digitalWrite(D8, 1);
          }
          else
          {
            digitalWrite(D8, 0);
          }
        }
        last_data = got_data;
       }
      }

} // Loop
