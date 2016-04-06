/*
 * motor_io.c
 *
 * Code generation for model "motor_io".
 *
 * Model version              : 1.37
 * Simulink Coder version : 8.7 (R2014b) 08-Sep-2014
 * C source code generated on : Wed Apr 06 17:44:57 2016
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

/*
 * Initial conditions for atomic system:
 *    '<Root>/Traject_and_Model_function 1'
 *    '<Root>/Traject_and_Model_function 3'
 */
void Traject_and_Model_function_Init(DW_Traject_and_Model_function_T *localDW)
{
  localDW->time = 0.0;
  localDW->oldVel = 0.0;
  localDW->oldPos = 0.0;
  localDW->rs = 0.0;
  localDW->oldErr = 0.0;
  localDW->olderErr = 0.0;
  localDW->oldPIDVolt = 0.0;
  localDW->olderPIDVolt = 0.0;
}

/*
 * Output and update for atomic system:
 *    '<Root>/Traject_and_Model_function 1'
 *    '<Root>/Traject_and_Model_function 3'
 */
void mot_Traject_and_Model_function1(real_T rtu_reset, real_T rtu_rs_in, real_T
  rtu_feedback, B_Traject_and_Model_function1_T *localB,
  DW_Traject_and_Model_function_T *localDW)
{
  real_T velocity;
  real_T position;
  real_T voltFollowing;
  real_T err;
  real_T t1;
  int32_T out2;
  int32_T out3;
  int32_T out4;

  /* MATLAB Function 'Traject_and_Model_function 1': '<S4>:1' */
  /*  PERSISTENT VARIABLES */
  /* Update "time" */
  if (rtu_reset == 1.0) {
    /* '<S4>:1:29' */
    /* '<S4>:1:33' */
    localDW->time = 0.0;
  }

  if (rtu_rs_in != localDW->rs) {
    /* '<S4>:1:35' */
    /* '<S4>:1:39' */
    localDW->oldPos = 0.0;

    /* '<S4>:1:40' */
    localDW->oldVel = 0.0;

    /* '<S4>:1:41' */
    /* '<S4>:1:42' */
    localDW->time = 0.0;
  }

  /* '<S4>:1:44' */
  localDW->rs = rtu_rs_in;

  /*  Trajectory Planner Variables */
  /* '<S4>:1:47' */
  /*  252; */
  /* '<S4>:1:49' */
  /* 369; */
  /* '<S4>:1:50' */
  /* '<S4>:1:51' */
  t1 = sqrt(localDW->rs / 255.0);

  /* '<S4>:1:53' */
  /* '<S4>:1:54' */
  /* Initial Value block */
  /* '<S4>:1:57' */
  /* %SIGNAL GENERATOR */
  /* Reset to 0 at t1 block */
  /* '<S4>:1:60' */
  out2 = 0;
  if (localDW->time >= t1) {
    /* '<S4>:1:61' */
    /* '<S4>:1:62' */
    out2 = -255;
  }

  /* retardation at t2 block */
  /* '<S4>:1:66' */
  out3 = 0;
  if (localDW->time >= t1) {
    /* '<S4>:1:67' */
    /* '<S4>:1:68' */
    out3 = -255;
  }

  /*  Reset at t3 block */
  /* '<S4>:1:72' */
  out4 = 255;
  if (localDW->time >= t1 + t1) {
    /* '<S4>:1:73' */
    /* '<S4>:1:74' */
    out4 = 510;
  }

  /* '<S4>:1:77' */
  out2 = (out2 + out3) + out4;

  /* '<S4>:1:78' */
  /* % INTEGRATOR PARTS */
  /* For velocity */
  /* '<S4>:1:81' */
  velocity = (real_T)(out2 + out2) * 0.01 / 2.0 + localDW->oldVel;

  /* '<S4>:1:82' */
  localDW->oldVel = velocity;

  /* For position */
  /* '<S4>:1:85' */
  position = (velocity + localDW->oldVel) * 0.01 / 2.0 + localDW->oldPos;

  /* '<S4>:1:87' */
  localDW->oldPos = position;

  /* % MODEL FOLLOWING PART */
  /*  Model Following variables */
  /* % Input Acceleration Part */
  /* '<S4>:1:100' */
  /* % Input Velocity Part */
  /* '<S4>:1:104' */
  /* '<S4>:1:105' */
  /* %Output */
  /* '<S4>:1:109' */
  voltFollowing = ((real_T)out2 * 2.4745999999999997E-5 + velocity * 1.0E-5) *
    112.0 / 0.0697 + velocity * 0.0697;

  /* % PID CONTROLLER */
  /*  PERSISTENT VARIABLES */
  /*  PID parameters */
  /*  Error */
  /* '<S4>:1:138' */
  err = position - rtu_feedback;

  /* %PID */
  /* '<S4>:1:141' */
  t1 = (((1348.0 * err + -1899.0 * localDW->oldErr) + 692.0 * localDW->olderErr)
        + 0.89 * localDW->olderPIDVolt) - -0.10999999999999999 *
    localDW->oldPIDVolt;

  /* '<S4>:1:142' */
  localDW->olderPIDVolt = localDW->oldPIDVolt;

  /* '<S4>:1:143' */
  localDW->oldPIDVolt = t1;

  /* '<S4>:1:144' */
  localDW->olderErr = localDW->oldErr;

  /* '<S4>:1:145' */
  localDW->oldErr = err;

  /* % OUTPUT */
  /* '<S4>:1:148' */
  t1 += voltFollowing;
  if (t1 >= 24.0) {
    /* '<S4>:1:150' */
    /* '<S4>:1:151' */
    t1 = 24.0;
  } else {
    if (t1 <= -24.0) {
      /* '<S4>:1:152' */
      /* '<S4>:1:153' */
      t1 = -24.0;
    }
  }

  /* '<S4>:1:157' */
  localDW->time += 0.01;
  localB->acceleration = out2;
  localB->velocity = velocity;
  localB->position = position;
  localB->voltFollowing = voltFollowing;
  localB->volt = t1;
  localB->err = err;
}

