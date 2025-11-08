#include "motor_control.h"

void pi_current_control(void) {
    static _iq Id_error_int = _IQ(0.0), Iq_error_int = _IQ(0.0);
    _iq Id_error, Iq_error, Vmax;

    Id_error = Id_ref - Id;
    Iq_error = Iq_ref - Iq;
    Vmax = _IQ(VDC * 0.5);

    Id_error_int += _IQmpy(KI_D, Id_error);
    if (_IQabs(Id_error_int) > Vmax) Id_error_int = _IQmpy(Vmax, _IQsgn(Id_error_int));
    Iq_error_int += _IQmpy(KI_Q, Iq_error);
    if (_IQabs(Iq_error_int) > Vmax) Iq_error_int = _IQmpy(Vmax, _IQsgn(Iq_error_int));

    Vd = _IQmpy(KP_D, Id_error) + Id_error_int;
    Vq = _IQmpy(KP_Q, Iq_error) + Iq_error_int;

    if (_IQabs(Vd) > Vmax) Vd = _IQmpy(Vmax, _IQsgn(Vd));
    if (_IQabs(Vq) > Vmax) Vq = _IQmpy(Vmax, _IQsgn(Vq));
}

void pi_position_control(void) {
    static _iq pos_error_int = _IQ(0.0);
    _iq pos_error;

    pos_error = pos_ref - pos;
    pos_error_int += _IQmpy(KI_POS, pos_error);
    if (_IQabs(pos_error_int) > _IQ(CURRENT_MAX)) {
        pos_error_int = _IQmpy(_IQ(CURRENT_MAX), _IQsgn(pos_error_int));
    }

    Iq_ref = _IQmpy(KP_POS, pos_error) + pos_error_int;
    Id_ref = _IQ(0.0);

    if (_IQabs(Iq_ref) > _IQ(CURRENT_MAX)) {
        Iq_ref = _IQmpy(_IQ(CURRENT_MAX), _IQsgn(Iq_ref));
    }
}

void pi_speed_control(void) {
    static _iq speed_error_int = _IQ(0.0);
    _iq speed_error;

    speed_error = speed_ref - speed;
    speed_error_int += _IQmpy(KI_SPEED, speed_error);
    if (_IQabs(speed_error_int) > _IQ(CURRENT_MAX)) {
        speed_error_int = _IQmpy(_IQ(CURRENT_MAX), _IQsgn(speed_error_int));
    }

    Iq_ref = _IQmpy(KP_SPEED, speed_error) + speed_error_int;
    Id_ref = _IQ(0.0);

    if (_IQabs(Iq_ref) > _IQ(CURRENT_MAX)) {
        Iq_ref = _IQmpy(_IQ(CURRENT_MAX), _IQsgn(Iq_ref));
    }
}

void pi_torque_control(void) {
    static _iq torque_error_int = _IQ(0.0);
    _iq torque_error, torque_actual;

    torque_actual = _IQmpy(_IQ(Kt), Iq);
    torque_error = torque_ref - torque_actual;
    torque_error_int += _IQmpy(KI_TORQUE, torque_error);
    if (_IQabs(torque_error_int) > _IQ(CURRENT_MAX)) {
        torque_error_int = _IQmpy(_IQ(CURRENT_MAX), _IQsgn(torque_error_int));
    }

    Iq_ref = _IQmpy(KP_TORQUE, torque_error) + torque_error_int;
    Id_ref = _IQ(0.0);

    if (_IQabs(Iq_ref) > _IQ(CURRENT_MAX)) {
        Iq_ref = _IQmpy(_IQ(CURRENT_MAX), _IQsgn(Iq_ref));
    }
}
