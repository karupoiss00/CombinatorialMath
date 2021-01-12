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
	array<size_t, 15> v2 = { 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	array<size_t, 20> v3 = { 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };


	cout << "10: " << GetGeneratingPermutationsTime(v1) << "s" << endl;
	cout << "15: " << GetGeneratingPermutationsTime(v2) << "s" << endl;
	cout << "20: " << GetGeneratingPermutationsTime(v3) << "s" << endl;

	return 0;
}