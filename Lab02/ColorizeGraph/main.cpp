#include <iostream>
#include <optional>
#include "../Lab02/GraphLib.h"

using namespace std;

struct Args
{
	string graphFilename;
};

void ColorizeGraph(const Matrix2D& graph, VertexList& vertexList);
void Print(VertexList& vertexList);
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

	VertexList vertexes(graph.size());
	ColorizeGraph(graph, vertexes);

	Print(vertexes);

	return 0;
}

void ColorizeGraph(const Matrix2D& graph, VertexList& vertexList)
{
	size_t color = 1;
	size_t colorizedVertexes = 0;
	bool canBeColorized = true;
	while (colorizedVertexes < graph.size())
	{
		for (size_t i = 0; i < graph.size(); ++i)
		{
			canBeColorized = !vertexList[i].color;

			if (!canBeColorized)
			{
				continue;
			}

			for (size_t j = 0; j < graph[i].size(); ++j)
			{
				if (graph[i][j] && vertexList[j].color == color)
				{
					canBeColorized = false;
					break;
				}
			}

			if (canBeColorized)
			{
				vertexList[i].color = color;
				++colorizedVertexes;
			}
		}
		++color;
	}
}

void Print(VertexList& vertexList)
{
	for (size_t i = 0; i < vertexList.size(); ++i)
	{
		cout << "Vertex " << i + 1 << " | Color " << vertexList[i].color << endl;
	}
}

optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count" << endl;
		cout << "Usage: ColorizeGraph.exe <graphFileName>" << endl;
		return nullopt;
	}

	Args args;
	args.graphFilename = argv[1];

	return args;
}