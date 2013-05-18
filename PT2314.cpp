/* Arduino PT2322 Library
 * Copyright (C) 2009 by oddWires
 *
 * This file is part of the Arduino PT2322 Library
 *
 * This Library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * <http://www.gnu.org/licenses/>.
 */ 

#include <Arduino.h>
#include <Wire.h>
#include <PT2314.h>

unsigned char PT2314::eq_table[] = {
	0,		// -14
	0,		// -13
	1,		// -12
	1,		// -11
	2,		// -10
	2,		// -9
	3,		// -8
	3,		// -7
	4,		// -6
	4,		// -5
	5,		// -4
	5,		// -3
	6,		// -2
	6,		// -1
	7,		// 0
	14,		// 1
	14,		// 2
	13,		// 3
	13,		// 4
	12,		// 5
	12,		// 6
	11,		// 7
	11,		// 8
	10,		// 9
	10,		// 10
	9,		// 11
	9,		// 12
	8,		// 13
	8,		// 14
};

int PT2314::volume_to_pt2314(int vol)
{
	return 63 - ((vol * 63) / 100);
}

int PT2314::eq_to_pt2314(int val)
{
	int r;

	if (val > 28) {
		return 0;
	}

	r = PT2314::eq_table[val];

	return r;
}

// helper method
int PT2314::writeI2CChar(unsigned char c) {
    Wire.beginTransmission(PT2314_I2C_ADDRESS); 
    Wire.write(c);   
    int rtnCode = Wire.endTransmission();
    return rtnCode;
} 

// initialize PT2314
int PT2314::init(void) {
	_volume = 0;
	_attenuationL = 100;
	_attenuationR = 100;
	_mute = false;
	_loudness = true;
	_channel = 0;
	_bass = 50;
	_treble = 50;

	updateAll();
	
	return 1;
}

void PT2314::volume(int v) {
	_volume = constrain(v, 0, 100);
	updateVolume();
}

void PT2314::muteOn(void) {   
	_mute = true;
	updateAttenuation();
	updateVolume();
}   

void PT2314::muteOff(void) {   
	_mute = false;
	updateAttenuation();
	updateVolume();
}   

void PT2314::channel(int ch) {
	_channel = constrain(ch, 0, 3);
	updateAudioSwitch();
}

void PT2314::loudnessOn(void) {   
	_loudness = true;
	updateAudioSwitch();
}   

void PT2314::loudnessOff(void) {   
	_loudness = false;
	updateAudioSwitch();
}   

void PT2314::attenuation(int l, int r) {
	_attenuationL = constrain(l, 0, 100);
	_attenuationR = constrain(r, 0, 100);
	updateAttenuation();
}
  
void PT2314::bass(int b) {   
	_bass = constrain(b, 0, 100);
	updateBass();
}      
   
void PT2314::treble(int t) {   
	_treble = constrain(t, 0, 100);
	updateTreble();
}

void PT2314::updateVolume() {
	unsigned int val = volume_to_pt2314(_volume);
	writeI2CChar(val);
}

void PT2314::updateAttenuation() {
	unsigned int aL = map(_attenuationL, 0, 100, 0b00011111, 0b00000000);
	unsigned int aR = map(_attenuationR, 0, 100, 0b00011111, 0b00000000);
	if (_mute) {
		writeI2CChar(0b11011111); 
		writeI2CChar(0b11111111);
	} else {
		writeI2CChar(0b11000000 | aL);
		writeI2CChar(0b11100000 | aR);
	}
}

void PT2314::updateAudioSwitch() {
	int audioByte = 0b01000000; // audio switch + gain +11.25dB.
	if (_loudness){
		audioByte |= 0x00;
	} else {
		audioByte |= 0x04;
	}
	audioByte |= _channel;
	writeI2CChar(audioByte);
}

void PT2314::updateBass() {
	unsigned int val = eq_to_pt2314(map(_bass, 0, 100, 0, 28));
	writeI2CChar(0x60 | val);
}

void PT2314::updateTreble() {
	unsigned int val = eq_to_pt2314(map(_treble, 0, 100, 0, 28));
	writeI2CChar(0x70 | val);
}

void PT2314::updateAll() {
	updateVolume();
	updateAttenuation();
	updateAudioSwitch();
	updateBass();
	updateTreble();
}
