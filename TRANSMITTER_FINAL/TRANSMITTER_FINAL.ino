#include <SPI.h>
#include <RF24.h>
 
RF24 radio(9, 10); // CE, CSN
 
#define BOTON_IZQ 2
#define BOTON_DER 3
#define JOYSTICK_X A0
#define JOYSTICK_Y A1
 
void setup() {
  radio.begin();
  radio.openWritingPipe(0xF3F0F0E1LL);
  radio.setPALevel(RF24_PA_LOW);    
 
  pinMode(BOTON_IZQ, INPUT_PULLUP);
  pinMode(BOTON_DER, INPUT_PULLUP);
  Serial.begin(9600);
}
 
void loop() {
  byte dataToSend = 0;
 
  dataToSend |= (!digitalRead(BOTON_IZQ) << 4);
  dataToSend |= (!digitalRead(BOTON_DER) << 5);
 
 
  int joystickX = analogRead(JOYSTICK_X);
  int joystickY = analogRead(JOYSTICK_Y);
 
  if (joystickX < 400)
    dataToSend |= (1 << 3);
  else if (joystickX > 600)
    dataToSend |= (1 << 1);
  else if (joystickY < 400)
    dataToSend |= (1 << 2);
  else if (joystickY > 600)
    dataToSend |= (1 << 0);
 
  radio.write(&dataToSend, sizeof(dataToSend));
  Serial.println(dataToSend);
  delay(20);
}
