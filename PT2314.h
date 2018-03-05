/* Arduino PT2314 Library
 * Copyright (C) 2013 by Andy Karpov <andy.karpov@gmail.com>
 *
 * This file is part of the Arduino PT2314 Library
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

#define  PT2314_I2C_ADDRESS			0x44

#define  PT2314_BASS_TONE_CONTROL   0x60 // 0b01100000 
#define  PT2314_TREBLE_TONE_CONTROL	0x70 // 0b01110000

#define  PT2314_AUDIO_BYTE			0x58 
#define  PT2314_AUDIO_BYTE_LOUD_ON	0x00
#define  PT2314_AUDIO_BYTE_LOAD_OFF 0x04

#define  PT2314_SPEAKER_ATTN_L   	0xc0 // 0b11000000
#define  PT2314_SPEAKER_ATTN_R   	0xe0 // 0b11100000
#define  PT2314_SPEAKER_ATTN_L_MUTE 0xdf 
#define  PT2314_SPEAKER_ATTN_R_MUTE 0xff 

#ifndef PT2314_h
#define PT2314_h

class PT2314 {
    
private:
	static unsigned char eq_table[];
	int _volume;
	int _attenuationL;
	int _attenuationR;
	bool _mute;
	bool _loudness;
	uint8_t _gain;
	int _channel;
	int _bass;
	int _treble;
	int volume_to_pt2314(int vol);
	int eq_to_pt2314(int val);
  int writeI2CChar(unsigned char c);
  bool updateVolume();
	bool updateAttenuation();
	bool updateAudioSwitch();
	bool updateBass();
	bool updateTreble();
	bool updateAll();
    
public:
    bool init(void);
    void muteOn(void); 
    void muteOff(void); 
    void volume(int v);
	void channel(int ch);
	void loudnessOn();
	void loudnessOff();
	void gain(int v);
	void attenuation(int l, int r); 
    void bass(int b); 
    void treble(int t);
};

#endif
