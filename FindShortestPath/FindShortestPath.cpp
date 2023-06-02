#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include "FindShortestPath.h"
#include "Exceptions.h" 

using namespace std;

bool ifStringIsDigit(const string s)
{
    int i = 0; int c = 0;
    for (; i < s.size(); i++) {
        // Если текущим значением не является цифра - вернуть false
        if (s[i] < '0' || s[i] > '9') {
            return false;
        }
        // Если текущим значением является 0 и это первое значение строки
        if (s[i] == '0' && i == 0) {
            c++; // Увеличить количество 0
        }
    }
    if (c == 1 && i == c) return true; // Если значение является цифрой 0 - вернуть true;
    else if (c == 1) return false; // Иначе Если значение начинается с 0, но не является цифрой 0 - вернуть false
    if (i == 0) return false; // Если значение пустое - вернуть false
    return true;
}

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

void fillRowInVector(vector<vector<int>>& adj_matrix, vector<string> labels, int &row, int& col, string line)
{
    if (line.size() < 1)
        throw InvalidInputException("Строка не должна быть пустой");
    stringstream ss(line);
    string value;
    col = 0;
    while (getline(ss, value, ';')) {
        if (value != "")
        {
            if (col > 0)
            {
                if (labels.size() + 1 == col)
                    throw InvalidInputException("содержится лишняя стоимость бензина");
                if (row == labels.size())
                    throw InvalidInputException("названия городов в таблице смежности несимметричны");
                ifStringIsDigit(value) ? adj_matrix[row][col - 1] = stoi(value) : throw InvalidInputException("значениеми таблицы должны являеться неотрицательные числа");
            }
        }
        else
            throw InvalidInputException("значениеми таблицы должны являеться неотрицательные числа");
        col++;
    }
    row++;
    if (labels.size() == row and row != col - 1)
        throw InvalidInputException("названия городов в таблице смежности несимметричны");
}

void matrixValidation(vector<vector<int>>& adj_matrix, vector<string> labels)
{
    int zeroCounter = 0;
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
                if (adj_matrix[labels.size() - 1][k] == 0)
                    zeroCounter++;
            }
            if (zeroCounter == labels.size())
                throw InvalidInputException("названия городов в таблице смежности несимметричны");

            if (adj_matrix[i][0] != 0)
                throw InvalidInputException("дороги в первый город быть не должно");

            if (((adj_matrix[i][j] == 0 and i > 0) and (adj_matrix[j][i] != 0 and j > 0)) or ((adj_matrix[i][j] != 0 and i > 0) and (adj_matrix[j][i] == 0 and j > 0))) {
                throw InvalidInputException("Дороги могут быть только двусторонними. "
                    "Убедитесь, что существуют оба пути между городами.\n");
            }
        }
    }
}

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
    }

    file.close();
    return labels;
}

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
