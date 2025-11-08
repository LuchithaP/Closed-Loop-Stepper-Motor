#ifndef MOTOR_CONSTANTS_H
#define MOTOR_CONSTANTS_H

// Mathematical constants
#define M_PI 3.14159265358979323846

// Motor parameters
#define POLE_PAIRS 50           // NEMA 17: 200 steps/rev / 4 phases = 50 pole pairs
#define VDC 15.0                // DC bus voltage (V)
#define PWM_PERIOD 4500         // 10 kHz PWM (90 MHz / (2 * 4500))
#define CURRENT_MAX 2.0         // Max current (A)
#define SPEED_MAX 1000.0        // Max speed (RPM)
#define ENCODER_COUNTS_PER_REV (200.0 * POLE_PAIRS) // 10000 counts/rev
#define Kt 0.2                  // Torque constant (Nm/A)

// ADC and current sensing
#define ADC_OFFSET 0            // No offset for INA3221
#define ADC_GAIN 1.0            // Adjust for INA3221 scaling
#define INA3221_ADDR 0x40       // INA3221 I2C address (A0 = GND)
#define INA3221_CONFIG_REG 0x00 // INA3221 configuration register
#define INA3221_CURRENT_REG_CH1 0x01 // Channel 1 current (Ia)
#define INA3221_CURRENT_REG_CH2 0x03 // Channel 2 current (Ib)
#define SHUNT_RESISTANCE 0.05   // 0.05 ohm shunt (verify module specs)
#define INA3221_CURRENT_LSB (40e-6 / SHUNT_RESISTANCE) // 0.8 mA/LSB for 0.05 ohm

// PI controller gains
#define KP_D 0.5                // D-axis current proportional gain
#define KI_D 0.01               // D-axis current integral gain
#define KP_Q 0.5                // Q-axis current proportional gain
#define KI_Q 0.01               // Q-axis current integral gain
#define KP_SPEED 0.1            // Speed proportional gain
#define KI_SPEED 0.001          // Speed integral gain
#define KP_POS 0.5              // Position proportional gain
#define KI_POS 0.01             // Position integral gain
#define KP_TORQUE 0.5           // Torque proportional gain
#define KI_TORQUE 0.01          // Torque integral gain

// Control modes
#define MODE_POSITION 0         // Control mode: Position
#define MODE_SPEED 1            // Control mode: Speed
#define MODE_TORQUE 2           // Control mode: Torque

#endif // MOTOR_CONSTANTS_H
