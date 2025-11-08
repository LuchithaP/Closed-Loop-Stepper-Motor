#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "F2806x_Device.h"
#include "F2806x_Examples.h"
#include "F2806x_I2c.h"
#include "IQmathLib.h"
#include "F2806x_EPwm.h"
#include "F2806x_EQep.h"
#include "F2806x_Gpio.h"
#include "F2806x_Adc.h"
#include <stdint.h>

// Include all module headers
#include "motor_constants.h"
#include "motor_variables.h"
#include "system_init.h"
#include "current_sensing.h"
#include "encoder_interface.h"
#include "pwm_control.h"
#include "transforms.h"
#include "pi_controllers.h"
#include "interrupts.h"
#include "utilities.h"

#endif // MOTOR_CONTROL_H
