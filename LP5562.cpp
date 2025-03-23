#include <Wire.h>

#include "Arduino.h"
#include "LP5562.h"


LP5562::LP5562() {
    _addr = LP5562_DEFAULT_ADDR;
    _red = 2;
    _green = 1;
    _blue = 0;
    _white = 12;
}

bool LP5562::begin(TwoWire &wirePort) {
    _i2cPort = &wirePort;
    _addr = LP5562_DEFAULT_ADDR;

    // Checking if sensor exists on the I2C line
    _i2cPort->beginTransmission(_addr);
	_i2cPort->write((uint8_t)0x00);
	if (_i2cPort->endTransmission())
		return false;

    setColor(0,0,0,0);
    writeReg(8, 1); // Set internal clock

    return true;
}

void LP5562::setColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t white) {
    setRed(red);
    setGreen(green);
    setBlue(blue);
    setWhite(white);
}

void LP5562::setRed(uint8_t value) {
	if(value != 0 && value < 8) 
		value = 8;
    setChannel(_red,(value>>3));
}

void LP5562::setGreen(uint8_t value) {
	if(value != 0 && value < 8) 
		value = 8;
    setChannel(_green,(value>>3));
}

void LP5562::setBlue(uint8_t value) {
	if(value != 0 && value < 8) 
		value = 8;

    setChannel(_blue,(value>>3));
}

void LP5562::setWhite(uint8_t value) {
	if(value != 0 && value < 8) 
		value = 8;

    setChannel(_white,(value>>3));
}

void LP5562::setChannel(uint8_t channel, uint8_t value) {
    writeReg(LP5562_REG_CHANNEL_BASE+channel, value);
}

void LP5562::writeReg(uint8_t reg, uint8_t value) {
    Wire.beginTransmission(_addr);
    Wire.write(((reg&0x7)<<5)|(value&0x1f)); // rrrvvvvv
    Wire.endTransmission();
}

void LP5562::setCurrent(uint8_t iled) {
    iled = (iled>30)?30:iled;

    writeReg(LP5562_REG_ILED, iled);
}

void LP5562::mapColors(uint8_t red, uint8_t green, uint8_t blue, uint8_t white) {
    _red = red;
    _green = green;
    _blue = blue;
    _white = white;
}

void LP5562::shutDown(void) {
	writeReg(0, 0);
}
