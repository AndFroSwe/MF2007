# =============================================================================
#  Make include file motor_io_position_new_rti.mk:
#
#   RTI1104 7.3 (02-Nov-2014)
<<<<<<< HEAD
#   Thu Apr 07 04:07:07 2016
=======
<<<<<<< HEAD
#   Wed Apr 06 22:37:50 2016
=======
#   Thu Apr 07 01:32:30 2016
>>>>>>> 698b95201d3ae24de2fb5ff3e6658cdd38e5f1ec
>>>>>>> origin/master
#
#   Copyright (c) 1999-2002 dSPACE GmbH, GERMANY
# =============================================================================

# Initialize variables used in blockset makefiles -----------------------------

BLOCKSET_LIBS     :=
BLOCKSET_SRCS     :=
BLOCKSET_INCLUDES :=

# Default rules for additional blocksets --------------------------------------

blockset_init          :
blockset_clean         :
blockset_deps          :
blockset_after_linkage :

# Includes for additional blocksets -------------------------------------------



# Model-specific options ------------------------------------------------------

# Additional C source files declared by the model
MDL_CUSTOM_C_SRCS = rti_assert.c rti_slv1104.c

# Additional assembler source files declared by the model
MDL_CUSTOM_ASM_SRCS =

# Additional libraries declared by the model
MDL_CUSTOM_LIBS =

# Additional objects declared by the model
MDL_CUSTOM_OBJS =

# Directories where additional C and assembler source files are stored
MDL_CUSTOM_SRCS_DIR =

# Directories where additional header files are stored
MDL_CUSTOM_INCLUDES_PATH =


# Define build type information
BUILDTYPE = RTI


# EOF -------------------------------------------------------------------------
