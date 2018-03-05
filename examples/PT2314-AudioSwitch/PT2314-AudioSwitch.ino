/*
 * Audio switch
 * MIT License
 * Copyright (c) 2017 Tomislav Tuksa https://github.com/ttuksa/
 * 
 * You can use this example to make a simple audio switch for 2, 3 or 4 channels with PT2314 audio processor
 * 
 * Requirements: my modified version of andykarpov's PT2314 library which has gain() method.
 * With gain() you can set the desired gain from 0 to 3, which corresponds to 0dB, +3.75dB, +7.5dB and +11.25dB, respectively.
 * 
 * Connect a simple button between pin 2 and GND. The pin should stay defined as INPUT_PULLUP, like in this sketch.
 * 
 * It has a nice fade out and fade in when switching channels.
 * The order of switching:
 * 1. Channel 1 + 0dB
 * 2. Channel 2 + 0dB
 * 3. Channel 1 + 11.25dB
 * 4. Channel 2 + 11.25dB
 * and again to step 1.
 * 
 */
#include <Wire.h>
#include <PT2314.h>

const int buttonPin = 2;
const int maxChannels = 2; // how many channels do you want? (4 is the physical maximum for PT2314).
uint8_t channel = 1;
bool loud = false; // this will be toggled later, don't touch.

PT2314 audioswitch;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  ledOff();
  delay(1000);
  Wire.begin();
  delay(1000);
  ledOn();
  audioswitch.init();
  audioswitch.gain(0);      // it starts with no added gain
  audioswitch.channel(0);   // switch to channel 1... 0-3 => channel 1-4
  audioswitch.volume(100);  // full volume
}

// LED helper functions
void ledOff() {
  digitalWrite(LED_BUILTIN, HIGH);
}

void ledOn() {
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  if (digitalRead(buttonPin)==LOW) {
    // Fade out
    ledOff();
    for (byte i=100; i>0; i=i-5) {
      audioswitch.volume(i);
      delay(20);
    }
    
    channel++;
    
    if (channel>maxChannels) {
      channel=1;
      // if you don't want it to change gain, just delete the "if-else" block underneath
      // and it will just cycle the channels. You can still set the desired gain by calling gain(value) where value is 0-3.
      if (loud) {
        audioswitch.gain(0);
        loud = false;
      } else {
        audioswitch.gain(3);
        loud = true;
      }
      // up to here
    }
    
    audioswitch.channel(channel - 1); // Minus 1 because physical channel 1 is channel 0 in the library.
    
    // Fade in
    for (byte i=0; i<=100; i=i+5) {
      audioswitch.volume(i);
      delay(20);
    }
    ledOn();
    
  }
}
