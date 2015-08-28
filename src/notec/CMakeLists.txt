set(SRCS notec.c)
add_executable(notec ${SRCS})
target_link_libraries(notec note)
install(TARGETS notec DESTINATION /usr/local/bin)
