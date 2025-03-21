#pragma once

namespace ssuds {
	/// <summary>
	/// A multipurpose container class that dynamically calculates the necessary size in memory for the objects it contains.
	/// </summary>
	template <class T> class ArrayList {
	private:
		T* self_array;
		int self_size;
		int self_capacity;
	public:
		/// <summary>
		/// Default constructor for the ArrayList class
		/// </summary>
		/// <param name="size">How many objects are currently stored in the array</param>
		/// <param name="capacity">How many objects can be stored in the array</param>
		ArrayList() {
			self_size = 0;
			self_capacity = 1;
			self_array = new T[self_capacity];
		}

		/// <summary>
		/// Constructor for the ArrayList class
		/// </summary>
		/// <param name="size">How many objects are currently stored in the array</param>
		/// <param name="capacity">How many objects can be stored in the array</param>
		ArrayList(int capacity) {
			int self_size = 0;
			int self_capacity = capacity;
			self_array = new T[self_capacity];
		}

		/// <summary>
		/// Destructor for the ArrayList class
		/// </summary>
		~ArrayList() {
			delete[] self_array;
		}

		/// <summary>
		/// Adds a new item to the end of the array
		/// </summary>
		/// <param name="new_item">Item to be added</param>
		void append(const T& new_item) {
			reserve(self_size + 1);
			self_array[self_size] = new_item;
			self_size++;
			resize();
		}

		/// <summary>
		/// Adds a new item to the beginning of the array
		/// </summary>
		/// <param name="new_item">Item to be added</param>
		void prepend(const T& new_item) {
			T* new_array = new T[self_capacity + 1];
			new_array[0] = new_item;
			for (int i = 0; i < self_size; i++) {
				new_array[i+1] = self_array[i];
			}

			delete[] self_array;
			self_array = new_array;
			self_size++;
			resize();
		}

		/// <summary>
		/// Inserts an item at a given index and makes room for it
		/// </summary>
		/// <param name="new_item">Item to be added</param>
		/// <param name="index">Index</param>
		void insert(const T& new_item, int index) {
			T* new_array = new T[self_capacity+1];

			for (int i = 0; i < index; i++) {
				new_array[i] = self_array[i];
			}

			new_array[index] = new_item;

			for (int i = index + 1; i < self_size + 1; i++) {
				new_array[i] = self_array[i-1];
			}
			
			delete[] self_array;
			self_array = new_array;
			self_size++;
			resize();
		}

		/// <summary>
		/// Deletes an item at a given index and shrinks the list accordingly
		/// </summary>
		/// <param name="index">Index of item to delete</param>
		/// <returns>Copy of deleted item</returns>
		T remove(int index) {
			T item_copy = self_array[index];
			T* new_array = new T[self_capacity];

			for (auto i = self_array.begin(); i != self_array.end(); i++) {
				new_array[i] = self_array[i];
			}

			for (auto i = self_array[index+1]; i != self_array.end(); i++) {
				new_array[i-1] = self_array[i];
			}
			self_size--;
			delete[] self_array;
			self_array = new_array;
			resize();
			return item_copy;
		}

		int find(T value) {
			int retval = 0;
			for (auto i = self_array.begin(); i != self_array.end(); i++) {
				if (*i == value) {
					retval++;
				}
			}
			return retval;
		}

		int remove_all(const T& removed_item) {
			int i = 0;
			int count = 0;

			while (self_array[i] != NULL) {
				if (self_array[i] == removed_item) {
					remove(i);
					i = 0;
					count++;
				}
				i++;
			}
			return count;
		}




		/// <summary>
		/// Changes the max capacity of the array. Either shrinks to half of current size or doubles current size 
		/// depending on situation
		/// </summary>
		void resize() {
			if (static_cast<float>(self_size)/static_cast<float>(self_capacity) > .5) { // The number of objects is too high; double the capacity
				T* new_array = new T[self_capacity * 2];

				for (int i = 0; i < self_size; i++) {
					new_array[i] = self_array[i];
				}

				delete[] self_array;
				self_array = new_array;
				self_capacity *= 2;
			}

			else if (static_cast<float>(self_size)/static_cast<float>(self_capacity) < .25) { // The capacity is higher than necessary; shrink it by half
				T* new_array = new T[self_capacity / 2];

				for (int i = 0; i < self_size; i++) {
					new_array[i] = self_array[i];
				}

				delete[] self_array;
				self_array = new_array;
				self_capacity /= 2;
			}

			else {}
		}

		void reserve(int new_capacity) {
			if (new_capacity <= self_capacity) {
				return;
			}

			T* new_array = new T[new_capacity];

			for (int i = 0; i < self_size; i++) {
				new_array[i] = self_array[i];
			}

			delete[] self_array;
			self_array = new_array;
			self_capacity = new_capacity;
		}

		/// <summary>
		/// Returns index of object's first instance, returns -1 if object not found
		/// </summary>
		/// <param name="item">Object to look for</param>
		/// <param name="start">Starting index (defaults to 0)</param>
		/// <returns>Index of object's first instance</returns>
		int find(const T& item, int start = 0) {
			for (int i = start; i < self_size; i++) {
				if (self_array[i] == item) {
					return i;
				}
			}
			return -1;
		}

		/// <summary>
		/// Returns the address of the object at that index, throws an error otherwise
		/// </summary>
		/// <param name="index">Index</param>
		/// <returns>Address of object at index</returns>
		T& at(int index) const {
			if (self_array[index] != NULL) {
				return self_array[index];
			}
			else {
				throw std::out_of_range("Error: Invalid index");
			}
		}


		/// <summary>
		/// Getter Method for number of items in array
		/// </summary>
		int get_size() const {
			return self_size;
		}

		/// <summary>
		/// Getter Method for current max number of items in array
		/// </summary>
		int get_capacity() const {
			return self_capacity;
		}

		T& operator[](const int index) {
			return self_array[index];
		}



		/// <summary>
		/// Returns array as string
		/// </summary>
		/// <param name="stream">Ostream for passing in of string operations</param>
		/// <returns>Array as string</returns>
		std::string output() {
			std::string return_string = "[";
			
			for (int i = 0; i < self_size; i++) {
				return_string.append(self_array[i]);
				if (i < self_size - 1) {
					return_string.append(", ");
				}
			}
			return_string.append("]");
			return return_string;
		}

		std::ostream& operator<<(std::ostream& os) {
			std::string return_string = "[";

			for (int i = 0; i < self_size; i++) {
				return_string.append(self_array[i]);
				if (i < self_size - 1) {
					return_string.append(", ");
				}
			}
			return_string.append("]");
			os << return_string;
			return os;
		}

		/// <summary>
		/// Iteratot for ArrayList class
		/// </summary>
		class ArrayListIterator {
		private:
			T* ptr;
		public:
			bool reversed;
			ArrayListIterator(T* p) : ptr(p) {
				reversed = false;
			}



			/// <summary>
			/// Return balue iterator points to
			/// </summary>
			T& operator*() {
				return *ptr;
			}


			/// <summary>
			/// Add to iterator
			/// </summary>
			T& operator+(const int other) {
				if (!reversed) {
					ptr += other;
					return ptr;
				}
				else {
					ptr -= other;
					return ptr;
				}
			}

			/// <summary>
			/// Increment
			/// </summary>
			ArrayListIterator& operator++() {
				if (!reversed) {
					++ptr;
					return *this;
				}
				else {
					--ptr;
					return *this;
				}
			}

			/// <summary>
			/// Increment on right hand side
			/// </summary>
			ArrayListIterator& operator++(int) {
				if (!reversed) {
					++ptr;
					return *this;
				}
				else {
					--ptr;
					return *this;
				}
			}

			/// <summary>
			/// Decrement
			/// </summary>
			ArrayListIterator& operator--() {
				if (!reversed) {
					--ptr;
					return *this;
				}
				else {
					++ptr;
					return *this;
				}
			}

			/// <summary>
			/// Decrement on right hand side
			/// </summary>
			ArrayListIterator& operator--(int) {
				if (!reversed) {
					--ptr;
					return *this;
				}
				else {
					++ptr;
					return *this;
				}
			}

			/*ArrayListIterator& operator=(const ArrayListIterator& other) {
				if (this != other) {
					delete[] ptr;
				}

				ptr = new ArrayListIterator;
				*ptr = *other;

				return *this;
			}*/
			
			/// <summary>
			/// Compares if two are equal
			/// </summary>
			/// <param name="other">Value comparing to</param>
			/// <returns>Bool value</returns>
			bool operator==(const T& other) {
				return *ptr == other;
			}

			/// <summary>
			/// Compares if two are not equal
			/// </summary>
			/// <param name="other">Value comparing to</param>
			/// <returns>Bool value</returns>
			bool operator!=(const T& other) {
				return *ptr != other;
			}
		};
		
		/// <summary>
		/// Returns reference to first in array
		/// </summary>
		ArrayListIterator begin() {
			return &self_array[0];
		}

		/// <summary>
		/// Returns reference to last in array
		/// </summary>
		ArrayListIterator end() {
			return &self_array[get_size()-1];
		}

		/// <summary>
		/// Returns reference to first in array, iterates backwards
		/// </summary>
		ArrayListIterator rbegin() {
			ArrayListIterator it = &self_array[get_size()-1];
			it.reversed = true;
			return it;
		}

		/// <summary>
		/// Returns reference to last in array, iterates backwards
		/// </summary>
		ArrayListIterator rend() {
			ArrayListIterator it = & self_array[0];
			it.reversed = true;
			return it;
		}

		/// <summary>
		/// Creates deep copy of other ArrayList object
		/// </summary>
		 ArrayList operator=(const ArrayList other) {
			 if (this != other) {
				 delete[] self_array;

				}

			 self_size = other.get_size();
			 self_capacity = other.get_capacity();

			 self_array = new T[self_capacity];

			 for (int i = 0; i < other.get_size(); i++) {
				 self_array[i] = other[i];
			 }
			 return *this;
			}



	};
}
