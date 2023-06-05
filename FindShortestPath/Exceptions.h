/*
 * \file
 * \brief Исключения, необходимые для функционирования программы
*/

#pragma once
#include <exception>
#include <string>

using namespace std;
/*!
* \brief Исключение неверного ввода данных
*/
class FileNotFoundException : public std::exception {

private:
    string message;
public:
    /*!
    * \brief Конструктор исключения
    * \param[in] message - сообщение исключения
    */
    FileNotFoundException(const string& message);
    /*!
    * \brief Получить сообщение исключения
    * \return сообщение исключения
    */
    const char* what() const noexcept override;
};

/*!
* \brief Исключение неверных входных данных
*/
class InvalidInputException : public std::exception {

private:
    /*!
    * \brief сообщение исключения
    */
    string message;
public:
    /*!
    * \brief Конструктор исключения
    * \param[in] message - сообщение исключения
    */
    InvalidInputException(const string& message);
    /*!
    * \brief Получить сообщение исключения
    * \return сообщение исключения
    */
    const char* what() const noexcept override;
};