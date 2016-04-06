#ifndef __c3_trajectory_planner_h__
#define __c3_trajectory_planner_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc3_trajectory_plannerInstanceStruct
#define typedef_SFc3_trajectory_plannerInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c3_sfEvent;
  boolean_T c3_isStable;
  boolean_T c3_doneDoubleBufferReInit;
  uint8_T c3_is_active_c3_trajectory_planner;
  real_T c3_time;
  boolean_T c3_time_not_empty;
  real_T c3_oldAcc;
  boolean_T c3_oldAcc_not_empty;
  real_T c3_oldVel;
  boolean_T c3_oldVel_not_empty;
  real_T c3_oldPos;
  boolean_T c3_oldPos_not_empty;
  real_T c3_rs;
  boolean_T c3_rs_not_empty;
  real_T c3_oldErr;
  boolean_T c3_oldErr_not_empty;
  real_T c3_olderErr;
  boolean_T c3_olderErr_not_empty;
  real_T c3_oldPIDVolt;
  boolean_T c3_oldPIDVolt_not_empty;
  real_T c3_olderPIDVolt;
  boolean_T c3_olderPIDVolt_not_empty;
  real_T *c3_reset;
  real_T *c3_rs_in;
  real_T *c3_acceleration;
  real_T *c3_velocity;
  real_T *c3_position;
  real_T *c3_voltFollowing;
  real_T *c3_volt;
  real_T *c3_feedback;
  real_T *c3_err;
} SFc3_trajectory_plannerInstanceStruct;

#endif                                 /*typedef_SFc3_trajectory_plannerInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c3_trajectory_planner_get_eml_resolved_functions_info
  (void);

/* Function Definitions */
extern void sf_c3_trajectory_planner_get_check_sum(mxArray *plhs[]);
extern void c3_trajectory_planner_method_dispatcher(SimStruct *S, int_T method,
  void *data);

#endif
