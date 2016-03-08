/*
 * motor_io_data.c
 *
 * Code generation for model "motor_io".
 *
 * Model version              : 1.22
 * Simulink Coder version : 8.7 (R2014b) 08-Sep-2014
 * C source code generated on : Fri Mar 04 16:46:50 2016
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
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Integrator1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Integrator'
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
                                        * Referenced by: '<S3>/Saturation'
                                        */
  -24.0,                               /* Expression: -24
                                        * Referenced by: '<S3>/Saturation'
                                        */
  0.020833333333333332,                /* Expression: 1/48
                                        * Referenced by: '<S3>/pwm_skalning'
                                        */
  0.5,                                 /* Expression: 0.5
                                        * Referenced by: '<S3>/pwm_offstet'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S3>/Enable[1_Off, 0_On]'
                                        */
  0.0697,                              /* Expression: motor.k
                                        * Referenced by: '<Root>/Gain1'
                                        */
  0.00062232142857142857,              /* Expression: motor.k/motor.R
                                        * Referenced by: '<Root>/k//R '
                                        */
  3.8E-6,                              /* Expression: motor.d
                                        * Referenced by: '<Root>/Motor viscous friction'
                                        */
  457456.54162854532,                  /* Expression: 1/Jtot
                                        * Referenced by: '<Root>/1//J'
                                        */
  0.0062831853071795866,               /* Expression: 2*pi/(1000)
                                        * Referenced by: '<S5>/fi1_scaling'
                                        */
  0.31415926535897931,                 /* Expression: 2*pi/(1000)/Ts
                                        * Referenced by: '<S5>/w1_scaling'
                                        */
  0.0                                  /* Expression: 0
                                        * Referenced by: '<S5>/Reset enc'
                                        */
};