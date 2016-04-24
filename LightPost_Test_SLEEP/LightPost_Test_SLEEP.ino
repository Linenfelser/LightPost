/*
  DigitalReadSerial
 Reads a digital input on pin 2, prints the result to the serial monitor

 This example code is in the public domain.
 */
#include <avr/interrupt.h>
#include <avr/power.h>
#include <avr/sleep.h>
#include <avr/io.h>

// digital pin 2 has a pushbutton attached to it. Give it a name:
int sensor =4;
int led = 3;

// the setup routine runs once when you press reset:
void setup() {
//  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(sensor, INPUT);
  pinMode(led, OUTPUT);
  pinMode(2,INPUT); //for interrupt
  digitalWrite(1,HIGH); //turn led on to see when awake or sleeping
}

// the loop routine runs over and over again forever:
void loop() {
  
  // read the input pin:
  int sensorState = digitalRead(sensor);
//  int sensorState = analogRead(sensor);
  delay(1);        // delay in between reads for stability
//  Serial.println(sensorState);
 
  if(sensorState != 0){
    int counter = 0;
    Blink(counter, sensorState);
  }
  else{  
    digitalWrite(led, LOW);
    delay(100);
    sleepNow();
  }
 
  
}

void sleepNow(void){
  digitalWrite(1,LOW);
  attachInterrupt(0,pinInterrupt,LOW);
  delay(1000);
  set_sleep_mode(SLEEP_MODE_PWR_SAVE);
  sleep_enable();
  sleep_mode();
  sleep_disable();
  digitalWrite(1,HIGH);
}
void pinInterrupt(void){
  detachInterrupt(0);
}

int Blink(int counter, int sensorState){
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    delay(100);
    

    int sensorState2 = digitalRead(sensor); //read sensor state again in order to determine coutner value
     
    if(sensorState2 != 0){ //if the sensor is currently pushed, dont start the timer/counter
      counter = 0;
    }
    else{
      counter ++;
    }
    
    if(counter <= 7 && sensorState !=0){ //if more than 60 seconds of no pressure, blink again
      Blink(counter,sensorState);
    }
    else{
     digitalWrite(led, LOW); //tunr off after a minute delay
    }
}




