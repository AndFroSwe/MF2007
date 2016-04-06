/* Include files */

#include <stddef.h>
#include "blas.h"
#include "motor_io_sfun.h"
#include "c4_motor_io.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "motor_io_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c4_debug_family_names[46] = { "rs", "Ts", "vmax", "amax",
  "amin", "t1", "t2", "t3", "voltmax", "out1", "out2", "out3", "out4", "J1",
  "motor_j", "n", "motor_k", "motor_R", "motor_d", "accPart", "velPartK",
  "velPartD", "s2", "s1", "s0", "r0", "PIDVolt", "nargin", "nargout", "reset",
  "rs_in", "feedback", "acceleration", "velocity", "position", "voltFollowing",
  "volt", "err", "time", "oldAcc", "oldVel", "oldPos", "oldErr", "olderErr",
  "oldPIDVolt", "olderPIDVolt" };

/* Function Declarations */
static void initialize_c4_motor_io(SFc4_motor_ioInstanceStruct *chartInstance);
static void initialize_params_c4_motor_io(SFc4_motor_ioInstanceStruct
  *chartInstance);
static void enable_c4_motor_io(SFc4_motor_ioInstanceStruct *chartInstance);
static void disable_c4_motor_io(SFc4_motor_ioInstanceStruct *chartInstance);
static void c4_update_debugger_state_c4_motor_io(SFc4_motor_ioInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c4_motor_io(SFc4_motor_ioInstanceStruct
  *chartInstance);
static void set_sim_state_c4_motor_io(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_st);
static void finalize_c4_motor_io(SFc4_motor_ioInstanceStruct *chartInstance);
static void sf_gateway_c4_motor_io(SFc4_motor_ioInstanceStruct *chartInstance);
static void mdl_start_c4_motor_io(SFc4_motor_ioInstanceStruct *chartInstance);
static void c4_chartstep_c4_motor_io(SFc4_motor_ioInstanceStruct *chartInstance);
static void initSimStructsc4_motor_io(SFc4_motor_ioInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c4_machineNumber, uint32_T
  c4_chartNumber, uint32_T c4_instanceNumber);
static const mxArray *c4_sf_marshallOut(void *chartInstanceVoid, void *c4_inData);
static real_T c4_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_b_olderPIDVolt, const char_T *c4_identifier);
static real_T c4_b_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_b_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static real_T c4_c_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_b_oldPIDVolt, const char_T *c4_identifier);
static real_T c4_d_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_c_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static real_T c4_e_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_b_olderErr, const char_T *c4_identifier);
static real_T c4_f_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_d_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static real_T c4_g_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_b_oldErr, const char_T *c4_identifier);
static real_T c4_h_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_e_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static real_T c4_i_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_b_oldPos, const char_T *c4_identifier);
static real_T c4_j_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_f_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static real_T c4_k_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_b_oldVel, const char_T *c4_identifier);
static real_T c4_l_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_g_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static real_T c4_m_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_b_oldAcc, const char_T *c4_identifier);
static real_T c4_n_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_h_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static real_T c4_o_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_b_time, const char_T *c4_identifier);
static real_T c4_p_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_i_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static real_T c4_q_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_b_err, const char_T *c4_identifier);
static real_T c4_r_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static void c4_info_helper(const mxArray **c4_info);
static const mxArray *c4_emlrt_marshallOut(const char * c4_u);
static const mxArray *c4_b_emlrt_marshallOut(const uint32_T c4_u);
static void c4_eml_error(SFc4_motor_ioInstanceStruct *chartInstance);
static const mxArray *c4_j_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static int32_T c4_s_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static uint8_T c4_t_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_b_is_active_c4_motor_io, const char_T *c4_identifier);
static uint8_T c4_u_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void init_dsm_address_info(SFc4_motor_ioInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc4_motor_ioInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c4_motor_io(SFc4_motor_ioInstanceStruct *chartInstance)
{
  chartInstance->c4_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c4_time_not_empty = false;
  chartInstance->c4_oldAcc_not_empty = false;
  chartInstance->c4_oldVel_not_empty = false;
  chartInstance->c4_oldPos_not_empty = false;
  chartInstance->c4_oldErr_not_empty = false;
  chartInstance->c4_olderErr_not_empty = false;
  chartInstance->c4_oldPIDVolt_not_empty = false;
  chartInstance->c4_olderPIDVolt_not_empty = false;
  chartInstance->c4_is_active_c4_motor_io = 0U;
}

static void initialize_params_c4_motor_io(SFc4_motor_ioInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c4_motor_io(SFc4_motor_ioInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c4_motor_io(SFc4_motor_ioInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c4_update_debugger_state_c4_motor_io(SFc4_motor_ioInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c4_motor_io(SFc4_motor_ioInstanceStruct
  *chartInstance)
{
  const mxArray *c4_st;
  const mxArray *c4_y = NULL;
  real_T c4_hoistedGlobal;
  real_T c4_u;
  const mxArray *c4_b_y = NULL;
  real_T c4_b_hoistedGlobal;
  real_T c4_b_u;
  const mxArray *c4_c_y = NULL;
  real_T c4_c_hoistedGlobal;
  real_T c4_c_u;
  const mxArray *c4_d_y = NULL;
  real_T c4_d_hoistedGlobal;
  real_T c4_d_u;
  const mxArray *c4_e_y = NULL;
  real_T c4_e_hoistedGlobal;
  real_T c4_e_u;
  const mxArray *c4_f_y = NULL;
  real_T c4_f_hoistedGlobal;
  real_T c4_f_u;
  const mxArray *c4_g_y = NULL;
  real_T c4_g_hoistedGlobal;
  real_T c4_g_u;
  const mxArray *c4_h_y = NULL;
  real_T c4_h_hoistedGlobal;
  real_T c4_h_u;
  const mxArray *c4_i_y = NULL;
  real_T c4_i_hoistedGlobal;
  real_T c4_i_u;
  const mxArray *c4_j_y = NULL;
  real_T c4_j_hoistedGlobal;
  real_T c4_j_u;
  const mxArray *c4_k_y = NULL;
  real_T c4_k_hoistedGlobal;
  real_T c4_k_u;
  const mxArray *c4_l_y = NULL;
  real_T c4_l_hoistedGlobal;
  real_T c4_l_u;
  const mxArray *c4_m_y = NULL;
  real_T c4_m_hoistedGlobal;
  real_T c4_m_u;
  const mxArray *c4_n_y = NULL;
  real_T c4_n_hoistedGlobal;
  real_T c4_n_u;
  const mxArray *c4_o_y = NULL;
  uint8_T c4_o_hoistedGlobal;
  uint8_T c4_o_u;
  const mxArray *c4_p_y = NULL;
  c4_st = NULL;
  c4_st = NULL;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_createcellmatrix(15, 1), false);
  c4_hoistedGlobal = *chartInstance->c4_acceleration;
  c4_u = c4_hoistedGlobal;
  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", &c4_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c4_y, 0, c4_b_y);
  c4_b_hoistedGlobal = *chartInstance->c4_err;
  c4_b_u = c4_b_hoistedGlobal;
  c4_c_y = NULL;
  sf_mex_assign(&c4_c_y, sf_mex_create("y", &c4_b_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c4_y, 1, c4_c_y);
  c4_c_hoistedGlobal = *chartInstance->c4_position;
  c4_c_u = c4_c_hoistedGlobal;
  c4_d_y = NULL;
  sf_mex_assign(&c4_d_y, sf_mex_create("y", &c4_c_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c4_y, 2, c4_d_y);
  c4_d_hoistedGlobal = *chartInstance->c4_velocity;
  c4_d_u = c4_d_hoistedGlobal;
  c4_e_y = NULL;
  sf_mex_assign(&c4_e_y, sf_mex_create("y", &c4_d_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c4_y, 3, c4_e_y);
  c4_e_hoistedGlobal = *chartInstance->c4_volt;
  c4_e_u = c4_e_hoistedGlobal;
  c4_f_y = NULL;
  sf_mex_assign(&c4_f_y, sf_mex_create("y", &c4_e_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c4_y, 4, c4_f_y);
  c4_f_hoistedGlobal = *chartInstance->c4_voltFollowing;
  c4_f_u = c4_f_hoistedGlobal;
  c4_g_y = NULL;
  sf_mex_assign(&c4_g_y, sf_mex_create("y", &c4_f_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c4_y, 5, c4_g_y);
  c4_g_hoistedGlobal = chartInstance->c4_oldAcc;
  c4_g_u = c4_g_hoistedGlobal;
  c4_h_y = NULL;
  if (!chartInstance->c4_oldAcc_not_empty) {
    sf_mex_assign(&c4_h_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c4_h_y, sf_mex_create("y", &c4_g_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_setcell(c4_y, 6, c4_h_y);
  c4_h_hoistedGlobal = chartInstance->c4_oldErr;
  c4_h_u = c4_h_hoistedGlobal;
  c4_i_y = NULL;
  if (!chartInstance->c4_oldErr_not_empty) {
    sf_mex_assign(&c4_i_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c4_i_y, sf_mex_create("y", &c4_h_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_setcell(c4_y, 7, c4_i_y);
  c4_i_hoistedGlobal = chartInstance->c4_oldPIDVolt;
  c4_i_u = c4_i_hoistedGlobal;
  c4_j_y = NULL;
  if (!chartInstance->c4_oldPIDVolt_not_empty) {
    sf_mex_assign(&c4_j_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c4_j_y, sf_mex_create("y", &c4_i_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_setcell(c4_y, 8, c4_j_y);
  c4_j_hoistedGlobal = chartInstance->c4_oldPos;
  c4_j_u = c4_j_hoistedGlobal;
  c4_k_y = NULL;
  if (!chartInstance->c4_oldPos_not_empty) {
    sf_mex_assign(&c4_k_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c4_k_y, sf_mex_create("y", &c4_j_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_setcell(c4_y, 9, c4_k_y);
  c4_k_hoistedGlobal = chartInstance->c4_oldVel;
  c4_k_u = c4_k_hoistedGlobal;
  c4_l_y = NULL;
  if (!chartInstance->c4_oldVel_not_empty) {
    sf_mex_assign(&c4_l_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c4_l_y, sf_mex_create("y", &c4_k_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_setcell(c4_y, 10, c4_l_y);
  c4_l_hoistedGlobal = chartInstance->c4_olderErr;
  c4_l_u = c4_l_hoistedGlobal;
  c4_m_y = NULL;
  if (!chartInstance->c4_olderErr_not_empty) {
    sf_mex_assign(&c4_m_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c4_m_y, sf_mex_create("y", &c4_l_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_setcell(c4_y, 11, c4_m_y);
  c4_m_hoistedGlobal = chartInstance->c4_olderPIDVolt;
  c4_m_u = c4_m_hoistedGlobal;
  c4_n_y = NULL;
  if (!chartInstance->c4_olderPIDVolt_not_empty) {
    sf_mex_assign(&c4_n_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c4_n_y, sf_mex_create("y", &c4_m_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_setcell(c4_y, 12, c4_n_y);
  c4_n_hoistedGlobal = chartInstance->c4_time;
  c4_n_u = c4_n_hoistedGlobal;
  c4_o_y = NULL;
  if (!chartInstance->c4_time_not_empty) {
    sf_mex_assign(&c4_o_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c4_o_y, sf_mex_create("y", &c4_n_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_setcell(c4_y, 13, c4_o_y);
  c4_o_hoistedGlobal = chartInstance->c4_is_active_c4_motor_io;
  c4_o_u = c4_o_hoistedGlobal;
  c4_p_y = NULL;
  sf_mex_assign(&c4_p_y, sf_mex_create("y", &c4_o_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c4_y, 14, c4_p_y);
  sf_mex_assign(&c4_st, c4_y, false);
  return c4_st;
}

static void set_sim_state_c4_motor_io(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_st)
{
  const mxArray *c4_u;
  chartInstance->c4_doneDoubleBufferReInit = true;
  c4_u = sf_mex_dup(c4_st);
  *chartInstance->c4_acceleration = c4_q_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c4_u, 0)), "acceleration");
  *chartInstance->c4_err = c4_q_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c4_u, 1)), "err");
  *chartInstance->c4_position = c4_q_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c4_u, 2)), "position");
  *chartInstance->c4_velocity = c4_q_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c4_u, 3)), "velocity");
  *chartInstance->c4_volt = c4_q_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c4_u, 4)), "volt");
  *chartInstance->c4_voltFollowing = c4_q_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c4_u, 5)), "voltFollowing");
  chartInstance->c4_oldAcc = c4_m_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c4_u, 6)), "oldAcc");
  chartInstance->c4_oldErr = c4_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c4_u, 7)), "oldErr");
  chartInstance->c4_oldPIDVolt = c4_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c4_u, 8)), "oldPIDVolt");
  chartInstance->c4_oldPos = c4_i_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c4_u, 9)), "oldPos");
  chartInstance->c4_oldVel = c4_k_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c4_u, 10)), "oldVel");
  chartInstance->c4_olderErr = c4_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c4_u, 11)), "olderErr");
  chartInstance->c4_olderPIDVolt = c4_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c4_u, 12)), "olderPIDVolt");
  chartInstance->c4_time = c4_o_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c4_u, 13)), "time");
  chartInstance->c4_is_active_c4_motor_io = c4_t_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c4_u, 14)), "is_active_c4_motor_io");
  sf_mex_destroy(&c4_u);
  c4_update_debugger_state_c4_motor_io(chartInstance);
  sf_mex_destroy(&c4_st);
}

