/*
 * motor_io.c
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
#include "motor_io_trc_ptr.h"
#include "motor_io.h"
#include "motor_io_private.h"

/* Block signals (auto storage) */
B_motor_io_T motor_io_B;

/* Continuous states */
X_motor_io_T motor_io_X;

/* Block states (auto storage) */
DW_motor_io_T motor_io_DW;

/* Previous zero-crossings (trigger) states */
PrevZCX_motor_io_T motor_io_PrevZCX;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_motor_io_T motor_io_Y;

/* Real-time model */
RT_MODEL_motor_io_T motor_io_M_;
RT_MODEL_motor_io_T *const motor_io_M = &motor_io_M_;

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
  motor_io_derivatives();
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
void motor_io_output(void)
{
  real_T temp;
  ZCEventType zcEvent;
  real_T u1;
  real_T u2;
  if (rtmIsMajorTimeStep(motor_io_M)) {
    /* set solver stop time */
    if (!(motor_io_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&motor_io_M->solverInfo,
                            ((motor_io_M->Timing.clockTickH0 + 1) *
        motor_io_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&motor_io_M->solverInfo,
                            ((motor_io_M->Timing.clockTick0 + 1) *
        motor_io_M->Timing.stepSize0 + motor_io_M->Timing.clockTickH0 *
        motor_io_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(motor_io_M)) {
    motor_io_M->Timing.t[0] = rtsiGetT(&motor_io_M->solverInfo);
  }

  /* Integrator: '<S1>/Integrator' */
  motor_io_B.Integrator = motor_io_X.Integrator_CSTATE;

  /* Outport: '<Root>/Vel1' */
  motor_io_Y.Vel1 = motor_io_B.Integrator;

  /* Integrator: '<S1>/Integrator1' */
  motor_io_B.Integrator1 = motor_io_X.Integrator1_CSTATE;

  /* Outport: '<Root>/Pos1' */
  motor_io_Y.Pos1 = motor_io_B.Integrator1;

  /* SignalGenerator: '<Root>/SinGenerator' */
  motor_io_B.SinGenerator = sin(motor_io_P.SinGenerator_Frequency *
    motor_io_M->Timing.t[0]) * motor_io_P.SinGenerator_Amplitude;

  /* SignalGenerator: '<Root>/SquareGenerator' */
  temp = motor_io_P.SquareGenerator_Frequency * motor_io_M->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    motor_io_B.SquareGenerator = motor_io_P.SquareGenerator_Amplitude;
  } else {
    motor_io_B.SquareGenerator = -motor_io_P.SquareGenerator_Amplitude;
  }

  /* End of SignalGenerator: '<Root>/SquareGenerator' */

  /* Switch: '<Root>/Switch' incorporates:
   *  Constant: '<Root>/SignalSelector[0Square,1Sine]'
   */
  if (motor_io_P.SignalSelector0Square1Sine_Valu != 0.0) {
    motor_io_B.ref = motor_io_B.SinGenerator;
  } else {
    motor_io_B.ref = motor_io_B.SquareGenerator;
  }

  /* End of Switch: '<Root>/Switch' */
  if (rtmIsMajorTimeStep(motor_io_M)) {
    /* S-Function (rti_commonblock): '<S14>/S-Function1' */
    /* This comment workarounds a code generation problem */

    /* Gain: '<S6>/fi1_scaling' */
    motor_io_B.fi1_scaling = motor_io_P.fi1_scaling_Gain * motor_io_B.SFunction1;

    /* Quantizer: '<Root>/Quantizer1' */
    temp = motor_io_B.fi1_scaling;
    motor_io_B.Quantizer1 = rt_roundd_snf(temp / motor_io_P.Ts) * motor_io_P.Ts;
  }

  /* Sum: '<Root>/Sum2' */
  motor_io_B.Sum2 = motor_io_B.ref - motor_io_B.Quantizer1;
  if (rtmIsMajorTimeStep(motor_io_M)) {
    /* Gain: '<S3>/Proportional Gain' */
    motor_io_B.ProportionalGain = motor_io_P.ProportionalGain_Gain *
      motor_io_B.Sum2;

    /* DiscreteIntegrator: '<S3>/Integrator' */
    motor_io_B.Integrator_m = motor_io_DW.Integrator_DSTATE;

    /* Gain: '<S3>/Derivative Gain' */
    motor_io_B.DerivativeGain = motor_io_P.DerivativeGain_Gain * motor_io_B.Sum2;

    /* DiscreteIntegrator: '<S3>/Filter' */
    motor_io_B.Filter = motor_io_DW.Filter_DSTATE;

    /* Sum: '<S3>/SumD' */
    motor_io_B.SumD = motor_io_B.DerivativeGain - motor_io_B.Filter;

    /* Gain: '<S3>/Filter Coefficient' */
    motor_io_B.FilterCoefficient = motor_io_P.FilterCoefficient_Gain *
      motor_io_B.SumD;

    /* Sum: '<S3>/Sum' */
    motor_io_B.Sum = (motor_io_B.ProportionalGain + motor_io_B.Integrator_m) +
      motor_io_B.FilterCoefficient;

    /* ZeroOrderHold: '<Root>/Zero-Order Hold1' */
    motor_io_B.ZeroOrderHold1 = motor_io_B.Sum;

    /* Gain: '<Root>/Gain' */
    motor_io_B.Gain = motor_io_P.Gain_Gain * motor_io_B.ZeroOrderHold1;

    /* Saturate: '<S4>/Saturation' */
    temp = motor_io_B.Gain;
    u1 = motor_io_P.Saturation_LowerSat;
    u2 = motor_io_P.Saturation_UpperSat;
    if (temp > u2) {
      motor_io_B.Volt = u2;
    } else if (temp < u1) {
      motor_io_B.Volt = u1;
    } else {
      motor_io_B.Volt = temp;
    }

    /* End of Saturate: '<S4>/Saturation' */

    /* Gain: '<S4>/pwm_skalning' */
    motor_io_B.pwm_skalning = motor_io_P.pwm_skalning_Gain * motor_io_B.Volt;

    /* Sum: '<S4>/Sum' incorporates:
     *  Constant: '<S4>/pwm_offstet'
     */
    motor_io_B.Sum_f = motor_io_B.pwm_skalning + motor_io_P.pwm_offstet_Value;

    /* S-Function (rti_commonblock): '<S10>/S-Function1' */
    /* This comment workarounds a code generation problem */

    /* dSPACE I/O Board DS1104 #1 Unit:PWM Group:PWM */
    ds1104_slave_dsp_pwm_duty_write(0, rti_slv1104_fcn_index[6],
      motor_io_B.Sum_f);

    /* S-Function (rti_commonblock): '<S10>/S-Function2' */
    /* This comment workarounds a code generation problem */

    /* S-Function (rti_commonblock): '<S10>/S-Function3' */
    /* This comment workarounds a code generation problem */

    /* S-Function (rti_commonblock): '<S10>/S-Function4' */
    /* This comment workarounds a code generation problem */

    /* DataTypeConversion: '<S4>/Data Type Conversion' incorporates:
     *  Constant: '<S4>/Enable[1_Off, 0_On]'
     */
    motor_io_B.DataTypeConversion = (motor_io_P.Enable1_Off0_On_Value != 0.0);

    /* S-Function (rti_commonblock): '<S9>/S-Function1' */
    /* This comment workarounds a code generation problem */

    /* dSPACE I/O Board DS1104 #1 Unit:BIT_IO Group:BIT_OUT */
    if (motor_io_B.DataTypeConversion > 0) {
      ds1104_bit_io_set(DS1104_DIO0);
    } else {
      ds1104_bit_io_clear(DS1104_DIO0);
    }
  }

  /* Quantizer: '<Root>/Quantizer' */
  temp = motor_io_B.Integrator1;
  motor_io_B.Quantizer = rt_roundd_snf(temp / motor_io_P.Ts) * motor_io_P.Ts;

  /* Sum: '<Root>/Sum1' */
  motor_io_B.Sum1 = motor_io_B.ref - motor_io_B.Quantizer;
  if (rtmIsMajorTimeStep(motor_io_M)) {
    /* Gain: '<S2>/Proportional Gain' */
    motor_io_B.ProportionalGain_k = motor_io_P.ProportionalGain_Gain_l *
      motor_io_B.Sum1;

    /* DiscreteIntegrator: '<S2>/Integrator' */
    motor_io_B.Integrator_b = motor_io_DW.Integrator_DSTATE_g;

    /* Gain: '<S2>/Derivative Gain' */
    motor_io_B.DerivativeGain_o = motor_io_P.DerivativeGain_Gain_l *
      motor_io_B.Sum1;

    /* DiscreteIntegrator: '<S2>/Filter' */
    motor_io_B.Filter_e = motor_io_DW.Filter_DSTATE_a;

    /* Sum: '<S2>/SumD' */
    motor_io_B.SumD_g = motor_io_B.DerivativeGain_o - motor_io_B.Filter_e;

    /* Gain: '<S2>/Filter Coefficient' */
    motor_io_B.FilterCoefficient_g = motor_io_P.FilterCoefficient_Gain_p *
      motor_io_B.SumD_g;

    /* Sum: '<S2>/Sum' */
    motor_io_B.Sum_h = (motor_io_B.ProportionalGain_k + motor_io_B.Integrator_b)
      + motor_io_B.FilterCoefficient_g;

    /* ZeroOrderHold: '<Root>/Zero-Order Hold' */
    motor_io_B.ZeroOrderHold = motor_io_B.Sum_h;

    /* Saturate: '<S1>/Saturation' */
    temp = motor_io_B.ZeroOrderHold;
    u1 = motor_io_P.Saturation_LowerSat_b;
    u2 = motor_io_P.Saturation_UpperSat_f;
    if (temp > u2) {
      motor_io_B.Saturation = u2;
    } else if (temp < u1) {
      motor_io_B.Saturation = u1;
    } else {
      motor_io_B.Saturation = temp;
    }

    /* End of Saturate: '<S1>/Saturation' */
  }

  /* Gain: '<S1>/Gain1' */
  motor_io_B.Gain1 = motor_io_P.Gain1_Gain * motor_io_B.Integrator;

  /* Sum: '<S1>/Add' */
  motor_io_B.Add = motor_io_B.Saturation - motor_io_B.Gain1;

  /* Gain: '<S1>/k//R ' */
  motor_io_B.kR = motor_io_P.kR_Gain * motor_io_B.Add;

  /* Switch: '<S7>/Switch1' incorporates:
   *  Constant: '<S7>/Constant'
   *  Constant: '<S7>/Constant1'
   */
  if (motor_io_B.Integrator > motor_io_P.Switch1_Threshold) {
    motor_io_B.Switch1 = motor_io_P.F_c;
  } else {
    motor_io_B.Switch1 = motor_io_P.Constant1_Value;
  }

  /* End of Switch: '<S7>/Switch1' */

  /* Saturate: '<S7>/Saturate to Fc' */
  temp = motor_io_B.Switch1;
  u1 = motor_io_P.SaturatetoFc_LowerSat;
  u2 = motor_io_P.F_c;
  if (temp > u2) {
    motor_io_B.Stickslipregion = u2;
  } else if (temp < u1) {
    motor_io_B.Stickslipregion = u1;
  } else {
    motor_io_B.Stickslipregion = temp;
  }

  /* End of Saturate: '<S7>/Saturate to Fc' */

  /* Abs: '<S7>/Abs' */
  motor_io_B.Abs = fabs(motor_io_B.Integrator);

  /* RelationalOperator: '<S8>/Compare' incorporates:
   *  Constant: '<S8>/Constant'
   */
  motor_io_B.Compare = (motor_io_B.Abs <= motor_io_P.Constant_Value);

  /* Gain: '<S7>/Vicous friction' */
  motor_io_B.Vicousfriction = motor_io_P.Vicousfriction_Gain *
    motor_io_B.Integrator;

  /* Signum: '<S7>/Sign' */
  temp = motor_io_B.Integrator;
  if (temp < 0.0) {
    motor_io_B.Sign = -1.0;
  } else if (temp > 0.0) {
    motor_io_B.Sign = 1.0;
  } else if (temp == 0.0) {
    motor_io_B.Sign = 0.0;
  } else {
    motor_io_B.Sign = temp;
  }

  /* End of Signum: '<S7>/Sign' */

  /* Product: '<S7>/Product' incorporates:
   *  Constant: '<S7>/Couloumb friction'
   */
  motor_io_B.Product = motor_io_P.F_c * motor_io_B.Sign;

  /* Sum: '<S7>/Add' */
  motor_io_B.Viscousregion = motor_io_B.Vicousfriction + motor_io_B.Product;

  /* Switch: '<S7>/Switch' */
  if (motor_io_B.Compare) {
    motor_io_B.Friction = motor_io_B.Stickslipregion;
  } else {
    motor_io_B.Friction = motor_io_B.Viscousregion;
  }

  /* End of Switch: '<S7>/Switch' */

  /* Sum: '<S1>/Add1' */
  motor_io_B.Add1 = motor_io_B.kR - motor_io_B.Friction;

  /* Gain: '<S1>/1//J' */
  motor_io_B.J = motor_io_P.J_Gain * motor_io_B.Add1;
  if (rtmIsMajorTimeStep(motor_io_M)) {
    /* Gain: '<S2>/Integral Gain' */
    motor_io_B.IntegralGain = motor_io_P.IntegralGain_Gain * motor_io_B.Sum1;

    /* Gain: '<S3>/Integral Gain' */
    motor_io_B.IntegralGain_j = motor_io_P.IntegralGain_Gain_e * motor_io_B.Sum2;

    /* S-Function (rti_commonblock): '<S14>/S-Function2' */
    /* This comment workarounds a code generation problem */

    /* Gain: '<S6>/w1_scaling' */
    motor_io_B.w1_scaling = motor_io_P.w1_scaling_Gain * motor_io_B.SFunction2;

    /* Outputs for Triggered SubSystem: '<S6>/DS1104ENC_SET_POS_C1' incorporates:
     *  TriggerPort: '<S16>/Trigger'
     */
    if (rtmIsMajorTimeStep(motor_io_M)) {
      /* Constant: '<S6>/Reset enc' */
      zcEvent = rt_ZCFcn(RISING_ZERO_CROSSING,
                         &motor_io_PrevZCX.DS1104ENC_SET_POS_C1_Trig_ZCE,
                         (motor_io_P.Resetenc_Value));
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
void motor_io_update(void)
{
  if (rtmIsMajorTimeStep(motor_io_M)) {
    /* Update for DiscreteIntegrator: '<S3>/Integrator' */
    motor_io_DW.Integrator_DSTATE += motor_io_P.Integrator_gainval *
      motor_io_B.IntegralGain_j;

    /* Update for DiscreteIntegrator: '<S3>/Filter' */
    motor_io_DW.Filter_DSTATE += motor_io_P.Filter_gainval *
      motor_io_B.FilterCoefficient;

    /* Update for DiscreteIntegrator: '<S2>/Integrator' */
    motor_io_DW.Integrator_DSTATE_g += motor_io_P.Integrator_gainval_a *
      motor_io_B.IntegralGain;

    /* Update for DiscreteIntegrator: '<S2>/Filter' */
    motor_io_DW.Filter_DSTATE_a += motor_io_P.Filter_gainval_l *
      motor_io_B.FilterCoefficient_g;
  }

  if (rtmIsMajorTimeStep(motor_io_M)) {
    rt_ertODEUpdateContinuousStates(&motor_io_M->solverInfo);
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
  if (!(++motor_io_M->Timing.clockTick0)) {
    ++motor_io_M->Timing.clockTickH0;
  }

  motor_io_M->Timing.t[0] = rtsiGetSolverStopTime(&motor_io_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.002s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++motor_io_M->Timing.clockTick1)) {
      ++motor_io_M->Timing.clockTickH1;
    }

    motor_io_M->Timing.t[1] = motor_io_M->Timing.clockTick1 *
      motor_io_M->Timing.stepSize1 + motor_io_M->Timing.clockTickH1 *
      motor_io_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void motor_io_derivatives(void)
{
  XDot_motor_io_T *_rtXdot;
  _rtXdot = ((XDot_motor_io_T *) motor_io_M->ModelData.derivs);

  /* Derivatives for Integrator: '<S1>/Integrator' */
  _rtXdot->Integrator_CSTATE = motor_io_B.J;

  /* Derivatives for Integrator: '<S1>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = motor_io_B.Integrator;
}

/* Model initialize function */
void motor_io_initialize(void)
{
  /* Start for S-Function (rti_commonblock): '<S10>/S-Function1' */

  /* dSPACE I/O Board DS1104 #1 Unit:PWM Group:PWM */
  motor_io_DW.SFunction1_IWORK[0] = 0;
  motor_io_PrevZCX.DS1104ENC_SET_POS_C1_Trig_ZCE = UNINITIALIZED_ZCSIG;

  /* InitializeConditions for Integrator: '<S1>/Integrator' */
  motor_io_X.Integrator_CSTATE = motor_io_P.Integrator_IC;

  /* InitializeConditions for Integrator: '<S1>/Integrator1' */
  motor_io_X.Integrator1_CSTATE = motor_io_P.Integrator1_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S3>/Integrator' */
  motor_io_DW.Integrator_DSTATE = motor_io_P.Integrator_IC_h;

  /* InitializeConditions for DiscreteIntegrator: '<S3>/Filter' */
  motor_io_DW.Filter_DSTATE = motor_io_P.Filter_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Integrator' */
  motor_io_DW.Integrator_DSTATE_g = motor_io_P.Integrator_IC_l;

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Filter' */
  motor_io_DW.Filter_DSTATE_a = motor_io_P.Filter_IC_j;
}

/* Model terminate function */
void motor_io_terminate(void)
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
  motor_io_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  motor_io_update();
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
  motor_io_initialize();
}

void MdlTerminate(void)
{
  motor_io_terminate();
}

/* Registration function */
RT_MODEL_motor_io_T *motor_io(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)motor_io_M, 0,
                sizeof(RT_MODEL_motor_io_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&motor_io_M->solverInfo,
                          &motor_io_M->Timing.simTimeStep);
    rtsiSetTPtr(&motor_io_M->solverInfo, &rtmGetTPtr(motor_io_M));
    rtsiSetStepSizePtr(&motor_io_M->solverInfo, &motor_io_M->Timing.stepSize0);
    rtsiSetdXPtr(&motor_io_M->solverInfo, &motor_io_M->ModelData.derivs);
    rtsiSetContStatesPtr(&motor_io_M->solverInfo, (real_T **)
                         &motor_io_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&motor_io_M->solverInfo,
      &motor_io_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&motor_io_M->solverInfo, (&rtmGetErrorStatus
      (motor_io_M)));
    rtsiSetRTModelPtr(&motor_io_M->solverInfo, motor_io_M);
  }

  rtsiSetSimTimeStep(&motor_io_M->solverInfo, MAJOR_TIME_STEP);
  motor_io_M->ModelData.intgData.f[0] = motor_io_M->ModelData.odeF[0];
  motor_io_M->ModelData.contStates = ((real_T *) &motor_io_X);
  rtsiSetSolverData(&motor_io_M->solverInfo, (void *)
                    &motor_io_M->ModelData.intgData);
  rtsiSetSolverName(&motor_io_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = motor_io_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    motor_io_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    motor_io_M->Timing.sampleTimes = (&motor_io_M->Timing.sampleTimesArray[0]);
    motor_io_M->Timing.offsetTimes = (&motor_io_M->Timing.offsetTimesArray[0]);

    /* task periods */
    motor_io_M->Timing.sampleTimes[0] = (0.0);
    motor_io_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    motor_io_M->Timing.offsetTimes[0] = (0.0);
    motor_io_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(motor_io_M, &motor_io_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = motor_io_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    motor_io_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(motor_io_M, -1);
  motor_io_M->Timing.stepSize0 = 0.002;
  motor_io_M->Timing.stepSize1 = 0.002;
  motor_io_M->solverInfoPtr = (&motor_io_M->solverInfo);
  motor_io_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&motor_io_M->solverInfo, 0.002);
  rtsiSetSolverMode(&motor_io_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  motor_io_M->ModelData.blockIO = ((void *) &motor_io_B);
  (void) memset(((void *) &motor_io_B), 0,
                sizeof(B_motor_io_T));

  {
    motor_io_B.Integrator = 0.0;
    motor_io_B.Integrator1 = 0.0;
    motor_io_B.SinGenerator = 0.0;
    motor_io_B.SquareGenerator = 0.0;
    motor_io_B.ref = 0.0;
    motor_io_B.SFunction1 = 0.0;
    motor_io_B.fi1_scaling = 0.0;
    motor_io_B.Quantizer1 = 0.0;
    motor_io_B.Sum2 = 0.0;
    motor_io_B.ProportionalGain = 0.0;
    motor_io_B.Integrator_m = 0.0;
    motor_io_B.DerivativeGain = 0.0;
    motor_io_B.Filter = 0.0;
    motor_io_B.SumD = 0.0;
    motor_io_B.FilterCoefficient = 0.0;
    motor_io_B.Sum = 0.0;
    motor_io_B.ZeroOrderHold1 = 0.0;
    motor_io_B.Gain = 0.0;
    motor_io_B.Volt = 0.0;
    motor_io_B.pwm_skalning = 0.0;
    motor_io_B.Sum_f = 0.0;
    motor_io_B.Quantizer = 0.0;
    motor_io_B.Sum1 = 0.0;
    motor_io_B.ProportionalGain_k = 0.0;
    motor_io_B.Integrator_b = 0.0;
    motor_io_B.DerivativeGain_o = 0.0;
    motor_io_B.Filter_e = 0.0;
    motor_io_B.SumD_g = 0.0;
    motor_io_B.FilterCoefficient_g = 0.0;
    motor_io_B.Sum_h = 0.0;
    motor_io_B.ZeroOrderHold = 0.0;
    motor_io_B.Saturation = 0.0;
    motor_io_B.Gain1 = 0.0;
    motor_io_B.Add = 0.0;
    motor_io_B.kR = 0.0;
    motor_io_B.Switch1 = 0.0;
    motor_io_B.Stickslipregion = 0.0;
    motor_io_B.Abs = 0.0;
    motor_io_B.Vicousfriction = 0.0;
    motor_io_B.Sign = 0.0;
    motor_io_B.Product = 0.0;
    motor_io_B.Viscousregion = 0.0;
    motor_io_B.Friction = 0.0;
    motor_io_B.Add1 = 0.0;
    motor_io_B.J = 0.0;
    motor_io_B.IntegralGain = 0.0;
    motor_io_B.IntegralGain_j = 0.0;
    motor_io_B.SFunction2 = 0.0;
    motor_io_B.w1_scaling = 0.0;
  }

  /* parameters */
  motor_io_M->ModelData.defaultParam = ((real_T *)&motor_io_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &motor_io_X;
    motor_io_M->ModelData.contStates = (x);
    (void) memset((void *)&motor_io_X, 0,
                  sizeof(X_motor_io_T));
  }

  /* states (dwork) */
  motor_io_M->ModelData.dwork = ((void *) &motor_io_DW);
  (void) memset((void *)&motor_io_DW, 0,
                sizeof(DW_motor_io_T));
  motor_io_DW.Integrator_DSTATE = 0.0;
  motor_io_DW.Filter_DSTATE = 0.0;
  motor_io_DW.Integrator_DSTATE_g = 0.0;
  motor_io_DW.Filter_DSTATE_a = 0.0;

  /* external outputs */
  motor_io_M->ModelData.outputs = (&motor_io_Y);
  motor_io_Y.Vel1 = 0.0;
  motor_io_Y.Pos1 = 0.0;

  {
    /* user code (registration function declaration) */
    /*Call the macro that initializes the global TRC pointers
       inside the model initialization/registration function. */
    RTI_INIT_TRC_POINTERS();
  }

  /* Initialize Sizes */
  motor_io_M->Sizes.numContStates = (2);/* Number of continuous states */
  motor_io_M->Sizes.numY = (2);        /* Number of model outputs */
  motor_io_M->Sizes.numU = (0);        /* Number of model inputs */
  motor_io_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  motor_io_M->Sizes.numSampTimes = (2);/* Number of sample times */
  motor_io_M->Sizes.numBlocks = (72);  /* Number of blocks */
  motor_io_M->Sizes.numBlockIO = (51); /* Number of block outputs */
  motor_io_M->Sizes.numBlockPrms = (44);/* Sum of parameter "widths" */
  return motor_io_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
