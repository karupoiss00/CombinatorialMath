#include <iostream>
#include <iterator>
#include <array>
#include <algorithm>
#include <boost/timer.hpp>

using namespace std;

template<size_t ARRAY_SIZE>
double GetGeneratingPermutationsTime(array<size_t, ARRAY_SIZE> arr)
{
	boost::timer t;
	t.restart();
	sort(arr.begin(), arr.end());
	do
	{

	} while (next_permutation(arr.begin(), arr.end()));

	double duration = t.elapsed();
	return duration;
}

int main()
{
	array<size_t, 10> v1 = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

	cout << "10: " << GetGeneratingPermutationsTime(v1) << "s" << endl;

	return 0;
}