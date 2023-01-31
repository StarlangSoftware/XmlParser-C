//
// Created by Olcay Taner YILDIZ on 30.01.2023.
//

#ifndef XMLPARSER_XMLATTRIBUTE_H
#define XMLPARSER_XMLATTRIBUTE_H

struct xml_attribute{
    char* name;
    char* value;
};

typedef struct xml_attribute Xml_attribute;
typedef Xml_attribute* Xml_attribute_ptr;

Xml_attribute_ptr create_xml_attribute(char* name);
void free_xml_attribute(Xml_attribute_ptr xml_attribute);
void set_xml_attribute_value(Xml_attribute_ptr xml_attribute, char* value);

#endif //XMLPARSER_XMLATTRIBUTE_H
