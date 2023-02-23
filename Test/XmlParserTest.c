//
// Created by Olcay Taner YILDIZ on 31.01.2023.
//

#include <string.h>
#include "../src/XmlDocument.h"

int main() {
    Xml_document_ptr doc = create_xml_document("test.xml");
    parse(doc);
    Xml_element_ptr root = doc->root;
    if (strcmp("frameset", root->name) != 0) {
        printf("Test Failed\n");
    }
    Xml_element_ptr firstChild = root->first_child;
    if (strcmp("role", firstChild->name) != 0) {
        printf("Test Failed\n");
    }
    if (strcmp("ali veli \"deneme yapmak\" = anlamında > bir deyim", firstChild->pcData) != 0) {
        printf("Test Failed\n");
    }
    Xml_element_ptr secondChild = firstChild->next_sibling;
    char *s = get_attribute_value(secondChild, "descr");
    if (strcmp("perceiver, alien \"x3\" to whom?", s) != 0) {
        printf("Test Failed\n");
    }
    s = get_attribute_value(secondChild, "f");
    if (strcmp("PAG", s) != 0) {
        printf("Test Failed\n");
    }
    s = get_attribute_value(secondChild, "n");
    if (strcmp("2", s) != 0) {
        printf("Test Failed\n");
    }
    free_document(doc);
}