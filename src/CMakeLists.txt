file(GLOB SRCS "*.cpp")

link_libraries(cuttle-parser cuttle-vm)

add_library(cuttle-translator SHARED ${SRCS})
