//
// Created by Olcay Taner YILDIZ on 30.01.2023.
//

#include <string.h>
#include "XmlAttribute.h"
#include "Memory/Memory.h"

Xml_attribute_ptr create_xml_attribute(const char *name) {
    Xml_attribute_ptr result = malloc_(sizeof(Xml_attribute));
    result->name = malloc_(strlen(name) + 1);
    strcpy(result->name, name);
    result->value = NULL;
    return result;
}

void free_xml_attribute(Xml_attribute_ptr xml_attribute) {
    if (xml_attribute->value != NULL) {
        free_(xml_attribute->value);
    }
    free_(xml_attribute->name);
    free_(xml_attribute);
}

void set_xml_attribute_value(Xml_attribute_ptr xml_attribute, const char *value) {
    if (xml_attribute->value != NULL) {
        free_(xml_attribute->value);
    }
    xml_attribute->value = malloc_(strlen(value) + 1);
    strcpy(xml_attribute->value, value);
}
