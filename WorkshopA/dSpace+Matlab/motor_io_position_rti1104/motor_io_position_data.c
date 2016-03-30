/*
 * motor_io_position_data.c
 *
 * Code generation for model "motor_io_position".
 *
 * Model version              : 1.36
 * Simulink Coder version : 8.7 (R2014b) 08-Sep-2014
 * C source code generated on : Wed Mar 30 13:09:28 2016
 *
 * Target selection: rti1104.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Custom
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "motor_io_position.h"
#include "motor_io_position_private.h"

/* Block parameters (auto storage) */
P_motor_io_position_T motor_io_position_P = {
  0.001,                               /* Variable: F_c
                                        * Referenced by:
                                        *   '<S6>/F_c'
                                        *   '<S6>/Saturate to Fc'
                                        */
  0.0006,                              /* Variable: J1
                                        * Referenced by: '<S1>/Load inertia'
                                        */
  0.0062831853071795866,               /* Variable: quant
                                        * Referenced by: '<S4>/Quantizer'
                                        */
  0.0062831853071795866,               /* Expression: 2*pi/(1000)
                                        * Referenced by: '<S5>/fi1_scaling'
                                        */

  /*  Expression: Gfb_d_p.num{1}
   * Referenced by: '<Root>/Gfbreal'
   */
  { 71.908604653933878, -110.97253176497472, 43.237547882271912 },

  /*  Expression: Gfb_d_p.den{1}
   * Referenced by: '<Root>/Gfbreal'
   */
  { 1.0, -0.78133517755683024, -0.21866482244316982 },
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Gfbreal'
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

  /*  Expression: Gff_d_p.num{1}
   * Referenced by: '<Root>/Gffreal'
   */
  { 4.5933482453411276, -0.42978067602387926, 0.010053201913815757 },

  /*  Expression: Gff_d_p.den{1}
   * Referenced by: '<Root>/Gffreal'
   */
  { 1.0, -0.78133517755683024, -0.21866482244316982 },
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Gffreal'
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

  /*  Expression: Gff_d_p.num{1}
   * Referenced by: '<Root>/Gff'
   */
  { 4.5933482453411276, -0.42978067602387926, 0.010053201913815757 },

  /*  Expression: Gff_d_p.den{1}
   * Referenced by: '<Root>/Gff'
   */
  { 1.0, -0.78133517755683024, -0.21866482244316982 },
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Gff'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Integrator1'
                                        */

  /*  Expression: Gfb_d_p.num{1}
   * Referenced by: '<Root>/Gfb'
   */
  { 71.908604653933878, -110.97253176497472, 43.237547882271912 },

  /*  Expression: Gfb_d_p.den{1}
   * Referenced by: '<Root>/Gfb'
   */
  { 1.0, -0.78133517755683024, -0.21866482244316982 },
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Gfb'
                                        */
  24.0,                                /* Expression: 24
                                        * Referenced by: '<Root>/Saturation'
                                        */
  -24.0,                               /* Expression: -24
                                        * Referenced by: '<Root>/Saturation'
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
  -0.001,                              /* Expression: -F_c
                                        * Referenced by: '<S6>/Saturate to Fc'
                                        */
  3.0,                                 /* Expression: const
                                        * Referenced by: '<S7>/Constant'
                                        */
  1.5E-5,                              /* Expression: motor.d
                                        * Referenced by: '<S6>/Vicous friction'
                                        */
  0.04,                                /* Expression: n^-2
                                        * Referenced by: '<S1>/Gain2'
                                        */
  7.46E-7,                             /* Expression: motor.J
                                        * Referenced by: '<S1>/Motor inertia'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S6>/Constant1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S6>/Switch1'
                                        */
  0.17249825543467656,                 /* Expression: 2*pi/(1000)/Ts
                                        * Referenced by: '<S5>/w1_scaling'
                                        */
  0.0                                  /* Expression: 0
                                        * Referenced by: '<S5>/Reset enc'
                                        */
};
