  /*********************** dSPACE target specific file *************************

   Header file motor_io_position_new_trc_ptr.h:

   Declaration of function that initializes the global TRC pointers

   RTI1104 7.3 (02-Nov-2014)
<<<<<<< HEAD
   Thu Apr 07 04:07:07 2016
=======
<<<<<<< HEAD
   Wed Apr 06 22:37:50 2016
=======
   Thu Apr 07 01:32:30 2016
>>>>>>> 698b95201d3ae24de2fb5ff3e6658cdd38e5f1ec
>>>>>>> origin/master

   (c) Copyright 2008, dSPACE GmbH. All rights reserved.

  *****************************************************************************/
  #ifndef RTI_HEADER_motor_io_position_new_trc_ptr_h_
  #define RTI_HEADER_motor_io_position_new_trc_ptr_h_
  /* Include the model header file. */
  #include "motor_io_position_new.h"
  #include "motor_io_position_new_private.h"

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
              EXTERN_C volatile  real_T *p_0_motor_io_position_new_real_T_0;
              EXTERN_C volatile  boolean_T *p_0_motor_io_position_new_boolean_T_1;
              EXTERN_C volatile  real_T *p_1_motor_io_position_new_real_T_0;
              EXTERN_C volatile  real_T *p_2_motor_io_position_new_real_T_0;
              EXTERN_C volatile  int_T *p_2_motor_io_position_new_int_T_2;
              EXTERN_C volatile  real_T *p_3_motor_io_position_new_real_T_0;

   #define RTI_INIT_TRC_POINTERS() \
<<<<<<< HEAD
              p_0_motor_io_position_new_real_T_0 = &motor_io_position_new_B.Gff;\
=======
              p_0_motor_io_position_new_real_T_0 = &motor_io_position_new_B.SinGenerator;\
>>>>>>> 698b95201d3ae24de2fb5ff3e6658cdd38e5f1ec
              p_0_motor_io_position_new_boolean_T_1 = &motor_io_position_new_B.DataTypeConversion;\
              p_1_motor_io_position_new_real_T_0 = &motor_io_position_new_P.F_c;\
              p_2_motor_io_position_new_real_T_0 = &motor_io_position_new_DW.Gff_states;\
              p_2_motor_io_position_new_int_T_2 = &motor_io_position_new_DW.SFunction1_IWORK[0];\
              p_3_motor_io_position_new_real_T_0 = &motor_io_position_new_X.Integrator1_CSTATE;\

   #endif                       /* RTI_HEADER_motor_io_position_new_trc_ptr_h_ */
