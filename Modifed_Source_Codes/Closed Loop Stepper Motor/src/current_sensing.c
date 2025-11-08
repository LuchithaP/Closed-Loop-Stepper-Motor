#include "motor_control.h"

void read_currents(void) {
    int16_t raw_current;
    float current;

    EALLOW;
    I2caRegs.I2CSAR = INA3221_ADDR;
    I2caRegs.I2CCNT = 1;
    I2caRegs.I2CDXR = INA3221_CURRENT_REG_CH1;
    I2caRegs.I2CMDR.all = 0x0620;
    while (I2caRegs.I2CSTR.bit.BB == 1);
    while (I2caRegs.I2CSTR.bit.XRDY == 0);

    I2caRegs.I2CCNT = 2;
    I2caRegs.I2CMDR.all = 0x0420;
    while (I2caRegs.I2CSTR.bit.RRDY == 0);
    i2c_buffer[0] = I2caRegs.I2CDRR;
    while (I2caRegs.I2CSTR.bit.RRDY == 0);
    i2c_buffer[1] = I2caRegs.I2CDRR;
    raw_current = (i2c_buffer[0] << 8) | i2c_buffer[1];
    current = (float)raw_current * INA3221_CURRENT_LSB;
    Ia = _IQmpy(_IQ(current), _IQ(ADC_GAIN));

    I2caRegs.I2CCNT = 1;
    I2caRegs.I2CDXR = INA3221_CURRENT_REG_CH2;
    I2caRegs.I2CMDR.all = 0x0620;
    while (I2caRegs.I2CSTR.bit.BB == 1);
    while (I2caRegs.I2CSTR.bit.XRDY == 0);

    I2caRegs.I2CCNT = 2;
    I2caRegs.I2CMDR.all = 0x0420;
    while (I2caRegs.I2CSTR.bit.RRDY == 0);
    i2c_buffer[0] = I2caRegs.I2CDRR;
    while (I2caRegs.I2CSTR.bit.RRDY == 0);
    i2c_buffer[1] = I2caRegs.I2CDRR;
    raw_current = (i2c_buffer[0] << 8) | i2c_buffer[1];
    current = (float)raw_current * INA3221_CURRENT_LSB;
    Ib = _IQmpy(_IQ(current), _IQ(ADC_GAIN));
    EDIS;
}
