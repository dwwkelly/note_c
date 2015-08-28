set(SRCS paths.c note.c)
include_directories(../../include)
add_library(note SHARED ${SRCS})
install(TARGETS note DESTINATION /usr/local/lib)
