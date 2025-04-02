#pragma once

#include <array_list.h>
#include <random>

namespace ssuds {
	enum class ArrayListSortOrder {
		/// <summary>
		/// This enum sorts the ArrayList from small to big
		/// </summary>
		ASCENDING,

		/// <summary>
		/// This enum sorts the ArrayList from big to small
		/// </summary>
		DESCENDING
	};

	/// <summary>
	/// Function for sorting an ArrayList via quicksort algorithm
	/// </summary>
	/// <typeparam name="T">Templated object</typeparam>
	/// <param name="SortArray">Reference to ArrayList object that is affected</param>
	/// <param name="sortOrder">Enum indicating whether to sort the ArrayList in ASCENDING or DESCENDING order</param>
	/// <returns>Number of swaps performed</returns>
	template <typename T>
	int quicksort(ArrayList<T>& SortArray, ArrayListSortOrder sortOrder, int left_index, int right_index);


	template <typename T>
	int partition(ArrayList<T> PartitionArray, ArrayListSortOrder sortOrder, int left_index, int right_index);
	
	template <typename T>
	void swap(ArrayList<T> SwapArray, int x, int y);
}