static void finalize_c4_motor_io(SFc4_motor_ioInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c4_motor_io(SFc4_motor_ioInstanceStruct *chartInstance)
{
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 1U, chartInstance->c4_sfEvent);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c4_reset, 0U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c4_rs_in, 1U);
  chartInstance->c4_sfEvent = CALL_EVENT;
  c4_chartstep_c4_motor_io(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_motor_ioMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c4_acceleration, 2U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c4_velocity, 3U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c4_position, 4U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c4_voltFollowing, 5U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c4_volt, 6U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c4_feedback, 7U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c4_err, 8U);
}

static void mdl_start_c4_motor_io(SFc4_motor_ioInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c4_chartstep_c4_motor_io(SFc4_motor_ioInstanceStruct *chartInstance)
{
  real_T c4_hoistedGlobal;
  real_T c4_b_hoistedGlobal;
  real_T c4_c_hoistedGlobal;
  real_T c4_b_reset;
  real_T c4_b_rs_in;
  real_T c4_b_feedback;
  uint32_T c4_debug_family_var_map[46];
  real_T c4_rs;
  real_T c4_Ts;
  real_T c4_vmax;
  real_T c4_amax;
  real_T c4_amin;
  real_T c4_t1;
  real_T c4_t2;
  real_T c4_t3;
  real_T c4_voltmax;
  real_T c4_out1;
  real_T c4_out2;
  real_T c4_out3;
  real_T c4_out4;
  real_T c4_J1;
  real_T c4_motor_j;
  real_T c4_n;
  real_T c4_motor_k;
  real_T c4_motor_R;
  real_T c4_motor_d;
  real_T c4_accPart;
  real_T c4_velPartK;
  real_T c4_velPartD;
  real_T c4_s2;
  real_T c4_s1;
  real_T c4_s0;
  real_T c4_r0;
  real_T c4_PIDVolt;
  real_T c4_nargin = 3.0;
  real_T c4_nargout = 6.0;
  real_T c4_b_acceleration;
  real_T c4_b_velocity;
  real_T c4_b_position;
  real_T c4_b_voltFollowing;
  real_T c4_b_volt;
  real_T c4_b_err;
  real_T c4_A;
  real_T c4_x;
  real_T c4_b_x;
  real_T c4_c_x;
  real_T c4_y;
  real_T c4_d_x;
  real_T c4_e_x;
  real_T c4_d_hoistedGlobal;
  real_T c4_e_hoistedGlobal;
  real_T c4_b_A;
  real_T c4_f_x;
  real_T c4_g_x;
  real_T c4_h_x;
  real_T c4_b_y;
  real_T c4_f_hoistedGlobal;
  real_T c4_g_hoistedGlobal;
  real_T c4_c_A;
  real_T c4_i_x;
  real_T c4_j_x;
  real_T c4_k_x;
  real_T c4_c_y;
  real_T c4_d_A;
  real_T c4_l_x;
  real_T c4_m_x;
  real_T c4_n_x;
  real_T c4_d_y;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 1U, chartInstance->c4_sfEvent);
  c4_hoistedGlobal = *chartInstance->c4_reset;
  c4_b_hoistedGlobal = *chartInstance->c4_rs_in;
  c4_c_hoistedGlobal = *chartInstance->c4_feedback;
  c4_b_reset = c4_hoistedGlobal;
  c4_b_rs_in = c4_b_hoistedGlobal;
  c4_b_feedback = c4_c_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 46U, 46U, c4_debug_family_names,
    c4_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_rs, 0U, c4_i_sf_marshallOut,
    c4_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_Ts, 1U, c4_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_vmax, 2U, c4_i_sf_marshallOut,
    c4_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_amax, 3U, c4_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_amin, 4U, c4_i_sf_marshallOut,
    c4_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_t1, 5U, c4_i_sf_marshallOut,
    c4_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_t2, 6U, c4_i_sf_marshallOut,
    c4_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_t3, 7U, c4_i_sf_marshallOut,
    c4_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_voltmax, 8U, c4_i_sf_marshallOut,
    c4_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_out1, 9U, c4_i_sf_marshallOut,
    c4_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_out2, 10U, c4_i_sf_marshallOut,
    c4_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_out3, 11U, c4_i_sf_marshallOut,
    c4_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_out4, 12U, c4_i_sf_marshallOut,
    c4_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_J1, 13U, c4_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_motor_j, 14U, c4_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_n, 15U, c4_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_motor_k, 16U, c4_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_motor_R, 17U, c4_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_motor_d, 18U, c4_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_accPart, 19U, c4_i_sf_marshallOut,
    c4_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_velPartK, 20U, c4_i_sf_marshallOut,
    c4_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_velPartD, 21U, c4_i_sf_marshallOut,
    c4_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_s2, 22U, c4_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_s1, 23U, c4_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_s0, 24U, c4_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_r0, 25U, c4_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_PIDVolt, 26U, c4_i_sf_marshallOut,
    c4_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_nargin, 27U, c4_i_sf_marshallOut,
    c4_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_nargout, 28U, c4_i_sf_marshallOut,
    c4_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_b_reset, 29U, c4_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_b_rs_in, 30U, c4_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_b_feedback, 31U, c4_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_b_acceleration, 32U,
    c4_i_sf_marshallOut, c4_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_b_velocity, 33U, c4_i_sf_marshallOut,
    c4_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_b_position, 34U, c4_i_sf_marshallOut,
    c4_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_b_voltFollowing, 35U,
    c4_i_sf_marshallOut, c4_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_b_volt, 36U, c4_i_sf_marshallOut,
    c4_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_b_err, 37U, c4_i_sf_marshallOut,
    c4_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c4_time, 38U,
    c4_h_sf_marshallOut, c4_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c4_oldAcc, 39U,
    c4_g_sf_marshallOut, c4_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c4_oldVel, 40U,
    c4_f_sf_marshallOut, c4_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c4_oldPos, 41U,
    c4_e_sf_marshallOut, c4_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c4_oldErr, 42U,
    c4_d_sf_marshallOut, c4_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c4_olderErr, 43U,
    c4_c_sf_marshallOut, c4_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c4_oldPIDVolt, 44U,
    c4_b_sf_marshallOut, c4_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c4_olderPIDVolt, 45U,
    c4_sf_marshallOut, c4_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 4);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 5);
  if (CV_EML_IF(0, 1, 0, !chartInstance->c4_time_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 6);
    chartInstance->c4_time = 0.0;
    chartInstance->c4_time_not_empty = true;
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 9);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 10);
  if (CV_EML_IF(0, 1, 1, !chartInstance->c4_oldAcc_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 11);
    chartInstance->c4_oldAcc = 0.0;
    chartInstance->c4_oldAcc_not_empty = true;
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 14);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 15);
  if (CV_EML_IF(0, 1, 2, !chartInstance->c4_oldVel_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 16);
    chartInstance->c4_oldVel = 0.0;
    chartInstance->c4_oldVel_not_empty = true;
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 19);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 20);
  if (CV_EML_IF(0, 1, 3, !chartInstance->c4_oldPos_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 21);
    chartInstance->c4_oldPos = 0.0;
    chartInstance->c4_oldPos_not_empty = true;
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 24);
  if (CV_EML_IF(0, 1, 4, CV_RELATIONAL_EVAL(4U, 0U, 0, c4_b_reset, 1.0, -1, 0U,
        c4_b_reset == 1.0))) {
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 25);
    c4_b_position = 0.0;
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 26);
    c4_b_velocity = 0.0;
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 27);
    c4_b_acceleration = 0.0;
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 28);
    c4_b_reset = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 30);
  c4_rs = c4_b_rs_in;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 32);
  c4_Ts = 0.01;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 33);
  c4_vmax = 270.0;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 34);
  c4_amax = 255.0;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 35);
  c4_amin = -c4_amax;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 36);
  c4_A = c4_rs;
  c4_x = c4_A;
  c4_b_x = c4_x;
  c4_c_x = c4_b_x;
  c4_y = c4_c_x / 255.0;
  c4_d_x = c4_y;
  c4_t1 = c4_d_x;
  if (c4_t1 < 0.0) {
    c4_eml_error(chartInstance);
  }

  c4_e_x = c4_t1;
  c4_t1 = c4_e_x;
  c4_t1 = muDoubleScalarSqrt(c4_t1);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 37);
  c4_t2 = c4_t1;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 38);
  c4_t3 = c4_t1 + c4_t2;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 39);
  c4_voltmax = 24.0;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 42);
  c4_out1 = 255.0;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 45);
  c4_out2 = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 46);
  if (CV_EML_IF(0, 1, 5, CV_RELATIONAL_EVAL(4U, 0U, 1, chartInstance->c4_time,
        c4_t1, -1, 5U, chartInstance->c4_time >= c4_t1))) {
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 47);
    c4_out2 = c4_amin;
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 51);
  c4_out3 = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 52);
  if (CV_EML_IF(0, 1, 6, CV_RELATIONAL_EVAL(4U, 0U, 2, chartInstance->c4_time,
        c4_t2, -1, 5U, chartInstance->c4_time >= c4_t2))) {
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 53);
    c4_out3 = c4_amin;
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 57);
  c4_out4 = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 58);
  if (CV_EML_IF(0, 1, 7, CV_RELATIONAL_EVAL(4U, 0U, 3, chartInstance->c4_time,
        c4_t3, -1, 5U, chartInstance->c4_time >= c4_t3))) {
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 59);
    c4_out4 = c4_amax;
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 62);
  c4_b_acceleration = ((c4_out1 + c4_out2) + c4_out3) + c4_out4;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 63);
  chartInstance->c4_oldAcc = c4_b_acceleration;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 66);
  c4_d_hoistedGlobal = chartInstance->c4_oldVel;
  c4_e_hoistedGlobal = chartInstance->c4_oldAcc;
  c4_b_A = 0.01 * (c4_b_acceleration + c4_e_hoistedGlobal);
  c4_f_x = c4_b_A;
  c4_g_x = c4_f_x;
  c4_h_x = c4_g_x;
  c4_b_y = c4_h_x / 2.0;
  c4_b_velocity = c4_d_hoistedGlobal + c4_b_y;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 67);
  chartInstance->c4_oldVel = c4_b_velocity;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 70);
  c4_f_hoistedGlobal = chartInstance->c4_oldPos;
  c4_g_hoistedGlobal = chartInstance->c4_oldVel;
  c4_c_A = 0.01 * (c4_b_velocity + c4_g_hoistedGlobal);
  c4_i_x = c4_c_A;
  c4_j_x = c4_i_x;
  c4_k_x = c4_j_x;
  c4_c_y = c4_k_x / 2.0;
  c4_b_position = c4_f_hoistedGlobal + c4_c_y;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 72);
  chartInstance->c4_oldPos = c4_b_position;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 77);
  c4_J1 = 0.0006;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 78);
  c4_motor_j = 7.46E-7;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 79);
  c4_n = 5.0;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 80);
  c4_motor_k = 0.0697;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 81);
  c4_motor_R = 112.0;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 82);
  c4_motor_d = 1.0E-5;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 85);
  c4_accPart = c4_b_acceleration * 2.4745999999999997E-5;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 89);
  c4_velPartK = c4_b_velocity * 0.0697;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 90);
  c4_velPartD = c4_b_velocity * 1.0E-5;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 94);
  c4_d_A = (c4_accPart + c4_velPartD) * 112.0;
  c4_l_x = c4_d_A;
  c4_m_x = c4_l_x;
  c4_n_x = c4_m_x;
  c4_d_y = c4_n_x / 0.0697;
  c4_b_voltFollowing = c4_d_y + c4_velPartK;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 100);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 101);
  if (CV_EML_IF(0, 1, 8, !chartInstance->c4_oldErr_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 102);
    chartInstance->c4_oldErr = 0.0;
    chartInstance->c4_oldErr_not_empty = true;
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 104);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 105);
  if (CV_EML_IF(0, 1, 9, !chartInstance->c4_olderErr_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 106);
    chartInstance->c4_olderErr = 0.0;
    chartInstance->c4_olderErr_not_empty = true;
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 108);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 109);
  if (CV_EML_IF(0, 1, 10, !chartInstance->c4_oldPIDVolt_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 110);
    chartInstance->c4_oldPIDVolt = 0.0;
    chartInstance->c4_oldPIDVolt_not_empty = true;
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 112);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 113);
  if (CV_EML_IF(0, 1, 11, !chartInstance->c4_olderPIDVolt_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 114);
    chartInstance->c4_olderPIDVolt = 0.0;
    chartInstance->c4_olderPIDVolt_not_empty = true;
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 117);
  c4_s2 = 1348.0;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 118);
  c4_s1 = -1899.0;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 119);
  c4_s0 = 692.0;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 120);
  c4_r0 = 0.89;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 123);
  c4_b_err = c4_b_position - c4_b_feedback;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 126);
  c4_PIDVolt = (((1348.0 * c4_b_err + -1899.0 * chartInstance->c4_oldErr) +
                 692.0 * chartInstance->c4_olderErr) + 0.89 *
                chartInstance->c4_olderPIDVolt) - -0.10999999999999999 *
    chartInstance->c4_oldPIDVolt;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, MAX_int8_T);
  chartInstance->c4_olderPIDVolt = chartInstance->c4_oldPIDVolt;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 128U);
  chartInstance->c4_oldPIDVolt = c4_PIDVolt;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 129U);
  chartInstance->c4_olderErr = chartInstance->c4_oldErr;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 130U);
  chartInstance->c4_oldErr = c4_b_err;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 133U);
  c4_b_volt = c4_b_voltFollowing + c4_PIDVolt;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 135U);
  if (CV_EML_IF(0, 1, 12, CV_RELATIONAL_EVAL(4U, 0U, 4, c4_b_volt, c4_voltmax,
        -1, 5U, c4_b_volt >= c4_voltmax))) {
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 136U);
    c4_b_volt = c4_voltmax;
  } else {
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 137U);
    if (CV_EML_IF(0, 1, 13, CV_RELATIONAL_EVAL(4U, 0U, 5, c4_b_volt, -c4_voltmax,
          -1, 3U, c4_b_volt <= -c4_voltmax))) {
      _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 138U);
      c4_b_volt = -c4_voltmax;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 142U);
  chartInstance->c4_time += c4_Ts;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, -142);
  _SFD_SYMBOL_SCOPE_POP();
  *chartInstance->c4_acceleration = c4_b_acceleration;
  *chartInstance->c4_velocity = c4_b_velocity;
  *chartInstance->c4_position = c4_b_position;
  *chartInstance->c4_voltFollowing = c4_b_voltFollowing;
  *chartInstance->c4_volt = c4_b_volt;
  *chartInstance->c4_err = c4_b_err;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c4_sfEvent);
}

