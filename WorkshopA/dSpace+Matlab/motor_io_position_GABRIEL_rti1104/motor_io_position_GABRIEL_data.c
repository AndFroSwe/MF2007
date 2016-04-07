/*
 * motor_io_position_GABRIEL_data.c
 *
 * Code generation for model "motor_io_position_GABRIEL".
 *
 * Model version              : 1.29
 * Simulink Coder version : 8.7 (R2014b) 08-Sep-2014
 * C source code generated on : Thu Apr 07 03:37:21 2016
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
                                        * Referenced by: '<S8>/F_c'
                                        */
  0.0015,                              /* Variable: F_c_upper
                                        * Referenced by: '<S8>/Saturate to Fc'
                                        */
  0.0006,                              /* Variable: J1
                                        * Referenced by: '<S3>/Load inertia'
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

  /*  Expression: Gff_d.num{1}
   * Referenced by: '<S1>/Gff1'
   */
  { 12.099005131079366, -9.2062246782288568, 1.7512715282745919 },

  /*  Expression: Gff_d.den{1}
   * Referenced by: '<S1>/Gff1'
   */
  { 1.0, -0.8948044758364484, -0.10519552416355157 },
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Gff1'
                                        */
  0.0062831853071795866,               /* Expression: 2*pi/(1000)
                                        * Referenced by: '<S7>/fi1_scaling'
                                        */

  /*  Expression: Gfb_d.num{1}
   * Referenced by: '<S1>/Gff2'
   */
  { 113.94845669065847, -187.0357937903751, 77.731389080841723 },

  /*  Expression: Gfb_d.den{1}
   * Referenced by: '<S1>/Gff2'
   */
  { 1.0, -0.8948044758364484, -0.10519552416355157 },
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Gff2'
                                        */
  24.0,                                /* Expression: 24
                                        * Referenced by: '<S1>/Saturation'
                                        */
  -24.0,                               /* Expression: -24
                                        * Referenced by: '<S1>/Saturation'
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

  /*  Expression: Gff_d.num{1}
   * Referenced by: '<S2>/Gff1'
   */
  { 12.099005131079366, -9.2062246782288568, 1.7512715282745919 },

  /*  Expression: Gff_d.den{1}
   * Referenced by: '<S2>/Gff1'
   */
  { 1.0, -0.8948044758364484, -0.10519552416355157 },
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S2>/Gff1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/Integrator1'
                                        */

  /*  Expression: Gfb_d.num{1}
   * Referenced by: '<S2>/Gff2'
   */
  { 113.94845669065847, -187.0357937903751, 77.731389080841723 },

  /*  Expression: Gfb_d.den{1}
   * Referenced by: '<S2>/Gff2'
   */
  { 1.0, -0.8948044758364484, -0.10519552416355157 },
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S2>/Gff2'
                                        */
  24.0,                                /* Expression: 24
                                        * Referenced by: '<S2>/Saturation'
                                        */
  -24.0,                               /* Expression: -24
                                        * Referenced by: '<S2>/Saturation'
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
  0.31500000000000006,                 /* Expression: 2*pi/(1000)/Ts
                                        * Referenced by: '<S7>/w1_scaling'
                                        */
  0.0                                  /* Expression: 0
                                        * Referenced by: '<S7>/Reset enc'
                                        */
};
