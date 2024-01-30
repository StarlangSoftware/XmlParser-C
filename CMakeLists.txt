cmake_minimum_required(VERSION 3.23)
project(XmlParser)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O3")

find_package(data_structure_c REQUIRED)

add_library(XmlParser src/XmlTextType.h src/XmlTokenType.h src/XmlAttribute.c src/XmlAttribute.h src/XmlElement.c src/XmlElement.h src/XmlDocument.c src/XmlDocument.h)
target_link_libraries(XmlParser data_structure_c::data_structure_c)
add_executable(XmlParserTest src/XmlTextType.h src/XmlTokenType.h src/XmlAttribute.c src/XmlAttribute.h src/XmlElement.c src/XmlElement.h src/XmlDocument.c src/XmlDocument.h Test/XmlParserTest.c)
target_link_libraries(XmlParserTest data_structure_c::data_structure_c)
