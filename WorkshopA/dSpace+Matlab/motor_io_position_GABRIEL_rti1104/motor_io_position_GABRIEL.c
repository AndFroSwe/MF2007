/*
 * motor_io_position_GABRIEL.c
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
#include "motor_io_position_GABRIEL_trc_ptr.h"
#include "motor_io_position_GABRIEL.h"
#include "motor_io_position_GABRIEL_private.h"

/* Block signals (auto storage) */
B_motor_io_position_GABRIEL_T motor_io_position_GABRIEL_B;

/* Continuous states */
X_motor_io_position_GABRIEL_T motor_io_position_GABRIEL_X;

/* Block states (auto storage) */
DW_motor_io_position_GABRIEL_T motor_io_position_GABRIEL_DW;

/* Previous zero-crossings (trigger) states */
PrevZCX_motor_io_position_GAB_T motor_io_position_GABRI_PrevZCX;

/* Real-time model */
RT_MODEL_motor_io_position_GA_T motor_io_position_GABRIEL_M_;
RT_MODEL_motor_io_position_GA_T *const motor_io_position_GABRIEL_M =
  &motor_io_position_GABRIEL_M_;

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 2;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  motor_io_position_GABRIEL_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; i++) {
    *x += h * f0[i];
    x++;
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/* Model output function */
void motor_io_position_GABRIEL_output(void)
{
  real_T temp;
  ZCEventType zcEvent;
  real_T u1;
  real_T u2;
  if (rtmIsMajorTimeStep(motor_io_position_GABRIEL_M)) {
    /* set solver stop time */
    if (!(motor_io_position_GABRIEL_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&motor_io_position_GABRIEL_M->solverInfo,
                            ((motor_io_position_GABRIEL_M->Timing.clockTickH0 +
        1) * motor_io_position_GABRIEL_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&motor_io_position_GABRIEL_M->solverInfo,
                            ((motor_io_position_GABRIEL_M->Timing.clockTick0 + 1)
        * motor_io_position_GABRIEL_M->Timing.stepSize0 +
        motor_io_position_GABRIEL_M->Timing.clockTickH0 *
        motor_io_position_GABRIEL_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(motor_io_position_GABRIEL_M)) {
    motor_io_position_GABRIEL_M->Timing.t[0] = rtsiGetT
      (&motor_io_position_GABRIEL_M->solverInfo);
  }

  /* SignalGenerator: '<Root>/SinGenerator' */
  motor_io_position_GABRIEL_B.SinGenerator = sin
    (motor_io_position_GABRIEL_P.SinGenerator_Frequency *
     motor_io_position_GABRIEL_M->Timing.t[0]) *
    motor_io_position_GABRIEL_P.SinGenerator_Amplitude;

  /* SignalGenerator: '<Root>/SquareGenerator' */
  temp = motor_io_position_GABRIEL_P.SquareGenerator_Frequency *
    motor_io_position_GABRIEL_M->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    motor_io_position_GABRIEL_B.SquareGenerator =
      motor_io_position_GABRIEL_P.SquareGenerator_Amplitude;
  } else {
    motor_io_position_GABRIEL_B.SquareGenerator =
      -motor_io_position_GABRIEL_P.SquareGenerator_Amplitude;
  }

  /* End of SignalGenerator: '<Root>/SquareGenerator' */

  /* Switch: '<Root>/Switch' incorporates:
   *  Constant: '<Root>/SignalSelector[0Square,1Sine]'
   */
  if (motor_io_position_GABRIEL_P.SignalSelector0Square1Sine_Valu != 0.0) {
    motor_io_position_GABRIEL_B.ref = motor_io_position_GABRIEL_B.SinGenerator;
  } else {
    motor_io_position_GABRIEL_B.ref =
      motor_io_position_GABRIEL_B.SquareGenerator;
  }

  /* End of Switch: '<Root>/Switch' */
  if (rtmIsMajorTimeStep(motor_io_position_GABRIEL_M)) {
    /* DiscreteTransferFcn: '<S2>/Gff' */
    temp = motor_io_position_GABRIEL_B.ref;
    temp -= motor_io_position_GABRIEL_P.R_sim[1] *
      motor_io_position_GABRIEL_DW.Gff_states[0];
    temp -= motor_io_position_GABRIEL_P.R_sim[2] *
      motor_io_position_GABRIEL_DW.Gff_states[1];
    temp /= motor_io_position_GABRIEL_P.R_sim[0];
    motor_io_position_GABRIEL_DW.Gff_tmp = temp;
    temp = motor_io_position_GABRIEL_P.T_sim[0] *
      motor_io_position_GABRIEL_DW.Gff_tmp;
    temp += motor_io_position_GABRIEL_P.T_sim[1] *
      motor_io_position_GABRIEL_DW.Gff_states[0];
    temp += motor_io_position_GABRIEL_P.T_sim[2] *
      motor_io_position_GABRIEL_DW.Gff_states[1];
    motor_io_position_GABRIEL_B.Gff = temp;

    /* S-Function (rti_commonblock): '<S14>/S-Function1' */
    /* This comment workarounds a code generation problem */

    /* Gain: '<S6>/fi1_scaling' */
    motor_io_position_GABRIEL_B.fi1_scaling =
      motor_io_position_GABRIEL_P.fi1_scaling_Gain *
      motor_io_position_GABRIEL_B.SFunction1;

    /* DiscreteTransferFcn: '<S2>/Gfb' */
    temp = motor_io_position_GABRIEL_B.fi1_scaling;
    temp -= motor_io_position_GABRIEL_P.R_sim[1] *
      motor_io_position_GABRIEL_DW.Gfb_states[0];
    temp -= motor_io_position_GABRIEL_P.R_sim[2] *
      motor_io_position_GABRIEL_DW.Gfb_states[1];
    temp /= motor_io_position_GABRIEL_P.R_sim[0];
    motor_io_position_GABRIEL_DW.Gfb_tmp = temp;
    temp = motor_io_position_GABRIEL_P.S_sim[0] *
      motor_io_position_GABRIEL_DW.Gfb_tmp;
    temp += motor_io_position_GABRIEL_P.S_sim[1] *
      motor_io_position_GABRIEL_DW.Gfb_states[0];
    temp += motor_io_position_GABRIEL_P.S_sim[2] *
      motor_io_position_GABRIEL_DW.Gfb_states[1];
    motor_io_position_GABRIEL_B.Gfb = temp;

    /* Sum: '<S2>/Sum1' */
    motor_io_position_GABRIEL_B.Sum1 = motor_io_position_GABRIEL_B.Gff -
      motor_io_position_GABRIEL_B.Gfb;

    /* Saturate: '<S2>/Saturation' */
    temp = motor_io_position_GABRIEL_B.Sum1;
    u1 = motor_io_position_GABRIEL_P.Saturation_LowerSat;
    u2 = motor_io_position_GABRIEL_P.Saturation_UpperSat;
    if (temp > u2) {
      motor_io_position_GABRIEL_B.Saturation = u2;
    } else if (temp < u1) {
      motor_io_position_GABRIEL_B.Saturation = u1;
    } else {
      motor_io_position_GABRIEL_B.Saturation = temp;
    }

    /* End of Saturate: '<S2>/Saturation' */

    /* Gain: '<Root>/Gain' */
    motor_io_position_GABRIEL_B.Gain = motor_io_position_GABRIEL_P.Gain_Gain *
      motor_io_position_GABRIEL_B.Saturation;

    /* Saturate: '<S4>/Saturation' */
    temp = motor_io_position_GABRIEL_B.Gain;
    u1 = motor_io_position_GABRIEL_P.Saturation_LowerSat_i;
    u2 = motor_io_position_GABRIEL_P.Saturation_UpperSat_l;
    if (temp > u2) {
      motor_io_position_GABRIEL_B.Volt = u2;
    } else if (temp < u1) {
      motor_io_position_GABRIEL_B.Volt = u1;
    } else {
      motor_io_position_GABRIEL_B.Volt = temp;
    }

    /* End of Saturate: '<S4>/Saturation' */

    /* Gain: '<S4>/pwm_skalning' */
    motor_io_position_GABRIEL_B.pwm_skalning =
      motor_io_position_GABRIEL_P.pwm_skalning_Gain *
      motor_io_position_GABRIEL_B.Volt;

    /* Sum: '<S4>/Sum' incorporates:
     *  Constant: '<S4>/pwm_offstet'
     */
    motor_io_position_GABRIEL_B.Sum = motor_io_position_GABRIEL_B.pwm_skalning +
      motor_io_position_GABRIEL_P.pwm_offstet_Value;

    /* S-Function (rti_commonblock): '<S10>/S-Function1' */
    /* This comment workarounds a code generation problem */

    /* dSPACE I/O Board DS1104 #1 Unit:PWM Group:PWM */
    ds1104_slave_dsp_pwm_duty_write(0, rti_slv1104_fcn_index[6],
      motor_io_position_GABRIEL_B.Sum);

    /* S-Function (rti_commonblock): '<S10>/S-Function2' */
    /* This comment workarounds a code generation problem */

    /* S-Function (rti_commonblock): '<S10>/S-Function3' */
    /* This comment workarounds a code generation problem */

    /* S-Function (rti_commonblock): '<S10>/S-Function4' */
    /* This comment workarounds a code generation problem */

    /* DataTypeConversion: '<S4>/Data Type Conversion' incorporates:
     *  Constant: '<S4>/Enable[1_Off, 0_On]'
     */
    motor_io_position_GABRIEL_B.DataTypeConversion =
      (motor_io_position_GABRIEL_P.Enable1_Off0_On_Value != 0.0);

    /* S-Function (rti_commonblock): '<S9>/S-Function1' */
    /* This comment workarounds a code generation problem */

    /* dSPACE I/O Board DS1104 #1 Unit:BIT_IO Group:BIT_OUT */
    if (motor_io_position_GABRIEL_B.DataTypeConversion > 0) {
      ds1104_bit_io_set(DS1104_DIO0);
    } else {
      ds1104_bit_io_clear(DS1104_DIO0);
    }
  }

  /* Integrator: '<S3>/Integrator1' */
  motor_io_position_GABRIEL_B.Integrator1 =
    motor_io_position_GABRIEL_X.Integrator1_CSTATE;

  /* Quantizer: '<Root>/Quantizer' */
  temp = motor_io_position_GABRIEL_B.Integrator1;
  motor_io_position_GABRIEL_B.Quantizer = rt_roundd_snf(temp /
    motor_io_position_GABRIEL_P.quant) * motor_io_position_GABRIEL_P.quant;
  if (rtmIsMajorTimeStep(motor_io_position_GABRIEL_M)) {
    /* DiscreteTransferFcn: '<S1>/Gfb' */
    temp = motor_io_position_GABRIEL_B.Quantizer;
    temp -= motor_io_position_GABRIEL_P.R_sim[1] *
      motor_io_position_GABRIEL_DW.Gfb_states_p[0];
    temp -= motor_io_position_GABRIEL_P.R_sim[2] *
      motor_io_position_GABRIEL_DW.Gfb_states_p[1];
    temp /= motor_io_position_GABRIEL_P.R_sim[0];
    motor_io_position_GABRIEL_DW.Gfb_tmp_l = temp;
    temp = motor_io_position_GABRIEL_P.S_sim[0] *
      motor_io_position_GABRIEL_DW.Gfb_tmp_l;
    temp += motor_io_position_GABRIEL_P.S_sim[1] *
      motor_io_position_GABRIEL_DW.Gfb_states_p[0];
    temp += motor_io_position_GABRIEL_P.S_sim[2] *
      motor_io_position_GABRIEL_DW.Gfb_states_p[1];
    motor_io_position_GABRIEL_B.Gfb_k = temp;

    /* DiscreteTransferFcn: '<S1>/Gff' */
    temp = motor_io_position_GABRIEL_B.ref;
    temp -= motor_io_position_GABRIEL_P.R_sim[1] *
      motor_io_position_GABRIEL_DW.Gff_states_c[0];
    temp -= motor_io_position_GABRIEL_P.R_sim[2] *
      motor_io_position_GABRIEL_DW.Gff_states_c[1];
    temp /= motor_io_position_GABRIEL_P.R_sim[0];
    motor_io_position_GABRIEL_DW.Gff_tmp_b = temp;
    temp = motor_io_position_GABRIEL_P.T_sim[0] *
      motor_io_position_GABRIEL_DW.Gff_tmp_b;
    temp += motor_io_position_GABRIEL_P.T_sim[1] *
      motor_io_position_GABRIEL_DW.Gff_states_c[0];
    temp += motor_io_position_GABRIEL_P.T_sim[2] *
      motor_io_position_GABRIEL_DW.Gff_states_c[1];
    motor_io_position_GABRIEL_B.Gff_b = temp;

    /* Sum: '<S1>/Sum1' */
    motor_io_position_GABRIEL_B.Sum1_h = motor_io_position_GABRIEL_B.Gff_b -
      motor_io_position_GABRIEL_B.Gfb_k;

    /* Saturate: '<S1>/Saturation' */
    temp = motor_io_position_GABRIEL_B.Sum1_h;
    u1 = motor_io_position_GABRIEL_P.Saturation_LowerSat_c;
    u2 = motor_io_position_GABRIEL_P.Saturation_UpperSat_lx;
    if (temp > u2) {
      motor_io_position_GABRIEL_B.Saturation_f = u2;
    } else if (temp < u1) {
      motor_io_position_GABRIEL_B.Saturation_f = u1;
    } else {
      motor_io_position_GABRIEL_B.Saturation_f = temp;
    }

    /* End of Saturate: '<S1>/Saturation' */
  }

  /* Integrator: '<S3>/Integrator' */
  motor_io_position_GABRIEL_B.Integrator =
    motor_io_position_GABRIEL_X.Integrator_CSTATE;

  /* Gain: '<S3>/Gain1' */
  motor_io_position_GABRIEL_B.Gain1 = motor_io_position_GABRIEL_P.Gain1_Gain *
    motor_io_position_GABRIEL_B.Integrator;

  /* Sum: '<S3>/Add' */
  motor_io_position_GABRIEL_B.Add = motor_io_position_GABRIEL_B.Saturation_f -
    motor_io_position_GABRIEL_B.Gain1;

  /* Gain: '<S3>/k//R ' */
  motor_io_position_GABRIEL_B.kR = motor_io_position_GABRIEL_P.kR_Gain *
    motor_io_position_GABRIEL_B.Add;

  /* Saturate: '<S7>/Saturate to Fc' */
  temp = motor_io_position_GABRIEL_B.kR;
  u1 = motor_io_position_GABRIEL_P.SaturatetoFc_LowerSat;
  u2 = motor_io_position_GABRIEL_P.F_c_upper;
  if (temp > u2) {
    motor_io_position_GABRIEL_B.Stickslipregion = u2;
  } else if (temp < u1) {
    motor_io_position_GABRIEL_B.Stickslipregion = u1;
  } else {
    motor_io_position_GABRIEL_B.Stickslipregion = temp;
  }

  /* End of Saturate: '<S7>/Saturate to Fc' */

  /* Abs: '<S7>/Abs' */
  motor_io_position_GABRIEL_B.Abs = fabs(motor_io_position_GABRIEL_B.Integrator);

  /* RelationalOperator: '<S8>/Compare' incorporates:
   *  Constant: '<S8>/Constant'
   */
  motor_io_position_GABRIEL_B.Compare = (motor_io_position_GABRIEL_B.Abs <=
    motor_io_position_GABRIEL_P.Constant_Value);

  /* Gain: '<S7>/Vicous friction' */
  motor_io_position_GABRIEL_B.Vicousfriction =
    motor_io_position_GABRIEL_P.Vicousfriction_Gain *
    motor_io_position_GABRIEL_B.Integrator;

  /* Signum: '<S7>/Sign' */
  temp = motor_io_position_GABRIEL_B.Integrator;
  if (temp < 0.0) {
    motor_io_position_GABRIEL_B.Sign = -1.0;
  } else if (temp > 0.0) {
    motor_io_position_GABRIEL_B.Sign = 1.0;
  } else if (temp == 0.0) {
    motor_io_position_GABRIEL_B.Sign = 0.0;
  } else {
    motor_io_position_GABRIEL_B.Sign = temp;
  }

  /* End of Signum: '<S7>/Sign' */

  /* Product: '<S7>/Product' incorporates:
   *  Constant: '<S7>/F_c'
   */
  motor_io_position_GABRIEL_B.Product = motor_io_position_GABRIEL_P.F_c *
    motor_io_position_GABRIEL_B.Sign;

  /* Sum: '<S7>/Add' */
  motor_io_position_GABRIEL_B.Viscousregion =
    motor_io_position_GABRIEL_B.Vicousfriction +
    motor_io_position_GABRIEL_B.Product;

  /* Switch: '<S7>/Switch' */
  if (motor_io_position_GABRIEL_B.Compare) {
    motor_io_position_GABRIEL_B.Friction =
      motor_io_position_GABRIEL_B.Stickslipregion;
  } else {
    motor_io_position_GABRIEL_B.Friction =
      motor_io_position_GABRIEL_B.Viscousregion;
  }

  /* End of Switch: '<S7>/Switch' */

  /* Sum: '<S3>/Add1' */
  motor_io_position_GABRIEL_B.Add1 = motor_io_position_GABRIEL_B.kR -
    motor_io_position_GABRIEL_B.Friction;
  if (rtmIsMajorTimeStep(motor_io_position_GABRIEL_M)) {
    /* Gain: '<S3>/Gain2' incorporates:
     *  Constant: '<S3>/Load inertia'
     */
    motor_io_position_GABRIEL_B.Gain2 = motor_io_position_GABRIEL_P.Gain2_Gain *
      motor_io_position_GABRIEL_P.J1;

    /* Sum: '<S3>/Add2' incorporates:
     *  Constant: '<S3>/Motor inertia'
     */
    motor_io_position_GABRIEL_B.Add2 = motor_io_position_GABRIEL_B.Gain2 +
      motor_io_position_GABRIEL_P.Motorinertia_Value;
  }

  /* Product: '<S3>/Inertias 1//J' */
  motor_io_position_GABRIEL_B.Inertias1J = 1.0 /
    motor_io_position_GABRIEL_B.Add2 * motor_io_position_GABRIEL_B.Add1;
  if (rtmIsMajorTimeStep(motor_io_position_GABRIEL_M)) {
    /* S-Function (rti_commonblock): '<S14>/S-Function2' */
    /* This comment workarounds a code generation problem */

    /* Gain: '<S6>/w1_scaling' */
    motor_io_position_GABRIEL_B.w1_scaling =
      motor_io_position_GABRIEL_P.w1_scaling_Gain *
      motor_io_position_GABRIEL_B.SFunction2;

    /* Outputs for Triggered SubSystem: '<S6>/DS1104ENC_SET_POS_C1' incorporates:
     *  TriggerPort: '<S16>/Trigger'
     */
    if (rtmIsMajorTimeStep(motor_io_position_GABRIEL_M)) {
      /* Constant: '<S6>/Reset enc' */
      zcEvent = rt_ZCFcn(RISING_ZERO_CROSSING,
                         &motor_io_position_GABRI_PrevZCX.DS1104ENC_SET_POS_C1_Trig_ZCE,
                         (motor_io_position_GABRIEL_P.Resetenc_Value));
      if (zcEvent != NO_ZCEVENT) {
        /* S-Function (rti_commonblock): '<S16>/S-Function1' */
        /* This comment workarounds a code generation problem */

        /* dSPACE I/O Board DS1104 Unit:ENC_SET */
        ds1104_inc_position_write(1, 0, DS1104_INC_LINE_SUBDIV_4);
      }
    }

    /* End of Outputs for SubSystem: '<S6>/DS1104ENC_SET_POS_C1' */

    /* S-Function (rti_commonblock): '<S15>/S-Function1' */
    /* This comment workarounds a code generation problem */

    /* S-Function (rti_commonblock): '<S15>/S-Function2' */
    /* This comment workarounds a code generation problem */
  }
}

/* Model update function */
void motor_io_position_GABRIEL_update(void)
{
  if (rtmIsMajorTimeStep(motor_io_position_GABRIEL_M)) {
    /* Update for DiscreteTransferFcn: '<S2>/Gff' */
    motor_io_position_GABRIEL_DW.Gff_states[1] =
      motor_io_position_GABRIEL_DW.Gff_states[0];
    motor_io_position_GABRIEL_DW.Gff_states[0] =
      motor_io_position_GABRIEL_DW.Gff_tmp;

    /* Update for DiscreteTransferFcn: '<S2>/Gfb' */
    motor_io_position_GABRIEL_DW.Gfb_states[1] =
      motor_io_position_GABRIEL_DW.Gfb_states[0];
    motor_io_position_GABRIEL_DW.Gfb_states[0] =
      motor_io_position_GABRIEL_DW.Gfb_tmp;

    /* Update for DiscreteTransferFcn: '<S1>/Gfb' */
    motor_io_position_GABRIEL_DW.Gfb_states_p[1] =
      motor_io_position_GABRIEL_DW.Gfb_states_p[0];
    motor_io_position_GABRIEL_DW.Gfb_states_p[0] =
      motor_io_position_GABRIEL_DW.Gfb_tmp_l;

    /* Update for DiscreteTransferFcn: '<S1>/Gff' */
    motor_io_position_GABRIEL_DW.Gff_states_c[1] =
      motor_io_position_GABRIEL_DW.Gff_states_c[0];
    motor_io_position_GABRIEL_DW.Gff_states_c[0] =
      motor_io_position_GABRIEL_DW.Gff_tmp_b;
  }

  if (rtmIsMajorTimeStep(motor_io_position_GABRIEL_M)) {
    rt_ertODEUpdateContinuousStates(&motor_io_position_GABRIEL_M->solverInfo);
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++motor_io_position_GABRIEL_M->Timing.clockTick0)) {
    ++motor_io_position_GABRIEL_M->Timing.clockTickH0;
  }

  motor_io_position_GABRIEL_M->Timing.t[0] = rtsiGetSolverStopTime
    (&motor_io_position_GABRIEL_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.010870562815189595s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++motor_io_position_GABRIEL_M->Timing.clockTick1)) {
      ++motor_io_position_GABRIEL_M->Timing.clockTickH1;
    }

    motor_io_position_GABRIEL_M->Timing.t[1] =
      motor_io_position_GABRIEL_M->Timing.clockTick1 *
      motor_io_position_GABRIEL_M->Timing.stepSize1 +
      motor_io_position_GABRIEL_M->Timing.clockTickH1 *
      motor_io_position_GABRIEL_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void motor_io_position_GABRIEL_derivatives(void)
{
  XDot_motor_io_position_GABRIE_T *_rtXdot;
  _rtXdot = ((XDot_motor_io_position_GABRIE_T *)
             motor_io_position_GABRIEL_M->ModelData.derivs);

  /* Derivatives for Integrator: '<S3>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = motor_io_position_GABRIEL_B.Integrator;

  /* Derivatives for Integrator: '<S3>/Integrator' */
  _rtXdot->Integrator_CSTATE = motor_io_position_GABRIEL_B.Inertias1J;
}

/* Model initialize function */
void motor_io_position_GABRIEL_initialize(void)
{
  /* Start for S-Function (rti_commonblock): '<S10>/S-Function1' */

  /* dSPACE I/O Board DS1104 #1 Unit:PWM Group:PWM */
  motor_io_position_GABRIEL_DW.SFunction1_IWORK[0] = 0;
  motor_io_position_GABRI_PrevZCX.DS1104ENC_SET_POS_C1_Trig_ZCE =
    UNINITIALIZED_ZCSIG;

  /* InitializeConditions for DiscreteTransferFcn: '<S2>/Gff' */
  motor_io_position_GABRIEL_DW.Gff_states[0] =
    motor_io_position_GABRIEL_P.Gff_InitialStates;
  motor_io_position_GABRIEL_DW.Gff_states[1] =
    motor_io_position_GABRIEL_P.Gff_InitialStates;

  /* InitializeConditions for DiscreteTransferFcn: '<S2>/Gfb' */
  motor_io_position_GABRIEL_DW.Gfb_states[0] =
    motor_io_position_GABRIEL_P.Gfb_InitialStates;
  motor_io_position_GABRIEL_DW.Gfb_states[1] =
    motor_io_position_GABRIEL_P.Gfb_InitialStates;

  /* InitializeConditions for Integrator: '<S3>/Integrator1' */
  motor_io_position_GABRIEL_X.Integrator1_CSTATE =
    motor_io_position_GABRIEL_P.Integrator1_IC;

  /* InitializeConditions for DiscreteTransferFcn: '<S1>/Gfb' */
  motor_io_position_GABRIEL_DW.Gfb_states_p[0] =
    motor_io_position_GABRIEL_P.Gfb_InitialStates_k;
  motor_io_position_GABRIEL_DW.Gfb_states_p[1] =
    motor_io_position_GABRIEL_P.Gfb_InitialStates_k;

  /* InitializeConditions for DiscreteTransferFcn: '<S1>/Gff' */
  motor_io_position_GABRIEL_DW.Gff_states_c[0] =
    motor_io_position_GABRIEL_P.Gff_InitialStates_d;
  motor_io_position_GABRIEL_DW.Gff_states_c[1] =
    motor_io_position_GABRIEL_P.Gff_InitialStates_d;

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
  motor_io_position_GABRIEL_X.Integrator_CSTATE =
    motor_io_position_GABRIEL_P.Integrator_IC;
}

/* Model terminate function */
void motor_io_position_GABRIEL_terminate(void)
{
  /* (no terminate code required) */
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  motor_io_position_GABRIEL_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  motor_io_position_GABRIEL_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  motor_io_position_GABRIEL_initialize();
}

void MdlTerminate(void)
{
  motor_io_position_GABRIEL_terminate();
}

/* Registration function */
RT_MODEL_motor_io_position_GA_T *motor_io_position_GABRIEL(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)motor_io_position_GABRIEL_M, 0,
                sizeof(RT_MODEL_motor_io_position_GA_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&motor_io_position_GABRIEL_M->solverInfo,
                          &motor_io_position_GABRIEL_M->Timing.simTimeStep);
    rtsiSetTPtr(&motor_io_position_GABRIEL_M->solverInfo, &rtmGetTPtr
                (motor_io_position_GABRIEL_M));
    rtsiSetStepSizePtr(&motor_io_position_GABRIEL_M->solverInfo,
                       &motor_io_position_GABRIEL_M->Timing.stepSize0);
    rtsiSetdXPtr(&motor_io_position_GABRIEL_M->solverInfo,
                 &motor_io_position_GABRIEL_M->ModelData.derivs);
    rtsiSetContStatesPtr(&motor_io_position_GABRIEL_M->solverInfo, (real_T **)
                         &motor_io_position_GABRIEL_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&motor_io_position_GABRIEL_M->solverInfo,
      &motor_io_position_GABRIEL_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&motor_io_position_GABRIEL_M->solverInfo,
                          (&rtmGetErrorStatus(motor_io_position_GABRIEL_M)));
    rtsiSetRTModelPtr(&motor_io_position_GABRIEL_M->solverInfo,
                      motor_io_position_GABRIEL_M);
  }

  rtsiSetSimTimeStep(&motor_io_position_GABRIEL_M->solverInfo, MAJOR_TIME_STEP);
  motor_io_position_GABRIEL_M->ModelData.intgData.f[0] =
    motor_io_position_GABRIEL_M->ModelData.odeF[0];
  motor_io_position_GABRIEL_M->ModelData.contStates = ((real_T *)
    &motor_io_position_GABRIEL_X);
  rtsiSetSolverData(&motor_io_position_GABRIEL_M->solverInfo, (void *)
                    &motor_io_position_GABRIEL_M->ModelData.intgData);
  rtsiSetSolverName(&motor_io_position_GABRIEL_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = motor_io_position_GABRIEL_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    motor_io_position_GABRIEL_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    motor_io_position_GABRIEL_M->Timing.sampleTimes =
      (&motor_io_position_GABRIEL_M->Timing.sampleTimesArray[0]);
    motor_io_position_GABRIEL_M->Timing.offsetTimes =
      (&motor_io_position_GABRIEL_M->Timing.offsetTimesArray[0]);

    /* task periods */
    motor_io_position_GABRIEL_M->Timing.sampleTimes[0] = (0.0);
    motor_io_position_GABRIEL_M->Timing.sampleTimes[1] = (0.010870562815189595);

    /* task offsets */
    motor_io_position_GABRIEL_M->Timing.offsetTimes[0] = (0.0);
    motor_io_position_GABRIEL_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(motor_io_position_GABRIEL_M,
             &motor_io_position_GABRIEL_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = motor_io_position_GABRIEL_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    motor_io_position_GABRIEL_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(motor_io_position_GABRIEL_M, -1);
  motor_io_position_GABRIEL_M->Timing.stepSize0 = 0.010870562815189595;
  motor_io_position_GABRIEL_M->Timing.stepSize1 = 0.010870562815189595;
  motor_io_position_GABRIEL_M->solverInfoPtr =
    (&motor_io_position_GABRIEL_M->solverInfo);
  motor_io_position_GABRIEL_M->Timing.stepSize = (0.010870562815189595);
  rtsiSetFixedStepSize(&motor_io_position_GABRIEL_M->solverInfo,
                       0.010870562815189595);
  rtsiSetSolverMode(&motor_io_position_GABRIEL_M->solverInfo,
                    SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  motor_io_position_GABRIEL_M->ModelData.blockIO = ((void *)
    &motor_io_position_GABRIEL_B);
  (void) memset(((void *) &motor_io_position_GABRIEL_B), 0,
                sizeof(B_motor_io_position_GABRIEL_T));

  {
    motor_io_position_GABRIEL_B.SinGenerator = 0.0;
    motor_io_position_GABRIEL_B.SquareGenerator = 0.0;
    motor_io_position_GABRIEL_B.ref = 0.0;
    motor_io_position_GABRIEL_B.Gff = 0.0;
    motor_io_position_GABRIEL_B.SFunction1 = 0.0;
    motor_io_position_GABRIEL_B.fi1_scaling = 0.0;
    motor_io_position_GABRIEL_B.Gfb = 0.0;
    motor_io_position_GABRIEL_B.Sum1 = 0.0;
    motor_io_position_GABRIEL_B.Saturation = 0.0;
    motor_io_position_GABRIEL_B.Gain = 0.0;
    motor_io_position_GABRIEL_B.Volt = 0.0;
    motor_io_position_GABRIEL_B.pwm_skalning = 0.0;
    motor_io_position_GABRIEL_B.Sum = 0.0;
    motor_io_position_GABRIEL_B.Integrator1 = 0.0;
    motor_io_position_GABRIEL_B.Quantizer = 0.0;
    motor_io_position_GABRIEL_B.Gfb_k = 0.0;
    motor_io_position_GABRIEL_B.Gff_b = 0.0;
    motor_io_position_GABRIEL_B.Sum1_h = 0.0;
    motor_io_position_GABRIEL_B.Saturation_f = 0.0;
    motor_io_position_GABRIEL_B.Integrator = 0.0;
    motor_io_position_GABRIEL_B.Gain1 = 0.0;
    motor_io_position_GABRIEL_B.Add = 0.0;
    motor_io_position_GABRIEL_B.kR = 0.0;
    motor_io_position_GABRIEL_B.Stickslipregion = 0.0;
    motor_io_position_GABRIEL_B.Abs = 0.0;
    motor_io_position_GABRIEL_B.Vicousfriction = 0.0;
    motor_io_position_GABRIEL_B.Sign = 0.0;
    motor_io_position_GABRIEL_B.Product = 0.0;
    motor_io_position_GABRIEL_B.Viscousregion = 0.0;
    motor_io_position_GABRIEL_B.Friction = 0.0;
    motor_io_position_GABRIEL_B.Add1 = 0.0;
    motor_io_position_GABRIEL_B.Gain2 = 0.0;
    motor_io_position_GABRIEL_B.Add2 = 0.0;
    motor_io_position_GABRIEL_B.Inertias1J = 0.0;
    motor_io_position_GABRIEL_B.SFunction2 = 0.0;
    motor_io_position_GABRIEL_B.w1_scaling = 0.0;
  }

  /* parameters */
  motor_io_position_GABRIEL_M->ModelData.defaultParam = ((real_T *)
    &motor_io_position_GABRIEL_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &motor_io_position_GABRIEL_X;
    motor_io_position_GABRIEL_M->ModelData.contStates = (x);
    (void) memset((void *)&motor_io_position_GABRIEL_X, 0,
                  sizeof(X_motor_io_position_GABRIEL_T));
  }

  /* states (dwork) */
  motor_io_position_GABRIEL_M->ModelData.dwork = ((void *)
    &motor_io_position_GABRIEL_DW);
  (void) memset((void *)&motor_io_position_GABRIEL_DW, 0,
                sizeof(DW_motor_io_position_GABRIEL_T));
  motor_io_position_GABRIEL_DW.Gff_states[0] = 0.0;
  motor_io_position_GABRIEL_DW.Gff_states[1] = 0.0;
  motor_io_position_GABRIEL_DW.Gfb_states[0] = 0.0;
  motor_io_position_GABRIEL_DW.Gfb_states[1] = 0.0;
  motor_io_position_GABRIEL_DW.Gfb_states_p[0] = 0.0;
  motor_io_position_GABRIEL_DW.Gfb_states_p[1] = 0.0;
  motor_io_position_GABRIEL_DW.Gff_states_c[0] = 0.0;
  motor_io_position_GABRIEL_DW.Gff_states_c[1] = 0.0;
  motor_io_position_GABRIEL_DW.Gff_tmp = 0.0;
  motor_io_position_GABRIEL_DW.Gfb_tmp = 0.0;
  motor_io_position_GABRIEL_DW.Gfb_tmp_l = 0.0;
  motor_io_position_GABRIEL_DW.Gff_tmp_b = 0.0;

  {
    /* user code (registration function declaration) */
    /*Call the macro that initializes the global TRC pointers
       inside the model initialization/registration function. */
    RTI_INIT_TRC_POINTERS();
  }

  /* Initialize Sizes */
  motor_io_position_GABRIEL_M->Sizes.numContStates = (2);/* Number of continuous states */
  motor_io_position_GABRIEL_M->Sizes.numY = (0);/* Number of model outputs */
  motor_io_position_GABRIEL_M->Sizes.numU = (0);/* Number of model inputs */
  motor_io_position_GABRIEL_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  motor_io_position_GABRIEL_M->Sizes.numSampTimes = (2);/* Number of sample times */
  motor_io_position_GABRIEL_M->Sizes.numBlocks = (56);/* Number of blocks */
  motor_io_position_GABRIEL_M->Sizes.numBlockIO = (38);/* Number of block outputs */
  motor_io_position_GABRIEL_M->Sizes.numBlockPrms = (44);/* Sum of parameter "widths" */
  return motor_io_position_GABRIEL_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
