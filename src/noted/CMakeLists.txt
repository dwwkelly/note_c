set(SRCS conf.c  main.c noted.c  parse.c)
include_directories(../../include)
add_executable(noted ${SRCS})
target_link_libraries(noted note)
target_link_libraries(noted json-c)

install(TARGETS noted DESTINATION /usr/local/bin)
