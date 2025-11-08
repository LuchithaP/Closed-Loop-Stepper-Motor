#include "motor_control.h"

__interrupt void timer0_isr(void) {
    read_currents();
    read_encoder();
    clarke_transform();
    park_transform();
    pi_current_control();
    inv_park_transform();
    svgen_pwm();

    switch (control_mode) {
        case MODE_POSITION:
            pi_position_control();
            break;
        case MODE_SPEED:
            pi_speed_control();
            break;
        case MODE_TORQUE:
            pi_torque_control();
            break;
    }

    CpuTimer0Regs.TCR.bit.TIF = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
