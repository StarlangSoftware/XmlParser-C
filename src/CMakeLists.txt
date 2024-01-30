cmake_minimum_required(VERSION 3.23)
project(XmlParser)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "-O3")

find_package(data_structure_c REQUIRED)

add_library(XmlParser XmlTextType.h XmlTokenType.h XmlAttribute.c XmlAttribute.h XmlElement.c XmlElement.h XmlDocument.c XmlDocument.h)
target_link_libraries(XmlParser data_structure_c::data_structure_c)
