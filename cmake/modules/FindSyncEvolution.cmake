# - Find SyncEvolution
#
#  This module defines the following variables:
#
#   SyncEvolution_FOUND         - system has syncevolution
#   SyncEvolution_INCLUDE_DIRS  - the syncevolution include directories
#   SyncEvolution_LIBRARIES     - the syncevolution libraries
 
#=============================================================================
# Copyright 2010 Sascha Peilicke <sasch.pe@gmx.de
#
# Distributed under the OSI-approved BSD License (the "License");
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================

include(LibFindMacros)

find_path(SyncEvolution_INCLUDE_DIR
    NAMES FOO
    PATHS FOO
)

find_library(SyncEvolution_LIBRARY
    NAMES FOO
    PATHS FOO
)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(SyncEvolution_PROCESS_INCLUDES SyncEvolution_INCLUDE_DIR SyncEvolution_INCLUDE_DIRS)
set(SyncEvolution_PROCESS_LIBS SyncEvolution_LIBRARY SyncEvolution_LIBRARIES)
libfind_process(SyncEvolution)

## handle the QUIETLY and REQUIRED arguments and set SyncEvolution_FOUND to TRUE
## if all listed variables are TRUE
#include(FindPackageHandleStandardArgs)
#FIND_PACKAGE_HANDLE_STANDARD_ARGS(SyncEvolution DEFAULT_MSG SyncEvolution_INCLUDE_DIR SyncEvolution_LIBRARY)
#
#mark_as_advanced(SyncEvolution_INCLUDE_DIR SyncEvolution_LIBRARY)