static void initSimStructsc4_motor_io(SFc4_motor_ioInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c4_machineNumber, uint32_T
  c4_chartNumber, uint32_T c4_instanceNumber)
{
  (void)c4_machineNumber;
  (void)c4_chartNumber;
  (void)c4_instanceNumber;
}

static const mxArray *c4_sf_marshallOut(void *chartInstanceVoid, void *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  real_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_motor_ioInstanceStruct *chartInstance;
  chartInstance = (SFc4_motor_ioInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(real_T *)c4_inData;
  c4_y = NULL;
  if (!chartInstance->c4_olderPIDVolt_not_empty) {
    sf_mex_assign(&c4_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static real_T c4_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_b_olderPIDVolt, const char_T *c4_identifier)
{
  real_T c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_olderPIDVolt),
    &c4_thisId);
  sf_mex_destroy(&c4_b_olderPIDVolt);
  return c4_y;
}

static real_T c4_b_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  real_T c4_y;
  real_T c4_d0;
  if (mxIsEmpty(c4_u)) {
    chartInstance->c4_olderPIDVolt_not_empty = false;
  } else {
    chartInstance->c4_olderPIDVolt_not_empty = true;
    sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_d0, 1, 0, 0U, 0, 0U, 0);
    c4_y = c4_d0;
  }

  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_olderPIDVolt;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y;
  SFc4_motor_ioInstanceStruct *chartInstance;
  chartInstance = (SFc4_motor_ioInstanceStruct *)chartInstanceVoid;
  c4_b_olderPIDVolt = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_olderPIDVolt),
    &c4_thisId);
  sf_mex_destroy(&c4_b_olderPIDVolt);
  *(real_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_b_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  real_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_motor_ioInstanceStruct *chartInstance;
  chartInstance = (SFc4_motor_ioInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(real_T *)c4_inData;
  c4_y = NULL;
  if (!chartInstance->c4_oldPIDVolt_not_empty) {
    sf_mex_assign(&c4_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static real_T c4_c_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_b_oldPIDVolt, const char_T *c4_identifier)
{
  real_T c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_oldPIDVolt),
    &c4_thisId);
  sf_mex_destroy(&c4_b_oldPIDVolt);
  return c4_y;
}

static real_T c4_d_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  real_T c4_y;
  real_T c4_d1;
  if (mxIsEmpty(c4_u)) {
    chartInstance->c4_oldPIDVolt_not_empty = false;
  } else {
    chartInstance->c4_oldPIDVolt_not_empty = true;
    sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_d1, 1, 0, 0U, 0, 0U, 0);
    c4_y = c4_d1;
  }

  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_oldPIDVolt;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y;
  SFc4_motor_ioInstanceStruct *chartInstance;
  chartInstance = (SFc4_motor_ioInstanceStruct *)chartInstanceVoid;
  c4_b_oldPIDVolt = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_oldPIDVolt),
    &c4_thisId);
  sf_mex_destroy(&c4_b_oldPIDVolt);
  *(real_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_c_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  real_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_motor_ioInstanceStruct *chartInstance;
  chartInstance = (SFc4_motor_ioInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(real_T *)c4_inData;
  c4_y = NULL;
  if (!chartInstance->c4_olderErr_not_empty) {
    sf_mex_assign(&c4_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static real_T c4_e_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_b_olderErr, const char_T *c4_identifier)
{
  real_T c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_olderErr),
    &c4_thisId);
  sf_mex_destroy(&c4_b_olderErr);
  return c4_y;
}

static real_T c4_f_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  real_T c4_y;
  real_T c4_d2;
  if (mxIsEmpty(c4_u)) {
    chartInstance->c4_olderErr_not_empty = false;
  } else {
    chartInstance->c4_olderErr_not_empty = true;
    sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_d2, 1, 0, 0U, 0, 0U, 0);
    c4_y = c4_d2;
  }

  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_olderErr;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y;
  SFc4_motor_ioInstanceStruct *chartInstance;
  chartInstance = (SFc4_motor_ioInstanceStruct *)chartInstanceVoid;
  c4_b_olderErr = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_olderErr),
    &c4_thisId);
  sf_mex_destroy(&c4_b_olderErr);
  *(real_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_d_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  real_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_motor_ioInstanceStruct *chartInstance;
  chartInstance = (SFc4_motor_ioInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(real_T *)c4_inData;
  c4_y = NULL;
  if (!chartInstance->c4_oldErr_not_empty) {
    sf_mex_assign(&c4_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static real_T c4_g_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_b_oldErr, const char_T *c4_identifier)
{
  real_T c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_oldErr),
    &c4_thisId);
  sf_mex_destroy(&c4_b_oldErr);
  return c4_y;
}

static real_T c4_h_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  real_T c4_y;
  real_T c4_d3;
  if (mxIsEmpty(c4_u)) {
    chartInstance->c4_oldErr_not_empty = false;
  } else {
    chartInstance->c4_oldErr_not_empty = true;
    sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_d3, 1, 0, 0U, 0, 0U, 0);
    c4_y = c4_d3;
  }

  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_oldErr;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y;
  SFc4_motor_ioInstanceStruct *chartInstance;
  chartInstance = (SFc4_motor_ioInstanceStruct *)chartInstanceVoid;
  c4_b_oldErr = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_oldErr),
    &c4_thisId);
  sf_mex_destroy(&c4_b_oldErr);
  *(real_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_e_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  real_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_motor_ioInstanceStruct *chartInstance;
  chartInstance = (SFc4_motor_ioInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(real_T *)c4_inData;
  c4_y = NULL;
  if (!chartInstance->c4_oldPos_not_empty) {
    sf_mex_assign(&c4_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static real_T c4_i_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_b_oldPos, const char_T *c4_identifier)
{
  real_T c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_oldPos),
    &c4_thisId);
  sf_mex_destroy(&c4_b_oldPos);
  return c4_y;
}

static real_T c4_j_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  real_T c4_y;
  real_T c4_d4;
  if (mxIsEmpty(c4_u)) {
    chartInstance->c4_oldPos_not_empty = false;
  } else {
    chartInstance->c4_oldPos_not_empty = true;
    sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_d4, 1, 0, 0U, 0, 0U, 0);
    c4_y = c4_d4;
  }

  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_oldPos;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y;
  SFc4_motor_ioInstanceStruct *chartInstance;
  chartInstance = (SFc4_motor_ioInstanceStruct *)chartInstanceVoid;
  c4_b_oldPos = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_oldPos),
    &c4_thisId);
  sf_mex_destroy(&c4_b_oldPos);
  *(real_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_f_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  real_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_motor_ioInstanceStruct *chartInstance;
  chartInstance = (SFc4_motor_ioInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(real_T *)c4_inData;
  c4_y = NULL;
  if (!chartInstance->c4_oldVel_not_empty) {
    sf_mex_assign(&c4_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static real_T c4_k_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_b_oldVel, const char_T *c4_identifier)
{
  real_T c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_oldVel),
    &c4_thisId);
  sf_mex_destroy(&c4_b_oldVel);
  return c4_y;
}

static real_T c4_l_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  real_T c4_y;
  real_T c4_d5;
  if (mxIsEmpty(c4_u)) {
    chartInstance->c4_oldVel_not_empty = false;
  } else {
    chartInstance->c4_oldVel_not_empty = true;
    sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_d5, 1, 0, 0U, 0, 0U, 0);
    c4_y = c4_d5;
  }

  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_oldVel;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y;
  SFc4_motor_ioInstanceStruct *chartInstance;
  chartInstance = (SFc4_motor_ioInstanceStruct *)chartInstanceVoid;
  c4_b_oldVel = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_oldVel),
    &c4_thisId);
  sf_mex_destroy(&c4_b_oldVel);
  *(real_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_g_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  real_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_motor_ioInstanceStruct *chartInstance;
  chartInstance = (SFc4_motor_ioInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(real_T *)c4_inData;
  c4_y = NULL;
  if (!chartInstance->c4_oldAcc_not_empty) {
    sf_mex_assign(&c4_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static real_T c4_m_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_b_oldAcc, const char_T *c4_identifier)
{
  real_T c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_n_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_oldAcc),
    &c4_thisId);
  sf_mex_destroy(&c4_b_oldAcc);
  return c4_y;
}

static real_T c4_n_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  real_T c4_y;
  real_T c4_d6;
  if (mxIsEmpty(c4_u)) {
    chartInstance->c4_oldAcc_not_empty = false;
  } else {
    chartInstance->c4_oldAcc_not_empty = true;
    sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_d6, 1, 0, 0U, 0, 0U, 0);
    c4_y = c4_d6;
  }

  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_oldAcc;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y;
  SFc4_motor_ioInstanceStruct *chartInstance;
  chartInstance = (SFc4_motor_ioInstanceStruct *)chartInstanceVoid;
  c4_b_oldAcc = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_n_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_oldAcc),
    &c4_thisId);
  sf_mex_destroy(&c4_b_oldAcc);
  *(real_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_h_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  real_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_motor_ioInstanceStruct *chartInstance;
  chartInstance = (SFc4_motor_ioInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(real_T *)c4_inData;
  c4_y = NULL;
  if (!chartInstance->c4_time_not_empty) {
    sf_mex_assign(&c4_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static real_T c4_o_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_b_time, const char_T *c4_identifier)
{
  real_T c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_p_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_time), &c4_thisId);
  sf_mex_destroy(&c4_b_time);
  return c4_y;
}

static real_T c4_p_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  real_T c4_y;
  real_T c4_d7;
  if (mxIsEmpty(c4_u)) {
    chartInstance->c4_time_not_empty = false;
  } else {
    chartInstance->c4_time_not_empty = true;
    sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_d7, 1, 0, 0U, 0, 0U, 0);
    c4_y = c4_d7;
  }

  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_time;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y;
  SFc4_motor_ioInstanceStruct *chartInstance;
  chartInstance = (SFc4_motor_ioInstanceStruct *)chartInstanceVoid;
  c4_b_time = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_p_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_time), &c4_thisId);
  sf_mex_destroy(&c4_b_time);
  *(real_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_i_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  real_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_motor_ioInstanceStruct *chartInstance;
  chartInstance = (SFc4_motor_ioInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(real_T *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static real_T c4_q_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_b_err, const char_T *c4_identifier)
{
  real_T c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_r_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_err), &c4_thisId);
  sf_mex_destroy(&c4_b_err);
  return c4_y;
}

