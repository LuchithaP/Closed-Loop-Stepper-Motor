#include "motor_control.h"

// Read phase currents
void read_currents(void) {
    Ia = _IQmpy(_IQ(AdcResult.ADCRESULT0 - ADC_OFFSET), _IQ(ADC_GAIN));
    Ib = _IQmpy(_IQ(AdcResult.ADCRESULT1 - ADC_OFFSET), _IQ(ADC_GAIN));
}

