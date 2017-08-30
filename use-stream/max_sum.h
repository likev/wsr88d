#pragma once

#ifndef _MAX_SUM
#define _MAX_SUM

#include <vector>
#include <algorithm>

template<typename T>
struct MaxRange
{
	unsigned left = 0, right = 0, top = 0, bottom = 0;
	T value = 0;
};

template<typename T1, typename T2>
MaxRange<T1> max_sum_subarray(const std::vector<T2> & arr) {
	T1 endsum = 0;

	MaxRange<T1> range;

	unsigned endsum_left = 0, n = arr.size();

	for (unsigned i = 0; i < n; ++i)
	{
		if (endsum <= 0)
		{
			endsum_left = i;
			endsum = arr[i];
		}
		else
		{
			endsum += arr[i];
		}


		if (endsum >= range.value)
		{
			range.value = endsum;

			range.left = endsum_left;
			range.right = i + 1;
		}
	}

	return range;
}

template<typename T>
MaxRange<int> max_sum_subarray(const std::vector<T> & arr) {
	return max_sum_subarray<int, T>(arr);
}

template<typename T1, typename T2>
MaxRange<T1> max_sum_submatrix(const std::vector< std::vector<T2> >& matrix) {

	MaxRange<T1> range;

	unsigned row = matrix.size(), col = 0;
	if (row > 0) col = matrix[0].size();

	std::vector<T1> array(col, 0);

	for (unsigned top = 0; top < row; ++top)
	{
		std::fill(array.begin(), array.end(), 0);

		for (unsigned bottom = top; bottom < row; ++bottom)
		{

			unsigned i = 0;
			for (auto & v : matrix[bottom])
			{
				array[i++] += v;
			}

			auto range_array = max_sum_subarray(array);

			if (range_array.value >= range.value)
			{
				range.value = range_array.value;
				range.top = top;
				range.bottom = bottom + 1;

				range.left = range_array.left;
				range.right = range_array.right;
			}

		}
	}

	return range;
}

template<typename T2>
MaxRange<int> max_sum_submatrix(const std::vector< std::vector<T2> >& matrix)
{
	return max_sum_submatrix<int, T2>(matrix);
}

#endif  //_MAX_SUM
