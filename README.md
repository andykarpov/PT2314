# PT2314
Arduino library to control PT2314 AKA ET2314 audio processor

## Example usage:
```c++
PT2314 audioswitch;
setup() {
  Wire.begin();
  audioswitch.init();
  audioswitch.gain(1);  // +3.75dB gain
  audioswitch.channel(0); // 0-3 => channel 1-4
  audioswitch.volume(100); // default volume is 0, so you get nothing out of the output. 100 = full volume.
}
```

## Useful snippets:

```c++
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
```