static real_T c4_r_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  real_T c4_y;
  real_T c4_d8;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_d8, 1, 0, 0U, 0, 0U, 0);
  c4_y = c4_d8;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_err;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y;
  SFc4_motor_ioInstanceStruct *chartInstance;
  chartInstance = (SFc4_motor_ioInstanceStruct *)chartInstanceVoid;
  c4_b_err = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_r_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_err), &c4_thisId);
  sf_mex_destroy(&c4_b_err);
  *(real_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

const mxArray *sf_c4_motor_io_get_eml_resolved_functions_info(void)
{
  const mxArray *c4_nameCaptureInfo = NULL;
  c4_nameCaptureInfo = NULL;
  sf_mex_assign(&c4_nameCaptureInfo, sf_mex_createstruct("structure", 2, 23, 1),
                false);
  c4_info_helper(&c4_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c4_nameCaptureInfo);
  return c4_nameCaptureInfo;
}

static void c4_info_helper(const mxArray **c4_info)
{
  const mxArray *c4_rhs0 = NULL;
  const mxArray *c4_lhs0 = NULL;
  const mxArray *c4_rhs1 = NULL;
  const mxArray *c4_lhs1 = NULL;
  const mxArray *c4_rhs2 = NULL;
  const mxArray *c4_lhs2 = NULL;
  const mxArray *c4_rhs3 = NULL;
  const mxArray *c4_lhs3 = NULL;
  const mxArray *c4_rhs4 = NULL;
  const mxArray *c4_lhs4 = NULL;
  const mxArray *c4_rhs5 = NULL;
  const mxArray *c4_lhs5 = NULL;
  const mxArray *c4_rhs6 = NULL;
  const mxArray *c4_lhs6 = NULL;
  const mxArray *c4_rhs7 = NULL;
  const mxArray *c4_lhs7 = NULL;
  const mxArray *c4_rhs8 = NULL;
  const mxArray *c4_lhs8 = NULL;
  const mxArray *c4_rhs9 = NULL;
  const mxArray *c4_lhs9 = NULL;
  const mxArray *c4_rhs10 = NULL;
  const mxArray *c4_lhs10 = NULL;
  const mxArray *c4_rhs11 = NULL;
  const mxArray *c4_lhs11 = NULL;
  const mxArray *c4_rhs12 = NULL;
  const mxArray *c4_lhs12 = NULL;
  const mxArray *c4_rhs13 = NULL;
  const mxArray *c4_lhs13 = NULL;
  const mxArray *c4_rhs14 = NULL;
  const mxArray *c4_lhs14 = NULL;
  const mxArray *c4_rhs15 = NULL;
  const mxArray *c4_lhs15 = NULL;
  const mxArray *c4_rhs16 = NULL;
  const mxArray *c4_lhs16 = NULL;
  const mxArray *c4_rhs17 = NULL;
  const mxArray *c4_lhs17 = NULL;
  const mxArray *c4_rhs18 = NULL;
  const mxArray *c4_lhs18 = NULL;
  const mxArray *c4_rhs19 = NULL;
  const mxArray *c4_lhs19 = NULL;
  const mxArray *c4_rhs20 = NULL;
  const mxArray *c4_lhs20 = NULL;
  const mxArray *c4_rhs21 = NULL;
  const mxArray *c4_lhs21 = NULL;
  const mxArray *c4_rhs22 = NULL;
  const mxArray *c4_lhs22 = NULL;
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("mrdivide"), "name", "name", 0);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "resolved",
                  "resolved", 0);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410807648U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1370009886U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c4_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs0), "lhs", "lhs", 0);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "context",
                  "context", 1);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.assert"),
                  "name", "name", 1);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/assert.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1389717774U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c4_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs1), "rhs", "rhs", 1);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs1), "lhs", "lhs", 1);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "context",
                  "context", 2);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("rdivide"), "name", "name", 2);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "resolved",
                  "resolved", 2);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1363713880U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c4_rhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs2), "rhs", "rhs", 2);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs2), "lhs", "lhs", 2);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 3);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 3);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 3);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1395931856U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c4_rhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs3), "rhs", "rhs", 3);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs3), "lhs", "lhs", 3);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 4);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 4);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 4);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1286818796U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c4_rhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs4), "rhs", "rhs", 4);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs4), "lhs", "lhs", 4);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 5);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_div"), "name", "name", 5);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 5);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "resolved",
                  "resolved", 5);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1386423952U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c4_rhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs5), "rhs", "rhs", 5);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs5), "lhs", "lhs", 5);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "context",
                  "context", 6);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.div"), "name",
                  "name", 6);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/div.p"), "resolved",
                  "resolved", 6);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410807770U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c4_rhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs6), "rhs", "rhs", 6);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs6), "lhs", "lhs", 6);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "context", "context", 7);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("sqrt"), "name", "name", 7);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 7);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m"), "resolved",
                  "resolved", 7);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1343830386U), "fileTimeLo",
                  "fileTimeLo", 7);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 7);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 7);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 7);
  sf_mex_assign(&c4_rhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs7), "rhs", "rhs", 7);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs7), "lhs", "lhs", 7);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m"), "context",
                  "context", 8);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_error"), "name", "name", 8);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 8);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m"), "resolved",
                  "resolved", 8);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1343830358U), "fileTimeLo",
                  "fileTimeLo", 8);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 8);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 8);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 8);
  sf_mex_assign(&c4_rhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs8), "rhs", "rhs", 8);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs8), "lhs", "lhs", 8);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m"), "context",
                  "context", 9);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_scalar_sqrt"), "name",
                  "name", 9);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 9);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sqrt.m"),
                  "resolved", "resolved", 9);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1286818738U), "fileTimeLo",
                  "fileTimeLo", 9);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 9);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 9);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 9);
  sf_mex_assign(&c4_rhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs9), "rhs", "rhs", 9);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs9), "lhs", "lhs", 9);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "context", "context", 10);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("mpower"), "name", "name", 10);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 10);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "resolved",
                  "resolved", 10);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1363713878U), "fileTimeLo",
                  "fileTimeLo", 10);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 10);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 10);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 10);
  sf_mex_assign(&c4_rhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs10), "rhs", "rhs",
                  10);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs10), "lhs", "lhs",
                  10);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 11);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 11);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 11);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 11);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1395931856U), "fileTimeLo",
                  "fileTimeLo", 11);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 11);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 11);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 11);
  sf_mex_assign(&c4_rhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs11), "rhs", "rhs",
                  11);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs11), "lhs", "lhs",
                  11);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 12);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("ismatrix"), "name", "name", 12);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 12);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/ismatrix.m"), "resolved",
                  "resolved", 12);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1331304858U), "fileTimeLo",
                  "fileTimeLo", 12);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 12);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 12);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 12);
  sf_mex_assign(&c4_rhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs12), "rhs", "rhs",
                  12);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs12), "lhs", "lhs",
                  12);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 13);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("power"), "name", "name", 13);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 13);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m"), "resolved",
                  "resolved", 13);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1395328506U), "fileTimeLo",
                  "fileTimeLo", 13);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 13);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 13);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 13);
  sf_mex_assign(&c4_rhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs13), "rhs", "rhs",
                  13);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs13), "lhs", "lhs",
                  13);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m"), "context",
                  "context", 14);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 14);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 14);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 14);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1395931856U), "fileTimeLo",
                  "fileTimeLo", 14);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 14);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 14);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 14);
  sf_mex_assign(&c4_rhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs14), "rhs", "rhs",
                  14);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs14), "lhs", "lhs",
                  14);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 15);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 15);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 15);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 15);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 15);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 15);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 15);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 15);
  sf_mex_assign(&c4_rhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs15), "rhs", "rhs",
                  15);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs15), "lhs", "lhs",
                  15);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "context",
                  "context", 16);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 16);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 16);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 16);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410807770U), "fileTimeLo",
                  "fileTimeLo", 16);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 16);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 16);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 16);
  sf_mex_assign(&c4_rhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs16), "rhs", "rhs",
                  16);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs16), "lhs", "lhs",
                  16);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 17);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_scalexp_alloc"), "name",
                  "name", 17);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 17);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "resolved", "resolved", 17);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 17);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 17);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 17);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 17);
  sf_mex_assign(&c4_rhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs17), "rhs", "rhs",
                  17);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs17), "lhs", "lhs",
                  17);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "context", "context", 18);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.scalexpAlloc"),
                  "name", "name", 18);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 18);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalexpAlloc.p"),
                  "resolved", "resolved", 18);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410807770U), "fileTimeLo",
                  "fileTimeLo", 18);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 18);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 18);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 18);
  sf_mex_assign(&c4_rhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs18), "rhs", "rhs",
                  18);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs18), "lhs", "lhs",
                  18);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 19);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("floor"), "name", "name", 19);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 19);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "resolved",
                  "resolved", 19);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1363713854U), "fileTimeLo",
                  "fileTimeLo", 19);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 19);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 19);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 19);
  sf_mex_assign(&c4_rhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs19), "rhs", "rhs",
                  19);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs19), "lhs", "lhs",
                  19);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 20);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 20);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 20);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 20);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1395931856U), "fileTimeLo",
                  "fileTimeLo", 20);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 20);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 20);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 20);
  sf_mex_assign(&c4_rhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs20), "rhs", "rhs",
                  20);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs20), "lhs", "lhs",
                  20);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 21);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_scalar_floor"), "name",
                  "name", 21);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 21);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m"),
                  "resolved", "resolved", 21);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1286818726U), "fileTimeLo",
                  "fileTimeLo", 21);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 21);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 21);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 21);
  sf_mex_assign(&c4_rhs21, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs21, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs21), "rhs", "rhs",
                  21);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs21), "lhs", "lhs",
                  21);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!scalar_float_power"),
                  "context", "context", 22);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 22);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 22);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 22);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 22);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 22);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 22);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 22);
  sf_mex_assign(&c4_rhs22, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs22, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs22), "rhs", "rhs",
                  22);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs22), "lhs", "lhs",
                  22);
  sf_mex_destroy(&c4_rhs0);
  sf_mex_destroy(&c4_lhs0);
  sf_mex_destroy(&c4_rhs1);
  sf_mex_destroy(&c4_lhs1);
  sf_mex_destroy(&c4_rhs2);
  sf_mex_destroy(&c4_lhs2);
  sf_mex_destroy(&c4_rhs3);
  sf_mex_destroy(&c4_lhs3);
  sf_mex_destroy(&c4_rhs4);
  sf_mex_destroy(&c4_lhs4);
  sf_mex_destroy(&c4_rhs5);
  sf_mex_destroy(&c4_lhs5);
  sf_mex_destroy(&c4_rhs6);
  sf_mex_destroy(&c4_lhs6);
  sf_mex_destroy(&c4_rhs7);
  sf_mex_destroy(&c4_lhs7);
  sf_mex_destroy(&c4_rhs8);
  sf_mex_destroy(&c4_lhs8);
  sf_mex_destroy(&c4_rhs9);
  sf_mex_destroy(&c4_lhs9);
  sf_mex_destroy(&c4_rhs10);
  sf_mex_destroy(&c4_lhs10);
  sf_mex_destroy(&c4_rhs11);
  sf_mex_destroy(&c4_lhs11);
  sf_mex_destroy(&c4_rhs12);
  sf_mex_destroy(&c4_lhs12);
  sf_mex_destroy(&c4_rhs13);
  sf_mex_destroy(&c4_lhs13);
  sf_mex_destroy(&c4_rhs14);
  sf_mex_destroy(&c4_lhs14);
  sf_mex_destroy(&c4_rhs15);
  sf_mex_destroy(&c4_lhs15);
  sf_mex_destroy(&c4_rhs16);
  sf_mex_destroy(&c4_lhs16);
  sf_mex_destroy(&c4_rhs17);
  sf_mex_destroy(&c4_lhs17);
  sf_mex_destroy(&c4_rhs18);
  sf_mex_destroy(&c4_lhs18);
  sf_mex_destroy(&c4_rhs19);
  sf_mex_destroy(&c4_lhs19);
  sf_mex_destroy(&c4_rhs20);
  sf_mex_destroy(&c4_lhs20);
  sf_mex_destroy(&c4_rhs21);
  sf_mex_destroy(&c4_lhs21);
  sf_mex_destroy(&c4_rhs22);
  sf_mex_destroy(&c4_lhs22);
}

