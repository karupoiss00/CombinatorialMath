#include <iostream>
#include <iterator>
#include <array>
#include <algorithm>
#include <boost/timer.hpp>

using namespace std;

struct Element {

	Element() {
		this->value = 0;
		this->isRightDirection = false;
	}

	Element(size_t value, bool rightDir) {
		this->value = value;
		this->isRightDirection = rightDir;
	}

	bool operator<<(Element el) const {
		cout << this->value;
	}
	bool operator<(Element el) const {
		return this->value < el.value;
	}
	bool operator>(Element el) const {
		return this->value > el.value;
	}

	size_t value;
	bool isRightDirection;
};

template<size_t ARRAY_SIZE>
array<size_t, ARRAY_SIZE> ConvertToArrayOfValue(array<Element, ARRAY_SIZE> arr) {
	array<size_t, ARRAY_SIZE> newArr;
	for (size_t i = 0; i < ARRAY_SIZE; i++) {
		newArr[i] = arr[i].value;
	}
	return newArr;
}

template<size_t ARRAY_SIZE>
double GetGeneratingPermutationsTime(array<Element, ARRAY_SIZE> arr)
{
	size_t m = -1;
	size_t mAsValueIndex;
	array<size_t, ARRAY_SIZE> valuesArray = ConvertToArrayOfValue(arr);
	boost::timer t;
	t.restart();
	sort(arr.begin(), arr.end());
	
	while (m != 0)
	{
		copy(valuesArray.begin(), valuesArray.end(), ostream_iterator<size_t>(cout, " "));
		cout << endl;
		m = ARRAY_SIZE - 1;
		while (m > 0 && arr[m] < arr[m - 1])
		{
			m--;
		}
		mAsValueIndex = distance(valuesArray.begin(), find(valuesArray.begin(), valuesArray.end(), m));
		swap(arr[m], arr[mAsValueIndex]);
		valuesArray = ConvertToArrayOfValue(arr);
		for (size_t i = 0; i < arr.size(); i++)
		{
			if (arr[i].value > m)
			{
				arr[i].isRightDirection = !arr[i].isRightDirection;
			}
		}
	}

	double duration = t.elapsed();
	return duration;	
}

int main()
{
	array<Element, 10> arr;

	for (size_t i = 0; i < arr.size(); ++i)
	{
		arr[i].value = i;
		arr[i].isRightDirection = false;
	}

	cout << GetGeneratingPermutationsTime(arr) << "s" << endl;

	return 0;
}