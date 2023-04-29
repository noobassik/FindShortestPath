#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include "x64/FindShortestPath.h"

using namespace std;

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
/*! Считать матрицу с файла
*\param[in,out] adj_matrix - матрица смежности
* return - вектор городов
*/
vector<string> readMatrixFromFile(vector<vector<int>>& adj_matrix)
{
    string line;
    vector<string> labels;
    //открытие файла
    ifstream file;
    file.open("input.csv");
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
    while (getline(file, line)) {
        stringstream ss(line);
        string value;
        int col = 0;
        while (getline(ss, value, ';')) {
            if (value != "" && col > 0) {
                adj_matrix[row][col - 1] = stoi(value);
            }
            col++;
        }
        row++;
    }

    bool allEqual = true;
    bool isLoop = false;
    for (size_t i = 0; i < labels.size(); i++)
    {
        for (size_t j = 0; j < labels.size(); j++)
        {
            for (size_t k = 0; k < labels.size(); k++)
            {
                if (adj_matrix[j][i] != adj_matrix[k][i] and adj_matrix[j][i] != 0 and adj_matrix[k][i] != 0)
                    allEqual = false;
                if (adj_matrix[k][k] != 0)
                    isLoop = true;
            }
        }
    }

    file.close();

    if (isLoop)
        throw InvalidInputException("в таблице смежности  содержится петля");
    if (!allEqual)
        throw InvalidInputException("в таблице смежности неверно указана стоимость бензина в городе прибытия.");



    return labels;
}
/*! Вывод результата в выходной файл
*\param[in] adj_matrix - матрица смежности
*\param[in] result - стоимость кратчайшего маршрута до города N
*/
void outputResultToFile(vector<vector<int>> adj_matrix, int result)
{
    //вывод в файл
    ofstream fout;
    fout.open("output.txt");

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

int main()
{
    setlocale(LC_ALL, "Russian");
    vector<vector<int>> adj_matrix;
    vector<string> labels;
    try
    {
        labels = readMatrixFromFile(adj_matrix);
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
    outputResultToFile(adj_matrix, result);

    return 0;
}
