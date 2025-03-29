#define LP5562_DEFAULT_ADDR 0x30

#define LP5562_REG_R_ILED 0x7
#define LP5562_REG_G_ILED 0x6
#define LP5562_REG_B_ILED 0x5
#define LP5562_REG_W_ILED 0xf
#define LP5562_REG_CHANNEL_BASE 2

class LP5562
{
    public:
        /**
         * Constructor
         */
        LP5562();

        /**
         * Initializes state of LP5562
         */
       bool begin(TwoWire &wirePort = Wire);

        /**
         * Sets all color channels. Values 0-255
         * 
         * @param red       Red channel
         * @param green     Green channel
         * @param blue      Blue channel
         * @param white     White channel
         */
        void setColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t white);

        /**
         * Sets ILED (max current per channel). Rounds to nearest step
         * 
         * @param iled      Max current in milliamps (mA). 
         */
        void setCurrent(uint8_t iled = 31);

        /**
         * Sets the value of a specific PWM channel
         * 
         * @param channel   PWM channel 0, 1, 2, 3 (White 0E)
         * @param value     PWM value 0-255
         */
        void setChannel(uint8_t channel, uint8_t value);

        /**
         * Sets the intensity of the red channel
         * 
         * @param value     Intensity 0-255
         */
        void setRed(uint8_t value);

        /**
         * Sets the intensity of the green channel
         * 
         * @param value     Intensity 0-255
         */
        void setGreen(uint8_t value);

        /**
         * Sets the intensity of the blue channel
         * 
         * @param value     Intensity 0-255
         */
        void setBlue(uint8_t value);

        /**
         * Sets the intensity of the white channel
         * 
         * @param value     Intensity 0-255
         */
        void setWhite(uint8_t value);

        /**
         * Writes to a register
         * 
         * @param reg       Register 0-7
         * @param value     Value 0-31
         */
        void writeReg(uint8_t reg, uint8_t value);

        /**
         * Maps colors to channels
         * 
         * @param red       Channel 0-2
         * @param green     Channel 0-2
         * @param blue      Channel 0-2
         * @param white     Channel 0-2
         */
        void mapColors(uint8_t red, uint8_t green, uint8_t blue, uint8_t white);

		/**
		 * Shutdown LP5562 for minimal power consumption 
		 * 
		 */
		void shutDown(void);

    private:
        /**
         * I2C address (usually hardcoded, but who knows what's out there)
         */
        uint8_t _addr;
        TwoWire *_i2cPort;
        /**
         * Channel map. Specifies which channels on the chip go to R, G, B or W.
         */
        uint8_t _red;
        uint8_t _green;
        uint8_t _blue;
        uint8_t _white;
};
