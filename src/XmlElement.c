//
// Created by Olcay Taner YILDIZ on 30.01.2023.
//

#include <stdlib.h>
#include <string.h>
#include "XmlElement.h"
#include "XmlAttribute.h"

/**
 * Constructor for xml element. Allocates memory and initializes an element.
 * @param name Name of the element
 * @param parent Parent of the Xml Element
 * @param hasAttributes If true, the element will have attributes, otherwise it won't have.
 * @return Constructed element
 */
Xml_element_ptr create_xml_element(char *name, Xml_element_ptr parent) {
    Xml_element_ptr result = malloc(sizeof(Xml_element));
    result->name = malloc(strlen(name) + 1);
    strcpy(result->name, name);
    result->parent = parent;
    result->attributes = create_array_list();
    result->next_sibling = NULL;
    result->first_child = NULL;
    return result;
}

void free_xml_element(Xml_element_ptr xml_element) {
    if (xml_element->next_sibling != NULL) {
        free_xml_element(xml_element->next_sibling);
    }
    if (xml_element->first_child != NULL) {
        free_xml_element(xml_element->first_child);
    }
    free(xml_element->name);
    free_array_list(xml_element->attributes, (void (*)(void *)) free_xml_attribute);
    free(xml_element);
}

/**
 * Sets the value of an attribute to a given value
 * @param attributeName Name of the attribute
 * @param attributeValue New attribute value
 */
void set_attribute_value(Xml_element_ptr xml_element, char *attribute_name, char *attribute_value) {
    for (int i = 0; i < xml_element->attributes->size; i++) {
        Xml_attribute_ptr xml_attribute = array_list_get(xml_element->attributes, i);
        if (strcmp(xml_attribute->name, attribute_name) == 0) {
            set_xml_attribute_value(xml_attribute, attribute_value);
        }
    }
}

/**
 * Finds the attribute with the given name of an Xml element
 * @param[in] attributeName Name of the attribute
 * @return If the Xml element has such an attribute returns its value, otherwise it returns NULL
 */
char *get_attribute_value(Xml_element_ptr xml_element, char *attribute_name) {
    for (int i = 0; i < xml_element->attributes->size; i++) {
        Xml_attribute_ptr xml_attribute = array_list_get(xml_element->attributes, i);
        if (strcmp(xml_attribute->name, attribute_name) == 0) {
            return xml_attribute->value;
        }
    }
    return NULL;
}

void add_attribute(Xml_element_ptr xml_element, Xml_attribute_ptr xml_attribute) {
    array_list_add(xml_element->attributes, xml_attribute);
}

bool has_attributes(Xml_element_ptr xml_element) {
    return !is_array_list_empty(xml_element->attributes);
}

int attribute_size(Xml_element_ptr xml_element) {
    return xml_element->attributes->size;
}

Xml_attribute_ptr get_attribute(Xml_element_ptr xml_element, int index) {
    return array_list_get(xml_element->attributes, index);
}
