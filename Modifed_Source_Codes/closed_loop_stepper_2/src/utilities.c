#include "motor_control.h"

void toggle_led(void) {
    led_state = !led_state;
    GpioDataRegs.GPBSET.bit.GPIO34 = led_state;
    GpioDataRegs.GPBCLEAR.bit.GPIO34 = !led_state;
}

_iq _IQsgn(_iq value) {
    if (_IQtoF(value) > 0) return _IQ(1.0);
    if (_IQtoF(value) < 0) return _IQ(-1.0);
    return _IQ(0.0);
}
