/*
 * motor_io_data.c
 *
 * Code generation for model "motor_io".
 *
 * Model version              : 1.26
 * Simulink Coder version : 8.7 (R2014b) 08-Sep-2014
 * C source code generated on : Sun Mar 06 14:16:21 2016
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
  0.0008,                              /* Variable: F_c
                                        * Referenced by:
                                        *   '<S7>/Constant'
                                        *   '<S7>/Couloumb friction'
                                        *   '<S7>/Saturate to Fc'
                                        */
  0.002,                               /* Variable: Ts
                                        * Referenced by:
                                        *   '<Root>/Quantizer'
                                        *   '<Root>/Quantizer1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Integrator'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Integrator1'
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
  0.0062831853071795866,               /* Expression: 2*pi/(1000)
                                        * Referenced by: '<S6>/fi1_scaling'
                                        */
  2.0,                                 /* Expression: P
                                        * Referenced by: '<S3>/Proportional Gain'
                                        */
  0.002,                               /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S3>/Integrator'
                                        */
  0.0,                                 /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S3>/Integrator'
                                        */
  1.0,                                 /* Expression: D
                                        * Referenced by: '<S3>/Derivative Gain'
                                        */
  0.002,                               /* Computed Parameter: Filter_gainval
                                        * Referenced by: '<S3>/Filter'
                                        */
  0.0,                                 /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S3>/Filter'
                                        */
  0.035836559690269741,                /* Expression: N
                                        * Referenced by: '<S3>/Filter Coefficient'
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
  2.0,                                 /* Expression: P
                                        * Referenced by: '<S2>/Proportional Gain'
                                        */
  0.002,                               /* Computed Parameter: Integrator_gainval_a
                                        * Referenced by: '<S2>/Integrator'
                                        */
  0.0,                                 /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S2>/Integrator'
                                        */
  1.0,                                 /* Expression: D
                                        * Referenced by: '<S2>/Derivative Gain'
                                        */
  0.002,                               /* Computed Parameter: Filter_gainval_l
                                        * Referenced by: '<S2>/Filter'
                                        */
  0.0,                                 /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S2>/Filter'
                                        */
  0.035836559690269741,                /* Expression: N
                                        * Referenced by: '<S2>/Filter Coefficient'
                                        */
  24.0,                                /* Expression: 24
                                        * Referenced by: '<S1>/Saturation'
                                        */
  -24.0,                               /* Expression: -24
                                        * Referenced by: '<S1>/Saturation'
                                        */
  0.0697,                              /* Expression: motor.k
                                        * Referenced by: '<S1>/Gain1'
                                        */
  0.00062232142857142857,              /* Expression: motor.k/motor.R
                                        * Referenced by: '<S1>/k//R '
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S7>/Constant1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S7>/Switch1'
                                        */
  -0.0008,                             /* Expression: -F_c
                                        * Referenced by: '<S7>/Saturate to Fc'
                                        */
  3.0,                                 /* Expression: const
                                        * Referenced by: '<S8>/Constant'
                                        */
  2.0E-5,                              /* Expression: motor.d
                                        * Referenced by: '<S7>/Vicous friction'
                                        */
  45000.0,                             /* Expression: 1/Jtot
                                        * Referenced by: '<S1>/1//J'
                                        */
  2.0,                                 /* Expression: I
                                        * Referenced by: '<S2>/Integral Gain'
                                        */
  2.0,                                 /* Expression: I
                                        * Referenced by: '<S3>/Integral Gain'
                                        */
  3.1415926535897931,                  /* Expression: 2*pi/(1000)/Ts
                                        * Referenced by: '<S6>/w1_scaling'
                                        */
  0.0                                  /* Expression: 0
                                        * Referenced by: '<S6>/Reset enc'
                                        */
};
