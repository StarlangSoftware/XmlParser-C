//
// Created by Olcay Taner YILDIZ on 30.01.2023.
//

#ifndef XMLPARSER_XMLTOKENTYPE_H
#define XMLPARSER_XMLTOKENTYPE_H

enum xml_token_type{
    XML_OPENING_TAG_WITH_ATTRIBUTES,
    XML_OPENING_TAG_WITHOUT_ATTRIBUTES,
    XML_OPENING_TAG_FINISH,
    XML_CLOSING_TAG_WITH_ATTRIBUTES,
    XML_CLOSING_TAG_WITHOUT_ATTRIBUTES,
    XML_ATTRIBUTE_VALUE,
    XML_EQUAL,
    XML_TEXT,
    XML_END
};

typedef enum xml_token_type Xml_token_type;
#endif //XMLPARSER_XMLTOKENTYPE_H