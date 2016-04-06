#ifndef __c1_motor_io_h__
#define __c1_motor_io_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc1_motor_ioInstanceStruct
#define typedef_SFc1_motor_ioInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c1_sfEvent;
  boolean_T c1_isStable;
  boolean_T c1_doneDoubleBufferReInit;
  uint8_T c1_is_active_c1_motor_io;
  real_T c1_time;
  boolean_T c1_time_not_empty;
  real_T c1_oldAcc;
  boolean_T c1_oldAcc_not_empty;
  real_T c1_oldVel;
  boolean_T c1_oldVel_not_empty;
  real_T c1_oldPos;
  boolean_T c1_oldPos_not_empty;
  real_T c1_rs;
  boolean_T c1_rs_not_empty;
  real_T c1_oldErr;
  boolean_T c1_oldErr_not_empty;
  real_T c1_olderErr;
  boolean_T c1_olderErr_not_empty;
  real_T c1_oldPIDVolt;
  boolean_T c1_oldPIDVolt_not_empty;
  real_T c1_olderPIDVolt;
  boolean_T c1_olderPIDVolt_not_empty;
  real_T *c1_reset;
  real_T *c1_rs_in;
  real_T *c1_acceleration;
  real_T *c1_velocity;
  real_T *c1_position;
  real_T *c1_voltFollowing;
  real_T *c1_volt;
  real_T *c1_feedback;
  real_T *c1_err;
} SFc1_motor_ioInstanceStruct;

#endif                                 /*typedef_SFc1_motor_ioInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c1_motor_io_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c1_motor_io_get_check_sum(mxArray *plhs[]);
extern void c1_motor_io_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
