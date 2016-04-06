#ifndef __c1_trajectory_planner_h__
#define __c1_trajectory_planner_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc1_trajectory_plannerInstanceStruct
#define typedef_SFc1_trajectory_plannerInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c1_sfEvent;
  boolean_T c1_isStable;
  boolean_T c1_doneDoubleBufferReInit;
  uint8_T c1_is_active_c1_trajectory_planner;
  real_T *c1_volt;
  real_T *c1_acceleration;
  real_T *c1_velocity;
} SFc1_trajectory_plannerInstanceStruct;

#endif                                 /*typedef_SFc1_trajectory_plannerInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c1_trajectory_planner_get_eml_resolved_functions_info
  (void);

/* Function Definitions */
extern void sf_c1_trajectory_planner_get_check_sum(mxArray *plhs[]);
extern void c1_trajectory_planner_method_dispatcher(SimStruct *S, int_T method,
  void *data);

#endif
