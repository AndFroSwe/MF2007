/*
 * motor_io_velocity_data.c
 *
 * Code generation for model "motor_io_velocity".
 *
 * Model version              : 1.31
 * Simulink Coder version : 8.7 (R2014b) 08-Sep-2014
 * C source code generated on : Fri Mar 11 10:25:49 2016
 *
 * Target selection: rti1104.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Custom
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "motor_io_velocity.h"
#include "motor_io_velocity_private.h"

/* Block parameters (auto storage) */
P_motor_io_velocity_T motor_io_velocity_P = {
  0.001,                               /* Variable: F_c
                                        * Referenced by:
                                        *   '<S5>/F_c'
                                        *   '<S5>/Saturate to Fc'
                                        */
  0.0006,                              /* Variable: J1
                                        * Referenced by: '<S1>/Load inertia'
                                        */

  /*  Variable: R_vector
   * Referenced by:
   *   '<Root>/G_fb_real'
   *   '<Root>/Gfb'
   *   '<Root>/Gff'
   *   '<Root>/Gff_real'
   */
  { 1.0, 0.0 },

  /*  Variable: S_vector
   * Referenced by:
   *   '<Root>/G_fb_real'
   *   '<Root>/Gfb'
   */
  { 35.693812195121943, 7952.80344332855 },

  /*  Variable: T_vector
   * Referenced by:
   *   '<Root>/Gff'
   *   '<Root>/Gff_real'
   */
  { 79.5280344332855, 39764.017216642751 },
  0.0062831853071795866,               /* Variable: quant
                                        * Referenced by: '<Root>/Quantizer'
                                        */
  11.423973285781067,                  /* Expression: 2*pi/(1000)/Ts
                                        * Referenced by: '<S4>/w1_scaling'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/G_fb_real'
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
                                        * Referenced by: '<Root>/Gff_real'
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
                                        * Referenced by: '<Root>/Gff'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Integrator'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Gfb'
                                        */
  24.0,                                /* Expression: 24
                                        * Referenced by: '<Root>/Saturation'
                                        */
  -24.0,                               /* Expression: -24
                                        * Referenced by: '<Root>/Saturation'
                                        */
  0.0697,                              /* Expression: motor.k
                                        * Referenced by: '<S1>/Gain1'
                                        */
  0.00062232142857142857,              /* Expression: motor.k/motor.R
                                        * Referenced by: '<S1>/k//R '
                                        */
  -0.001,                              /* Expression: -F_c
                                        * Referenced by: '<S5>/Saturate to Fc'
                                        */
  3.0,                                 /* Expression: const
                                        * Referenced by: '<S6>/Constant'
                                        */
  1.5E-5,                              /* Expression: motor.d
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
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S5>/Constant1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S5>/Switch1'
                                        */
  0.0062831853071795866,               /* Expression: 2*pi/(1000)
                                        * Referenced by: '<S4>/fi1_scaling'
                                        */
  0.0                                  /* Expression: 0
                                        * Referenced by: '<S4>/Reset enc'
                                        */
};
