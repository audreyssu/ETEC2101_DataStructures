#pragma once

namespace ssuds {
	template <class T>
	
	class LinkedList {
		enum class LinkedListIteratorType
		{
			/// <summary>
			/// This LinkedList iterator visits items from beginning to end
			/// </summary>
			forward,

			/// <summary>
			/// This LinkedList iterator visits items from end to beginning
			/// </summary>
			backwards
		};
	private:



	protected:
		class Node {
		public:
			T data;

			Node* next;
			Node* prev;

			Node(T value) : data(value), next(nullptr), prev(nullptr) {}
			};
		
		/// <summary>
		/// Head of the linked list
		/// </summary>
		Node* start;

		/// <summary>
		/// Tail of the linked list
		/// </summary>
		Node* end;

		/// <summary>
		/// Number of nodes in linked list, retrieved through getSize() method
		/// </summary>
		unsigned int size;

		/// <summary>
		/// Increase the size by one; used for when a new item is added
		/// </summary>
		void grow() {
			size++;
		}

		/// <summary>
		/// Decrease the size by one; used for when an item is removed
		/// </summary>
		void shrink() {
			size--;
		}


	public:
		class LinkedListIterator {
			/// <summary>
			/// A pointer to the containing LinkedList
			/// </summary>
			const LinkedList* mLinkedList;

			/// <summary>
			/// The current position within the linked list
			/// </summary>
			int mPosition;


			/// <summary>
			/// Which type of iterator are we?
			/// </summary>
			LinkedListIteratorType mType;

		public:
			/// <summary>
			/// The main constructor
			/// </summary>
			/// <param name="linklist">The LinkedList we are to traverse</param>
			/// <param name="tp">What type of traversal to do</param>
			/// <param name="start_index">The index to start on</param>
			LinkedListIterator(const LinkedList* linklist, LinkedListIteratorType tp, int start_index) : mLinkedList(linklist), mPosition(start_index), mType(tp)
			{
				// intentionally empty
			}


			/// <summary>
			/// This constructor only really has value if the user makes an iterator (BUT DOES NOT USE!)
			/// and then later assigns it a real value.  If the user does anything with an iterator
			/// created like this, bad thigs will happen...
			/// </summary>
			LinkedListIterator() : mLinkedList(nullptr), mType(LinkedListIteratorType::forward), mPosition(0)
			{
				// intentionally empty
			}


			/// <summary>
			/// Copy-constructor
			/// </summary>
			/// <param name="other"></param>
			LinkedListIterator(const LinkedListIterator& other) : mLinkedList(other.mLinkedList), mPosition(other.mPosition),
				mType(other.mType)
			{
				// intentionally empty
			}


			/// <summary>
			/// Are we equal to the other iterator?  I'm currently not considering the LinkedListIterator type...
			/// I'm not sure if that's the right call or not.
			/// </summary>
			/// <param name="other">The iterator we're comparing ourself to</param>
			/// <returns>true if we're equal</returns>
			bool operator==(const LinkedListIterator& other) const
			{
				return mLinkedList == other.mLinkedList && mPosition == other.mPosition;
			}

			/// <summary>
			/// Are we not equal to the other iterator?  This is computed by inverting the result of the
			/// == operator
			/// </summary>
			/// <param name="other">The iterator we're comparing ourself to</param>
			/// <returns>true if we're NOT equal</returns>
			bool operator!=(const LinkedListIterator& other) const
			{
				return !(*this == other);
			}


			/// <summary>
			/// Increments / advances the iterator (prefix ++x version).  This version of ++ returns
			/// a copy of the Iterator *after* the ++ is performed.  So if the user did this:
			/// y = ++x
			/// X is changed, and a copy is returned which can be assigned to y.
			/// It is the responsibility of the user to NOT call this if the iterator is 
			/// invalid (equal to end/rend) -- if they ignore this rule, the results are indeterminate.
			/// </summary>
			LinkedListIterator operator++()
			{
				if (mType == LinkedListIteratorType::forward)
					++mPosition;
				else
					--mPosition;

				return LinkedListIterator(mLinkedList, mType, mPosition);
			}


