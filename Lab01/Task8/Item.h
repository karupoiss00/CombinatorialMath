#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>

struct Item
{
	size_t cost;
	size_t weight;

	Item()
		: cost(0), weight(0)
	{
	}

	bool operator< (const Item& item) const
	{
		if (cost != item.cost)
		{
			return cost < item.cost;
		}

		return weight < item.weight;
	}

	friend std::ostream& operator<< (std::ostream& os, const Item& item);
}; 
