#------------------------------------------------------------------------------
# Copyright (c) 2015 The University of Manchester, UK.
#
# BSD Licenced. See LICENCE for details.
#
# CppMT-replay was developed in the IDInteraction project, funded by the
# Engineering and Physical Sciences Research Council, UK through grant
# agreement number EP/M017133/1.
#
# Author: Robert Haines
#------------------------------------------------------------------------------

# Source files.
set(REPLAY_EXE_SRCS
  main.cpp
)

# Turn on all compiler warnings.
set_source_files_properties(
  ${REPLAY_EXE_SRCS}
  PROPERTIES COMPILE_FLAGS -Wall
)

# Create and link executable.
add_executable(cmt-replay ${REPLAY_EXE_SRCS})
target_link_libraries(cmt-replay ${OpenCV_LIBS})