static const mxArray *c4_emlrt_marshallOut(const char * c4_u)
{
  const mxArray *c4_y = NULL;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c4_u)), false);
  return c4_y;
}

static const mxArray *c4_b_emlrt_marshallOut(const uint32_T c4_u)
{
  const mxArray *c4_y = NULL;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 7, 0U, 0U, 0U, 0), false);
  return c4_y;
}

static void c4_eml_error(SFc4_motor_ioInstanceStruct *chartInstance)
{
  int32_T c4_i0;
  static char_T c4_cv0[30] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'E', 'l', 'F', 'u', 'n', 'D', 'o', 'm', 'a', 'i', 'n',
    'E', 'r', 'r', 'o', 'r' };

  char_T c4_u[30];
  const mxArray *c4_y = NULL;
  int32_T c4_i1;
  static char_T c4_cv1[4] = { 's', 'q', 'r', 't' };

  char_T c4_b_u[4];
  const mxArray *c4_b_y = NULL;
  (void)chartInstance;
  for (c4_i0 = 0; c4_i0 < 30; c4_i0++) {
    c4_u[c4_i0] = c4_cv0[c4_i0];
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 10, 0U, 1U, 0U, 2, 1, 30), false);
  for (c4_i1 = 0; c4_i1 < 4; c4_i1++) {
    c4_b_u[c4_i1] = c4_cv1[c4_i1];
  }

  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", c4_b_u, 10, 0U, 1U, 0U, 2, 1, 4),
                false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message", 1U,
    2U, 14, c4_y, 14, c4_b_y));
}

