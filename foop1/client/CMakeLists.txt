set(foop1_client_SRCS
    cellitem.cpp
    main.cpp
    mainwindow.cpp
    scene.cpp
)

qt4_wrap_cpp(foop1_client_MOC
    mainwindow.h
    scene.h
)

qt4_wrap_ui(foop1_client_UI
    mainwindow.ui
)

add_executable(foop1_client
    ${foop1_client_SRCS}
    ${foop1_client_MOC}
    ${foop1_client_UI}
)

target_link_libraries(foop1_client
    ${QT_LIBRARIES}
    ${COMMON_LIBRARIES}
)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${QT_INCLUDES}
    ${COMMON_INCLUDES}
)

# vim:set ts=4 sw=4 et:
