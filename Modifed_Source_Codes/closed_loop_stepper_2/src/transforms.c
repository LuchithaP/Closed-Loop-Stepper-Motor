#include "motor_control.h"

void clarke_transform(void) {
    Ialpha = Ia;
    Ibeta = _IQmpy(_IQ(0.57735026919), Ia) + _IQmpy(_IQ(1.15470053838), Ib);
}

void park_transform(void) {
    _iq cos_theta = _IQcos(theta_e);
    _iq sin_theta = _IQsin(theta_e);
    Id = _IQmpy(Ialpha, cos_theta) + _IQmpy(Ibeta, sin_theta);
    Iq = _IQmpy(Ibeta, cos_theta) - _IQmpy(Ialpha, sin_theta);
}

void inv_park_transform(void) {
    _iq cos_theta = _IQcos(theta_e);
    _iq sin_theta = _IQsin(theta_e);
    Valpha = _IQmpy(Vd, cos_theta) - _IQmpy(Vq, sin_theta);
    Vbeta = _IQmpy(Vd, sin_theta) + _IQmpy(Vq, cos_theta);
}