static const mxArray *c4_j_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_motor_ioInstanceStruct *chartInstance;
  chartInstance = (SFc4_motor_ioInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(int32_T *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static int32_T c4_s_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  int32_T c4_y;
  int32_T c4_i2;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_i2, 1, 6, 0U, 0, 0U, 0);
  c4_y = c4_i2;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_sfEvent;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  int32_T c4_y;
  SFc4_motor_ioInstanceStruct *chartInstance;
  chartInstance = (SFc4_motor_ioInstanceStruct *)chartInstanceVoid;
  c4_b_sfEvent = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_s_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_sfEvent),
    &c4_thisId);
  sf_mex_destroy(&c4_b_sfEvent);
  *(int32_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static uint8_T c4_t_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_b_is_active_c4_motor_io, const char_T *c4_identifier)
{
  uint8_T c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_u_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c4_b_is_active_c4_motor_io), &c4_thisId);
  sf_mex_destroy(&c4_b_is_active_c4_motor_io);
  return c4_y;
}

static uint8_T c4_u_emlrt_marshallIn(SFc4_motor_ioInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  uint8_T c4_y;
  uint8_T c4_u0;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_u0, 1, 3, 0U, 0, 0U, 0);
  c4_y = c4_u0;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void init_dsm_address_info(SFc4_motor_ioInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc4_motor_ioInstanceStruct *chartInstance)
{
  chartInstance->c4_reset = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c4_rs_in = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c4_acceleration = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c4_velocity = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c4_position = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c4_voltFollowing = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 4);
  chartInstance->c4_volt = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 5);
  chartInstance->c4_feedback = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c4_err = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 6);
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c4_motor_io_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(271287565U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3885934416U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1378765283U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1028584941U);
}

