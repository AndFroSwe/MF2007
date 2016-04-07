/*
 * motor_io_types.h
 *
 * Code generation for model "motor_io".
 *
 * Model version              : 1.28
 * Simulink Coder version : 8.7 (R2014b) 08-Sep-2014
 * C source code generated on : Wed Apr 06 14:40:23 2016
 *
 * Target selection: rti1104.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Custom
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#ifndef RTW_HEADER_motor_io_types_h_
#define RTW_HEADER_motor_io_types_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#ifndef _DEFINED_TYPEDEF_FOR_struct_XYVQccOAjWFHyjxZ8WEEeB_
#define _DEFINED_TYPEDEF_FOR_struct_XYVQccOAjWFHyjxZ8WEEeB_

typedef struct {
  real_T R;
  real_T L;
  real_T d;
  real_T k;
  real_T J;
} struct_XYVQccOAjWFHyjxZ8WEEeB;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_struct_isB4Cw3Ovpp8VfzP6RUqbD_
#define _DEFINED_TYPEDEF_FOR_struct_isB4Cw3Ovpp8VfzP6RUqbD_

typedef struct {
  int32_T OutputPortsWidth;
} struct_isB4Cw3Ovpp8VfzP6RUqbD;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_struct_dZjXwTiylTPloSUBFpnHJB_
#define _DEFINED_TYPEDEF_FOR_struct_dZjXwTiylTPloSUBFpnHJB_

typedef struct {
  int32_T InputPortsWidth;
} struct_dZjXwTiylTPloSUBFpnHJB;

#endif

/* Parameters (auto storage) */
typedef struct P_motor_io_T_ P_motor_io_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_motor_io_T RT_MODEL_motor_io_T;

#endif                                 /* RTW_HEADER_motor_io_types_h_ */
