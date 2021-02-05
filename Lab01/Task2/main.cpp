#include <iostream>
#include <iterator>
#include <array>
#include <algorithm>
#include <boost/timer.hpp>

using namespace std;
/*
template<size_t ARRAY_SIZE>
double GetGeneratingPermutationsTime(array<size_t, ARRAY_SIZE> arr)
{
	int m = -1;
	int maxElement = 0;
	array<int, ARRAY_SIZE> directions;
	for (size_t i = 0; i < directions.size(); ++i)
	{
		directions[i] = -1;
	}
	arr[0] = ARRAY_SIZE + 1;
	directions[1] = 0;
	array<size_t, ARRAY_SIZE> currentPermutation = arr;
	array<size_t, ARRAY_SIZE> reversedCurrentPermutation = arr;
	boost::timer t;
	t.restart();
	m = ARRAY_SIZE - 1;
	maxElement = ARRAY_SIZE - 1;
	while (m != 1)
	{
		copy(currentPermutation.begin(), currentPermutation.end(), std::ostream_iterator<size_t>(std::cout, " "));
		cout << endl << reversedCurrentPermutation[9] << endl;
		m = maxElement;
		cout  << "curr perm " << currentPermutation[reversedCurrentPermutation[m] + directions[m]] << "< "<< m << endl;
		while (currentPermutation[reversedCurrentPermutation[m] + directions[m]] > m)
		{
			directions[m] = -directions[m];
			m--;
		}
		swap(currentPermutation[m], currentPermutation[m + directions[m]]);
		swap(reversedCurrentPermutation[currentPermutation[reversedCurrentPermutation[m]]], reversedCurrentPermutation[m]);
		for (size_t i = 0; i < directions.size(); i++)
		{
			if (arr[i] > m)
			{
				directions[i] = -directions[i];
			}
		}
	}

	double duration = t.elapsed();
	return duration;
}*/

template<size_t ARRAY_SIZE>
double GetGeneratingPermutationsTime(array<size_t, ARRAY_SIZE> arr)
{
	array<size_t, ARRAY_SIZE> reversedArr = arr;
	array<int, ARRAY_SIZE> directions;
	int m = ARRAY_SIZE + 1;
	for (size_t i = 0; i < directions.size(); ++i)
	{
		directions[i] = -1;
	}
	directions[1] = 0;
 	arr[0] = m;
	arr[ARRAY_SIZE - 1] = m;	
	boost::timer t;
	t.restart();
	while (m != 1)
	{
		//copy(arr.begin(), arr.end(), std::ostream_iterator<size_t>(std::cout, " "));
		//cout << endl;
		m = ARRAY_SIZE - 2;
		while (arr[reversedArr[m] + directions[m]] > m)
		{
			directions[m] = -directions[m];
			m--;
		}
		swap(arr[reversedArr[m]], arr[reversedArr[m] + directions[m]]);
		swap(reversedArr[arr[reversedArr[m]]], reversedArr[m]);
	}

	double duration = t.elapsed();
	return duration;
}


int main()
{
	array<size_t, 12> arr10;
	for (size_t i = 1; i < arr10.size(); ++i)
	{
		arr10[i] = i;
	}

	array<size_t, 15> arr15;
	for (size_t i = 1; i < arr15.size(); ++i)
	{
		arr15[i] = i;
	}

	array<size_t, 22> arr20;
	for (size_t i = 1; i < arr20.size(); ++i)
	{
		arr20[i] = i;
	}

	//cout << GetGeneratingPermutationsTime<arr10.size()>(arr10) << "s" << endl;
	cout << GetGeneratingPermutationsTime<arr15.size()>(arr15) << "s" << endl;
	//cout << GetGeneratingPermutationsTime<arr20.size()>(arr20) << "s" << endl;

	return 0;
}