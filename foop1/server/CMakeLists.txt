set(foop1_server_SRCS
    main.cpp
)

add_executable(foop1_server
    ${foop1_server_SRCS}
)

target_link_libraries(foop1_server
    ${QT_LIBRARIES}
    ${COMMON_LIBRARIES}
)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${QT_INCLUDES}
    ${COMMON_INCLUDES}
)

# vim:set ts=4 sw=4 et:
