#include "motor_control.h"

// System initialization
void init_system(void) {
    InitSysCtrl(); // Initialize system clock (90 MHz)
    DINT; // Disable interrupts

    InitPieCtrl();
    IER = 0x0000; // Clear interrupt enable register
    IFR = 0x0000; // Clear interrupt flag register

    InitPieVectTable();
    EALLOW;
    PieVectTable.TINT0 = &timer0_isr; // Map Timer0 interrupt
    EDIS;

    // Configure LED (GPIO34)
    EALLOW;
    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0; // GPIO function
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1; // Output
    GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1; // LED off
    EDIS;

    // Enable Timer0 interrupt
    IER |= M_INT1;
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1; // Timer0 interrupt
}


// ADC initialization
void init_adc(void) {
    InitAdc(); // Initialize ADC module
    EALLOW; // Enable protected register access

    AdcRegs.ADCCTL1.bit.INTPULSEPOS = 1; // Interrupt pulse at end of conversion
    AdcRegs.ADCCTL1.bit.ADCBGPWD = 1;    // Power up band gap
    AdcRegs.ADCCTL1.bit.ADCPWDN = 1;     // Power up ADC

    AdcRegs.ADCSOC0CTL.bit.CHSEL = 0;    // SOC0: ADCINA0 (Ia)
    AdcRegs.ADCSOC1CTL.bit.CHSEL = 1;    // SOC1: ADCINA1 (Ib)
    AdcRegs.ADCSOC0CTL.bit.ACQPS = 6;    // Acquisition window: 6 cycles
    AdcRegs.ADCSOC1CTL.bit.ACQPS = 6;    // Acquisition window: 6 cycles
    AdcRegs.ADCSOC0CTL.bit.TRIGSEL = 5;  // Trigger: ePWM1 SOCA
    AdcRegs.ADCSOC1CTL.bit.TRIGSEL = 5;  // Trigger: ePWM1 SOCA

    AdcRegs.ADCINTSOCSEL1.bit.SOC1 = 1;  // SOC1 triggers ADCINT1
    AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;// Clear ADCINT1 flag
    AdcRegs.INTSEL1N2.bit.INT1E = 1;     // Enable ADCINT1
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;   // Enable PIE interrupt for ADCINT1

    EDIS; // Disable protected register access

    AdcRegs.ADCSOCFRC1.all = 0x0003;     // Force SOC0 and SOC1 to start
}

// eQEP initialization
void init_eqep(void) {
    InitEQep1Gpio();
    EALLOW;
    EQep1Regs.QEPCTL.bit.QPEN = 1; // Enable eQEP
    EQep1Regs.QDECCTL.bit.QSRC = 0; // Quadrature count mode
    EQep1Regs.QPOSMAX = 200 * POLE_PAIRS - 1; // Max position count
    EQep1Regs.QPOSINIT = 0; // Initial position
    EQep1Regs.QEPCTL.bit.PCRM = 0; // Position reset on index
    EQep1Regs.QEINT.bit.PCE = 1; // Position counter error interrupt
    EQep1Regs.QCLR.bit.PCE = 1; // Clear position error
    EDIS;
}

// PWM initialization
void init_pwm(void) {
    InitEPwm1Gpio();
    InitEPwm2Gpio();
    EALLOW;
    EPwm1Regs.TBCTL.bit.CTRMODE = 3; // Up-down count
    EPwm1Regs.TBPRD = PWM_PERIOD; // 10 kHz PWM
    EPwm1Regs.CMPA.half.CMPA = 0; // Initial compare value
    EPwm1Regs.AQCTLA.bit.CAU = 2; // Set on CMPA up
    EPwm1Regs.AQCTLA.bit.CAD = 1; // Clear on CMPA down
    EPwm1Regs.TBCTL.bit.PHSEN = 0; // Disable phaseCube
    EPwm2Regs.TBCTL.bit.CTRMODE = 3;
    EPwm2Regs.TBPRD = PWM_PERIOD;
    EPwm2Regs.CMPA.half.CMPA = 0;
    EPwm2Regs.AQCTLA.bit.CAU = 2;
    EPwm2Regs.AQCTLA.bit.CAD = 1;
    EPwm2Regs.TBCTL.bit.PHSEN = 0;

    EPwm1Regs.ETSEL.bit.SOCAEN = 1; // Enable SOCA
    EPwm1Regs.ETSEL.bit.SOCASEL = 1; // Trigger on period match
    EPwm1Regs.ETPS.bit.SOCAPRD = 1; // Trigger every period
    EDIS;

    InitCpuTimers();
    ConfigCpuTimer(&CpuTimer0, 90, 100); // 90 MHz, 100 us period (10 kHz)
    CpuTimer0Regs.TCR.bit.TSS = 0; // Start timer
}

//dead time initialization
void init_pwm_deadband(void) {
    EALLOW; // Enable protected register access

    // Configure Dead-Band for EPWM1 (EPWM1A and EPWM1B)
    EPwm1Regs.DBCTL.bit.OUT_MODE = 3; // Enable Dead-Band for both RED and FED
    EPwm1Regs.DBCTL.bit.POLSEL = 2;   // Active high complementary (AHC) mode
    EPwm1Regs.DBCTL.bit.IN_MODE = 0;  // EPWMxA is source for both RED and FED
    EPwm1Regs.DBRED.bit.DBRED = 8;    // Rising Edge Delay: ~80 ns (8 cycles at 90 MHz)
    EPwm1Regs.DBFED.bit.DBFED = 8;    // Falling Edge Delay: ~80 ns (8 cycles at 90 MHz)

    // Configure Dead-Band for EPWM2 (EPWM2A and EPWM2B)
    EPwm2Regs.DBCTL.bit.OUT_MODE = 3; // Enable Dead-Band for both RED and FED
    EPwm2Regs.DBCTL.bit.POLSEL = 2;   // Active high complementary (AHC) mode
    EPwm2Regs.DBCTL.bit.IN_MODE = 0;  // EPWMxA is source for both RED and FED
    EPwm2Regs.DBRED.bit.DBRED = 8;    // Rising Edge Delay: ~80 ns (8 cycles at 90 MHz)
    EPwm2Regs.DBFED.bit.DBFED = 8;    // Falling Edge Delay: ~80 ns (8 cycles at 90 MHz)

    EDIS; // Disable protected register access
}