mxArray* sf_c4_motor_io_get_post_codegen_info(void);
mxArray *sf_c4_motor_io_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("DsKW5TboqvULGmKMrmS4VD");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,6,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c4_motor_io_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c4_motor_io_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c4_motor_io_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "incompatibleSymbol", };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 3, infoFields);
  mxArray *fallbackReason = mxCreateString("feature_off");
  mxArray *incompatibleSymbol = mxCreateString("");
  mxArray *fallbackType = mxCreateString("early");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c4_motor_io_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c4_motor_io_get_post_codegen_info(void)
{
  const char* fieldNames[] = { "exportedFunctionsUsedByThisChart",
    "exportedFunctionsChecksum" };

  mwSize dims[2] = { 1, 1 };

  mxArray* mxPostCodegenInfo = mxCreateStructArray(2, dims, sizeof(fieldNames)/
    sizeof(fieldNames[0]), fieldNames);

  {
    mxArray* mxExportedFunctionsChecksum = mxCreateString("");
    mwSize exp_dims[2] = { 0, 1 };

    mxArray* mxExportedFunctionsUsedByThisChart = mxCreateCellArray(2, exp_dims);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsUsedByThisChart",
               mxExportedFunctionsUsedByThisChart);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsChecksum",
               mxExportedFunctionsChecksum);
  }

  return mxPostCodegenInfo;
}

