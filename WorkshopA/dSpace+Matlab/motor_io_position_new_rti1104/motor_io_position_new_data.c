/*
 * motor_io_position_new_data.c
 *
 * Code generation for model "motor_io_position_new".
 *
 * Model version              : 1.29
 * Simulink Coder version : 8.7 (R2014b) 08-Sep-2014
 * C source code generated on : Thu Apr 07 04:07:07 2016
 *
 * Target selection: rti1104.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Custom
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "motor_io_position_new.h"
#include "motor_io_position_new_private.h"

/* Block parameters (auto storage) */
P_motor_io_position_new_T motor_io_position_new_P = {
  0.0015,                              /* Variable: F_c
                                        * Referenced by: '<S8>/F_c'
                                        */
  0.0015,                              /* Variable: F_c_upper
                                        * Referenced by: '<S8>/Saturate to Fc'
                                        */
  0.0006,                              /* Variable: J1
                                        * Referenced by: '<S3>/Load inertia'
                                        */
  100000.0,                            /* Variable: Kb
                                        * Referenced by:
                                        *   '<S1>/Gain2'
                                        *   '<S2>/Gain2'
                                        */

  /*  Variable: R_sim
   * Referenced by:
   *   '<S1>/Gff1'
   *   '<S1>/Gff2'
   *   '<S2>/Gff1'
   *   '<S2>/Gff2'
   */
  { 1.0, -0.21395969335166476, -0.78604030664833524 },

  /*  Variable: S_sim
   * Referenced by:
   *   '<S1>/Gff2'
   *   '<S2>/Gff2'
   */
  { 13.260312718064553, -15.013624161393334, 4.8848145587514109 },

  /*  Variable: T_sim
   * Referenced by:
   *   '<S1>/Gff1'
   *   '<S2>/Gff1'
   */
  { 3.1950853131544035, -0.063901706263088068, 0.00031950853131544035 },
  1.7533216376841885,                  /* Variable: c0
                                        * Referenced by:
                                        *   '<S1>/Gain'
                                        *   '<S2>/Gain'
                                        */
  1.7533216376841894,                  /* Variable: c0_
                                        * Referenced by:
                                        *   '<S1>/Gain1'
                                        *   '<S2>/Gain1'
                                        */
  0.0062831853071795866,               /* Variable: quant
                                        * Referenced by: '<S6>/Quantizer'
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

  /*  Expression: [d1_ d0_]
   * Referenced by: '<S2>/Gff'
   */
  { 3.1950853131544035, 1.3780408613240207 },

  /*  Expression: [1 r0]
   * Referenced by: '<S2>/Gff'
   */
  { 1.0, 0.78604030664833524 },
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S2>/Gff'
                                        */

  /*  Expression: [0 1]
   * Referenced by: '<S2>/I part1'
   */
  { 0.0, 1.0 },

  /*  Expression: [1 -1]
   * Referenced by: '<S2>/I part1'
   */
  { 1.0, -1.0 },
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S2>/I part1'
                                        */

  /*  Expression: [0 1]
   * Referenced by: '<S2>/I part'
   */
  { 0.0, 1.0 },

  /*  Expression: [1 -1]
   * Referenced by: '<S2>/I part'
   */
  { 1.0, -1.0 },
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S2>/I part'
                                        */
  0.0062831853071795866,               /* Expression: 2*pi/(1000)
                                        * Referenced by: '<S7>/fi1_scaling'
                                        */

  /*  Expression: [d1 d0]
   * Referenced by: '<S2>/PD part'
   */
  { 13.260312718064553, -3.50663308101297 },

  /*  Expression: [1 r0]
   * Referenced by: '<S2>/PD part'
   */
  { 1.0, 0.78604030664833524 },
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S2>/PD part'
                                        */
  24.0,                                /* Expression: 24
                                        * Referenced by: '<S2>/Voltage Saturation '
                                        */
  -24.0,                               /* Expression: -24
                                        * Referenced by: '<S2>/Voltage Saturation '
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

  /*  Expression: [d1_ d0_]
   * Referenced by: '<S1>/Gff'
   */
  { 3.1950853131544035, 1.3780408613240207 },

  /*  Expression: [1 r0]
   * Referenced by: '<S1>/Gff'
   */
  { 1.0, 0.78604030664833524 },
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Gff'
                                        */

  /*  Expression: [0 1]
   * Referenced by: '<S1>/I part1'
   */
  { 0.0, 1.0 },

  /*  Expression: [1 -1]
   * Referenced by: '<S1>/I part1'
   */
  { 1.0, -1.0 },
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/I part1'
                                        */

  /*  Expression: [0 1]
   * Referenced by: '<S1>/I part'
   */
  { 0.0, 1.0 },

  /*  Expression: [1 -1]
   * Referenced by: '<S1>/I part'
   */
  { 1.0, -1.0 },
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/I part'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/Integrator1'
                                        */

  /*  Expression: [d1 d0]
   * Referenced by: '<S1>/PD part'
   */
  { 13.260312718064553, -3.50663308101297 },

  /*  Expression: [1 r0]
   * Referenced by: '<S1>/PD part'
   */
  { 1.0, 0.78604030664833524 },
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/PD part'
                                        */
  24.0,                                /* Expression: 24
                                        * Referenced by: '<S1>/Voltage Saturation '
                                        */
  -24.0,                               /* Expression: -24
                                        * Referenced by: '<S1>/Voltage Saturation '
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Gff1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Gff2'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S2>/Gff1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S2>/Gff2'
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
                                        * Referenced by: '<S8>/Saturate to Fc'
                                        */
  3.0,                                 /* Expression: const
                                        * Referenced by: '<S9>/Constant'
                                        */
  1.0E-5,                              /* Expression: motor.d
                                        * Referenced by: '<S8>/Vicous friction'
                                        */
  0.04,                                /* Expression: n^-2
                                        * Referenced by: '<S3>/Gain2'
                                        */
  7.46E-7,                             /* Expression: motor.J
                                        * Referenced by: '<S3>/Motor inertia'
                                        */
  0.057800000000000004,                /* Expression: 2*pi/(1000)/Ts
                                        * Referenced by: '<S7>/w1_scaling'
                                        */
  0.0                                  /* Expression: 0
                                        * Referenced by: '<S7>/Reset enc'
                                        */
};
