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

bool ifStringIsDigit(const string str)
{
    int i = 0; int c = 0;
    for (; i < str.size(); i++) {
        // Если текущее значение не цифра, то вернуть false
        if (str[i] < '0' or str[i] > '9') {
            return false;
        }
        // Если текущее значение 0 и это первое значение
        if (str[i] == '0' and i == 0) {
            c++;    // Увеличить счетчик нулей
        }
    }
    if (c == 1 and i == c) return true;     // Если значение цифроа 0, то вернуть true
    else if (c == 1) return false;          // Иначе если значение начинается с 0, но не является цифрой 0, то вернуть false
    if (i == 0) return false;               // Если значение пустое, вернуть false
    return true;
}

int findShortestPath(vector<vector<int>> adj_matrix, int V, int src)
{
    vector<int> dist(V, INT_MAX); // Инициализировать все расстояния как бесконечные
    dist[src] = 0;              // Расстояние исходной вершины от самой себя всегда равно 0 

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    // Поместить исходную вершину с расстоянием 0 в приоритетную очередь
    pq.push(make_pair(0, src));
    while (!pq.empty()) {
        // Получить вершину с минимальным расстоянием от приоритетной очереди
        int u = pq.top().second;
        // Удаляем вершину из приоритетной очереди
        pq.pop();
        // Перебираем все соседние вершины u
        for (int v = 0; v < V; v++) {
            // Проверяем, есть ли ребро между u и v и найден ли более короткий путь к v
            if (adj_matrix[u][v] != 0 && dist[v] > dist[u] + adj_matrix[u][v]) {
                // Обновить расстояние v более коротким путем
                dist[v] = dist[u] + adj_matrix[u][v];
                // Поместить обновленное расстояние и v в приоритетную очередь  
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    // Вернуть кратчайшее расстояние до последней вершины графа
    return dist.back();
}

void fillRowInVector(vector<vector<int>>& adj_matrix, vector<string> labels, int &row, int& col, string line)
{
    if (line.size() < 1)
        throw InvalidInputException("Строка не должна быть пустой");
    stringstream ss(line);
    string value;
    col = 0;
    // Перебрать все символы в строке по заданному разделителю
    while (getline(ss, value, ';')) {
        if (value != "")    // Если символ не является пустой строкой
        {
            if (col > 0)    // Если рассматривается не первый символ строки
            {
                // Если существует лишняя стоимость бензина, то выдать исключение
                if (labels.size() + 1 == col)
                    throw InvalidInputException("содержится лишняя стоимость бензина");
                // Если количество строк совпадает с количеством городов (row при корректных данных меньше количества городов на единицу), то выдать исключение
                if (row == labels.size())
                    throw InvalidInputException("названия городов в таблице смежности несимметричны");
                // Если символ является числом, то записать его в матрицу смежности, иначе выдать исключение
                ifStringIsDigit(value) ? adj_matrix[row][col - 1] = stoi(value) : throw InvalidInputException("значениеми таблицы должны являеться неотрицательные числа");
            }
            else if (row == labels.size())
                throw InvalidInputException("названия городов в таблице смежности несимметричны");
            else if (col == 0 and labels[row] != value)     // Если названия городов не совпадают
                throw InvalidInputException("названия городов не совпадают");
        }
        else                // Иначе выдать исключение
            throw InvalidInputException("значениеми таблицы должны являеться неотрицательные числа");
        col++;
    }
    row++;
}

void matrixValidation(vector<vector<int>>& adj_matrix, vector<string> labels)
{
    int zeroCounter = 0;    // Счетчик нулевых значений в строке 
    for (size_t i = 0; i < labels.size(); i++)
    {
        for (size_t j = 0; j < labels.size(); j++)
        {
            for (size_t k = 0; k < labels.size(); k++)
            {
                // Если в городе прибытия неверно указана стоимость в матрице смежности (в одном столбце значения либо равны, либо нулевые)
                if (adj_matrix[j][i] != adj_matrix[k][i] and adj_matrix[j][i] != 0 and adj_matrix[k][i] != 0)
                    throw InvalidInputException("в таблице смежности неверно указана стоимость бензина в городе прибытия.");
                // Если существует дорога из города в этот же город (петля)
                if (adj_matrix[k][k] != 0)
                    throw InvalidInputException("в таблице смежности содержится петля");
                // Если последняя строка содержит нули, то увеличить счетчик
                if (adj_matrix[labels.size() - 1][k] == 0)
                    zeroCounter++;
            }
            // Если счетчик нулей равен количеству городов, то выдать исключение
            if (zeroCounter == labels.size())
                throw InvalidInputException("названия городов в таблице смежности несимметричны");
            // Если существует дорога в первый город (первый столбец должен состоять из нулей)
            if (adj_matrix[i][0] != 0)
                throw InvalidInputException("дороги в первый город быть не должно");
            // Если существует односторонняя дорога, кроме первого города, то выдать исключение
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
    ifstream file;
    file.open(inputFilePath);   // Открыть файл по указанному пути
    // Если файл открыть не удалось, то выдать исключение
    if (!file) {
        throw FileNotFoundException("input.csv, неверно указан файл с входными данными.");
    }
    // Считывание первой строки файла
    getline(file, line);
    stringstream ss(line);

    string label;

    // Заполнить вектор названиями городов
    while (getline(ss, label, ';')) {
        if (label != "") {
            labels.push_back(label);
        }
    }
    adj_matrix.resize(labels.size(), vector<int>(labels.size(), 0));
    // Заполнение матрицы смежности из файла
    int row = 0;
    int col;
    // Пока в файле есть строки
    while (getline(file, line)) {
        // Заполнить матрицу построчно
        fillRowInVector(adj_matrix, labels, row, col, line);
    }
    // Закрыть файл
    file.close();
    // Вернуть вектор городов
    return labels;
}

void outputResultToFile(int result, const string& outputFilePath)
{
    ofstream fout;
    fout.open(outputFilePath);  // Создать выходной файл по указанному пути

    try {
        // Если файл не удалось создать, то выдать исключение
        if (!fout) {
            throw exception("Неверно указан файл для выходных данных. Возможно указанного расположения не существует или нет прав на запись.");
        }
        // Записать результат в файл
        fout << result;
    }
    catch (const ofstream::failure& e) {
        cout << "Error: " << e.what() << endl;
    }
    // Закрыть файл
    fout.close();
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
    // Если количество аргументов командной строки не равно трем, то выдать ошибку
    if (argc != 3)
    {
        std::cerr << "Неправильно указаны параметры для запуска. "
            "Убедитесь, что параметры соотвествуют шаблону: \n"
            << argv[0] << " <path/input_file> <path/output_file>\n";
        return 1;
    }
    // Задать второй аргумент командной строки как путь к входному файлу
    std::ifstream inputFile(argv[1]);
    // Если входной файл не удалось открыть по указанному пути, то выдать ошибку
    if (!inputFile.is_open()) {
        std::cerr << "Неверно указан файл с входными данными. Возможно, файл не существует." << argv[1] << '\n';
        return 1;
    }
    // Задать третий аргумент командной строки как путь к выходному файлу
    filesystem::path outputPath = filesystem::path(argv[2]);
    // Если выходной файл не может существовать по указанному пути, то выдать ошибку
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
        return 0;
    }

    int result = findShortestPath(adj_matrix, labels.size(), 0);
    outputResultToFile(result, argv[2]);

    return 0;
}
