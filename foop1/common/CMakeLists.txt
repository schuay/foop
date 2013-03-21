set(foop1_common_SRCS
    QsDebugOutput.cpp
    QsLog.cpp
    QsLogDest.cpp
)

add_library(foop1_common
    ${foop1_common_SRCS}
)

target_link_libraries(foop1_common
    ${QT_LIBRARIES}
)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${QT_INCLUDES}
)

# vim:set ts=4 sw=4 et:
