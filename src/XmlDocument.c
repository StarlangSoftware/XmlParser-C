//
// Created by Olcay Taner YILDIZ on 30.01.2023.
//

#include <string.h>
#include <Memory/Memory.h>
#include "XmlDocument.h"


/**
 * Creates an empty xml document.
 * @param file_name Name of the xml file
 * @return Empty xml document. Xml file is not parsed yet.
 */
Xml_document_ptr create_xml_document(const char *file_name) {
    Xml_document_ptr result = malloc_(sizeof(Xml_document), "create_xml_document_1");
    result->file_name = malloc_(strlen(file_name) + 1, "create_xml_document_2");
    strcpy(result->file_name, file_name);
    result->root = NULL;
    result->last_read_token_type = XML_END;
    return result;
}

void free_document(Xml_document_ptr xml_document) {
    fclose(xml_document->input_stream);
    free_xml_element(xml_document->root);
    free_(xml_document->file_name);
    free_(xml_document);
}

/**
 * Reads a token character by character from xml file.
 * @param previousChar Previous character read
 * @param nextChar The character after the token
 * @param extraAllowed If true, space or slash is allowed in the token, otherwise it is not allowed
 * @return Token read
 */
char *read_token(const Xml_document* xml_document,
                 char previousChar,
                 char *nextChar,
                 int extraAllowed,
                 int quotaAllowed) {
    char *buffer;
    char *result = NULL;
    buffer = calloc_(1000, sizeof(char), "read_token_1");
    char ch = previousChar;
    int index = 0;
    while ((ch != '\'' || extraAllowed) && (ch != '\"' || quotaAllowed) && (ch != '=' || quotaAllowed) &&
           (ch != ' ' || extraAllowed) && (ch != '/' || extraAllowed) && (ch != EOF) && (ch != '<') &&
           (ch != '>' || quotaAllowed)) {
        buffer[index] = ch;
        index++;
        ch = fgetc(xml_document->input_stream);
    }
    *nextChar = ch;
    if (strlen(buffer) > 0){
        result = malloc_(strlen(buffer) + 1, "read_token_2");
        strcpy(result, buffer);
    }
    free_(buffer);
    return result;
}

/**
 * Parses a tag like <mytag> or </mytag>
 * @return Token read
 */
char *parse_tag(Xml_document_ptr xml_document) {
    char *token;
    char ch;
    ch = fgetc(xml_document->input_stream);
    if (ch == '/') {
        xml_document->last_read_token_type = XML_CLOSING_TAG_WITHOUT_ATTRIBUTES;
        ch = fgetc(xml_document->input_stream);
    } else {
        xml_document->last_read_token_type = XML_OPENING_TAG_WITH_ATTRIBUTES;
    }
    token = read_token(xml_document, ch, &ch, 0, 0);
    if (ch == '>' && xml_document->last_read_token_type == XML_OPENING_TAG_WITH_ATTRIBUTES) {
        xml_document->last_read_token_type = XML_OPENING_TAG_WITHOUT_ATTRIBUTES;
    }
    if (xml_document->last_read_token_type == XML_CLOSING_TAG_WITHOUT_ATTRIBUTES && ch != '>') {
        xml_document->last_read_token_type = XML_END;
        free_(token);
        return NULL;
    } else {
        return token;
    }
}

/**
 * Parses an attribute value like "attribute value" or 'attribute value'
 * @return Attribute value read
 */
char *parse_attribute_value(Xml_document_ptr xml_document) {
    char *token;
    char ch;
    ch = fgetc(xml_document->input_stream);
    if (ch == '\"') {
        xml_document->last_read_token_type = XML_ATTRIBUTE_VALUE;
        return NULL;
    }
    token = read_token(xml_document, ch, &ch, 1, 0);
    if (ch != '\"') {
        free_(token);
        xml_document->last_read_token_type = XML_END;
        return "";
    }
    xml_document->last_read_token_type = XML_ATTRIBUTE_VALUE;
    return token;
}

/**
 * Parses a tag like />
 * @return nullptr
 */
char *parse_empty_tag(Xml_document_ptr xml_document) {
    char ch;
    ch = fgetc(xml_document->input_stream);
    if (ch != '>') {
        xml_document->last_read_token_type = XML_END;
    } else {
        xml_document->last_read_token_type = XML_CLOSING_TAG_WITH_ATTRIBUTES;
    }
    return NULL;
}

/**
 * Gets next token from file.
 * @return Token read. If not successful, returns empty string.
 */
char *get_next_token(Xml_document_ptr xml_document, Xml_text_type xml_text_type) {
    char ch;
    char *token;
    ch = fgetc(xml_document->input_stream);
    if (ch == EOF) {
        xml_document->last_read_token_type = XML_END;
        return NULL;
    }
    while (ch == ' ' || ch == '\t' || ch == '\n') {
        ch = fgetc(xml_document->input_stream);
    }
    switch (ch) {
        case '<':
            return parse_tag(xml_document);
        case '\"':
            if (xml_text_type == XML_TEXT_VALUE) {
                token = read_token(xml_document, ch, &ch, 1, 1);
                xml_document->last_read_token_type = XML_TEXT;
                ungetc(ch, xml_document->input_stream);
                return token;
            } else {
                return parse_attribute_value(xml_document);
            }
        case '/':
            return parse_empty_tag(xml_document);
        case '=':
            if (xml_text_type == XML_TEXT_VALUE) {
                token = read_token(xml_document, ch, &ch, 1, 1);
                xml_document->last_read_token_type = XML_TEXT;
                ungetc(ch, xml_document->input_stream);
                return token;
            } else {
                xml_document->last_read_token_type = XML_EQUAL;
            }
            break;
        case '>':
            if (xml_text_type == XML_TEXT_VALUE) {
                token = read_token(xml_document, ch, &ch, 1, 1);
                xml_document->last_read_token_type = XML_TEXT;
                ungetc(ch, xml_document->input_stream);
                return token;
            } else {
                xml_document->last_read_token_type = XML_OPENING_TAG_FINISH;
            }
            return NULL;
        default  :
            if (xml_text_type == XML_TEXT_VALUE) {
                token = read_token(xml_document, ch, &ch, 1, 1);
            } else {
                token = read_token(xml_document, ch, &ch, 1, 0);
            }
            xml_document->last_read_token_type = XML_TEXT;
            ungetc(ch, xml_document->input_stream);
            return token;
    }
    return NULL;
}

/**
 * Parses given xml document
 */
void parse(Xml_document_ptr xml_document) {
    Xml_text_type text_type = XML_TEXT_ATTRIBUTE;
    int sibling_closed = 0;
    char *token;
    Xml_attribute_ptr xml_attribute;
    Xml_element_ptr sibling = NULL, current = NULL, parent = NULL;
    xml_document->input_stream = fopen(xml_document->file_name, "r");
    token = get_next_token(xml_document, text_type);
    while (xml_document->last_read_token_type != XML_END) {
        switch (xml_document->last_read_token_type) {
            case XML_OPENING_TAG_WITH_ATTRIBUTES:
            case XML_OPENING_TAG_WITHOUT_ATTRIBUTES:
                current = create_xml_element(token, parent);
                if (parent) {
                    if (sibling && sibling_closed) {
                        sibling->next_sibling = current;
                        sibling = current;
                    } else {
                        parent->first_child = current;
                    }
                } else {
                    if (!xml_document->root) {
                        xml_document->root = current;
                    }
                }
                parent = current;
                sibling_closed = 0;
                if (xml_document->last_read_token_type == XML_OPENING_TAG_WITH_ATTRIBUTES) {
                    text_type = XML_TEXT_ATTRIBUTE;
                } else {
                    text_type = XML_TEXT_VALUE;
                }
                break;
            case XML_OPENING_TAG_FINISH:
                text_type = XML_TEXT_VALUE;
                sibling_closed = 0;
                break;
            case XML_CLOSING_TAG_WITH_ATTRIBUTES:
                sibling = current;
                parent = current->parent;
                text_type = XML_TEXT_VALUE;
                sibling_closed = 1;
                break;
            case XML_CLOSING_TAG_WITHOUT_ATTRIBUTES:
                if (strcmp(token, current->name) == 0) {
                    sibling = current;
                    parent = current->parent;
                } else {
                    if (strcmp(token, current->parent->name) == 0) {
                        sibling = parent;
                        parent = current->parent->parent;
                        current = current->parent;
                    }
                }
                sibling_closed = 1;
                text_type = XML_TEXT_VALUE;
                break;
            case XML_ATTRIBUTE_VALUE:
                if (token != NULL) {
                    token = replace_escape_characters(token);
                    set_xml_attribute_value(xml_attribute, token);
                } else {
                    set_xml_attribute_value(xml_attribute, "");
                }
                add_attribute(current, xml_attribute);
                text_type = XML_TEXT_ATTRIBUTE;
                break;
            case XML_EQUAL:
                text_type = XML_TEXT_NOT_AVAILABLE;
                break;
            case XML_TEXT:
                if (text_type == XML_TEXT_ATTRIBUTE) {
                    xml_attribute = create_xml_attribute(token);
                } else {
                    if (text_type == XML_TEXT_VALUE) {
                        token = replace_escape_characters(token);
                        if (token != NULL){
                            current->pcData = malloc_((strlen(token) + 1) * sizeof(char), "parse");
                            strcpy(current->pcData, token);
                        } else {
                            current->pcData = NULL;
                        }
                    }
                }
                break;
            case XML_END:
                break;
        }
        if (token != NULL){
            free_(token);
        }
        token = get_next_token(xml_document, text_type);
    }
    fclose(xml_document->input_stream);
}

char *replace_word(char *s, const char *old_word, const char *new_word) {
    if (s == NULL){
        return s;
    }
    char *result, *start = s;
    int i, count = 0;
    int new_word_length = strlen(new_word);
    int old_word_length = strlen(old_word);
    for (i = 0; s[i] != '\0'; i++) {
        if (strstr(&s[i], old_word) == &s[i]) {
            count++;
            i += old_word_length - 1;
        }
    }
    if (count == 0) {
        return s;
    }
    result = (char *) malloc_(i + count * (new_word_length - old_word_length) + 1, "replace_word");
    i = 0;
    while (*s) {
        if (strstr(s, old_word) == s) {
            strcpy(&result[i], new_word);
            i += new_word_length;
            s += old_word_length;
        } else {
            result[i++] = *s++;
        }
    }
    result[i] = '\0';
    free_(start);
    return result;
}

char *replace_escape_characters(char *token) {
    token = replace_word(token, "&quot;", "\"");
    token = replace_word(token, "&amp;", "&");
    token = replace_word(token, "&lt;", "<");
    token = replace_word(token, "&gt;", ">");
    return replace_word(token, "&apos;", "'");
}
