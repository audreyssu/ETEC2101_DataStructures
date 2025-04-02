#include <array_list_utility.h>

template <typename T>
int ssuds::quicksort(ArrayList<T>& SortArray, ArrayListSortOrder sort_order, int left_index, int right_index) {
	if (left_index >= right_index) {
		return; // only one value
	}

	int pivot_index = partition(SortArray, sort_order, left_index, right_index);
	// Pivot is in proper place. Sort halves on either side
	quicksort(SortArray, left_index, pivot_index - 1);
	quicksort(SortArray, pivot_index + 1, right_index);
}

template <typename T>
int ssuds::partition(ArrayList<T> PartitionArray, ArrayListSortOrder sort_order, int left_index, int right_index) {
	// Get index of pivot
	int mid_index = (left_index + right_index) / 2;
	T pivot_value = PartitionArray[mid_index];

	// Swap last element with pivot
	swap(PartitionArray, mid_index, right_index);

	// Put elements on "right" side of pivot
	int swap_index = left_index;

	for (int i = left_index; i < right_index; i++) {
		if (PartitionArray[i] <= pivot_value) { // If my_list[i] is the pivot or should go to its left
			swap(PartitionArray, i, swap_index);
			swap_index++;
		}
	}

	return swap_index - 1;
}

template <typename T>
void ssuds::swap(ArrayList<T> SwapArray, int x, int y) {
	T temp = SwapArray[x];
	SwapArray[x] = SwapArray[y];
	SwapArray[y] = SwapArray[x];
}