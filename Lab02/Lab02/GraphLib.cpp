#include "GraphLib.h"

#include <fstream>
#include <sstream>
#include <regex>

using namespace std;

bool LoadGraphFromFile(const string& fileName, Matrix2D& graph)
{
	ifstream strm(fileName);

	if (!strm.is_open())
	{
		cout << "Failed to open " << fileName << " for reading" << endl;
		return false;
	}

	int vertexCount;

	if (!ReadGraphVertexCount(strm, vertexCount))
	{
		cout << "Failed to read count of vertices of graph" << endl;
		return false;
	}

	if (!ReadWeightEdgesGraph(strm, graph, vertexCount))
	{
		cout << "Failed to read weight of edges of graph" << endl;
		return false;
	}

	return true;
}

bool ReadGraphVertexCount(istream& strm, int& count)
{
	string line;

	if (!getline(strm, line))
	{
		return false;
	}

	try
	{
		count = atoi(line.c_str());

		if (count < 2)
		{
			throw;
		}
	}
	catch (...)
	{
		return false;
	}

	return true;
}

bool ResizeMatrix(Matrix2D& matrix, size_t lines, size_t columns, int value)
{
	try
	{
		matrix.resize(lines);

		for (size_t i = 0; i < matrix.size(); ++i)
		{
			matrix[i].resize(columns, value);
		}
	}
	catch (...)
	{
		cout << "Failed to resize matrix" << endl;
		return false;
	}

	return true;
}

bool ReadWeightEdgesGraph(istream& strm, Matrix2D& graph, int vertexCount)
{
	if (!ResizeMatrix(graph, vertexCount, 0))
	{
		return false;
	}

	string line;

	for (int i = 0; i < vertexCount; i++)
	{
		if (!getline(strm, line))
		{
			return false;
		}

		stringstream stream(line);
		graph[i].insert(graph[i].begin(), istream_iterator<int>(stream), istream_iterator<int>());

		if (graph[i].size() != vertexCount)
		{
			return false;
		}
	}

	return true;
}