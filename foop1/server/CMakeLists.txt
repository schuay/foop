set(foop1_server_SRCS
    main.cpp
    server.cpp
)

qt4_wrap_cpp(foop1_server_MOC
    server.h
)

add_executable(foop1_server
    ${foop1_server_SRCS}
    ${foop1_server_MOC}
)

target_link_libraries(foop1_server
    ${QT_LIBRARIES}
    ${QT_QTNETWORK_LIBRARY}
    ${COMMON_LIBRARIES}
)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${QT_INCLUDES}
    ${COMMON_INCLUDES}
)

# vim:set ts=4 sw=4 et:
