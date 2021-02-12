#include <iostream>
#include <sstream>
#include <istream>
#include <string>
#include <bitset>
#include <iterator>
#include <array>
#include <algorithm>
#include <stdlib.h>
#include <regex>
#include <boost/timer.hpp>
#include "Item.h"

using namespace std;

template<size_t ARRAY_SIZE>
vector<Item> GenerateSubsetsOfSet(array<Item, ARRAY_SIZE> arr, size_t maxWeigth, size_t minCost, bool needPrint);
template<size_t ARRAY_SIZE>
array<Item, ARRAY_SIZE> ParseDataFromFile(string filename);

inline std::ostream& operator<<(std::ostream& os, const Item& item)
{
	os << "{cost: " << item.cost << "  weight: " << item.weight << "}";
	return os;
}



int main()
{
	size_t maxWeight = 0;
	size_t minCost = 0;
	array<Item, 8> arr;
	vector<Item> backpack;
	cout << "Type max weight:";
	cin >> maxWeight;
	cout << "Type min cost:";
	cin >> minCost;

	arr = ParseDataFromFile<8>("backpack.txt");

	for (size_t i = 0; i < arr.size(); ++i)
	{
		cout << arr[i] << endl;
	}
	boost::timer t;
	t.restart();
	backpack = GenerateSubsetsOfSet(arr, maxWeight, minCost, true);
	cout << t.elapsed() << "s" << endl;
	for (size_t i = 1; i < backpack.size(); ++i)
	{
		cout << backpack[i] << endl;
	}
	return 0;
}

size_t GetItemListCost(vector<Item> itemList) {
	size_t totalCost = 0;
	for (size_t i = 0; i < itemList.size(); i++) {
		totalCost += itemList[i].cost;
	}
	return totalCost;
}

size_t GetItemListWeigth(vector<Item> itemList) {
	size_t totalWeight = 0;
	for (size_t i = 0; i < itemList.size(); i++) {
		totalWeight += itemList[i].weight;
	}
	return totalWeight;
}

template<size_t ARRAY_SIZE>
vector<Item> BuildOptimizedBackpack(array<Item, ARRAY_SIZE> items, bitset<ARRAY_SIZE> whatNeedToPack) {
	vector<Item> optimizedBackpack;
	for (size_t i = 0; i < ARRAY_SIZE; i++)
	{
		if (whatNeedToPack[i]) {
			optimizedBackpack.push_back(items[i]);
		}
	}
	return optimizedBackpack;
}

template<size_t ARRAY_SIZE>
vector<Item> GenerateSubsetsOfSet(array<Item, ARRAY_SIZE> arr, size_t maxWeigth, size_t minCost, bool needPrint)
{
	array<Item, ARRAY_SIZE> binArr;
	vector<Item> currentBackpack;
	vector<Item> optimizedBackpack;
	size_t curCost = 0;
	size_t bestCost = 0;

	for (size_t k = 0; k < (1llu << ARRAY_SIZE); ++k) {
		size_t n = 0;
		for (size_t i = 0, j = 1; i < ARRAY_SIZE; ++i, j <<= 1) {
			if (k & j)
				binArr[n++] = arr[i];
		}
		currentBackpack = BuildOptimizedBackpack(arr, bitset<ARRAY_SIZE>(k));
		if (needPrint)
		{
			for (size_t i = 0; i < currentBackpack.size(); ++i)
			{
				cout << currentBackpack[i] << "," << endl;
			}
			cout << "_________________________" << endl;
		}
		
		curCost = GetItemListCost(currentBackpack);
		if ((GetItemListWeigth(currentBackpack) < maxWeigth) 
			&& (curCost > minCost))
		{
			bestCost = curCost;
			optimizedBackpack = currentBackpack;	
		}
	}

	return optimizedBackpack;
}

int GetNumberFromString(string& strWithNums)
{
	smatch searchResult;
	regex rgx("[0-9]+");

	if (!regex_search(strWithNums, searchResult, rgx))
	{
		throw invalid_argument("Error: string without numbers argument");
	}

	string value = searchResult.str();
	strWithNums = searchResult.suffix().str();

	return atoi(value.c_str());
}

template<size_t ARRAY_SIZE>
array<Item, ARRAY_SIZE> ParseDataFromFile(string filename)
{
	array<Item, ARRAY_SIZE> tempArr;
	Item curItem;
	string temp;
	ifstream inputFile(filename, ios::in);
	size_t i = 0;
	inputFile.seekg(0, ios::beg);
	while (getline(inputFile, temp) && i < ARRAY_SIZE)
	{
		if (temp.find_first_of(";", 0) != string::npos)
		{
			continue;
		}
		
		curItem.cost = GetNumberFromString(temp);
		cout << curItem.cost << " ";
		curItem.weight = GetNumberFromString(temp);
		cout << curItem.weight << endl;
		tempArr[i] = curItem;
		i++;
	}

	inputFile.close();
	return tempArr;
}