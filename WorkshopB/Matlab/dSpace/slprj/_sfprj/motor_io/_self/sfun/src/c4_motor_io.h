#ifndef __c4_motor_io_h__
#define __c4_motor_io_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc4_motor_ioInstanceStruct
#define typedef_SFc4_motor_ioInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c4_sfEvent;
  boolean_T c4_isStable;
  boolean_T c4_doneDoubleBufferReInit;
  uint8_T c4_is_active_c4_motor_io;
  real_T c4_time;
  boolean_T c4_time_not_empty;
  real_T c4_oldAcc;
  boolean_T c4_oldAcc_not_empty;
  real_T c4_oldVel;
  boolean_T c4_oldVel_not_empty;
  real_T c4_oldPos;
  boolean_T c4_oldPos_not_empty;
  real_T c4_oldErr;
  boolean_T c4_oldErr_not_empty;
  real_T c4_olderErr;
  boolean_T c4_olderErr_not_empty;
  real_T c4_oldPIDVolt;
  boolean_T c4_oldPIDVolt_not_empty;
  real_T c4_olderPIDVolt;
  boolean_T c4_olderPIDVolt_not_empty;
  real_T *c4_reset;
  real_T *c4_rs_in;
  real_T *c4_acceleration;
  real_T *c4_velocity;
  real_T *c4_position;
  real_T *c4_voltFollowing;
  real_T *c4_volt;
  real_T *c4_feedback;
  real_T *c4_err;
} SFc4_motor_ioInstanceStruct;

#endif                                 /*typedef_SFc4_motor_ioInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c4_motor_io_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c4_motor_io_get_check_sum(mxArray *plhs[]);
extern void c4_motor_io_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
