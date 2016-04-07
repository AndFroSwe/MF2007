/*
 * motor_io_data.c
 *
 * Code generation for model "motor_io".
 *
 * Model version              : 1.28
 * Simulink Coder version : 8.7 (R2014b) 08-Sep-2014
 * C source code generated on : Wed Apr 06 14:40:23 2016
 *
 * Target selection: rti1104.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Custom
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "motor_io.h"
#include "motor_io_private.h"

/* Block parameters (auto storage) */
P_motor_io_T motor_io_P = {
  0.0015,                              /* Variable: F_c
                                        * Referenced by: '<S5>/F_c'
                                        */
  0.0015,                              /* Variable: F_c_upper
                                        * Referenced by: '<S5>/Saturate to Fc'
                                        */
  0.0006,                              /* Variable: J1
                                        * Referenced by: '<S1>/Load inertia'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/SinGenerator'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<Root>/SinGenerator'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<Root>/SignalSelector[0Square,1Sine]'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/SquareGenerator'
                                        */
  0.15915494309189535,                 /* Computed Parameter: SquareGenerator_Frequency
                                        * Referenced by: '<Root>/SquareGenerator'
                                        */
  -1.0,                                /* Expression: -1
                                        * Referenced by: '<Root>/Gain'
                                        */
  24.0,                                /* Expression: 24
                                        * Referenced by: '<S2>/Saturation'
                                        */
  -24.0,                               /* Expression: -24
                                        * Referenced by: '<S2>/Saturation'
                                        */
  0.020833333333333332,                /* Expression: 1/48
                                        * Referenced by: '<S2>/pwm_skalning'
                                        */
  0.5,                                 /* Expression: 0.5
                                        * Referenced by: '<S2>/pwm_offstet'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S2>/Enable[1_Off, 0_On]'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Integrator'
                                        */
  0.0697,                              /* Expression: motor.k
                                        * Referenced by: '<S1>/Gain1'
                                        */
  0.00062232142857142857,              /* Expression: motor.k/motor.R
                                        * Referenced by: '<S1>/k//R '
                                        */
  -0.0015,                             /* Expression: -F_c_lower
                                        * Referenced by: '<S5>/Saturate to Fc'
                                        */
  3.0,                                 /* Expression: const
                                        * Referenced by: '<S6>/Constant'
                                        */
  1.0E-5,                              /* Expression: motor.d
                                        * Referenced by: '<S5>/Vicous friction'
                                        */
  0.04,                                /* Expression: n^-2
                                        * Referenced by: '<S1>/Gain2'
                                        */
  7.46E-7,                             /* Expression: motor.J
                                        * Referenced by: '<S1>/Motor inertia'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Integrator1'
                                        */
  0.0062831853071795866,               /* Expression: 2*pi/(1000)
                                        * Referenced by: '<S4>/fi1_scaling'
                                        */
  0.57800000000000007,                 /* Expression: 2*pi/(1000)/Ts
                                        * Referenced by: '<S4>/w1_scaling'
                                        */
  0.0                                  /* Expression: 0
                                        * Referenced by: '<S4>/Reset enc'
                                        */
};
