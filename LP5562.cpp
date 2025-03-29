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

    Wire.begin();
    writeReg(0x00, 0x40); // enable LP5562
    writeReg(0x08, 0x01); // Set internal clock
    writeReg(0x70, 0x00); // Direct control via I2C
    setColor(140,45,0,0);

    return true;
}

void LP5562::setColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t white) {
    setRed(red);
    setGreen(green);
    setBlue(blue);
    setWhite(white);
}

void LP5562::setRed(uint8_t value) {
    value = (value>255)?255:value;
    setChannel(_red, value);
}

void LP5562::setGreen(uint8_t value) {
    value = (value>255)?255:value;
    setChannel(_green, value);
}

void LP5562::setBlue(uint8_t value) {
	value = (value>255)?255:value;
    setChannel(_blue, value);
}

void LP5562::setWhite(uint8_t value) {
	value = (value>255)?255:value;
    setChannel(_white, value);
}

void LP5562::setChannel(uint8_t channel, uint8_t value) {
    writeReg(LP5562_REG_CHANNEL_BASE+channel, value);
}

void LP5562::writeReg(uint8_t reg, uint8_t value) {
    Wire.beginTransmission(_addr);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}

void LP5562::setCurrent(uint8_t iled) {
    iled = (iled>30)?30:iled;
    uint8_t iled_multiplyer = 8;
    uint8_t iled_value = iled * iled_multiplyer;
    iled_value = (iled_value>174)?174:iled_value;
    writeReg(LP5562_REG_R_ILED, iled_value);
    writeReg(LP5562_REG_G_ILED, iled_value);
    writeReg(LP5562_REG_B_ILED, iled_value);
    writeReg(LP5562_REG_W_ILED, iled_value);
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
