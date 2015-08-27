
set(SRCS paths.c)
include_directories(../../include)
add_library(notecommon SHARED ${SRCS})
