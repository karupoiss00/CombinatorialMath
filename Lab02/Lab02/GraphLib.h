#pragma once
#include <iostream>
#include <utility>
#include <vector>

struct Vertex
{
	Vertex()
		: number(-1), color(0), visited(false)
	{}

	int number;
	int color;

	bool visited;
};

typedef std::vector<std::vector<int>> Matrix2D;
typedef std::vector<Vertex> VertexList;

bool LoadGraphFromFile(const std::string& fileName, Matrix2D& graph);
bool ReadGraphVertexCount(std::istream& strm, int& count);
bool ReadWeightEdgesGraph(std::istream& strm, Matrix2D& graph, int vertexCount);
bool ResizeMatrix(Matrix2D& matrix, size_t lines, size_t columns, int value = 0);