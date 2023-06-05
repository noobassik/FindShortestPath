/*
 * \file
 * \brief Функции, необходимые для работы с выражениями программы
 * Данный файл содержит функции программы
*/

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Exceptions.h"
using namespace std;

/*! 
 * \brief Определить, является ли строка числом
 * \param[in] str - анализируемая строка
 * \return - является строка числом или нет
*/
bool ifStringIsDigit(const string str);

/*! 
 * \brief Найти стоимость кратчайшего маршрута с заданного источника до последнего города
 * \param[in] adj_matrix - матрица смежности
 * \param[in] V - количество рассматриваемых вершин
 * \param[in] src - источник
 * \return - стоимость кратчайшего маршрута до последнего города
*/
int findShortestPath(vector<vector<int>> adj_matrix, int V, int src);

/*! 
 * \brief Заполнение строки в матрице
 * \param[in, out] adj_matrix - матрица смежности
 * \param[in] labels - вектор городов
 * \param[in, out] row - количество строк
 * \param[in, out] col - количество столбцов
 * \param[in] line - строка, из которой берутся значения
 * \throw InvalidInputException - пустая строка
 * \throw InvalidInputException - лишняя стоимость бензина
 * \throw InvalidInputException - названия городов несимметричны
 * \throw InvalidInputException - названия городов не совпадают
 * \throw InvalidInputException - значениеми таблицы не являются неотрицательные числа
*/
void fillRowInVector(vector<vector<int>>& adj_matrix, vector<string> labels, int& row, int& col, string line);

/*! 
 * \brief Валидация считанной матрицы
 * \param[in] adj_matrix - матрица смежности
 * \param[in] labels - вектор городов
 * \throw InvalidInputException - неверно указана стоимость бензина в городе прибытия
 * \throw InvalidInputException - существует петля
 * \throw InvalidInputException - названия городов несимметричны
 * \throw InvalidInputException - существует дорога в первый город
 * \throw InvalidInputException - существует односторонняя дорога
*/
void matrixValidation(vector<vector<int>>& adj_matrix, vector<string> labels);

/*! 
 * \brief Считать матрицу с файла
 * \param[in,out] adj_matrix - матрица смежности
 * \param[in] inputFilePath - путь к входному файлу
 * \throw FileNotFoundException - не удалось открыть файл по указанному пути	
 * \return - вектор городов
*/
vector<string> readMatrixFromFile(vector<vector<int>>& adj_matrix, const string& inputFilePath);

/*! 
 * \brief Вывод результата в выходной файл
 * \param[in] result - стоимость кратчайшего маршрута до последнего города
 * \param[in] outputFilePath - путь к выходному файлу
 * \throw exception - не удалось создать выходной файл по указанному пути
*/
void outputResultToFile(int result, const string& outputFilePath);



