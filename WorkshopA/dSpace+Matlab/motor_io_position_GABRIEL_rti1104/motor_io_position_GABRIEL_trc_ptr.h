  /*********************** dSPACE target specific file *************************

   Header file motor_io_position_GABRIEL_trc_ptr.h:

   Declaration of function that initializes the global TRC pointers

   RTI1104 7.3 (02-Nov-2014)
   Thu Apr 07 03:37:21 2016

   (c) Copyright 2008, dSPACE GmbH. All rights reserved.

  *****************************************************************************/
  #ifndef RTI_HEADER_motor_io_position_GABRIEL_trc_ptr_h_
  #define RTI_HEADER_motor_io_position_GABRIEL_trc_ptr_h_
  /* Include the model header file. */
  #include "motor_io_position_GABRIEL.h"
  #include "motor_io_position_GABRIEL_private.h"

  #ifdef EXTERN_C
  #undef EXTERN_C
  #endif

  #ifdef __cplusplus
  #define EXTERN_C                       extern "C"
  #else
  #define EXTERN_C                       extern
  #endif

  /*
   *  Declare the global TRC pointers
   */
              EXTERN_C volatile  real_T *p_0_motor_io_position_GABRIEL_real_T_0;
              EXTERN_C volatile  boolean_T *p_0_motor_io_position_GABRIEL_boolean_T_1;
              EXTERN_C volatile  real_T *p_1_motor_io_position_GABRIEL_real_T_0;
              EXTERN_C volatile  real_T *p_2_motor_io_position_GABRIEL_real_T_0;
              EXTERN_C volatile  int_T *p_2_motor_io_position_GABRIEL_int_T_2;
              EXTERN_C volatile  real_T *p_3_motor_io_position_GABRIEL_real_T_0;

   #define RTI_INIT_TRC_POINTERS() \
              p_0_motor_io_position_GABRIEL_real_T_0 = &motor_io_position_GABRIEL_B.SinGenerator;\
              p_0_motor_io_position_GABRIEL_boolean_T_1 = &motor_io_position_GABRIEL_B.DataTypeConversion;\
              p_1_motor_io_position_GABRIEL_real_T_0 = &motor_io_position_GABRIEL_P.F_c;\
              p_2_motor_io_position_GABRIEL_real_T_0 = &motor_io_position_GABRIEL_DW.Gff1_states[0];\
              p_2_motor_io_position_GABRIEL_int_T_2 = &motor_io_position_GABRIEL_DW.SFunction1_IWORK[0];\
              p_3_motor_io_position_GABRIEL_real_T_0 = &motor_io_position_GABRIEL_X.Integrator1_CSTATE;\

   #endif                       /* RTI_HEADER_motor_io_position_GABRIEL_trc_ptr_h_ */
