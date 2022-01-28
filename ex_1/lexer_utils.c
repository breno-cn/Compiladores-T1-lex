#include "lexer_utils.h"

int isLowerCaseAlpha(char c) {
    return c >= 'a' && c <= 'z';
}

int isUpperCaseAlpha(char c) {
    return c >= 'A' && c <= 'Z';
}

int isDigit(char c) {
    return c >= '0' && c <= '9';
}

int isWhitespace(char c) {
    return c == ' ' || c == '\t';
}

int isLineBreak(char c) {
    return c == '\n';
}

int isSingleLineDigest(char c) {
    return isLowerCaseAlpha(c) || isUpperCaseAlpha(c) || isDigit(c) || isWhitespace(c);
}

int isMultiLineDigest(char c) {
    return isLowerCaseAlpha(c) || isUpperCaseAlpha(c) || isDigit(c) || isWhitespace(c) || isLineBreak(c);
}
