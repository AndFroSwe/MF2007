/*
 * motor_io_velocity.c
 *
 * Code generation for model "motor_io_velocity".
 *
 * Model version              : 1.33
 * Simulink Coder version : 8.7 (R2014b) 08-Sep-2014
 * C source code generated on : Wed Mar 30 15:57:58 2016
 *
 * Target selection: rti1104.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Custom
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "motor_io_velocity_trc_ptr.h"
#include "motor_io_velocity.h"
#include "motor_io_velocity_private.h"

/* Block signals (auto storage) */
B_motor_io_velocity_T motor_io_velocity_B;

/* Continuous states */
X_motor_io_velocity_T motor_io_velocity_X;

/* Block states (auto storage) */
DW_motor_io_velocity_T motor_io_velocity_DW;

/* Previous zero-crossings (trigger) states */
PrevZCX_motor_io_velocity_T motor_io_velocity_PrevZCX;

/* Real-time model */
RT_MODEL_motor_io_velocity_T motor_io_velocity_M_;
RT_MODEL_motor_io_velocity_T *const motor_io_velocity_M = &motor_io_velocity_M_;

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
  motor_io_velocity_derivatives();
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
void motor_io_velocity_output(void)
{
  real_T temp;
  ZCEventType zcEvent;
  real_T u1;
  real_T u2;
  if (rtmIsMajorTimeStep(motor_io_velocity_M)) {
    /* set solver stop time */
    if (!(motor_io_velocity_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&motor_io_velocity_M->solverInfo,
                            ((motor_io_velocity_M->Timing.clockTickH0 + 1) *
        motor_io_velocity_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&motor_io_velocity_M->solverInfo,
                            ((motor_io_velocity_M->Timing.clockTick0 + 1) *
        motor_io_velocity_M->Timing.stepSize0 +
        motor_io_velocity_M->Timing.clockTickH0 *
        motor_io_velocity_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(motor_io_velocity_M)) {
    motor_io_velocity_M->Timing.t[0] = rtsiGetT(&motor_io_velocity_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(motor_io_velocity_M)) {
    /* S-Function (rti_commonblock): '<S12>/S-Function2' */
    /* This comment workarounds a code generation problem */

    /* Gain: '<S4>/w1_scaling' */
    motor_io_velocity_B.w1_scaling = motor_io_velocity_P.w1_scaling_Gain *
      motor_io_velocity_B.SFunction2;

    /* DiscreteTransferFcn: '<Root>/G_fb_real' */
    temp = motor_io_velocity_B.w1_scaling;
    temp -= motor_io_velocity_P.G_fb_real_DenCoef[1] *
      motor_io_velocity_DW.G_fb_real_states;
    temp /= motor_io_velocity_P.G_fb_real_DenCoef[0];
    motor_io_velocity_DW.G_fb_real_tmp = temp;
    temp = motor_io_velocity_P.G_fb_real_NumCoef[0] *
      motor_io_velocity_DW.G_fb_real_tmp;
    temp += motor_io_velocity_P.G_fb_real_NumCoef[1] *
      motor_io_velocity_DW.G_fb_real_states;
    motor_io_velocity_B.G_fb_real = temp;
  }

  /* SignalGenerator: '<Root>/SinGenerator' */
  motor_io_velocity_B.SinGenerator = sin
    (motor_io_velocity_P.SinGenerator_Frequency * motor_io_velocity_M->Timing.t
     [0]) * motor_io_velocity_P.SinGenerator_Amplitude;

  /* SignalGenerator: '<Root>/SquareGenerator' */
  temp = motor_io_velocity_P.SquareGenerator_Frequency *
    motor_io_velocity_M->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    motor_io_velocity_B.SquareGenerator =
      motor_io_velocity_P.SquareGenerator_Amplitude;
  } else {
    motor_io_velocity_B.SquareGenerator =
      -motor_io_velocity_P.SquareGenerator_Amplitude;
  }

  /* End of SignalGenerator: '<Root>/SquareGenerator' */

  /* Switch: '<Root>/Switch' incorporates:
   *  Constant: '<Root>/SignalSelector[0Square,1Sine]'
   */
  if (motor_io_velocity_P.SignalSelector0Square1Sine_Valu != 0.0) {
    motor_io_velocity_B.ref = motor_io_velocity_B.SinGenerator;
  } else {
    motor_io_velocity_B.ref = motor_io_velocity_B.SquareGenerator;
  }

  /* End of Switch: '<Root>/Switch' */
  if (rtmIsMajorTimeStep(motor_io_velocity_M)) {
    /* DiscreteTransferFcn: '<Root>/Gff_real' */
    temp = motor_io_velocity_B.ref;
    temp -= motor_io_velocity_P.Gff_real_DenCoef[1] *
      motor_io_velocity_DW.Gff_real_states;
    temp /= motor_io_velocity_P.Gff_real_DenCoef[0];
    motor_io_velocity_DW.Gff_real_tmp = temp;
    temp = motor_io_velocity_P.Gff_real_NumCoef[0] *
      motor_io_velocity_DW.Gff_real_tmp;
    temp += motor_io_velocity_P.Gff_real_NumCoef[1] *
      motor_io_velocity_DW.Gff_real_states;
    motor_io_velocity_B.Gff_real = temp;

    /* Sum: '<Root>/Sum' */
    motor_io_velocity_B.Sum = motor_io_velocity_B.Gff_real -
      motor_io_velocity_B.G_fb_real;

    /* Gain: '<Root>/Gain' */
    motor_io_velocity_B.Gain = motor_io_velocity_P.Gain_Gain *
      motor_io_velocity_B.Sum;

    /* Saturate: '<S2>/Saturation' */
    temp = motor_io_velocity_B.Gain;
    u1 = motor_io_velocity_P.Saturation_LowerSat;
    u2 = motor_io_velocity_P.Saturation_UpperSat;
    if (temp > u2) {
      motor_io_velocity_B.Volt = u2;
    } else if (temp < u1) {
      motor_io_velocity_B.Volt = u1;
    } else {
      motor_io_velocity_B.Volt = temp;
    }

    /* End of Saturate: '<S2>/Saturation' */

    /* Gain: '<S2>/pwm_skalning' */
    motor_io_velocity_B.pwm_skalning = motor_io_velocity_P.pwm_skalning_Gain *
      motor_io_velocity_B.Volt;

    /* Sum: '<S2>/Sum' incorporates:
     *  Constant: '<S2>/pwm_offstet'
     */
    motor_io_velocity_B.Sum_f = motor_io_velocity_B.pwm_skalning +
      motor_io_velocity_P.pwm_offstet_Value;

    /* S-Function (rti_commonblock): '<S8>/S-Function1' */
    /* This comment workarounds a code generation problem */

    /* dSPACE I/O Board DS1104 #1 Unit:PWM Group:PWM */
    ds1104_slave_dsp_pwm_duty_write(0, rti_slv1104_fcn_index[6],
      motor_io_velocity_B.Sum_f);

    /* S-Function (rti_commonblock): '<S8>/S-Function2' */
    /* This comment workarounds a code generation problem */

    /* S-Function (rti_commonblock): '<S8>/S-Function3' */
    /* This comment workarounds a code generation problem */

    /* S-Function (rti_commonblock): '<S8>/S-Function4' */
    /* This comment workarounds a code generation problem */

    /* DataTypeConversion: '<S2>/Data Type Conversion' incorporates:
     *  Constant: '<S2>/Enable[1_Off, 0_On]'
     */
    motor_io_velocity_B.DataTypeConversion =
      (motor_io_velocity_P.Enable1_Off0_On_Value != 0.0);

    /* S-Function (rti_commonblock): '<S7>/S-Function1' */
    /* This comment workarounds a code generation problem */

    /* dSPACE I/O Board DS1104 #1 Unit:BIT_IO Group:BIT_OUT */
    if (motor_io_velocity_B.DataTypeConversion > 0) {
      ds1104_bit_io_set(DS1104_DIO0);
    } else {
      ds1104_bit_io_clear(DS1104_DIO0);
    }

    /* DiscreteTransferFcn: '<Root>/Gff1' */
    temp = motor_io_velocity_B.ref;
    temp -= motor_io_velocity_P.Gff1_DenCoef[1] *
      motor_io_velocity_DW.Gff1_states;
    temp /= motor_io_velocity_P.Gff1_DenCoef[0];
    motor_io_velocity_DW.Gff1_tmp = temp;
    temp = motor_io_velocity_P.Gff1_NumCoef[0] * motor_io_velocity_DW.Gff1_tmp;
    temp += motor_io_velocity_P.Gff1_NumCoef[1] *
      motor_io_velocity_DW.Gff1_states;
    motor_io_velocity_B.Gff1 = temp;
  }

  /* Integrator: '<S1>/Integrator' */
  motor_io_velocity_B.Integrator = motor_io_velocity_X.Integrator_CSTATE;

  /* Quantizer: '<Root>/Quantizer' */
  temp = motor_io_velocity_B.Integrator;
  motor_io_velocity_B.Quantizer = rt_roundd_snf(temp / motor_io_velocity_P.quant)
    * motor_io_velocity_P.quant;
  if (rtmIsMajorTimeStep(motor_io_velocity_M)) {
    /* DiscreteTransferFcn: '<Root>/Gfb1' */
    temp = motor_io_velocity_B.Quantizer;
    temp -= motor_io_velocity_P.Gfb1_DenCoef[1] *
      motor_io_velocity_DW.Gfb1_states;
    temp /= motor_io_velocity_P.Gfb1_DenCoef[0];
    motor_io_velocity_DW.Gfb1_tmp = temp;
    temp = motor_io_velocity_P.Gfb1_NumCoef[0] * motor_io_velocity_DW.Gfb1_tmp;
    temp += motor_io_velocity_P.Gfb1_NumCoef[1] *
      motor_io_velocity_DW.Gfb1_states;
    motor_io_velocity_B.Gfb1 = temp;

    /* Sum: '<Root>/Sum1' */
    motor_io_velocity_B.Sum1 = motor_io_velocity_B.Gff1 -
      motor_io_velocity_B.Gfb1;

    /* Saturate: '<Root>/Saturation' */
    temp = motor_io_velocity_B.Sum1;
    u1 = motor_io_velocity_P.Saturation_LowerSat_c;
    u2 = motor_io_velocity_P.Saturation_UpperSat_p;
    if (temp > u2) {
      motor_io_velocity_B.Saturation = u2;
    } else if (temp < u1) {
      motor_io_velocity_B.Saturation = u1;
    } else {
      motor_io_velocity_B.Saturation = temp;
    }

    /* End of Saturate: '<Root>/Saturation' */
  }

  /* Gain: '<S1>/Gain1' */
  motor_io_velocity_B.Gain1 = motor_io_velocity_P.Gain1_Gain *
    motor_io_velocity_B.Integrator;

  /* Sum: '<S1>/Add' */
  motor_io_velocity_B.Add = motor_io_velocity_B.Saturation -
    motor_io_velocity_B.Gain1;

  /* Gain: '<S1>/k//R ' */
  motor_io_velocity_B.kR = motor_io_velocity_P.kR_Gain * motor_io_velocity_B.Add;

  /* Saturate: '<S5>/Saturate to Fc' */
  temp = motor_io_velocity_B.kR;
  u1 = motor_io_velocity_P.SaturatetoFc_LowerSat;
  u2 = motor_io_velocity_P.F_c;
  if (temp > u2) {
    motor_io_velocity_B.Stickslipregion = u2;
  } else if (temp < u1) {
    motor_io_velocity_B.Stickslipregion = u1;
  } else {
    motor_io_velocity_B.Stickslipregion = temp;
  }

  /* End of Saturate: '<S5>/Saturate to Fc' */

  /* Abs: '<S5>/Abs' */
  motor_io_velocity_B.Abs = fabs(motor_io_velocity_B.Integrator);

  /* RelationalOperator: '<S6>/Compare' incorporates:
   *  Constant: '<S6>/Constant'
   */
  motor_io_velocity_B.Compare = (motor_io_velocity_B.Abs <=
    motor_io_velocity_P.Constant_Value);

  /* Gain: '<S5>/Vicous friction' */
  motor_io_velocity_B.Vicousfriction = motor_io_velocity_P.Vicousfriction_Gain *
    motor_io_velocity_B.Integrator;

  /* Signum: '<S5>/Sign' */
  temp = motor_io_velocity_B.Integrator;
  if (temp < 0.0) {
    motor_io_velocity_B.Sign = -1.0;
  } else if (temp > 0.0) {
    motor_io_velocity_B.Sign = 1.0;
  } else if (temp == 0.0) {
    motor_io_velocity_B.Sign = 0.0;
  } else {
    motor_io_velocity_B.Sign = temp;
  }

  /* End of Signum: '<S5>/Sign' */

  /* Product: '<S5>/Product' incorporates:
   *  Constant: '<S5>/F_c'
   */
  motor_io_velocity_B.Product = motor_io_velocity_P.F_c *
    motor_io_velocity_B.Sign;

  /* Sum: '<S5>/Add' */
  motor_io_velocity_B.Viscousregion = motor_io_velocity_B.Vicousfriction +
    motor_io_velocity_B.Product;

  /* Switch: '<S5>/Switch' */
  if (motor_io_velocity_B.Compare) {
    motor_io_velocity_B.Friction = motor_io_velocity_B.Stickslipregion;
  } else {
    motor_io_velocity_B.Friction = motor_io_velocity_B.Viscousregion;
  }

  /* End of Switch: '<S5>/Switch' */

  /* Sum: '<S1>/Add1' */
  motor_io_velocity_B.Add1 = motor_io_velocity_B.kR -
    motor_io_velocity_B.Friction;
  if (rtmIsMajorTimeStep(motor_io_velocity_M)) {
    /* Gain: '<S1>/Gain2' incorporates:
     *  Constant: '<S1>/Load inertia'
     */
    motor_io_velocity_B.Gain2 = motor_io_velocity_P.Gain2_Gain *
      motor_io_velocity_P.J1;

    /* Sum: '<S1>/Add2' incorporates:
     *  Constant: '<S1>/Motor inertia'
     */
    motor_io_velocity_B.Add2 = motor_io_velocity_B.Gain2 +
      motor_io_velocity_P.Motorinertia_Value;
  }

  /* Product: '<S1>/Inertias 1//J' */
  motor_io_velocity_B.Inertias1J = 1.0 / motor_io_velocity_B.Add2 *
    motor_io_velocity_B.Add1;

  /* Integrator: '<S1>/Integrator1' */
  motor_io_velocity_B.Integrator1 = motor_io_velocity_X.Integrator1_CSTATE;
  if (rtmIsMajorTimeStep(motor_io_velocity_M)) {
  }

  /* Switch: '<S5>/Switch1' incorporates:
   *  Constant: '<S5>/Constant1'
   *  Constant: '<S5>/F_c'
   */
  if (motor_io_velocity_B.Integrator > motor_io_velocity_P.Switch1_Threshold) {
    motor_io_velocity_B.Switch1 = motor_io_velocity_P.F_c;
  } else {
    motor_io_velocity_B.Switch1 = motor_io_velocity_P.Constant1_Value;
  }

  /* End of Switch: '<S5>/Switch1' */
  if (rtmIsMajorTimeStep(motor_io_velocity_M)) {
    /* S-Function (rti_commonblock): '<S12>/S-Function1' */
    /* This comment workarounds a code generation problem */

    /* Gain: '<S4>/fi1_scaling' */
    motor_io_velocity_B.fi1_scaling = motor_io_velocity_P.fi1_scaling_Gain *
      motor_io_velocity_B.SFunction1;

    /* Outputs for Triggered SubSystem: '<S4>/DS1104ENC_SET_POS_C1' incorporates:
     *  TriggerPort: '<S14>/Trigger'
     */
    if (rtmIsMajorTimeStep(motor_io_velocity_M)) {
      /* Constant: '<S4>/Reset enc' */
      zcEvent = rt_ZCFcn(RISING_ZERO_CROSSING,
                         &motor_io_velocity_PrevZCX.DS1104ENC_SET_POS_C1_Trig_ZCE,
                         (motor_io_velocity_P.Resetenc_Value));
      if (zcEvent != NO_ZCEVENT) {
        /* S-Function (rti_commonblock): '<S14>/S-Function1' */
        /* This comment workarounds a code generation problem */

        /* dSPACE I/O Board DS1104 Unit:ENC_SET */
        ds1104_inc_position_write(1, 0, DS1104_INC_LINE_SUBDIV_4);
      }
    }

    /* End of Outputs for SubSystem: '<S4>/DS1104ENC_SET_POS_C1' */

    /* S-Function (rti_commonblock): '<S13>/S-Function1' */
    /* This comment workarounds a code generation problem */

    /* S-Function (rti_commonblock): '<S13>/S-Function2' */
    /* This comment workarounds a code generation problem */
  }
}

/* Model update function */
void motor_io_velocity_update(void)
{
  if (rtmIsMajorTimeStep(motor_io_velocity_M)) {
    /* Update for DiscreteTransferFcn: '<Root>/G_fb_real' */
    motor_io_velocity_DW.G_fb_real_states = motor_io_velocity_DW.G_fb_real_tmp;

    /* Update for DiscreteTransferFcn: '<Root>/Gff_real' */
    motor_io_velocity_DW.Gff_real_states = motor_io_velocity_DW.Gff_real_tmp;

    /* Update for DiscreteTransferFcn: '<Root>/Gff1' */
    motor_io_velocity_DW.Gff1_states = motor_io_velocity_DW.Gff1_tmp;

    /* Update for DiscreteTransferFcn: '<Root>/Gfb1' */
    motor_io_velocity_DW.Gfb1_states = motor_io_velocity_DW.Gfb1_tmp;
  }

  if (rtmIsMajorTimeStep(motor_io_velocity_M)) {
    rt_ertODEUpdateContinuousStates(&motor_io_velocity_M->solverInfo);
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
  if (!(++motor_io_velocity_M->Timing.clockTick0)) {
    ++motor_io_velocity_M->Timing.clockTickH0;
  }

  motor_io_velocity_M->Timing.t[0] = rtsiGetSolverStopTime
    (&motor_io_velocity_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.021970064966318436s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++motor_io_velocity_M->Timing.clockTick1)) {
      ++motor_io_velocity_M->Timing.clockTickH1;
    }

    motor_io_velocity_M->Timing.t[1] = motor_io_velocity_M->Timing.clockTick1 *
      motor_io_velocity_M->Timing.stepSize1 +
      motor_io_velocity_M->Timing.clockTickH1 *
      motor_io_velocity_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void motor_io_velocity_derivatives(void)
{
  XDot_motor_io_velocity_T *_rtXdot;
  _rtXdot = ((XDot_motor_io_velocity_T *) motor_io_velocity_M->ModelData.derivs);

  /* Derivatives for Integrator: '<S1>/Integrator' */
  _rtXdot->Integrator_CSTATE = motor_io_velocity_B.Inertias1J;

  /* Derivatives for Integrator: '<S1>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = motor_io_velocity_B.Integrator;
}

/* Model initialize function */
void motor_io_velocity_initialize(void)
{
  /* Start for S-Function (rti_commonblock): '<S8>/S-Function1' */

  /* dSPACE I/O Board DS1104 #1 Unit:PWM Group:PWM */
  motor_io_velocity_DW.SFunction1_IWORK[0] = 0;
  motor_io_velocity_PrevZCX.DS1104ENC_SET_POS_C1_Trig_ZCE = UNINITIALIZED_ZCSIG;

  /* InitializeConditions for DiscreteTransferFcn: '<Root>/G_fb_real' */
  motor_io_velocity_DW.G_fb_real_states =
    motor_io_velocity_P.G_fb_real_InitialStates;

  /* InitializeConditions for DiscreteTransferFcn: '<Root>/Gff_real' */
  motor_io_velocity_DW.Gff_real_states =
    motor_io_velocity_P.Gff_real_InitialStates;

  /* InitializeConditions for DiscreteTransferFcn: '<Root>/Gff1' */
  motor_io_velocity_DW.Gff1_states = motor_io_velocity_P.Gff1_InitialStates;

  /* InitializeConditions for Integrator: '<S1>/Integrator' */
  motor_io_velocity_X.Integrator_CSTATE = motor_io_velocity_P.Integrator_IC;

  /* InitializeConditions for DiscreteTransferFcn: '<Root>/Gfb1' */
  motor_io_velocity_DW.Gfb1_states = motor_io_velocity_P.Gfb1_InitialStates;

  /* InitializeConditions for Integrator: '<S1>/Integrator1' */
  motor_io_velocity_X.Integrator1_CSTATE = motor_io_velocity_P.Integrator1_IC;
}

/* Model terminate function */
void motor_io_velocity_terminate(void)
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
  motor_io_velocity_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  motor_io_velocity_update();
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
  motor_io_velocity_initialize();
}

void MdlTerminate(void)
{
  motor_io_velocity_terminate();
}

/* Registration function */
RT_MODEL_motor_io_velocity_T *motor_io_velocity(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)motor_io_velocity_M, 0,
                sizeof(RT_MODEL_motor_io_velocity_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&motor_io_velocity_M->solverInfo,
                          &motor_io_velocity_M->Timing.simTimeStep);
    rtsiSetTPtr(&motor_io_velocity_M->solverInfo, &rtmGetTPtr
                (motor_io_velocity_M));
    rtsiSetStepSizePtr(&motor_io_velocity_M->solverInfo,
                       &motor_io_velocity_M->Timing.stepSize0);
    rtsiSetdXPtr(&motor_io_velocity_M->solverInfo,
                 &motor_io_velocity_M->ModelData.derivs);
    rtsiSetContStatesPtr(&motor_io_velocity_M->solverInfo, (real_T **)
                         &motor_io_velocity_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&motor_io_velocity_M->solverInfo,
      &motor_io_velocity_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&motor_io_velocity_M->solverInfo, (&rtmGetErrorStatus
      (motor_io_velocity_M)));
    rtsiSetRTModelPtr(&motor_io_velocity_M->solverInfo, motor_io_velocity_M);
  }

  rtsiSetSimTimeStep(&motor_io_velocity_M->solverInfo, MAJOR_TIME_STEP);
  motor_io_velocity_M->ModelData.intgData.f[0] =
    motor_io_velocity_M->ModelData.odeF[0];
  motor_io_velocity_M->ModelData.contStates = ((real_T *) &motor_io_velocity_X);
  rtsiSetSolverData(&motor_io_velocity_M->solverInfo, (void *)
                    &motor_io_velocity_M->ModelData.intgData);
  rtsiSetSolverName(&motor_io_velocity_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = motor_io_velocity_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    motor_io_velocity_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    motor_io_velocity_M->Timing.sampleTimes =
      (&motor_io_velocity_M->Timing.sampleTimesArray[0]);
    motor_io_velocity_M->Timing.offsetTimes =
      (&motor_io_velocity_M->Timing.offsetTimesArray[0]);

    /* task periods */
    motor_io_velocity_M->Timing.sampleTimes[0] = (0.0);
    motor_io_velocity_M->Timing.sampleTimes[1] = (0.021970064966318436);

    /* task offsets */
    motor_io_velocity_M->Timing.offsetTimes[0] = (0.0);
    motor_io_velocity_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(motor_io_velocity_M, &motor_io_velocity_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = motor_io_velocity_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    motor_io_velocity_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(motor_io_velocity_M, -1);
  motor_io_velocity_M->Timing.stepSize0 = 0.021970064966318436;
  motor_io_velocity_M->Timing.stepSize1 = 0.021970064966318436;
  motor_io_velocity_M->solverInfoPtr = (&motor_io_velocity_M->solverInfo);
  motor_io_velocity_M->Timing.stepSize = (0.021970064966318436);
  rtsiSetFixedStepSize(&motor_io_velocity_M->solverInfo, 0.021970064966318436);
  rtsiSetSolverMode(&motor_io_velocity_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  motor_io_velocity_M->ModelData.blockIO = ((void *) &motor_io_velocity_B);
  (void) memset(((void *) &motor_io_velocity_B), 0,
                sizeof(B_motor_io_velocity_T));

  {
    motor_io_velocity_B.SFunction2 = 0.0;
    motor_io_velocity_B.w1_scaling = 0.0;
    motor_io_velocity_B.G_fb_real = 0.0;
    motor_io_velocity_B.SinGenerator = 0.0;
    motor_io_velocity_B.SquareGenerator = 0.0;
    motor_io_velocity_B.ref = 0.0;
    motor_io_velocity_B.Gff_real = 0.0;
    motor_io_velocity_B.Sum = 0.0;
    motor_io_velocity_B.Gain = 0.0;
    motor_io_velocity_B.Volt = 0.0;
    motor_io_velocity_B.pwm_skalning = 0.0;
    motor_io_velocity_B.Sum_f = 0.0;
    motor_io_velocity_B.Gff1 = 0.0;
    motor_io_velocity_B.Integrator = 0.0;
    motor_io_velocity_B.Quantizer = 0.0;
    motor_io_velocity_B.Gfb1 = 0.0;
    motor_io_velocity_B.Sum1 = 0.0;
    motor_io_velocity_B.Saturation = 0.0;
    motor_io_velocity_B.Gain1 = 0.0;
    motor_io_velocity_B.Add = 0.0;
    motor_io_velocity_B.kR = 0.0;
    motor_io_velocity_B.Stickslipregion = 0.0;
    motor_io_velocity_B.Abs = 0.0;
    motor_io_velocity_B.Vicousfriction = 0.0;
    motor_io_velocity_B.Sign = 0.0;
    motor_io_velocity_B.Product = 0.0;
    motor_io_velocity_B.Viscousregion = 0.0;
    motor_io_velocity_B.Friction = 0.0;
    motor_io_velocity_B.Add1 = 0.0;
    motor_io_velocity_B.Gain2 = 0.0;
    motor_io_velocity_B.Add2 = 0.0;
    motor_io_velocity_B.Inertias1J = 0.0;
    motor_io_velocity_B.Integrator1 = 0.0;
    motor_io_velocity_B.Switch1 = 0.0;
    motor_io_velocity_B.SFunction1 = 0.0;
    motor_io_velocity_B.fi1_scaling = 0.0;
  }

  /* parameters */
  motor_io_velocity_M->ModelData.defaultParam = ((real_T *)&motor_io_velocity_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &motor_io_velocity_X;
    motor_io_velocity_M->ModelData.contStates = (x);
    (void) memset((void *)&motor_io_velocity_X, 0,
                  sizeof(X_motor_io_velocity_T));
  }

  /* states (dwork) */
  motor_io_velocity_M->ModelData.dwork = ((void *) &motor_io_velocity_DW);
  (void) memset((void *)&motor_io_velocity_DW, 0,
                sizeof(DW_motor_io_velocity_T));
  motor_io_velocity_DW.G_fb_real_states = 0.0;
  motor_io_velocity_DW.Gff_real_states = 0.0;
  motor_io_velocity_DW.Gff1_states = 0.0;
  motor_io_velocity_DW.Gfb1_states = 0.0;
  motor_io_velocity_DW.G_fb_real_tmp = 0.0;
  motor_io_velocity_DW.Gff_real_tmp = 0.0;
  motor_io_velocity_DW.Gff1_tmp = 0.0;
  motor_io_velocity_DW.Gfb1_tmp = 0.0;

  {
    /* user code (registration function declaration) */
    /*Call the macro that initializes the global TRC pointers
       inside the model initialization/registration function. */
    RTI_INIT_TRC_POINTERS();
  }

  /* Initialize Sizes */
  motor_io_velocity_M->Sizes.numContStates = (2);/* Number of continuous states */
  motor_io_velocity_M->Sizes.numY = (0);/* Number of model outputs */
  motor_io_velocity_M->Sizes.numU = (0);/* Number of model inputs */
  motor_io_velocity_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  motor_io_velocity_M->Sizes.numSampTimes = (2);/* Number of sample times */
  motor_io_velocity_M->Sizes.numBlocks = (57);/* Number of blocks */
  motor_io_velocity_M->Sizes.numBlockIO = (38);/* Number of block outputs */
  motor_io_velocity_M->Sizes.numBlockPrms = (50);/* Sum of parameter "widths" */
  return motor_io_velocity_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
