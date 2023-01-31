cmake_minimum_required(VERSION 3.23)
project(XmlParser C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "-O3")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_library(XmlParser src/XmlTextType.h src/XmlTokenType.h src/XmlAttribute.c src/XmlAttribute.h src/XmlElement.c src/XmlElement.h src/XmlDocument.c src/XmlDocument.h)
target_link_libraries(XmlParser ${CONAN_LIBS})
