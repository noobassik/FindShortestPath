#include <iostream>
#include <vector>
#include <string>
#include "Exceptions.h"
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
        return "Во входном файле: " + message;
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
        return "входные данные " + message;
    }

};

/*! Определить, является ли строка числом
*\param[in] str - анализируемая строка
* return - является строка числом или нет
*/
bool ifStringIsDigit(const string str);

/*! Найти стоимость кратчайшего маршрута с заданного источника до последнего города
*\param[in] adj_matrix - матрица смежности
*\param[in] V - количество рассматриваемых вершин
*\param[in] src - источник
* return - стоимость кратчайшего маршрута до последнего города
*/
int findShortestPath(vector<vector<int>> adj_matrix, int V, int src);

/*! Заполнение строки в матрице
*\param[in, out] adj_matrix - матрица смежности
*\param[in] labels - вектор городов
*\param[in, out] row - количество строк
*\param[in, out] col - количество столбцов
*\param[in] line - строка, из которой берутся значения
*/
void fillRowInVector(vector<vector<int>>& adj_matrix, vector<string> labels, int& row, int& col, string line);

/* Валидация считанной матрицы
*\param[in] adj_matrix - матрица смежности
*\param[in] labels - вектор городов
*/
void matrixValidation(vector<vector<int>>& adj_matrix, vector<string> labels);

/*! Считать матрицу с файла
*\param[in,out] adj_matrix - матрица смежности
*\param[in] inputFilePath - путь к входному файлу
* return - вектор городов
*/
vector<string> readMatrixFromFile(vector<vector<int>>& adj_matrix, const string& inputFilePath);

/*! Вывод результата в выходной файл
*\param[in] result - стоимость кратчайшего маршрута до последнего города
*\param[in] outputFilePath - путь к выходному файлу
*/
void outputResultToFile(int result, const string& outputFilePath);



