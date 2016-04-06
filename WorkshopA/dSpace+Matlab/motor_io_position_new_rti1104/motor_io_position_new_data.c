/*
 * motor_io_position_new_data.c
 *
 * Code generation for model "motor_io_position_new".
 *
 * Model version              : 1.29
 * Simulink Coder version : 8.7 (R2014b) 08-Sep-2014
 * C source code generated on : Wed Apr 06 22:37:50 2016
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
                                        * Referenced by: '<S10>/F_c'
                                        */
  0.0015,                              /* Variable: F_c_upper
                                        * Referenced by: '<S10>/Saturate to Fc'
                                        */
  0.0006,                              /* Variable: J1
                                        * Referenced by: '<S5>/Load inertia'
                                        */
  10.0,                                /* Variable: Kb
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
   *   '<S3>/Gff1'
   *   '<S3>/Gff2'
   *   '<S4>/Gff1'
   *   '<S4>/Gff2'
   */
  { 1.0, -1.086245261022224, 0.086245261022224018 },

  /*  Variable: S_sim
   * Referenced by:
   *   '<S1>/Gff2'
   *   '<S2>/Gff2'
   *   '<S3>/Gff2'
   *   '<S4>/Gff2'
   */
  { 144.51995109314527, -258.96433785868282, 116.58929291576712 },

  /*  Variable: T_sim
   * Referenced by:
   *   '<S1>/Gff1'
   *   '<S2>/Gff1'
   *   '<S3>/Gff1'
   *   '<S4>/Gff1'
   */
  { 23.832290558106795, -33.365206781349514, 11.677822373472328 },
  2.34735433780522,                    /* Variable: c0
                                        * Referenced by:
                                        *   '<S1>/Gain'
                                        *   '<S2>/Gain'
                                        */
  2.3473543378052746,                  /* Variable: c0_
                                        * Referenced by:
                                        *   '<S1>/Gain1'
                                        *   '<S2>/Gain1'
                                        */
  0.0062831853071795866,               /* Variable: quant
                                        * Referenced by: '<S8>/Quantizer'
                                        */

  /*  Expression: [d1_ d0_]
   * Referenced by: '<S1>/Gff'
   */
  { 23.832290558106795, 0.89976972255851539 },

  /*  Expression: [1 r0]
   * Referenced by: '<S1>/Gff'
   */
  { 1.0, -0.086245261022224018 },
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

  /*  Expression: [d1 d0]
   * Referenced by: '<S1>/PD part'
   */
  { 144.51995109314527, -116.79174110334277 },

  /*  Expression: [1 r0]
   * Referenced by: '<S1>/PD part'
   */
  { 1.0, -0.086245261022224018 },
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

  /*  Expression: [d1_ d0_]
   * Referenced by: '<S2>/Gff'
   */
  { 23.832290558106795, 0.89976972255851539 },

  /*  Expression: [1 r0]
   * Referenced by: '<S2>/Gff'
   */
  { 1.0, -0.086245261022224018 },
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

  /*  Expression: [d1 d0]
   * Referenced by: '<S2>/PD part'
   */
  { 144.51995109314527, -116.79174110334277 },

  /*  Expression: [1 r0]
   * Referenced by: '<S2>/PD part'
   */
  { 1.0, -0.086245261022224018 },
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S2>/PD part'
                                        */
  24.0,                                /* Expression: 24
                                        * Referenced by: '<S2>/Voltage Saturation '
                                        */
  -24.0,                               /* Expression: -24
                                        * Referenced by: '<S2>/Voltage Saturation '
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S2>/Gff1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S2>/Gff2'
                                        */
  0.0062831853071795866,               /* Expression: 2*pi/(1000)
                                        * Referenced by: '<S9>/fi1_scaling'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S4>/Gff1'
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
                                        * Referenced by: '<S4>/Gff2'
                                        */
  24.0,                                /* Expression: 24
                                        * Referenced by: '<S4>/Voltage Saturation '
                                        */
  -24.0,                               /* Expression: -24
                                        * Referenced by: '<S4>/Voltage Saturation '
                                        */
  -1.0,                                /* Expression: -1
                                        * Referenced by: '<Root>/Gain'
                                        */
  24.0,                                /* Expression: 24
                                        * Referenced by: '<S6>/Saturation'
                                        */
  -24.0,                               /* Expression: -24
                                        * Referenced by: '<S6>/Saturation'
                                        */
  0.020833333333333332,                /* Expression: 1/48
                                        * Referenced by: '<S6>/pwm_skalning'
                                        */
  0.5,                                 /* Expression: 0.5
                                        * Referenced by: '<S6>/pwm_offstet'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S6>/Enable[1_Off, 0_On]'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/Gff1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S5>/Integrator1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/Gff2'
                                        */
  24.0,                                /* Expression: 24
                                        * Referenced by: '<S3>/Voltage Saturation '
                                        */
  -24.0,                               /* Expression: -24
                                        * Referenced by: '<S3>/Voltage Saturation '
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S5>/Integrator'
                                        */
  0.0697,                              /* Expression: motor.k
                                        * Referenced by: '<S5>/Gain1'
                                        */
  0.00062232142857142857,              /* Expression: motor.k/motor.R
                                        * Referenced by: '<S5>/k//R '
                                        */
  -0.0015,                             /* Expression: -F_c_lower
                                        * Referenced by: '<S10>/Saturate to Fc'
                                        */
  3.0,                                 /* Expression: const
                                        * Referenced by: '<S11>/Constant'
                                        */
  1.0E-5,                              /* Expression: motor.d
                                        * Referenced by: '<S10>/Vicous friction'
                                        */
  0.04,                                /* Expression: n^-2
                                        * Referenced by: '<S5>/Gain2'
                                        */
  7.46E-7,                             /* Expression: motor.J
                                        * Referenced by: '<S5>/Motor inertia'
                                        */
  0.57800000000000007,                 /* Expression: 2*pi/(1000)/Ts
                                        * Referenced by: '<S9>/w1_scaling'
                                        */
  0.0                                  /* Expression: 0
                                        * Referenced by: '<S9>/Reset enc'
                                        */
};
