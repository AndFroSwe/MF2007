/*
 * motor_io_position_GABRIEL_data.c
 *
 * Code generation for model "motor_io_position_GABRIEL".
 *
 * Model version              : 1.29
 * Simulink Coder version : 8.7 (R2014b) 08-Sep-2014
 * C source code generated on : Wed Apr 06 18:23:15 2016
 *
 * Target selection: rti1104.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Custom
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "motor_io_position_GABRIEL.h"
#include "motor_io_position_GABRIEL_private.h"

/* Block parameters (auto storage) */
P_motor_io_position_GABRIEL_T motor_io_position_GABRIEL_P = {
  0.0015,                              /* Variable: F_c
                                        * Referenced by: '<S7>/F_c'
                                        */
  0.0015,                              /* Variable: F_c_upper
                                        * Referenced by: '<S7>/Saturate to Fc'
                                        */
  0.0006,                              /* Variable: J1
                                        * Referenced by: '<S3>/Load inertia'
                                        */

  /*  Variable: R_sim
   * Referenced by:
   *   '<S1>/Gfb'
   *   '<S1>/Gff'
   *   '<S2>/Gfb'
   *   '<S2>/Gff'
   */
  { 1.0, -0.80443175214939378, -0.1955682478506062 },

  /*  Variable: S_sim
   * Referenced by:
   *   '<S1>/Gfb'
   *   '<S2>/Gfb'
   */
  { 258.59614086612646, -454.28461401807357, 200.59111578104344 },

  /*  Variable: T_sim
   * Referenced by:
   *   '<S1>/Gff'
   *   '<S2>/Gff'
   */
  { 13.618451747489638, -10.894761397991712, 2.1789522795983425 },
  0.0062831853071795866,               /* Variable: quant
                                        * Referenced by: '<Root>/Quantizer'
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
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S2>/Gff'
                                        */
  0.0062831853071795866,               /* Expression: 2*pi/(1000)
                                        * Referenced by: '<S6>/fi1_scaling'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S2>/Gfb'
                                        */
  24.0,                                /* Expression: 24
                                        * Referenced by: '<S2>/Saturation'
                                        */
  -24.0,                               /* Expression: -24
                                        * Referenced by: '<S2>/Saturation'
                                        */
  -1.0,                                /* Expression: -1
                                        * Referenced by: '<Root>/Gain'
                                        */
  24.0,                                /* Expression: 24
                                        * Referenced by: '<S4>/Saturation'
                                        */
  -24.0,                               /* Expression: -24
                                        * Referenced by: '<S4>/Saturation'
                                        */
  0.020833333333333332,                /* Expression: 1/48
                                        * Referenced by: '<S4>/pwm_skalning'
                                        */
  0.5,                                 /* Expression: 0.5
                                        * Referenced by: '<S4>/pwm_offstet'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S4>/Enable[1_Off, 0_On]'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/Integrator1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Gfb'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Gff'
                                        */
  24.0,                                /* Expression: 24
                                        * Referenced by: '<S1>/Saturation'
                                        */
  -24.0,                               /* Expression: -24
                                        * Referenced by: '<S1>/Saturation'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/Integrator'
                                        */
  0.0697,                              /* Expression: motor.k
                                        * Referenced by: '<S3>/Gain1'
                                        */
  0.00062232142857142857,              /* Expression: motor.k/motor.R
                                        * Referenced by: '<S3>/k//R '
                                        */
  -0.0015,                             /* Expression: -F_c_lower
                                        * Referenced by: '<S7>/Saturate to Fc'
                                        */
  3.0,                                 /* Expression: const
                                        * Referenced by: '<S8>/Constant'
                                        */
  1.0E-5,                              /* Expression: motor.d
                                        * Referenced by: '<S7>/Vicous friction'
                                        */
  0.04,                                /* Expression: n^-2
                                        * Referenced by: '<S3>/Gain2'
                                        */
  7.46E-7,                             /* Expression: motor.J
                                        * Referenced by: '<S3>/Motor inertia'
                                        */
  0.57800000000000007,                 /* Expression: 2*pi/(1000)/Ts
                                        * Referenced by: '<S6>/w1_scaling'
                                        */
  0.0                                  /* Expression: 0
                                        * Referenced by: '<S6>/Reset enc'
                                        */
};
