set(foop1_common_SRCS
    board.cpp
    jsonvariantsocket.cpp
    messagefactory.cpp
    QsDebugOutput.cpp
    QsLog.cpp
    QsLogDest.cpp
    snake.cpp
    statemessage.cpp
    directionmessage.cpp
)

qt4_wrap_cpp(foop1_common_MOC
    abstractvariantsocket.h
    jsonvariantsocket.h
)

add_library(foop1_common
    ${foop1_common_SRCS}
    ${foop1_common_MOC}
)

target_link_libraries(foop1_common
    ${QT_LIBRARIES}
    ${QJSON_LIBRARIES}
    ${qjson_LIBRARIES}
)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${QT_INCLUDES}
    ${QJSON_INCLUDE_DIR}
)

# vim:set ts=4 sw=4 et:
