#include "utils.h"

bool isLetter(char ch) {
    return (ch <= 'z' && ch >= 'a') || (ch <= 'Z' && ch >= 'A');
}

bool isDigit(char ch) {
    return (ch <= '9' && ch >= '0');
}

bool isAlphanumeric(char ch) {
    return isLetter(ch) || isDigit(ch);
}