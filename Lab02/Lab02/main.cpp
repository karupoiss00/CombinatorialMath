#include <iostream>
#include <optional>
#include "GraphLib.h"

using namespace std;

void NumberVertex(const Matrix2D& graph, VertexList& vertexList, size_t& visitCount, int visitNumber);
void InvertEdges(Matrix2D& graph);

struct Args
{
	string graphFilename;
};

optional<Args> ParseArgs(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);

	if (!args)
	{
		return 1;
	}

	Matrix2D graph;

	if (!LoadGraphFromFile(args->graphFilename, graph))
	{
		cout << "Failed to load graph from file" << endl;
		return 1;
	}

	VertexList vertexList(graph.size());
	size_t visitCount = 0;

	NumberVertex(graph, vertexList, visitCount, 0);

	if (visitCount < graph.size())
	{
		cout << "No" << endl;
		return 0;
	}

	InvertEdges(graph);

	vertexList.assign(graph.size(), Vertex());
	visitCount = 0;

	NumberVertex(graph, vertexList, visitCount, 0);

	if (visitCount < graph.size())
	{
		cout << "No" << endl;
		return 0;
	}

	cout << "Yes" << endl;

	return 0;
}

void NumberVertex(const Matrix2D& graph, VertexList& vertexList, size_t& visitCount, int visitNumber)
{
	vertexList[visitNumber].visited = true;

	for (size_t i = 0; i < graph.size(); ++i)
	{
		if (graph[visitNumber][i] < 1 || i == visitNumber)
		{
			continue;
		}

		if (!vertexList[i].visited)
		{
			NumberVertex(graph, vertexList, visitCount, i);
		}
	}

	++visitCount;
}

void InvertEdges(Matrix2D& graph)
{
	for (size_t i = 0; i < graph.size(); ++i)
	{
		for (size_t j = i; j < graph.size(); ++j)
		{
			int temp = graph[j][i];
			graph[j][i] = graph[i][j];
			graph[i][j] = temp;
		}
	}
}

optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count" << endl;
		cout << "Usage: StronglyConnectedGraph.exe <graphFileName>" << endl;
		return nullopt;
	}

	Args args;
	args.graphFilename = argv[1];

	return args;
}