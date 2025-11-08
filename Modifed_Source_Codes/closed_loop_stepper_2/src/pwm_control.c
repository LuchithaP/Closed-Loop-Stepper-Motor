void svgen_pwm(void) {
    _iq Va, Vb;
    Uint16 cmpa, cmpb;
    float temp;

    Va = Valpha;
    Vb = _IQmpy(_IQ(-0.5), Valpha) + _IQmpy(_IQ(0.86602540378), Vbeta);

    temp = _IQtoF(_IQmpy(_IQ(Va / VDC), _IQ(PWM_PERIOD / 2)) + _IQ(PWM_PERIOD / 2));
    if (temp > PWM_PERIOD) temp = PWM_PERIOD;
    else if (temp < 0) temp = 0;
    cmpa = (Uint16)temp;

    temp = _IQtoF(_IQmpy(_IQ(Vb / VDC), _IQ(PWM_PERIOD / 2)) + _IQ(PWM_PERIOD / 2));
    if (temp > PWM_PERIOD) temp = PWM_PERIOD;
    else if (temp < 0) temp = 0;
    cmpb = (Uint16)temp;

    EPwm1Regs.CMPA.half.CMPA = cmpa;
    EPwm2Regs.CMPA.half.CMPA = cmpb;
}
