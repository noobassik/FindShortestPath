#include <iostream>
using namespace std;

class FileNotFoundException : public std::exception {

private:
    string message;


public:

    FileNotFoundException(string msg)
    {
        this->message = msg;
    }


    string what()
    {
        return "Файл не найден: " + message;
    }

};

class InvalidInputException : public std::exception {

private:
    string message;


public:

    InvalidInputException(string msg)
    {
        this->message = msg;
    }


    string what()
    {
        return "Во входном файле " + message;
    }

};