static const mxArray *sf_get_sim_state_info_c4_motor_io(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x10'type','srcId','name','auxInfo'{{M[1],M[13],T\"acceleration\",},{M[1],M[17],T\"err\",},{M[1],M[15],T\"position\",},{M[1],M[14],T\"velocity\",},{M[1],M[9],T\"volt\",},{M[1],M[16],T\"voltFollowing\",},{M[4],M[0],T\"oldAcc\",S'l','i','p'{{M1x2[198 204],M[0],}}},{M[4],M[0],T\"oldErr\",S'l','i','p'{{M1x2[1561 1567],M[0],}}},{M[4],M[0],T\"oldPIDVolt\",S'l','i','p'{{M1x2[1679 1689],M[0],}}},{M[4],M[0],T\"oldPos\",S'l','i','p'{{M1x2[316 322],M[0],}}}}",
    "100 S1x5'type','srcId','name','auxInfo'{{M[4],M[0],T\"oldVel\",S'l','i','p'{{M1x2[257 263],M[0],}}},{M[4],M[0],T\"olderErr\",S'l','i','p'{{M1x2[1618 1626],M[0],}}},{M[4],M[0],T\"olderPIDVolt\",S'l','i','p'{{M1x2[1748 1760],M[0],}}},{M[4],M[0],T\"time\",S'l','i','p'{{M1x2[145 149],M[0],}}},{M[8],M[0],T\"is_active_c4_motor_io\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 15, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c4_motor_io_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc4_motor_ioInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc4_motor_ioInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _motor_ioMachineNumber_,
           4,
           1,
           1,
           0,
           9,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_motor_ioMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_motor_ioMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _motor_ioMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"reset");
          _SFD_SET_DATA_PROPS(1,1,1,0,"rs_in");
          _SFD_SET_DATA_PROPS(2,2,0,1,"acceleration");
          _SFD_SET_DATA_PROPS(3,2,0,1,"velocity");
          _SFD_SET_DATA_PROPS(4,2,0,1,"position");
          _SFD_SET_DATA_PROPS(5,2,0,1,"voltFollowing");
          _SFD_SET_DATA_PROPS(6,2,0,1,"volt");
          _SFD_SET_DATA_PROPS(7,1,1,0,"feedback");
          _SFD_SET_DATA_PROPS(8,2,0,1,"err");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,14,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,2227);
        _SFD_CV_INIT_EML_IF(0,1,0,151,167,-1,185);
        _SFD_CV_INIT_EML_IF(0,1,1,206,224,-1,244);
        _SFD_CV_INIT_EML_IF(0,1,2,265,283,-1,303);
        _SFD_CV_INIT_EML_IF(0,1,3,324,342,-1,362);
        _SFD_CV_INIT_EML_IF(0,1,4,378,392,-1,469);
        _SFD_CV_INIT_EML_IF(0,1,5,717,731,-1,752);
        _SFD_CV_INIT_EML_IF(0,1,6,789,803,-1,824);
        _SFD_CV_INIT_EML_IF(0,1,7,856,870,-1,891);
        _SFD_CV_INIT_EML_IF(0,1,8,1568,1586,-1,1606);
        _SFD_CV_INIT_EML_IF(0,1,9,1627,1647,-1,1667);
        _SFD_CV_INIT_EML_IF(0,1,10,1690,1712,-1,1736);
        _SFD_CV_INIT_EML_IF(0,1,11,1761,1785,-1,1811);
        _SFD_CV_INIT_EML_IF(0,1,12,2114,2133,2154,2178);
        _SFD_CV_INIT_EML_IF(0,1,13,2154,2178,-1,2178);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,0,381,391,-1,0);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,1,720,730,-1,5);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,2,792,802,-1,5);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,3,859,869,-1,5);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,4,2117,2132,-1,5);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,5,2161,2177,-1,3);
        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_i_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_i_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_i_sf_marshallOut,(MexInFcnForType)c4_i_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_i_sf_marshallOut,(MexInFcnForType)c4_i_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_i_sf_marshallOut,(MexInFcnForType)c4_i_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_i_sf_marshallOut,(MexInFcnForType)c4_i_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_i_sf_marshallOut,(MexInFcnForType)c4_i_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_i_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_i_sf_marshallOut,(MexInFcnForType)c4_i_sf_marshallIn);
        _SFD_SET_DATA_VALUE_PTR(0U, chartInstance->c4_reset);
        _SFD_SET_DATA_VALUE_PTR(1U, chartInstance->c4_rs_in);
        _SFD_SET_DATA_VALUE_PTR(2U, chartInstance->c4_acceleration);
        _SFD_SET_DATA_VALUE_PTR(3U, chartInstance->c4_velocity);
        _SFD_SET_DATA_VALUE_PTR(4U, chartInstance->c4_position);
        _SFD_SET_DATA_VALUE_PTR(5U, chartInstance->c4_voltFollowing);
        _SFD_SET_DATA_VALUE_PTR(6U, chartInstance->c4_volt);
        _SFD_SET_DATA_VALUE_PTR(7U, chartInstance->c4_feedback);
        _SFD_SET_DATA_VALUE_PTR(8U, chartInstance->c4_err);
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _motor_ioMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "9R7kSVXrHnxdQcVYbyWBEG";
}

static void sf_opaque_initialize_c4_motor_io(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc4_motor_ioInstanceStruct*) chartInstanceVar)
    ->S,0);
  initialize_params_c4_motor_io((SFc4_motor_ioInstanceStruct*) chartInstanceVar);
  initialize_c4_motor_io((SFc4_motor_ioInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c4_motor_io(void *chartInstanceVar)
{
  enable_c4_motor_io((SFc4_motor_ioInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c4_motor_io(void *chartInstanceVar)
{
  disable_c4_motor_io((SFc4_motor_ioInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c4_motor_io(void *chartInstanceVar)
{
  sf_gateway_c4_motor_io((SFc4_motor_ioInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c4_motor_io(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  return get_sim_state_c4_motor_io((SFc4_motor_ioInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c4_motor_io(SimStruct* S, const mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  set_sim_state_c4_motor_io((SFc4_motor_ioInstanceStruct*)
    chartInfo->chartInstance, st);
}

static void sf_opaque_terminate_c4_motor_io(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc4_motor_ioInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_motor_io_optimization_info();
    }

    finalize_c4_motor_io((SFc4_motor_ioInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (crtInfo != NULL) {
      utFree(crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc4_motor_io((SFc4_motor_ioInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c4_motor_io(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    initialize_params_c4_motor_io((SFc4_motor_ioInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c4_motor_io(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_motor_io_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,4);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,4,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,4,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,4);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,4,3);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,4,6);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=6; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 3; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,4);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3500055431U));
  ssSetChecksum1(S,(1929124776U));
  ssSetChecksum2(S,(3723338875U));
  ssSetChecksum3(S,(3782506503U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c4_motor_io(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c4_motor_io(SimStruct *S)
{
  SFc4_motor_ioInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc4_motor_ioInstanceStruct *)utMalloc(sizeof
    (SFc4_motor_ioInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc4_motor_ioInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c4_motor_io;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c4_motor_io;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c4_motor_io;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c4_motor_io;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c4_motor_io;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c4_motor_io;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c4_motor_io;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c4_motor_io;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c4_motor_io;
  chartInstance->chartInfo.mdlStart = mdlStart_c4_motor_io;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c4_motor_io;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  crtInfo->checksum = SF_RUNTIME_INFO_CHECKSUM;
  crtInfo->instanceInfo = (&(chartInstance->chartInfo));
  crtInfo->isJITEnabled = false;
  crtInfo->compiledInfo = NULL;
  ssSetUserData(S,(void *)(crtInfo));  /* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c4_motor_io_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c4_motor_io(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c4_motor_io(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c4_motor_io(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c4_motor_io_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
