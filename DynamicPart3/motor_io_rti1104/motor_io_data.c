/*
 * motor_io_data.c
 *
 * Code generation for model "motor_io".
 *
 * Model version              : 1.20
 * Simulink Coder version : 8.7 (R2014b) 08-Sep-2014
 * C source code generated on : Fri Mar 04 14:12:40 2016
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
  0.001,                               /* Variable: F_c
                                        * Referenced by:
                                        *   '<S9>/Couloumb friction'
                                        *   '<S9>/Saturate to Fc'
                                        */
  1.0,                                 /* Variable: enable_karnop
                                        * Referenced by: '<S7>/Enable Karnop'
                                        */
  5.0,                                 /* Variable: n
                                        * Referenced by: '<S6>/n'
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
                                        * Referenced by: '<S8>/Integrator'
                                        */
  0.0697,                              /* Expression: motor.k
                                        * Referenced by: '<S8>/Current constant'
                                        */
  -0.001,                              /* Expression: -F_c
                                        * Referenced by: '<S9>/Saturate to Fc'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S8>/Integrator1'
                                        */
  3.0,                                 /* Expression: const
                                        * Referenced by: '<S10>/Constant'
                                        */
  3.8E-6,                              /* Expression: motor.d
                                        * Referenced by: '<S9>/Vicous friction'
                                        */
  3.8E-6,                              /* Expression: motor.d
                                        * Referenced by: '<S7>/Motor viscous friction'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S7>/Switch'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S5>/Unit Delay'
                                        */
  1.3404825737265416E+6,               /* Expression: 1/motor.J
                                        * Referenced by: '<S8>/Inertia of motor'
                                        */
  1.44E-6,                             /* Expression: J/n^2
                                        * Referenced by: '<S7>/Load Inertia after gear'
                                        */
  0.0697,                              /* Expression: motor.k
                                        * Referenced by: '<S8>/Gain3'
                                        */
  112.0,                               /* Expression: motor.R
                                        * Referenced by: '<S8>/Resistance in motor'
                                        */
  87.719298245614027,                  /* Expression: 1/motor.L
                                        * Referenced by: '<S8>/Inductance in motor'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S8>/Integrator2'
                                        */
  0.2,                                 /* Expression: 1/n
                                        * Referenced by: '<S6>/1//n2'
                                        */
  0.2,                                 /* Expression: 1/n
                                        * Referenced by: '<S6>/1//n'
                                        */
  0.2,                                 /* Expression: 1/n
                                        * Referenced by: '<S6>/1//n1'
                                        */
  0.0062831853071795866,               /* Expression: 2*pi/(1000)
                                        * Referenced by: '<S4>/fi1_scaling'
                                        */
  0.31415926535897931,                 /* Expression: 2*pi/(1000)/Ts
                                        * Referenced by: '<S4>/w1_scaling'
                                        */
  0.0                                  /* Expression: 0
                                        * Referenced by: '<S4>/Reset enc'
                                        */
};
