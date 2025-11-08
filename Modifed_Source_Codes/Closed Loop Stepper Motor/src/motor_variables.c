#include "motor_control.h"

// Global variable definitions
_iq Id_ref = _IQ(0.0);          // D-axis current reference
_iq Iq_ref = _IQ(0.0);          // Q-axis current reference
_iq speed_ref = _IQ(100.0);     // Speed reference (RPM)
_iq pos_ref = _IQ(0.0);         // Position reference (radians)
_iq torque_ref = _IQ(0.0);      // Torque reference (Nm)
_iq theta_e = _IQ(0.0);         // Electrical angle
_iq pos = _IQ(0.0);             // Measured position
_iq speed = _IQ(0.0);           // Measured speed
_iq Ia, Ib;                     // Phase currents
_iq Ialpha, Ibeta;              // Clarke transform outputs
_iq Id, Iq;                     // Park transform outputs
_iq Vd, Vq;                     // Voltage outputs
_iq Valpha, Vbeta;              // Inverse Park transform outputs
Uint32 encoder_pos;             // Encoder position
static Uint32 last_pos = 0;     // Previous encoder position
Uint16 led_state = 0;           // LED state
Uint32 loop_count = 0;          // Loop counter for LED
int control_mode = MODE_SPEED;  // Control mode (default: speed)
Uint16 i2c_buffer[2];           // I2C buffer for INA3221 reads