/* Model output function */
void motor_io_output(void)
{
  ZCEventType zcEvent;
  real_T u0;
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

  if (rtmIsMajorTimeStep(motor_io_M)) {
    /* S-Function (rti_commonblock): '<S14>/S-Function1' */
    /* This comment workarounds a code generation problem */

    /* Gain: '<S6>/fi1_scaling' */
    motor_io_B.fi1_scaling = motor_io_P.fi1_scaling_Gain * motor_io_B.SFunction1;

    /* MATLAB Function: '<Root>/Traject_and_Model_function 1' incorporates:
     *  Constant: '<Root>/RS'
     *  Constant: '<Root>/Reset enc'
     */
    mot_Traject_and_Model_function1(motor_io_P.Resetenc_Value,
      motor_io_P.RS_Value, motor_io_B.fi1_scaling,
      &motor_io_B.sf_Traject_and_Model_function1,
      &motor_io_DW.sf_Traject_and_Model_function1);

    /* Gain: '<Root>/Gain' */
    motor_io_B.Gain = motor_io_P.Gain_Gain *
      motor_io_B.sf_Traject_and_Model_function1.volt;

    /* Saturate: '<S2>/Saturation' */
    u0 = motor_io_B.Gain;
    u1 = motor_io_P.Saturation_LowerSat;
    u2 = motor_io_P.Saturation_UpperSat;
    if (u0 > u2) {
      motor_io_B.Volt = u2;
    } else if (u0 < u1) {
      motor_io_B.Volt = u1;
    } else {
      motor_io_B.Volt = u0;
    }

    /* End of Saturate: '<S2>/Saturation' */

    /* Gain: '<S2>/pwm_skalning' */
    motor_io_B.pwm_skalning = motor_io_P.pwm_skalning_Gain * motor_io_B.Volt;

    /* Sum: '<S2>/Sum' incorporates:
     *  Constant: '<S2>/pwm_offstet'
     */
    motor_io_B.Sum = motor_io_B.pwm_skalning + motor_io_P.pwm_offstet_Value;

    /* S-Function (rti_commonblock): '<S10>/S-Function1' */
    /* This comment workarounds a code generation problem */

    /* dSPACE I/O Board DS1104 #1 Unit:PWM Group:PWM */
    ds1104_slave_dsp_pwm_duty_write(0, rti_slv1104_fcn_index[6], motor_io_B.Sum);

    /* S-Function (rti_commonblock): '<S10>/S-Function2' */
    /* This comment workarounds a code generation problem */

    /* S-Function (rti_commonblock): '<S10>/S-Function3' */
    /* This comment workarounds a code generation problem */

    /* S-Function (rti_commonblock): '<S10>/S-Function4' */
    /* This comment workarounds a code generation problem */

    /* DataTypeConversion: '<S2>/Data Type Conversion' incorporates:
     *  Constant: '<S2>/Enable[1_Off, 0_On]'
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

  /* Integrator: '<S1>/Integrator1' */
  motor_io_B.Integrator1 = motor_io_X.Integrator1_CSTATE;
  if (rtmIsMajorTimeStep(motor_io_M)) {
    /* MATLAB Function: '<Root>/Traject_and_Model_function 3' incorporates:
     *  Constant: '<Root>/RS'
     *  Constant: '<Root>/Reset enc'
     */
    mot_Traject_and_Model_function1(motor_io_P.Resetenc_Value,
      motor_io_P.RS_Value, motor_io_B.Integrator1,
      &motor_io_B.sf_Traject_and_Model_function3,
      &motor_io_DW.sf_Traject_and_Model_function3);
  }

  /* Integrator: '<S1>/Integrator' */
  motor_io_B.Integrator = motor_io_X.Integrator_CSTATE;

  /* Gain: '<S1>/Gain1' */
  motor_io_B.Gain1 = motor_io_P.Gain1_Gain * motor_io_B.Integrator;

  /* Sum: '<S1>/Add' */
  motor_io_B.Add = motor_io_B.sf_Traject_and_Model_function3.volt -
    motor_io_B.Gain1;

  /* Gain: '<S1>/k//R ' */
  motor_io_B.kR = motor_io_P.kR_Gain * motor_io_B.Add;

  /* Saturate: '<S7>/Saturate to Fc' */
  u0 = motor_io_B.kR;
  u1 = motor_io_P.SaturatetoFc_LowerSat;
  u2 = motor_io_P.F_c_upper;
  if (u0 > u2) {
    motor_io_B.Stickslipregion = u2;
  } else if (u0 < u1) {
    motor_io_B.Stickslipregion = u1;
  } else {
    motor_io_B.Stickslipregion = u0;
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
  u0 = motor_io_B.Integrator;
  if (u0 < 0.0) {
    motor_io_B.Sign = -1.0;
  } else if (u0 > 0.0) {
    motor_io_B.Sign = 1.0;
  } else if (u0 == 0.0) {
    motor_io_B.Sign = 0.0;
  } else {
    motor_io_B.Sign = u0;
  }

  /* End of Signum: '<S7>/Sign' */

  /* Product: '<S7>/Product' incorporates:
   *  Constant: '<S7>/F_c'
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
  if (rtmIsMajorTimeStep(motor_io_M)) {
    /* Gain: '<S1>/Gain2' incorporates:
     *  Constant: '<S1>/Load inertia'
     */
    motor_io_B.Gain2 = motor_io_P.Gain2_Gain * motor_io_P.J1;

    /* Sum: '<S1>/Add2' incorporates:
     *  Constant: '<S1>/Motor inertia'
     */
    motor_io_B.Add2 = motor_io_B.Gain2 + motor_io_P.Motorinertia_Value;
  }

  /* Product: '<S1>/Inertias 1//J' */
  motor_io_B.Inertias1J = 1.0 / motor_io_B.Add2 * motor_io_B.Add1;
  if (rtmIsMajorTimeStep(motor_io_M)) {
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
                         (motor_io_P.Resetenc_Value_k));
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

  /* SignalGenerator: '<Root>/SinGenerator' */
  motor_io_B.SinGenerator = sin(motor_io_P.SinGenerator_Frequency *
    motor_io_M->Timing.t[0]) * motor_io_P.SinGenerator_Amplitude;

  /* SignalGenerator: '<Root>/SquareGenerator' */
  u0 = motor_io_P.SquareGenerator_Frequency * motor_io_M->Timing.t[0];
  if (u0 - floor(u0) >= 0.5) {
    motor_io_B.SquareGenerator = motor_io_P.SquareGenerator_Amplitude;
  } else {
    motor_io_B.SquareGenerator = -motor_io_P.SquareGenerator_Amplitude;
  }

  /* End of SignalGenerator: '<Root>/SquareGenerator' */

  /* Switch: '<Root>/Switch' incorporates:
   *  Constant: '<Root>/SignalSelector[0Square,1Sine]'
   */
  if (motor_io_P.SignalSelector0Square1Sine_Valu != 0.0) {
    motor_io_B.Switch = motor_io_B.SinGenerator;
  } else {
    motor_io_B.Switch = motor_io_B.SquareGenerator;
  }

  /* End of Switch: '<Root>/Switch' */
}

/* Model update function */
void motor_io_update(void)
{
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
    /* Update absolute timer for sample time: [0.01s, 0.0s] */
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

  /* Derivatives for Integrator: '<S1>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = motor_io_B.Integrator;

  /* Derivatives for Integrator: '<S1>/Integrator' */
  _rtXdot->Integrator_CSTATE = motor_io_B.Inertias1J;
}

/* Model initialize function */
void motor_io_initialize(void)
{
  /* Start for S-Function (rti_commonblock): '<S10>/S-Function1' */

  /* dSPACE I/O Board DS1104 #1 Unit:PWM Group:PWM */
  motor_io_DW.SFunction1_IWORK[0] = 0;
  motor_io_PrevZCX.DS1104ENC_SET_POS_C1_Trig_ZCE = UNINITIALIZED_ZCSIG;

  /* InitializeConditions for MATLAB Function: '<Root>/Traject_and_Model_function 1' */
  Traject_and_Model_function_Init(&motor_io_DW.sf_Traject_and_Model_function1);

  /* InitializeConditions for Integrator: '<S1>/Integrator1' */
  motor_io_X.Integrator1_CSTATE = motor_io_P.Integrator1_IC;

  /* InitializeConditions for MATLAB Function: '<Root>/Traject_and_Model_function 3' */
  Traject_and_Model_function_Init(&motor_io_DW.sf_Traject_and_Model_function3);

  /* InitializeConditions for Integrator: '<S1>/Integrator' */
  motor_io_X.Integrator_CSTATE = motor_io_P.Integrator_IC;
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
    motor_io_M->Timing.sampleTimes[1] = (0.01);

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
  motor_io_M->Timing.stepSize0 = 0.01;
  motor_io_M->Timing.stepSize1 = 0.01;
  motor_io_M->solverInfoPtr = (&motor_io_M->solverInfo);
  motor_io_M->Timing.stepSize = (0.01);
  rtsiSetFixedStepSize(&motor_io_M->solverInfo, 0.01);
  rtsiSetSolverMode(&motor_io_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  motor_io_M->ModelData.blockIO = ((void *) &motor_io_B);
  (void) memset(((void *) &motor_io_B), 0,
                sizeof(B_motor_io_T));

  {
    motor_io_B.SFunction1 = 0.0;
    motor_io_B.fi1_scaling = 0.0;
    motor_io_B.Gain = 0.0;
    motor_io_B.Volt = 0.0;
    motor_io_B.pwm_skalning = 0.0;
    motor_io_B.Sum = 0.0;
    motor_io_B.Integrator1 = 0.0;
    motor_io_B.Integrator = 0.0;
    motor_io_B.Gain1 = 0.0;
    motor_io_B.Add = 0.0;
    motor_io_B.kR = 0.0;
    motor_io_B.Stickslipregion = 0.0;
    motor_io_B.Abs = 0.0;
    motor_io_B.Vicousfriction = 0.0;
    motor_io_B.Sign = 0.0;
    motor_io_B.Product = 0.0;
    motor_io_B.Viscousregion = 0.0;
    motor_io_B.Friction = 0.0;
    motor_io_B.Add1 = 0.0;
    motor_io_B.Gain2 = 0.0;
    motor_io_B.Add2 = 0.0;
    motor_io_B.Inertias1J = 0.0;
    motor_io_B.SFunction2 = 0.0;
    motor_io_B.w1_scaling = 0.0;
    motor_io_B.SinGenerator = 0.0;
    motor_io_B.SquareGenerator = 0.0;
    motor_io_B.Switch = 0.0;
    motor_io_B.sf_Traject_and_Model_function3.acceleration = 0.0;
    motor_io_B.sf_Traject_and_Model_function3.velocity = 0.0;
    motor_io_B.sf_Traject_and_Model_function3.position = 0.0;
    motor_io_B.sf_Traject_and_Model_function3.voltFollowing = 0.0;
    motor_io_B.sf_Traject_and_Model_function3.volt = 0.0;
    motor_io_B.sf_Traject_and_Model_function3.err = 0.0;
    motor_io_B.sf_Traject_and_Model_function1.acceleration = 0.0;
    motor_io_B.sf_Traject_and_Model_function1.velocity = 0.0;
    motor_io_B.sf_Traject_and_Model_function1.position = 0.0;
    motor_io_B.sf_Traject_and_Model_function1.voltFollowing = 0.0;
    motor_io_B.sf_Traject_and_Model_function1.volt = 0.0;
    motor_io_B.sf_Traject_and_Model_function1.err = 0.0;
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
  motor_io_DW.sf_Traject_and_Model_function3.time = 0.0;
  motor_io_DW.sf_Traject_and_Model_function3.oldVel = 0.0;
  motor_io_DW.sf_Traject_and_Model_function3.oldPos = 0.0;
  motor_io_DW.sf_Traject_and_Model_function3.rs = 0.0;
  motor_io_DW.sf_Traject_and_Model_function3.oldErr = 0.0;
  motor_io_DW.sf_Traject_and_Model_function3.olderErr = 0.0;
  motor_io_DW.sf_Traject_and_Model_function3.oldPIDVolt = 0.0;
  motor_io_DW.sf_Traject_and_Model_function3.olderPIDVolt = 0.0;
  motor_io_DW.sf_Traject_and_Model_function1.time = 0.0;
  motor_io_DW.sf_Traject_and_Model_function1.oldVel = 0.0;
  motor_io_DW.sf_Traject_and_Model_function1.oldPos = 0.0;
  motor_io_DW.sf_Traject_and_Model_function1.rs = 0.0;
  motor_io_DW.sf_Traject_and_Model_function1.oldErr = 0.0;
  motor_io_DW.sf_Traject_and_Model_function1.olderErr = 0.0;
  motor_io_DW.sf_Traject_and_Model_function1.oldPIDVolt = 0.0;
  motor_io_DW.sf_Traject_and_Model_function1.olderPIDVolt = 0.0;

  {
    /* user code (registration function declaration) */
    /*Call the macro that initializes the global TRC pointers
       inside the model initialization/registration function. */
    RTI_INIT_TRC_POINTERS();
  }

  /* Initialize Sizes */
  motor_io_M->Sizes.numContStates = (2);/* Number of continuous states */
  motor_io_M->Sizes.numY = (0);        /* Number of model outputs */
  motor_io_M->Sizes.numU = (0);        /* Number of model inputs */
  motor_io_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  motor_io_M->Sizes.numSampTimes = (2);/* Number of sample times */
  motor_io_M->Sizes.numBlocks = (52);  /* Number of blocks */
  motor_io_M->Sizes.numBlockIO = (41); /* Number of block outputs */
  motor_io_M->Sizes.numBlockPrms = (28);/* Sum of parameter "widths" */
  return motor_io_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
