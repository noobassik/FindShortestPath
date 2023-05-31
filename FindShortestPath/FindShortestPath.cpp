#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include "FindShortestPath.h"

using namespace std;
/*! Определить, является ли строка числом
*\param[in] s - анализируемая строка
* return - является строка числом или нет
*/
bool ifStringIsDigit(const string s) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] < '0' or s[i] > '9') {
            return false;
        }
    }
    return true;
}
/*! Найти стоимость кратчайшего маршрута с заданного источника до последнего города
*\param[in] adj_matrix - матрица смежности
*\param[in] V - количество рассматриваемых вершин
*\param[in] src - источник
* return - стоимость кратчайшего маршрута до последнего города
*/
int findShortestPath(vector<vector<int>> adj_matrix, int V, int src)
{
    vector<int> dist(V, INT_MAX); // Инициализировать все расстояния как бесконечные
    dist[src] = 0; // Расстояние исходной вершины от самой себя всегда равно 0 

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(0, src));
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        for (int v = 0; v < V; v++) {
            if (adj_matrix[u][v] != 0 && dist[v] > dist[u] + adj_matrix[u][v]) {
                dist[v] = dist[u] + adj_matrix[u][v];
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    return dist.back();
}
void fillRowInVector(vector<vector<int>>& adj_matrix, vector<string> labels, int row, int& col, string line)
{
    stringstream ss(line);
    string value;
    col = 0;
    while (getline(ss, value, ';')) {
        if (value != "" and col > 0)
        {
            if (labels.size() + 1 == col)
                throw InvalidInputException("содержится лишняя стоимость бензина");
            ifStringIsDigit(value) ? adj_matrix[row][col - 1] = stoi(value) : throw InvalidInputException("в таблице смежности неверно указана стоимость бензина ");
        }
        col++;
    }
}
void matrixValidation(vector<vector<int>>& adj_matrix, vector<string> labels)
{
    for (size_t i = 0; i < labels.size(); i++)
    {
        for (size_t j = 0; j < labels.size(); j++)
        {
            for (size_t k = 0; k < labels.size(); k++)
            {
                if (adj_matrix[j][i] != adj_matrix[k][i] and adj_matrix[j][i] != 0 and adj_matrix[k][i] != 0)
                    throw InvalidInputException("в таблице смежности неверно указана стоимость бензина в городе прибытия.");
                if (adj_matrix[k][k] != 0)
                    throw InvalidInputException("в таблице смежности содержится петля");
            }
            if (adj_matrix[i][j] < 0)
                throw InvalidInputException("стоимость бензина не может быть отрицательной");
        }
    }
}
/*! Считать матрицу с файла
*\param[in,out] adj_matrix - матрица смежности
*\param[in] inputFilePath - путь к входному файлу
* return - вектор городов
*/
vector<string> readMatrixFromFile(vector<vector<int>>& adj_matrix, const string& inputFilePath)
{
    string line;
    vector<string> labels;
    //открытие файла
    ifstream file;
    file.open(inputFilePath);
    if (!file) {
        throw FileNotFoundException("input.csv, неверно указан файл с входными данными.");
    }

    //считывание первой строки файла
    getline(file, line);
    stringstream ss(line);

    string label;

    //заполнить вектор названиями городов
    while (getline(ss, label, ';')) {
        if (label != "") {
            labels.push_back(label);
        }
    }
    adj_matrix.resize(labels.size(), vector<int>(labels.size(), 0));
    //заполнение матрицы смежности из файла
    int row = 0;
    int col;
    while (getline(file, line)) {

        fillRowInVector(adj_matrix, labels, row, col, line);
        row++;
    }
    if (row != col - 1)
        throw InvalidInputException("названия городов в таблице смежности несимметричны");


    file.close();
    return labels;
}
/*! Вывод результата в выходной файл
*\param[in] result - стоимость кратчайшего маршрута до последнего города
*\param[in] outputFilePath - путь к выходному файлу
*/
void outputResultToFile(int result, const string& outputFilePath)
{
    //вывод в файл
    ofstream fout;
    fout.open(outputFilePath);

    try {
        if (!fout) {
            throw exception("Неверно указан файл для выходных данных. Возможно указанного расположения не существует или нет прав на запись.");
        }
        fout << result;
    }
    catch (const ofstream::failure& e) {
        cout << "Error: " << e.what() << endl;
    }
    fout.close();
}


int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");

    if (argc != 3)
    {
        std::cerr << "Неправильно указаны параметры для запуска. "
            "Убедитесь, что параметры соотвествуют шаблону: \n"
            << argv[0] << " <path/input_file> <path/output_file>\n";
        return 1;
    }

    std::ifstream inputFile(argv[1]);

    if (!inputFile.is_open()) {
        std::cerr << "Неверно указан файл с входными данными. Возможно, файл не существует." << argv[1] << '\n';
        return 1;
    }

    filesystem::path outputPath = filesystem::path(argv[2]);

    if (!(filesystem::exists(outputPath.parent_path()) &&
        filesystem::is_directory(outputPath.parent_path()) &&
        outputPath.has_filename()))
    {
        std::cerr << "Неверно указан файл для выходных данных. "
            "Возможно, указанного расположения не существует или нет прав на запись." << '\n';
        return 1;
    }

    std::ofstream outputFile(outputPath);

    if (!outputFile.is_open()) {
        std::cerr << "Неверно указан файл для выходных данных. "
            "Возможно, указанного расположения не существует или нет прав на запись." << '\n';
        return 1;
    }

    
    vector<vector<int>> adj_matrix;
    vector<string> labels;
    try
    {
        labels = readMatrixFromFile(adj_matrix, argv[1]);
        matrixValidation(adj_matrix, labels);
    }
    catch (FileNotFoundException e)
    {
        cout << e.what() << endl;
        return 0;   
    }
    catch (InvalidInputException e)
    {
        cout << e.what() << endl;
    }

    int num_nodes = labels.size();

    if (num_nodes == 0)
    {
        return 0;
    }
    int result = findShortestPath(adj_matrix, labels.size(), 0);
    outputResultToFile(result, argv[2]);

    return 0;
}
