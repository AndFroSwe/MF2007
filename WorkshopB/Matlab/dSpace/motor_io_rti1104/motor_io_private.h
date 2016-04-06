/*
 * motor_io_private.h
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
#ifndef RTW_HEADER_motor_io_private_h_
#define RTW_HEADER_motor_io_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"

extern void Traject_and_Model_function_Init(DW_Traject_and_Model_function_T
  *localDW);
extern void mot_Traject_and_Model_function1(real_T rtu_reset, real_T rtu_rs_in,
  real_T rtu_feedback, B_Traject_and_Model_function1_T *localB,
  DW_Traject_and_Model_function_T *localDW);

/* private model entry point functions */
extern void motor_io_derivatives(void);

#endif                                 /* RTW_HEADER_motor_io_private_h_ */
