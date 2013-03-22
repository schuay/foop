set(foop1_server_SRCS
    clientconnection.cpp
    main.cpp
    server.cpp
)

qt4_wrap_cpp(foop1_server_MOC
    clientconnection.h
    server.h
)

add_executable(foop1_server
    ${foop1_server_SRCS}
    ${foop1_server_MOC}
)

target_link_libraries(foop1_server
    ${QT_LIBRARIES}
    ${QT_QTNETWORK_LIBRARY}
    ${QJSON_LIBRARIES}
    ${COMMON_LIBRARIES}
)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${QT_INCLUDES}
    ${QJSON_INCLUDE_DIR}
    ${COMMON_INCLUDES}
)

# vim:set ts=4 sw=4 et:
