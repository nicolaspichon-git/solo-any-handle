# solo-any-handle/tests/CMakeLists.txt

# Collect test sources (exclude main)
file(GLOB_RECURSE SOLO_ANY_HANDLE_TEST_SOURCES
    CONFIGURE_DEPENDS
        "*.cpp"
)

list(REMOVE_ITEM SOLO_ANY_HANDLE_TEST_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/solo_any_handle_boost_testsuite_main.cpp"
)

# Executable test
add_executable(solo_any_handle_boost_testsuite
    solo_any_handle_boost_testsuite_main.cpp
    ${SOLO_ANY_HANDLE_TEST_SOURCES}
)

# include headers
target_include_directories(solo_any_handle_boost_testsuite
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/libs
)

# Link solo-any-handle
target_link_libraries(solo_any_handle_boost_testsuite
    PRIVATE
        solo-any-handle
)

target_compile_features(solo_any_handle_boost_testsuite
    PRIVATE
        cxx_std_14)

set_target_properties(solo_any_handle_boost_testsuite
    PROPERTIES
        CXX_EXTENSIONS OFF
)

target_include_directories(solo_any_handle_boost_testsuite
    PRIVATE
        ${CMAKE_SOURCE_DIR}/external/eggs/include
)

# CTest
add_test(
    NAME solo_any_handle_boost_testsuite
    COMMAND solo_any_handle_boost_testsuite
)
