#include <iostream>
#include <vector>
#include <string>
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
        return "���� �� ������: " + message;
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
        return "�� ������� ����� " + message;
    }

};

/*! ����������, �������� �� ������ ������
*\param[in] s - ������������� ������
* return - �������� ������ ������ ��� ���
*/
bool ifStringIsDigit(const string s);

/*! ����� ��������� ����������� �������� � ��������� ��������� �� ���������� ������
*\param[in] adj_matrix - ������� ���������
*\param[in] V - ���������� ��������������� ������
*\param[in] src - ��������
* return - ��������� ����������� �������� �� ���������� ������
*/
int findShortestPath(vector<vector<int>> adj_matrix, int V, int src);

/*! ���������� ������ � �������
*\param[in, out] adj_matrix - ������� ���������
*\param[in] labels - ������ �������
*\param[in] row - ���������� �����
*\param[in, out] col - ���������� ��������
*\param[in] line - ������, �� ������� ������� ��������
*/
void fillRowInVector(vector<vector<int>>& adj_matrix, vector<string> labels, int row, int& col, string line);

/* ��������� ��������� �������
*\param[in] adj_matrix
*\param[in] labels
*/
void matrixValidation(vector<vector<int>>& adj_matrix, vector<string> labels);

/*! ������� ������� � �����
*\param[in,out] adj_matrix - ������� ���������
*\param[in] inputFilePath - ���� � �������� �����
* return - ������ �������
*/
vector<string> readMatrixFromFile(vector<vector<int>>& adj_matrix, const string& inputFilePath);

/*! ����� ���������� � �������� ����
*\param[in] result - ��������� ����������� �������� �� ���������� ������
*\param[in] outputFilePath - ���� � ��������� �����
*/
void outputResultToFile(int result, const string& outputFilePath);



