//
// Created by Olcay Taner YILDIZ on 30.01.2023.
//

#include <stdlib.h>
#include <string.h>
#include "XmlAttribute.h"

Xml_attribute_ptr create_xml_attribute(const char *name) {
    Xml_attribute_ptr result = malloc(sizeof(Xml_attribute));
    result->name = malloc(strlen(name) + 1);
    strcpy(result->name, name);
    result->value = NULL;
    return result;
}

void free_xml_attribute(Xml_attribute_ptr xml_attribute) {
    if (xml_attribute->value != NULL) {
        free(xml_attribute->value);
    }
    free(xml_attribute->name);
    free(xml_attribute);
}

void set_xml_attribute_value(Xml_attribute_ptr xml_attribute, const char *value) {
    if (xml_attribute->value != NULL) {
        free(xml_attribute->value);
    }
    xml_attribute->value = malloc(strlen(value) + 1);
    strcpy(xml_attribute->value, value);
}
