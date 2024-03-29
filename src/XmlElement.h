//
// Created by Olcay Taner YILDIZ on 30.01.2023.
//

#ifndef XMLPARSER_XMLELEMENT_H
#define XMLPARSER_XMLELEMENT_H

#include <ArrayList.h>
#include "XmlAttribute.h"

struct xml_element {
    char *name;
    char *pcData;
    Array_list_ptr attributes;
    struct xml_element *parent;
    struct xml_element *first_child;
    struct xml_element *next_sibling;
};

typedef struct xml_element Xml_element;
typedef Xml_element *Xml_element_ptr;

Xml_element_ptr create_xml_element(const char *name, Xml_element_ptr parent);

void free_xml_element(Xml_element_ptr xml_element);

void set_attribute_value(Xml_element_ptr xml_element, const char *attribute_name, const char *attribute_value);

char *get_attribute_value(const Xml_element* xml_element, const char *attribute_name);

void add_attribute(Xml_element_ptr xml_element, Xml_attribute_ptr xml_attribute);

bool has_attributes(const Xml_element* xml_element);

int attribute_size(const Xml_element* xml_element);

Xml_attribute_ptr get_attribute(const Xml_element* xml_element, int index);

#endif //XMLPARSER_XMLELEMENT_H
