#ifndef MOTOR_VARIABLES_H
#define MOTOR_VARIABLES_H

#include "IQmathLib.h"

// External variable declarations
extern _iq Id_ref;              // D-axis current reference
extern _iq Iq_ref;              // Q-axis current reference
extern _iq speed_ref;           // Speed reference (RPM)
extern _iq pos_ref;             // Position reference (radians)
extern _iq torque_ref;          // Torque reference (Nm)
extern _iq theta_e;             // Electrical angle
extern _iq pos;                 // Measured position
extern _iq speed;               // Measured speed
extern _iq Ia, Ib;              // Phase currents
extern _iq Ialpha, Ibeta;       // Clarke transform outputs
extern _iq Id, Iq;              // Park transform outputs
extern _iq Vd, Vq;              // Voltage outputs
extern _iq Valpha, Vbeta;       // Inverse Park transform outputs
extern Uint32 encoder_pos;      // Encoder position
extern Uint16 led_state;        // LED state
extern Uint32 loop_count;       // Loop counter for LED
extern int control_mode;        // Control mode
extern Uint16 i2c_buffer[2];    // I2C buffer for INA3221 reads

#endif // MOTOR_VARIABLES_H
