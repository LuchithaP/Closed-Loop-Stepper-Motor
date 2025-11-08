#include "motor_control.h"

extern Uint32 last_pos; // Defined in motor_variables.c

void read_encoder(void) {
    _iq delta_pos;
    encoder_pos = EQep1Regs.QPOSCNT;
    pos = _IQmpy(_IQ(encoder_pos), _IQ(2.0 * M_PI / ENCODER_COUNTS_PER_REV));
    theta_e = _IQmpy(_IQ(encoder_pos), _IQ(2.0 * M_PI / (200.0 * POLE_PAIRS)));
    delta_pos = _IQ(encoder_pos - last_pos);
    speed = _IQmpy(delta_pos, _IQ(60.0 / (0.0001 * 200.0 * POLE_PAIRS)));
    last_pos = encoder_pos;
}
