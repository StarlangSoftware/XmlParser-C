//
// Created by Olcay Taner YILDIZ on 30.01.2023.
//

#include <string.h>
#include <Memory/Memory.h>
#include "XmlElement.h"
#include "XmlAttribute.h"

/**
 * Constructor for xml element. Allocates memory and initializes an element.
 * @param name Name of the element
 * @param parent Parent of the Xml Element
 * @return Constructed element
 */
Xml_element_ptr create_xml_element(const char *name, Xml_element_ptr parent) {
    Xml_element_ptr result = malloc_(sizeof(Xml_element), "create_xml_element_1");
    result->name = malloc_(strlen(name) + 1, "create_xml_element_2");
    strcpy(result->name, name);
    result->parent = parent;
    result->attributes = create_array_list();
    result->next_sibling = NULL;
    result->first_child = NULL;
    result->pcData = NULL;
    return result;
}

void free_xml_element(Xml_element_ptr xml_element) {
    if (xml_element->next_sibling != NULL) {
        free_xml_element(xml_element->next_sibling);
    }
    if (xml_element->first_child != NULL) {
        free_xml_element(xml_element->first_child);
    }
    free_(xml_element->name);
    if (xml_element->pcData != NULL){
        free_(xml_element->pcData);
    }
    free_array_list(xml_element->attributes, (void (*)(void *)) free_xml_attribute);
    free_(xml_element);
}

/**
 * Sets the value of an attribute to a given value
 * @param xml_element Xml element
 * @param attribute_name Name of the attribute
 * @param attribute_value New attribute value
 */
void set_attribute_value(Xml_element_ptr xml_element, const char *attribute_name, const char *attribute_value) {
    for (int i = 0; i < xml_element->attributes->size; i++) {
        Xml_attribute_ptr xml_attribute = array_list_get(xml_element->attributes, i);
        if (strcmp(xml_attribute->name, attribute_name) == 0) {
            set_xml_attribute_value(xml_attribute, attribute_value);
        }
    }
}

/**
 * Finds the attribute with the given name of an Xml element
 * @param xml_element Xml element
 * @param[in] attribute_name Name of the attribute
 * @return If the Xml element has such an attribute returns its value, otherwise it returns NULL
 */
char *get_attribute_value(const Xml_element* xml_element, const char *attribute_name) {
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

bool has_attributes(const Xml_element* xml_element) {
    return !is_array_list_empty(xml_element->attributes);
}

int attribute_size(const Xml_element* xml_element) {
    return xml_element->attributes->size;
}

Xml_attribute_ptr get_attribute(const Xml_element* xml_element, int index) {
    return array_list_get(xml_element->attributes, index);
}
