/*
 * motor_io_position_new.c
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
#include "motor_io_position_new_trc_ptr.h"
#include "motor_io_position_new.h"
#include "motor_io_position_new_private.h"

/* Block signals (auto storage) */
B_motor_io_position_new_T motor_io_position_new_B;

/* Continuous states */
X_motor_io_position_new_T motor_io_position_new_X;

/* Block states (auto storage) */
DW_motor_io_position_new_T motor_io_position_new_DW;

/* Previous zero-crossings (trigger) states */
PrevZCX_motor_io_position_new_T motor_io_position_new_PrevZCX;

/* Real-time model */
RT_MODEL_motor_io_position_ne_T motor_io_position_new_M_;
RT_MODEL_motor_io_position_ne_T *const motor_io_position_new_M =
  &motor_io_position_new_M_;

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
  motor_io_position_new_derivatives();
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
void motor_io_position_new_output(void)
{
  real_T temp;
  ZCEventType zcEvent;
  real_T u1;
  real_T u2;
  if (rtmIsMajorTimeStep(motor_io_position_new_M)) {
    /* set solver stop time */
    if (!(motor_io_position_new_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&motor_io_position_new_M->solverInfo,
                            ((motor_io_position_new_M->Timing.clockTickH0 + 1) *
        motor_io_position_new_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&motor_io_position_new_M->solverInfo,
                            ((motor_io_position_new_M->Timing.clockTick0 + 1) *
        motor_io_position_new_M->Timing.stepSize0 +
        motor_io_position_new_M->Timing.clockTickH0 *
        motor_io_position_new_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(motor_io_position_new_M)) {
    motor_io_position_new_M->Timing.t[0] = rtsiGetT
      (&motor_io_position_new_M->solverInfo);
  }

  /* SignalGenerator: '<Root>/SinGenerator' */
  motor_io_position_new_B.SinGenerator = sin
    (motor_io_position_new_P.SinGenerator_Frequency *
     motor_io_position_new_M->Timing.t[0]) *
    motor_io_position_new_P.SinGenerator_Amplitude;

  /* SignalGenerator: '<Root>/SquareGenerator' */
  temp = motor_io_position_new_P.SquareGenerator_Frequency *
    motor_io_position_new_M->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    motor_io_position_new_B.SquareGenerator =
      motor_io_position_new_P.SquareGenerator_Amplitude;
  } else {
    motor_io_position_new_B.SquareGenerator =
      -motor_io_position_new_P.SquareGenerator_Amplitude;
  }

  /* End of SignalGenerator: '<Root>/SquareGenerator' */

  /* Switch: '<Root>/Switch' incorporates:
   *  Constant: '<Root>/SignalSelector[0Square,1Sine]'
   */
  if (motor_io_position_new_P.SignalSelector0Square1Sine_Valu != 0.0) {
    motor_io_position_new_B.ref = motor_io_position_new_B.SinGenerator;
  } else {
    motor_io_position_new_B.ref = motor_io_position_new_B.SquareGenerator;
  }

  /* End of Switch: '<Root>/Switch' */
  if (rtmIsMajorTimeStep(motor_io_position_new_M)) {
    /* DiscreteTransferFcn: '<S2>/Gff' */
    temp = motor_io_position_new_B.ref;
    temp -= motor_io_position_new_P.Gff_DenCoef[1] *
      motor_io_position_new_DW.Gff_states;
    temp /= motor_io_position_new_P.Gff_DenCoef[0];
    motor_io_position_new_DW.Gff_tmp = temp;
    temp = motor_io_position_new_P.Gff_NumCoef[0] *
      motor_io_position_new_DW.Gff_tmp;
    temp += motor_io_position_new_P.Gff_NumCoef[1] *
      motor_io_position_new_DW.Gff_states;
    motor_io_position_new_B.Gff = temp;

    /* DiscreteTransferFcn: '<S2>/I part1' */
    temp = motor_io_position_new_P.Ipart1_NumCoef[1] *
      motor_io_position_new_DW.Ipart1_states;
    motor_io_position_new_B.Ipart1 = temp;

    /* Sum: '<S2>/Sum1' */
    motor_io_position_new_B.Sum1 = motor_io_position_new_B.Gff +
      motor_io_position_new_B.Ipart1;

    /* DiscreteTransferFcn: '<S2>/I part' */
    temp = motor_io_position_new_P.Ipart_NumCoef[1] *
      motor_io_position_new_DW.Ipart_states;
    motor_io_position_new_B.Ipart = temp;

    /* S-Function (rti_commonblock): '<S15>/S-Function1' */
    /* This comment workarounds a code generation problem */

    /* Gain: '<S7>/fi1_scaling' */
    motor_io_position_new_B.fi1_scaling =
      motor_io_position_new_P.fi1_scaling_Gain *
      motor_io_position_new_B.SFunction1;

    /* DiscreteTransferFcn: '<S2>/PD part' */
    temp = motor_io_position_new_B.fi1_scaling;
    temp -= motor_io_position_new_P.PDpart_DenCoef[1] *
      motor_io_position_new_DW.PDpart_states;
    temp /= motor_io_position_new_P.PDpart_DenCoef[0];
    motor_io_position_new_DW.PDpart_tmp = temp;
    temp = motor_io_position_new_P.PDpart_NumCoef[0] *
      motor_io_position_new_DW.PDpart_tmp;
    temp += motor_io_position_new_P.PDpart_NumCoef[1] *
      motor_io_position_new_DW.PDpart_states;
    motor_io_position_new_B.PDpart = temp;

    /* Sum: '<S2>/Sum' */
    motor_io_position_new_B.Sum = motor_io_position_new_B.Ipart +
      motor_io_position_new_B.PDpart;

    /* Sum: '<S2>/Sum2' */
    motor_io_position_new_B.Sum2 = motor_io_position_new_B.Sum1 -
      motor_io_position_new_B.Sum;

    /* Saturate: '<S2>/Voltage Saturation ' */
    temp = motor_io_position_new_B.Sum2;
    u1 = motor_io_position_new_P.VoltageSaturation_LowerSat;
    u2 = motor_io_position_new_P.VoltageSaturation_UpperSat;
    if (temp > u2) {
      motor_io_position_new_B.VoltageSaturation = u2;
    } else if (temp < u1) {
      motor_io_position_new_B.VoltageSaturation = u1;
    } else {
      motor_io_position_new_B.VoltageSaturation = temp;
    }

    /* End of Saturate: '<S2>/Voltage Saturation ' */

    /* Gain: '<Root>/Gain' */
    motor_io_position_new_B.Gain = motor_io_position_new_P.Gain_Gain *
      motor_io_position_new_B.VoltageSaturation;

    /* Saturate: '<S4>/Saturation' */
    temp = motor_io_position_new_B.Gain;
    u1 = motor_io_position_new_P.Saturation_LowerSat;
    u2 = motor_io_position_new_P.Saturation_UpperSat;
    if (temp > u2) {
      motor_io_position_new_B.Volt = u2;
    } else if (temp < u1) {
      motor_io_position_new_B.Volt = u1;
    } else {
      motor_io_position_new_B.Volt = temp;
    }

    /* End of Saturate: '<S4>/Saturation' */

    /* Gain: '<S4>/pwm_skalning' */
    motor_io_position_new_B.pwm_skalning =
      motor_io_position_new_P.pwm_skalning_Gain * motor_io_position_new_B.Volt;

    /* Sum: '<S4>/Sum' incorporates:
     *  Constant: '<S4>/pwm_offstet'
     */
    motor_io_position_new_B.Sum_f = motor_io_position_new_B.pwm_skalning +
      motor_io_position_new_P.pwm_offstet_Value;

    /* S-Function (rti_commonblock): '<S11>/S-Function1' */
    /* This comment workarounds a code generation problem */

    /* dSPACE I/O Board DS1104 #1 Unit:PWM Group:PWM */
    ds1104_slave_dsp_pwm_duty_write(0, rti_slv1104_fcn_index[6],
      motor_io_position_new_B.Sum_f);

    /* S-Function (rti_commonblock): '<S11>/S-Function2' */
    /* This comment workarounds a code generation problem */

    /* S-Function (rti_commonblock): '<S11>/S-Function3' */
    /* This comment workarounds a code generation problem */

    /* S-Function (rti_commonblock): '<S11>/S-Function4' */
    /* This comment workarounds a code generation problem */

    /* DataTypeConversion: '<S4>/Data Type Conversion' incorporates:
     *  Constant: '<S4>/Enable[1_Off, 0_On]'
     */
    motor_io_position_new_B.DataTypeConversion =
      (motor_io_position_new_P.Enable1_Off0_On_Value != 0.0);

    /* S-Function (rti_commonblock): '<S10>/S-Function1' */
    /* This comment workarounds a code generation problem */

    /* dSPACE I/O Board DS1104 #1 Unit:BIT_IO Group:BIT_OUT */
    if (motor_io_position_new_B.DataTypeConversion > 0) {
      ds1104_bit_io_set(DS1104_DIO0);
    } else {
      ds1104_bit_io_clear(DS1104_DIO0);
    }

    /* DiscreteTransferFcn: '<S1>/Gff' */
    temp = motor_io_position_new_B.ref;
    temp -= motor_io_position_new_P.Gff_DenCoef_h[1] *
      motor_io_position_new_DW.Gff_states_d;
    temp /= motor_io_position_new_P.Gff_DenCoef_h[0];
    motor_io_position_new_DW.Gff_tmp_k = temp;
    temp = motor_io_position_new_P.Gff_NumCoef_k[0] *
      motor_io_position_new_DW.Gff_tmp_k;
    temp += motor_io_position_new_P.Gff_NumCoef_k[1] *
      motor_io_position_new_DW.Gff_states_d;
    motor_io_position_new_B.Gff_e = temp;

    /* DiscreteTransferFcn: '<S1>/I part1' */
    temp = motor_io_position_new_P.Ipart1_NumCoef_o[1] *
      motor_io_position_new_DW.Ipart1_states_o;
    motor_io_position_new_B.Ipart1_d = temp;

    /* Sum: '<S1>/Sum1' */
    motor_io_position_new_B.Sum1_e = motor_io_position_new_B.Gff_e +
      motor_io_position_new_B.Ipart1_d;

    /* DiscreteTransferFcn: '<S1>/I part' */
    temp = motor_io_position_new_P.Ipart_NumCoef_f[1] *
      motor_io_position_new_DW.Ipart_states_f;
    motor_io_position_new_B.Ipart_a = temp;
  }

  /* Integrator: '<S3>/Integrator1' */
  motor_io_position_new_B.Integrator1 =
    motor_io_position_new_X.Integrator1_CSTATE;

  /* Quantizer: '<S6>/Quantizer' */
  temp = motor_io_position_new_B.Integrator1;
  motor_io_position_new_B.Quantizer = rt_roundd_snf(temp /
    motor_io_position_new_P.quant) * motor_io_position_new_P.quant;
  if (rtmIsMajorTimeStep(motor_io_position_new_M)) {
    /* ZeroOrderHold: '<S6>/Zero-Order Hold' */
    motor_io_position_new_B.ZeroOrderHold = motor_io_position_new_B.Quantizer;

    /* DiscreteTransferFcn: '<S1>/PD part' */
    temp = motor_io_position_new_B.ZeroOrderHold;
    temp -= motor_io_position_new_P.PDpart_DenCoef_h[1] *
      motor_io_position_new_DW.PDpart_states_j;
    temp /= motor_io_position_new_P.PDpart_DenCoef_h[0];
    motor_io_position_new_DW.PDpart_tmp_m = temp;
    temp = motor_io_position_new_P.PDpart_NumCoef_o[0] *
      motor_io_position_new_DW.PDpart_tmp_m;
    temp += motor_io_position_new_P.PDpart_NumCoef_o[1] *
      motor_io_position_new_DW.PDpart_states_j;
    motor_io_position_new_B.PDpart_k = temp;

    /* Sum: '<S1>/Sum' */
    motor_io_position_new_B.Sum_e = motor_io_position_new_B.Ipart_a +
      motor_io_position_new_B.PDpart_k;

    /* Sum: '<S1>/Sum2' */
    motor_io_position_new_B.Sum2_n = motor_io_position_new_B.Sum1_e -
      motor_io_position_new_B.Sum_e;

    /* Saturate: '<S1>/Voltage Saturation ' */
    temp = motor_io_position_new_B.Sum2_n;
    u1 = motor_io_position_new_P.VoltageSaturation_LowerSat_h;
    u2 = motor_io_position_new_P.VoltageSaturation_UpperSat_g;
    if (temp > u2) {
      motor_io_position_new_B.VoltageSaturation_j = u2;
    } else if (temp < u1) {
      motor_io_position_new_B.VoltageSaturation_j = u1;
    } else {
      motor_io_position_new_B.VoltageSaturation_j = temp;
    }

    /* End of Saturate: '<S1>/Voltage Saturation ' */

    /* Sum: '<S1>/Sum3' */
    motor_io_position_new_B.Sum3 = motor_io_position_new_B.VoltageSaturation_j -
      motor_io_position_new_B.Sum2_n;

    /* Gain: '<S1>/Gain' */
    motor_io_position_new_B.Gain_m = motor_io_position_new_P.c0 *
      motor_io_position_new_B.ZeroOrderHold;
  }

  /* Gain: '<S1>/Gain1' */
  motor_io_position_new_B.Gain1 = motor_io_position_new_P.c0_ *
    motor_io_position_new_B.ref;
  if (rtmIsMajorTimeStep(motor_io_position_new_M)) {
    /* Gain: '<S1>/Gain2' */
    motor_io_position_new_B.Gain2 = motor_io_position_new_P.Kb *
      motor_io_position_new_B.Sum3;

    /* Sum: '<S1>/Sum4' */
    motor_io_position_new_B.Sum4 = motor_io_position_new_B.Gain2 +
      motor_io_position_new_B.Gain_m;
  }

  /* Sum: '<S1>/Sum5' */
  motor_io_position_new_B.Sum5 = motor_io_position_new_B.Gain1 +
    motor_io_position_new_B.Gain2;
  if (rtmIsMajorTimeStep(motor_io_position_new_M)) {
    /* DiscreteTransferFcn: '<S1>/Gff1' */
    temp = 0.0 - motor_io_position_new_P.R_sim[1] *
      motor_io_position_new_DW.Gff1_states[0];
    temp -= motor_io_position_new_P.R_sim[2] *
      motor_io_position_new_DW.Gff1_states[1];
    temp /= motor_io_position_new_P.R_sim[0];
    motor_io_position_new_DW.Gff1_tmp = temp;
    temp = motor_io_position_new_P.T_sim[0] * motor_io_position_new_DW.Gff1_tmp;
    temp += motor_io_position_new_P.T_sim[1] *
      motor_io_position_new_DW.Gff1_states[0];
    temp += motor_io_position_new_P.T_sim[2] *
      motor_io_position_new_DW.Gff1_states[1];
    motor_io_position_new_B.Gff1 = temp;

    /* DiscreteTransferFcn: '<S1>/Gff2' */
    temp = 0.0 - motor_io_position_new_P.R_sim[1] *
      motor_io_position_new_DW.Gff2_states[0];
    temp -= motor_io_position_new_P.R_sim[2] *
      motor_io_position_new_DW.Gff2_states[1];
    temp /= motor_io_position_new_P.R_sim[0];
    motor_io_position_new_DW.Gff2_tmp = temp;
    temp = motor_io_position_new_P.S_sim[0] * motor_io_position_new_DW.Gff2_tmp;
    temp += motor_io_position_new_P.S_sim[1] *
      motor_io_position_new_DW.Gff2_states[0];
    temp += motor_io_position_new_P.S_sim[2] *
      motor_io_position_new_DW.Gff2_states[1];
    motor_io_position_new_B.Gff2 = temp;

    /* Sum: '<S2>/Sum3' */
    motor_io_position_new_B.Sum3_o = motor_io_position_new_B.VoltageSaturation -
      motor_io_position_new_B.Sum2;

    /* Gain: '<S2>/Gain' */
    motor_io_position_new_B.Gain_g = motor_io_position_new_P.c0 *
      motor_io_position_new_B.fi1_scaling;
  }

  /* Gain: '<S2>/Gain1' */
  motor_io_position_new_B.Gain1_k = motor_io_position_new_P.c0_ *
    motor_io_position_new_B.ref;
  if (rtmIsMajorTimeStep(motor_io_position_new_M)) {
    /* Gain: '<S2>/Gain2' */
    motor_io_position_new_B.Gain2_n = motor_io_position_new_P.Kb *
      motor_io_position_new_B.Sum3_o;

    /* Sum: '<S2>/Sum4' */
    motor_io_position_new_B.Sum4_b = motor_io_position_new_B.Gain2_n +
      motor_io_position_new_B.Gain_g;
  }

  /* Sum: '<S2>/Sum5' */
  motor_io_position_new_B.Sum5_a = motor_io_position_new_B.Gain1_k +
    motor_io_position_new_B.Gain2_n;
  if (rtmIsMajorTimeStep(motor_io_position_new_M)) {
    /* DiscreteTransferFcn: '<S2>/Gff1' */
    temp = 0.0 - motor_io_position_new_P.R_sim[1] *
      motor_io_position_new_DW.Gff1_states_n[0];
    temp -= motor_io_position_new_P.R_sim[2] *
      motor_io_position_new_DW.Gff1_states_n[1];
    temp /= motor_io_position_new_P.R_sim[0];
    motor_io_position_new_DW.Gff1_tmp_o = temp;
    temp = motor_io_position_new_P.T_sim[0] *
      motor_io_position_new_DW.Gff1_tmp_o;
    temp += motor_io_position_new_P.T_sim[1] *
      motor_io_position_new_DW.Gff1_states_n[0];
    temp += motor_io_position_new_P.T_sim[2] *
      motor_io_position_new_DW.Gff1_states_n[1];
    motor_io_position_new_B.Gff1_p = temp;

    /* DiscreteTransferFcn: '<S2>/Gff2' */
    temp = 0.0 - motor_io_position_new_P.R_sim[1] *
      motor_io_position_new_DW.Gff2_states_b[0];
    temp -= motor_io_position_new_P.R_sim[2] *
      motor_io_position_new_DW.Gff2_states_b[1];
    temp /= motor_io_position_new_P.R_sim[0];
    motor_io_position_new_DW.Gff2_tmp_k = temp;
    temp = motor_io_position_new_P.S_sim[0] *
      motor_io_position_new_DW.Gff2_tmp_k;
    temp += motor_io_position_new_P.S_sim[1] *
      motor_io_position_new_DW.Gff2_states_b[0];
    temp += motor_io_position_new_P.S_sim[2] *
      motor_io_position_new_DW.Gff2_states_b[1];
    motor_io_position_new_B.Gff2_p = temp;
  }

  /* Integrator: '<S3>/Integrator' */
  motor_io_position_new_B.Integrator = motor_io_position_new_X.Integrator_CSTATE;

  /* Gain: '<S3>/Gain1' */
  motor_io_position_new_B.Gain1_b = motor_io_position_new_P.Gain1_Gain *
    motor_io_position_new_B.Integrator;

  /* Sum: '<S3>/Add' */
  motor_io_position_new_B.Add = motor_io_position_new_B.VoltageSaturation_j -
    motor_io_position_new_B.Gain1_b;

  /* Gain: '<S3>/k//R ' */
  motor_io_position_new_B.kR = motor_io_position_new_P.kR_Gain *
    motor_io_position_new_B.Add;

  /* Saturate: '<S8>/Saturate to Fc' */
  temp = motor_io_position_new_B.kR;
  u1 = motor_io_position_new_P.SaturatetoFc_LowerSat;
  u2 = motor_io_position_new_P.F_c_upper;
  if (temp > u2) {
    motor_io_position_new_B.Stickslipregion = u2;
  } else if (temp < u1) {
    motor_io_position_new_B.Stickslipregion = u1;
  } else {
    motor_io_position_new_B.Stickslipregion = temp;
  }

  /* End of Saturate: '<S8>/Saturate to Fc' */

  /* Abs: '<S8>/Abs' */
  motor_io_position_new_B.Abs = fabs(motor_io_position_new_B.Integrator);

  /* RelationalOperator: '<S9>/Compare' incorporates:
   *  Constant: '<S9>/Constant'
   */
  motor_io_position_new_B.Compare = (motor_io_position_new_B.Abs <=
    motor_io_position_new_P.Constant_Value);

  /* Gain: '<S8>/Vicous friction' */
  motor_io_position_new_B.Vicousfriction =
    motor_io_position_new_P.Vicousfriction_Gain *
    motor_io_position_new_B.Integrator;

  /* Signum: '<S8>/Sign' */
  temp = motor_io_position_new_B.Integrator;
  if (temp < 0.0) {
    motor_io_position_new_B.Sign = -1.0;
  } else if (temp > 0.0) {
    motor_io_position_new_B.Sign = 1.0;
  } else if (temp == 0.0) {
    motor_io_position_new_B.Sign = 0.0;
  } else {
    motor_io_position_new_B.Sign = temp;
  }

  /* End of Signum: '<S8>/Sign' */

  /* Product: '<S8>/Product' incorporates:
   *  Constant: '<S8>/F_c'
   */
  motor_io_position_new_B.Product = motor_io_position_new_P.F_c *
    motor_io_position_new_B.Sign;

  /* Sum: '<S8>/Add' */
  motor_io_position_new_B.Viscousregion = motor_io_position_new_B.Vicousfriction
    + motor_io_position_new_B.Product;

  /* Switch: '<S8>/Switch' */
  if (motor_io_position_new_B.Compare) {
    motor_io_position_new_B.Friction = motor_io_position_new_B.Stickslipregion;
  } else {
    motor_io_position_new_B.Friction = motor_io_position_new_B.Viscousregion;
  }

  /* End of Switch: '<S8>/Switch' */

  /* Sum: '<S3>/Add1' */
  motor_io_position_new_B.Add1 = motor_io_position_new_B.kR -
    motor_io_position_new_B.Friction;
  if (rtmIsMajorTimeStep(motor_io_position_new_M)) {
    /* Gain: '<S3>/Gain2' incorporates:
     *  Constant: '<S3>/Load inertia'
     */
    motor_io_position_new_B.Gain2_j = motor_io_position_new_P.Gain2_Gain *
      motor_io_position_new_P.J1;

    /* Sum: '<S3>/Add2' incorporates:
     *  Constant: '<S3>/Motor inertia'
     */
    motor_io_position_new_B.Add2 = motor_io_position_new_B.Gain2_j +
      motor_io_position_new_P.Motorinertia_Value;
  }

  /* Product: '<S3>/Inertias 1//J' */
  motor_io_position_new_B.Inertias1J = 1.0 / motor_io_position_new_B.Add2 *
    motor_io_position_new_B.Add1;
  if (rtmIsMajorTimeStep(motor_io_position_new_M)) {
    /* S-Function (rti_commonblock): '<S15>/S-Function2' */
    /* This comment workarounds a code generation problem */

    /* Gain: '<S7>/w1_scaling' */
    motor_io_position_new_B.w1_scaling = motor_io_position_new_P.w1_scaling_Gain
      * motor_io_position_new_B.SFunction2;

    /* Outputs for Triggered SubSystem: '<S7>/DS1104ENC_SET_POS_C1' incorporates:
     *  TriggerPort: '<S17>/Trigger'
     */
    if (rtmIsMajorTimeStep(motor_io_position_new_M)) {
      /* Constant: '<S7>/Reset enc' */
      zcEvent = rt_ZCFcn(RISING_ZERO_CROSSING,
                         &motor_io_position_new_PrevZCX.DS1104ENC_SET_POS_C1_Trig_ZCE,
                         (motor_io_position_new_P.Resetenc_Value));
      if (zcEvent != NO_ZCEVENT) {
        /* S-Function (rti_commonblock): '<S17>/S-Function1' */
        /* This comment workarounds a code generation problem */

        /* dSPACE I/O Board DS1104 Unit:ENC_SET */
        ds1104_inc_position_write(1, 0, DS1104_INC_LINE_SUBDIV_4);
      }
    }

    /* End of Outputs for SubSystem: '<S7>/DS1104ENC_SET_POS_C1' */

    /* S-Function (rti_commonblock): '<S16>/S-Function1' */
    /* This comment workarounds a code generation problem */

    /* S-Function (rti_commonblock): '<S16>/S-Function2' */
    /* This comment workarounds a code generation problem */
  }
}

/* Model update function */
void motor_io_position_new_update(void)
{
  real_T denAccum;
  if (rtmIsMajorTimeStep(motor_io_position_new_M)) {
    /* Update for DiscreteTransferFcn: '<S2>/Gff' */
    motor_io_position_new_DW.Gff_states = motor_io_position_new_DW.Gff_tmp;

    /* Update for DiscreteTransferFcn: '<S2>/I part1' */
    denAccum = motor_io_position_new_B.Sum5_a;
    denAccum -= motor_io_position_new_P.Ipart1_DenCoef[1] *
      motor_io_position_new_DW.Ipart1_states;
    denAccum /= motor_io_position_new_P.Ipart1_DenCoef[0];
    motor_io_position_new_DW.Ipart1_states = denAccum;

    /* Update for DiscreteTransferFcn: '<S2>/I part' */
    denAccum = motor_io_position_new_B.Sum4_b;
    denAccum -= motor_io_position_new_P.Ipart_DenCoef[1] *
      motor_io_position_new_DW.Ipart_states;
    denAccum /= motor_io_position_new_P.Ipart_DenCoef[0];
    motor_io_position_new_DW.Ipart_states = denAccum;

    /* Update for DiscreteTransferFcn: '<S2>/PD part' */
    motor_io_position_new_DW.PDpart_states = motor_io_position_new_DW.PDpart_tmp;

    /* Update for DiscreteTransferFcn: '<S1>/Gff' */
    motor_io_position_new_DW.Gff_states_d = motor_io_position_new_DW.Gff_tmp_k;

    /* Update for DiscreteTransferFcn: '<S1>/I part1' */
    denAccum = motor_io_position_new_B.Sum5;
    denAccum -= motor_io_position_new_P.Ipart1_DenCoef_n[1] *
      motor_io_position_new_DW.Ipart1_states_o;
    denAccum /= motor_io_position_new_P.Ipart1_DenCoef_n[0];
    motor_io_position_new_DW.Ipart1_states_o = denAccum;

    /* Update for DiscreteTransferFcn: '<S1>/I part' */
    denAccum = motor_io_position_new_B.Sum4;
    denAccum -= motor_io_position_new_P.Ipart_DenCoef_n[1] *
      motor_io_position_new_DW.Ipart_states_f;
    denAccum /= motor_io_position_new_P.Ipart_DenCoef_n[0];
    motor_io_position_new_DW.Ipart_states_f = denAccum;

    /* Update for DiscreteTransferFcn: '<S1>/PD part' */
    motor_io_position_new_DW.PDpart_states_j =
      motor_io_position_new_DW.PDpart_tmp_m;

    /* Update for DiscreteTransferFcn: '<S1>/Gff1' */
    motor_io_position_new_DW.Gff1_states[1] =
      motor_io_position_new_DW.Gff1_states[0];
    motor_io_position_new_DW.Gff1_states[0] = motor_io_position_new_DW.Gff1_tmp;

    /* Update for DiscreteTransferFcn: '<S1>/Gff2' */
    motor_io_position_new_DW.Gff2_states[1] =
      motor_io_position_new_DW.Gff2_states[0];
    motor_io_position_new_DW.Gff2_states[0] = motor_io_position_new_DW.Gff2_tmp;

    /* Update for DiscreteTransferFcn: '<S2>/Gff1' */
    motor_io_position_new_DW.Gff1_states_n[1] =
      motor_io_position_new_DW.Gff1_states_n[0];
    motor_io_position_new_DW.Gff1_states_n[0] =
      motor_io_position_new_DW.Gff1_tmp_o;

    /* Update for DiscreteTransferFcn: '<S2>/Gff2' */
    motor_io_position_new_DW.Gff2_states_b[1] =
      motor_io_position_new_DW.Gff2_states_b[0];
    motor_io_position_new_DW.Gff2_states_b[0] =
      motor_io_position_new_DW.Gff2_tmp_k;
  }

  if (rtmIsMajorTimeStep(motor_io_position_new_M)) {
    rt_ertODEUpdateContinuousStates(&motor_io_position_new_M->solverInfo);
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
  if (!(++motor_io_position_new_M->Timing.clockTick0)) {
    ++motor_io_position_new_M->Timing.clockTickH0;
  }

  motor_io_position_new_M->Timing.t[0] = rtsiGetSolverStopTime
    (&motor_io_position_new_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.10870562815189595s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++motor_io_position_new_M->Timing.clockTick1)) {
      ++motor_io_position_new_M->Timing.clockTickH1;
    }

    motor_io_position_new_M->Timing.t[1] =
      motor_io_position_new_M->Timing.clockTick1 *
      motor_io_position_new_M->Timing.stepSize1 +
      motor_io_position_new_M->Timing.clockTickH1 *
      motor_io_position_new_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void motor_io_position_new_derivatives(void)
{
  XDot_motor_io_position_new_T *_rtXdot;
  _rtXdot = ((XDot_motor_io_position_new_T *)
             motor_io_position_new_M->ModelData.derivs);

  /* Derivatives for Integrator: '<S3>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = motor_io_position_new_B.Integrator;

  /* Derivatives for Integrator: '<S3>/Integrator' */
  _rtXdot->Integrator_CSTATE = motor_io_position_new_B.Inertias1J;
}

/* Model initialize function */
void motor_io_position_new_initialize(void)
{
  /* Start for S-Function (rti_commonblock): '<S11>/S-Function1' */

  /* dSPACE I/O Board DS1104 #1 Unit:PWM Group:PWM */
  motor_io_position_new_DW.SFunction1_IWORK[0] = 0;
  motor_io_position_new_PrevZCX.DS1104ENC_SET_POS_C1_Trig_ZCE =
    UNINITIALIZED_ZCSIG;

  /* InitializeConditions for DiscreteTransferFcn: '<S2>/Gff' */
  motor_io_position_new_DW.Gff_states =
    motor_io_position_new_P.Gff_InitialStates;

  /* InitializeConditions for DiscreteTransferFcn: '<S2>/I part1' */
  motor_io_position_new_DW.Ipart1_states =
    motor_io_position_new_P.Ipart1_InitialStates;

  /* InitializeConditions for DiscreteTransferFcn: '<S2>/I part' */
  motor_io_position_new_DW.Ipart_states =
    motor_io_position_new_P.Ipart_InitialStates;

  /* InitializeConditions for DiscreteTransferFcn: '<S2>/PD part' */
  motor_io_position_new_DW.PDpart_states =
    motor_io_position_new_P.PDpart_InitialStates;

  /* InitializeConditions for DiscreteTransferFcn: '<S1>/Gff' */
  motor_io_position_new_DW.Gff_states_d =
    motor_io_position_new_P.Gff_InitialStates_e;

  /* InitializeConditions for DiscreteTransferFcn: '<S1>/I part1' */
  motor_io_position_new_DW.Ipart1_states_o =
    motor_io_position_new_P.Ipart1_InitialStates_h;

  /* InitializeConditions for DiscreteTransferFcn: '<S1>/I part' */
  motor_io_position_new_DW.Ipart_states_f =
    motor_io_position_new_P.Ipart_InitialStates_f;

  /* InitializeConditions for Integrator: '<S3>/Integrator1' */
  motor_io_position_new_X.Integrator1_CSTATE =
    motor_io_position_new_P.Integrator1_IC;

  /* InitializeConditions for DiscreteTransferFcn: '<S1>/PD part' */
  motor_io_position_new_DW.PDpart_states_j =
    motor_io_position_new_P.PDpart_InitialStates_h;

  /* InitializeConditions for DiscreteTransferFcn: '<S1>/Gff1' */
  motor_io_position_new_DW.Gff1_states[0] =
    motor_io_position_new_P.Gff1_InitialStates;
  motor_io_position_new_DW.Gff1_states[1] =
    motor_io_position_new_P.Gff1_InitialStates;

  /* InitializeConditions for DiscreteTransferFcn: '<S1>/Gff2' */
  motor_io_position_new_DW.Gff2_states[0] =
    motor_io_position_new_P.Gff2_InitialStates;
  motor_io_position_new_DW.Gff2_states[1] =
    motor_io_position_new_P.Gff2_InitialStates;

  /* InitializeConditions for DiscreteTransferFcn: '<S2>/Gff1' */
  motor_io_position_new_DW.Gff1_states_n[0] =
    motor_io_position_new_P.Gff1_InitialStates_k;
  motor_io_position_new_DW.Gff1_states_n[1] =
    motor_io_position_new_P.Gff1_InitialStates_k;

  /* InitializeConditions for DiscreteTransferFcn: '<S2>/Gff2' */
  motor_io_position_new_DW.Gff2_states_b[0] =
    motor_io_position_new_P.Gff2_InitialStates_g;
  motor_io_position_new_DW.Gff2_states_b[1] =
    motor_io_position_new_P.Gff2_InitialStates_g;

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
  motor_io_position_new_X.Integrator_CSTATE =
    motor_io_position_new_P.Integrator_IC;
}

/* Model terminate function */
void motor_io_position_new_terminate(void)
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
  motor_io_position_new_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  motor_io_position_new_update();
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
  motor_io_position_new_initialize();
}

void MdlTerminate(void)
{
  motor_io_position_new_terminate();
}

/* Registration function */
RT_MODEL_motor_io_position_ne_T *motor_io_position_new(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)motor_io_position_new_M, 0,
                sizeof(RT_MODEL_motor_io_position_ne_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&motor_io_position_new_M->solverInfo,
                          &motor_io_position_new_M->Timing.simTimeStep);
    rtsiSetTPtr(&motor_io_position_new_M->solverInfo, &rtmGetTPtr
                (motor_io_position_new_M));
    rtsiSetStepSizePtr(&motor_io_position_new_M->solverInfo,
                       &motor_io_position_new_M->Timing.stepSize0);
    rtsiSetdXPtr(&motor_io_position_new_M->solverInfo,
                 &motor_io_position_new_M->ModelData.derivs);
    rtsiSetContStatesPtr(&motor_io_position_new_M->solverInfo, (real_T **)
                         &motor_io_position_new_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&motor_io_position_new_M->solverInfo,
      &motor_io_position_new_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&motor_io_position_new_M->solverInfo,
                          (&rtmGetErrorStatus(motor_io_position_new_M)));
    rtsiSetRTModelPtr(&motor_io_position_new_M->solverInfo,
                      motor_io_position_new_M);
  }

  rtsiSetSimTimeStep(&motor_io_position_new_M->solverInfo, MAJOR_TIME_STEP);
  motor_io_position_new_M->ModelData.intgData.f[0] =
    motor_io_position_new_M->ModelData.odeF[0];
  motor_io_position_new_M->ModelData.contStates = ((real_T *)
    &motor_io_position_new_X);
  rtsiSetSolverData(&motor_io_position_new_M->solverInfo, (void *)
                    &motor_io_position_new_M->ModelData.intgData);
  rtsiSetSolverName(&motor_io_position_new_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = motor_io_position_new_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    motor_io_position_new_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    motor_io_position_new_M->Timing.sampleTimes =
      (&motor_io_position_new_M->Timing.sampleTimesArray[0]);
    motor_io_position_new_M->Timing.offsetTimes =
      (&motor_io_position_new_M->Timing.offsetTimesArray[0]);

    /* task periods */
    motor_io_position_new_M->Timing.sampleTimes[0] = (0.0);
    motor_io_position_new_M->Timing.sampleTimes[1] = (0.10870562815189595);

    /* task offsets */
    motor_io_position_new_M->Timing.offsetTimes[0] = (0.0);
    motor_io_position_new_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(motor_io_position_new_M, &motor_io_position_new_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = motor_io_position_new_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    motor_io_position_new_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(motor_io_position_new_M, -1);
  motor_io_position_new_M->Timing.stepSize0 = 0.10870562815189595;
  motor_io_position_new_M->Timing.stepSize1 = 0.10870562815189595;
  motor_io_position_new_M->solverInfoPtr = (&motor_io_position_new_M->solverInfo);
  motor_io_position_new_M->Timing.stepSize = (0.10870562815189595);
  rtsiSetFixedStepSize(&motor_io_position_new_M->solverInfo, 0.10870562815189595);
  rtsiSetSolverMode(&motor_io_position_new_M->solverInfo,
                    SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  motor_io_position_new_M->ModelData.blockIO = ((void *)
    &motor_io_position_new_B);
  (void) memset(((void *) &motor_io_position_new_B), 0,
                sizeof(B_motor_io_position_new_T));

  {
    motor_io_position_new_B.SinGenerator = 0.0;
    motor_io_position_new_B.SquareGenerator = 0.0;
    motor_io_position_new_B.ref = 0.0;
    motor_io_position_new_B.Gff = 0.0;
    motor_io_position_new_B.Ipart1 = 0.0;
    motor_io_position_new_B.Sum1 = 0.0;
    motor_io_position_new_B.Ipart = 0.0;
    motor_io_position_new_B.SFunction1 = 0.0;
    motor_io_position_new_B.fi1_scaling = 0.0;
    motor_io_position_new_B.PDpart = 0.0;
    motor_io_position_new_B.Sum = 0.0;
    motor_io_position_new_B.Sum2 = 0.0;
    motor_io_position_new_B.VoltageSaturation = 0.0;
    motor_io_position_new_B.Gain = 0.0;
    motor_io_position_new_B.Volt = 0.0;
    motor_io_position_new_B.pwm_skalning = 0.0;
    motor_io_position_new_B.Sum_f = 0.0;
    motor_io_position_new_B.Gff_e = 0.0;
    motor_io_position_new_B.Ipart1_d = 0.0;
    motor_io_position_new_B.Sum1_e = 0.0;
    motor_io_position_new_B.Ipart_a = 0.0;
    motor_io_position_new_B.Integrator1 = 0.0;
    motor_io_position_new_B.Quantizer = 0.0;
    motor_io_position_new_B.ZeroOrderHold = 0.0;
    motor_io_position_new_B.PDpart_k = 0.0;
    motor_io_position_new_B.Sum_e = 0.0;
    motor_io_position_new_B.Sum2_n = 0.0;
    motor_io_position_new_B.VoltageSaturation_j = 0.0;
    motor_io_position_new_B.Sum3 = 0.0;
    motor_io_position_new_B.Gain_m = 0.0;
    motor_io_position_new_B.Gain1 = 0.0;
    motor_io_position_new_B.Gain2 = 0.0;
    motor_io_position_new_B.Sum4 = 0.0;
    motor_io_position_new_B.Sum5 = 0.0;
    motor_io_position_new_B.Gff1 = 0.0;
    motor_io_position_new_B.Gff2 = 0.0;
    motor_io_position_new_B.Sum3_o = 0.0;
    motor_io_position_new_B.Gain_g = 0.0;
    motor_io_position_new_B.Gain1_k = 0.0;
    motor_io_position_new_B.Gain2_n = 0.0;
    motor_io_position_new_B.Sum4_b = 0.0;
    motor_io_position_new_B.Sum5_a = 0.0;
    motor_io_position_new_B.Gff1_p = 0.0;
    motor_io_position_new_B.Gff2_p = 0.0;
    motor_io_position_new_B.Integrator = 0.0;
    motor_io_position_new_B.Gain1_b = 0.0;
    motor_io_position_new_B.Add = 0.0;
    motor_io_position_new_B.kR = 0.0;
    motor_io_position_new_B.Stickslipregion = 0.0;
    motor_io_position_new_B.Abs = 0.0;
    motor_io_position_new_B.Vicousfriction = 0.0;
    motor_io_position_new_B.Sign = 0.0;
    motor_io_position_new_B.Product = 0.0;
    motor_io_position_new_B.Viscousregion = 0.0;
    motor_io_position_new_B.Friction = 0.0;
    motor_io_position_new_B.Add1 = 0.0;
    motor_io_position_new_B.Gain2_j = 0.0;
    motor_io_position_new_B.Add2 = 0.0;
    motor_io_position_new_B.Inertias1J = 0.0;
    motor_io_position_new_B.SFunction2 = 0.0;
    motor_io_position_new_B.w1_scaling = 0.0;
  }

  /* parameters */
  motor_io_position_new_M->ModelData.defaultParam = ((real_T *)
    &motor_io_position_new_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &motor_io_position_new_X;
    motor_io_position_new_M->ModelData.contStates = (x);
    (void) memset((void *)&motor_io_position_new_X, 0,
                  sizeof(X_motor_io_position_new_T));
  }

  /* states (dwork) */
  motor_io_position_new_M->ModelData.dwork = ((void *) &motor_io_position_new_DW);
  (void) memset((void *)&motor_io_position_new_DW, 0,
                sizeof(DW_motor_io_position_new_T));
  motor_io_position_new_DW.Gff_states = 0.0;
  motor_io_position_new_DW.Ipart1_states = 0.0;
  motor_io_position_new_DW.Ipart_states = 0.0;
  motor_io_position_new_DW.PDpart_states = 0.0;
  motor_io_position_new_DW.Gff_states_d = 0.0;
  motor_io_position_new_DW.Ipart1_states_o = 0.0;
  motor_io_position_new_DW.Ipart_states_f = 0.0;
  motor_io_position_new_DW.PDpart_states_j = 0.0;
  motor_io_position_new_DW.Gff1_states[0] = 0.0;
  motor_io_position_new_DW.Gff1_states[1] = 0.0;
  motor_io_position_new_DW.Gff2_states[0] = 0.0;
  motor_io_position_new_DW.Gff2_states[1] = 0.0;
  motor_io_position_new_DW.Gff1_states_n[0] = 0.0;
  motor_io_position_new_DW.Gff1_states_n[1] = 0.0;
  motor_io_position_new_DW.Gff2_states_b[0] = 0.0;
  motor_io_position_new_DW.Gff2_states_b[1] = 0.0;
  motor_io_position_new_DW.Gff_tmp = 0.0;
  motor_io_position_new_DW.PDpart_tmp = 0.0;
  motor_io_position_new_DW.Gff_tmp_k = 0.0;
  motor_io_position_new_DW.PDpart_tmp_m = 0.0;
  motor_io_position_new_DW.Gff1_tmp = 0.0;
  motor_io_position_new_DW.Gff2_tmp = 0.0;
  motor_io_position_new_DW.Gff1_tmp_o = 0.0;
  motor_io_position_new_DW.Gff2_tmp_k = 0.0;

  {
    /* user code (registration function declaration) */
    /*Call the macro that initializes the global TRC pointers
       inside the model initialization/registration function. */
    RTI_INIT_TRC_POINTERS();
  }

  /* Initialize Sizes */
  motor_io_position_new_M->Sizes.numContStates = (2);/* Number of continuous states */
  motor_io_position_new_M->Sizes.numY = (0);/* Number of model outputs */
  motor_io_position_new_M->Sizes.numU = (0);/* Number of model inputs */
  motor_io_position_new_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  motor_io_position_new_M->Sizes.numSampTimes = (2);/* Number of sample times */
  motor_io_position_new_M->Sizes.numBlocks = (83);/* Number of blocks */
  motor_io_position_new_M->Sizes.numBlockIO = (63);/* Number of block outputs */
  motor_io_position_new_M->Sizes.numBlockPrms = (87);/* Sum of parameter "widths" */
  return motor_io_position_new_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
