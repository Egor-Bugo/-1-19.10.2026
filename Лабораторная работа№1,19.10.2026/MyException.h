#pragma once
#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H
class MyException {
private:
    char message[256];
public:
    MyException(const char* msg);
    const char* getMessage() const;
};

#endif