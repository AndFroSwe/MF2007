#ifndef __c2_trajectory_planner_h__
#define __c2_trajectory_planner_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc2_trajectory_plannerInstanceStruct
#define typedef_SFc2_trajectory_plannerInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c2_sfEvent;
  boolean_T c2_isStable;
  boolean_T c2_doneDoubleBufferReInit;
  uint8_T c2_is_active_c2_trajectory_planner;
  real_T c2_time;
  boolean_T c2_time_not_empty;
  real_T c2_oldAcc;
  boolean_T c2_oldAcc_not_empty;
  real_T c2_oldVel;
  boolean_T c2_oldVel_not_empty;
  real_T c2_oldPos;
  boolean_T c2_oldPos_not_empty;
  real_T c2_rs;
  boolean_T c2_rs_not_empty;
  real_T c2_oldErr;
  boolean_T c2_oldErr_not_empty;
  real_T c2_olderErr;
  boolean_T c2_olderErr_not_empty;
  real_T c2_oldPIDVolt;
  boolean_T c2_oldPIDVolt_not_empty;
  real_T c2_olderPIDVolt;
  boolean_T c2_olderPIDVolt_not_empty;
  real_T *c2_reset;
  real_T *c2_rs_in;
  real_T *c2_acceleration;
  real_T *c2_velocity;
  real_T *c2_position;
  real_T *c2_voltFollowing;
  real_T *c2_volt;
  real_T *c2_feedback;
  real_T *c2_err;
} SFc2_trajectory_plannerInstanceStruct;

#endif                                 /*typedef_SFc2_trajectory_plannerInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c2_trajectory_planner_get_eml_resolved_functions_info
  (void);

/* Function Definitions */
extern void sf_c2_trajectory_planner_get_check_sum(mxArray *plhs[]);
extern void c2_trajectory_planner_method_dispatcher(SimStruct *S, int_T method,
  void *data);

#endif
