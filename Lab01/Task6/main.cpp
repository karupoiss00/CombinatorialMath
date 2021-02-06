#include <iostream>
#include <sstream>
#include <bitset>
#include <iterator>
#include <array>
#include <algorithm>
#include <boost/timer.hpp>

using namespace std;

template<size_t ARRAY_SIZE>
void GenerateSubsetsOfSet(array<size_t, ARRAY_SIZE> arr, bool needPrint);

int main()
{
	array<size_t, 16> arr;

	for (size_t i = 1; i < arr.size(); ++i)
	{
		arr[i] = i;
	}
	boost::timer t;
	t.restart();
	GenerateSubsetsOfSet<arr.size()>(arr, true);
	cout << t.elapsed() << "s" << endl;

	return 0;
}


template<size_t ARRAY_SIZE>
void GenerateSubsetsOfSet(array<size_t, ARRAY_SIZE> arr, bool needPrint)
{
	array<size_t, ARRAY_SIZE> binArr;

	for (size_t k = 0; k < (1llu << ARRAY_SIZE); ++k) {
		size_t n = 0;
		if (needPrint)
		{
			cout << std::bitset<ARRAY_SIZE>(k) << endl;
		}
		for (size_t i = 0, j = 1; i < ARRAY_SIZE; ++i, j <<= 1) {

			if (k & j)
				binArr[n++] = arr[i];
		}
	}

}