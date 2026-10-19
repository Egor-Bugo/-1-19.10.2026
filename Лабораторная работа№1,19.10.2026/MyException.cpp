#define _CRT_SECURE_NO_WARNINGS
#include "MyException.h"
#include <cstring>

MyException::MyException(const char* msg) {
    strncpy(message, msg, sizeof(message) - 1);
    message[sizeof(message) - 1] = '\0';
}

const char* MyException::getMessage() const {
    return message;
}