			/// <summary>
			/// Increments / advances the iterator (postfix x++ version).  This version of ++ returns
			/// a copy of the Iterator *before* the ++ is performed.  So if the user did this:
			/// y = x++
			/// X is changed, but y will hold the iterator value before the change.  
			/// It is the responsibility of the user to NOT call this if the iterator is 
			/// invalid (equal to end/rend) -- if they ignore this rule, the results are indeterminate.
			/// <param name="not_used">This parameter is not used at all, but the compiler passes us
			/// a value so we can have both versions of ++</param>
			/// </summary>
			LinkedListIterator operator++(int not_used)
			{
				LinkedListIterator return_val(mLinkedList, mType, mPosition);
				if (mType == LinkedListIteratorType::forward)
					++mPosition;
				else
					--mPosition;
				return return_val;
			}


			/// <summary>
			/// Returns a copy of this iterator that is some amount offset from the current position.
			/// The resulting index of that iterator is constratined to be within -1...mSize
			/// </summary>
			/// <param name="offset">The amount to offset this iterator (positive or negative)</param>
			/// <returns>A copy of this iterator with the given offset applied</returns>
			LinkedListIterator operator+(int offset) const
			{
				int new_index = mPosition + offset;
				if (new_index < -1)
					new_index = -1;
				if (new_index >= (int)mLinkedList->size())
					new_index = (int)mLinkedList->size();

				return LinkedListIterator(mLinkedList, mType, new_index);
			}


			/// <summary>
			/// I don't think std::vector does this, but it is the inverse of the + operator and easy to add
			/// </summary>
			/// <param name="offset">The amount to offset this iterator by (inverted)</param>
			/// <returns>A copy of this iterator with the given offset</returns>
			LinkedListIterator operator-(int offset) const
			{
				return (*this) + (-offset);
			}


			/// <summary>
			/// Returns a reference to the current item in the LinkedList.  It is important that the
			/// user only call this method if the iterator is not in an invalid state (defined by being
			/// equal to end/rend)
			/// </summary>
			/// <returns>A reference to the current object</returns>
			T& operator*()
			{
				return (*mLinkedList)[mPosition];
			}


			/// <summary>
			/// Used to copy one LinkedListIterator value to another
			/// </summary>
			/// <param name="other">The LinkedListIterator we're copying from</param>
			/// <returns>A reference to this changed LinkedListIterator</returns>
			LinkedListIterator& operator=(const LinkedListIterator& other)
			{
				mLinkedList = other.mLinkedList;
				mPosition = other.mPosition;
				mType = other.mType;
				return *this;
			}

			// I needed access in the remove method.
			friend class LinkedList;
		};



		/// <summary>
		/// Default constructor
		/// </summary>
		LinkedList() : start(nullptr), end(nullptr), size(0) {}

		/// METHODS
		/// <returns>Number of elements in linked list</returns>
		unsigned int getSize() const {
			return size;
		}

		void insert(int index, const T& newval) {
			/*///list is empty -> make one element
			if (getSize() == 0) {
				grow();
			}
			///list non-empty, index = 0 -> prepend()
			else if (getSize() > 0) && (index == 0) {
				prepend(newval);
			}
			///non-empty, index = size -> append()
			else if (getSize() > 0) && (index == getSize()) {
				append(newval);
			}
			///non-empty, 0 < index < size
			else if (getSize() > 0) && (0 < index < size) {
				/// allocate new node
				///iterate until cur points at node with proper index, not needed if class has an iterator
				/// re-route pointers
				/// grow()
				
				grow();*/

			grow();
			///invalid index -> raise exception
		}

		void append(const T& newval) {
			Node* newNode = new Node(newval);

			if (start == nullptr) {
				start = newNode;
			}

			else {
				Node* current = start;

				while (current != nullptr) {
					current = current->next;
				}

				newNode->prev = current;
				current->next = newNode;
			}
			grow();
		}

		void prepend(const T& newval) {
			Node* newNode = new Node(newval);

			if (start == nullptr) {
				start = newNode;
			}

			else {
				Node* current = start;

				newNode->next = current;
				current->prev = newNode;

				start = newNode;
			}
			grow();
		}

		void remove() {
			shrink();
		}

		void remove_all() {
			/// take in value, if current == given remove current, it++
		}

		void clear() {
			/// while start != null, remove start
		}

		/// <summary>
		/// Destructor
		/// </summary>
		~LinkedList() {

		}

		
	};


}