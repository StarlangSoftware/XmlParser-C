//
// Created by Olcay Taner YILDIZ on 30.01.2023.
//

#ifndef XMLPARSER_XMLDOCUMENT_H
#define XMLPARSER_XMLDOCUMENT_H

#include <stdio.h>
#include "XmlTokenType.h"
#include "XmlTextType.h"
#include "XmlElement.h"

struct xml_document {
    char *file_name;
    FILE *input_stream;
    Xml_token_type last_read_token_type;
    Xml_element_ptr root;
};

typedef struct xml_document Xml_document;
typedef Xml_document *Xml_document_ptr;

Xml_document_ptr create_xml_document(char *file_name);

void free_document(Xml_document_ptr xml_document);

char *read_token(Xml_document_ptr xml_document, char previousChar, char *nextChar, int extraAllowed, int quotaAllowed);

char *parse_tag(Xml_document_ptr xml_document);

char *parse_attribute_value(Xml_document_ptr xml_document);

char *parse_empty_tag(Xml_document_ptr xml_document);

char *get_next_token(Xml_document_ptr xml_document, Xml_text_type xml_text_type);

void parse(Xml_document_ptr xml_document);

char *replace_escape_characters(char *token);

char *replace_word(char *s, const char *oldW, const char *newW);

#endif //XMLPARSER_XMLDOCUMENT_H
