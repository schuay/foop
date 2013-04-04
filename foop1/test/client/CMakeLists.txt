set(jsonVariantSocketTest_QTHEADERS
    jsonvariantsockettest.h
)

qt4_wrap_cpp(jsonVariantSocketTest_QTHEADERS_MOC
    ${jsonVariantSocketTest_QTHEADERS}
)

add_executable(jsonVariantSocketTest
    jsonvariantsockettest.cpp
    ${jsonVariantSocketTest_QTHEADERS_MOC}
)

add_dependencies(jsonVariantSocketTest
    foop1_common 
)

target_link_libraries(jsonVariantSocketTest
    ${QT_LIBRARIES}
    ${QT_QTTEST_LIBRARY}
)

add_test(NAME jsonVariantSocketTest
    COMMAND jsonVariantSocketTest
)
