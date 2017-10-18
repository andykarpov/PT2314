# PT2314
Arduino library to control PT2314 AKA ET2314 audio processor

I made a few changes to andykarpov's PT2314 library, which is awesome BTW.
andykarpov made a default gain of 11.25dB which made the sound on my speakers clipped and distorted, 
so I changed the default values and added the variable _gain and the method gain() with which
you can set the desired gain from 0 to 3, which corresponds to 0dB, +3.75dB, +7.5dB and +11.25dB.

Example:

PT2314 audioswitch;
setup() {
  Wire.begin();
  audioswitch.init();
  audioswitch.gain(1);  // +3.75dB gain
  audioswitch.channel(0); // 0-3 => channel 1-4
  audioswitch.volume(100); // default volume is 0, so you get nothing out of the output. 100 = full volume.
}

// USEFUL SNIPPETS:

// FADE OUT
for (byte i=100; i>0; i=i-5) {
  audioswitch.volume(i);
  delay(20);
}

// FADE IN
for (byte i=0; i<=100; i=i+5) {
  audioswitch.volume(i);
  delay(20);
}
