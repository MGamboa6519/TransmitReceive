#include <SPI.h>
#include <RF24.h>
#include <Wire.h>

int rBack = 3;
int rFront = 4;
int lBack = 5;
int lFront = 6;
int dc = 1;
 
RF24 radio(9, 10); // CE, CSN
 
void setup() {
  Wire.begin();
  radio.begin();
  radio.openReadingPipe(1, 0xF3F0F0E1LL);
  radio.startListening();
  Serial.begin(9600);
  pinMode(rBack, OUTPUT);
  pinMode(rFront, OUTPUT);
  pinMode(lBack, OUTPUT);
  pinMode(lFront, OUTPUT);
}
 
void loop() {
  if (radio.available()) {
    byte dataReceived;
    radio.read(&dataReceived, sizeof(dataReceived));
    if (dataReceived & (1 << 0)) {
      front();
      Serial.println("FRONT");
    }
    else if (dataReceived & (1 << 1)) {
      right();
      Serial.println("RIGHT");
    }
    else if (dataReceived & (1 << 2)) {
      back();
      Serial.println("BACK");
    }
    else if (dataReceived & (1 << 3)) {
      left();
      Serial.println("LEFT");
    }
    else {
      stop();
      Serial.println("STOP");
    }
    
    if (dataReceived & (1 << 4)) {
      dcMotor();
    }
    else {
      stopDcMotor();
    }
  }
}

void front() {
  rightFront();
  leftFront();
}

void back() {
  rightBack();
  leftBack();
}

void right() {
  rightBack();
  leftFront();
}

void left() {
  rightFront();
  leftBack();
}

void stop() {
  digitalWrite(rBack, LOW);
  digitalWrite(rFront, LOW);
  digitalWrite(lBack, LOW);
  digitalWrite(lFront, LOW);
}

void rightFront() {
  digitalWrite(rBack, LOW);
  digitalWrite(rFront, HIGH);
}

void rightBack() {
  digitalWrite(rBack, HIGH);
  digitalWrite(rFront, LOW);
}

void leftFront() {
  digitalWrite(lBack, LOW);
  digitalWrite(lFront, HIGH);
}

void leftBack() {
  digitalWrite(lBack, HIGH);
  digitalWrite(lFront, LOW);
}

void dcMotor(){
  digitalWrite(dc, HIGH);
  }

void stopDcMotor() {
  digitalWrite(dc, LOW);
}
