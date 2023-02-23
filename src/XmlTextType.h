//
// Created by Olcay Taner YILDIZ on 30.01.2023.
//

#ifndef XMLPARSER_XMLELEMENTTYPE_H
#define XMLPARSER_XMLELEMENTTYPE_H

enum xml_text_type {
    XML_TEXT_ATTRIBUTE,
    XML_TEXT_VALUE,
    XML_TEXT_NOT_AVAILABLE
};

typedef enum xml_text_type Xml_text_type;

#endif //XMLPARSER_XMLELEMENTTYPE_H
