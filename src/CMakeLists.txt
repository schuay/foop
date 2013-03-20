set(foop1_SRCS
    main.cpp
    mainwindow.cpp
)

qt4_wrap_cpp(foop1_MOC
    mainwindow.h
)

qt4_wrap_ui(foop1_UI
    mainwindow.ui
)

add_executable(foop1
    ${foop1_SRCS}
    ${foop1_MOC}
    ${foop1_UI}
)

target_link_libraries(foop1
    ${QT_LIBRARIES}
)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${QT_INCLUDES}
)

# vim:set ts=4 sw=4 et:
