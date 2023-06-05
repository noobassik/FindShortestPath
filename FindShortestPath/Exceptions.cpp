#include <exception>
#include <string>
#include "Exceptions.h"

using namespace std;

FileNotFoundException::FileNotFoundException(const string& message) : message(message) {}

const char* FileNotFoundException::what() const noexcept {
	return message.c_str();
}

InvalidInputException::InvalidInputException(const string& message) : message(message) {}

const char* InvalidInputException::what() const noexcept {
	return message.c_str();
}