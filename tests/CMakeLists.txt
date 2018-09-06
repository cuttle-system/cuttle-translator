include_directories("../src" ${Boost_INCLUDE_DIR})
link_libraries(cuttle-translator ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

file(GLOB_RECURSE TEST_SRCS "*.cpp")

add_executable(cuttle-translator-tests ${TEST_SRCS})