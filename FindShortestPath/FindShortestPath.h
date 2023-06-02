#include <iostream>
#include <vector>
#include <string>
#include "Exceptions.h"
using namespace std;

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



