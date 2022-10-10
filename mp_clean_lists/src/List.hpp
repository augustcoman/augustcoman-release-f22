/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return ++List<T>::ListIterator(tail_);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  while(head_ != NULL) {
      ListNode* temp = head_->next;
      delete head_;
      head_ = temp;
  }
  tail_ = NULL;
  length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  if(head_ == NULL) {
    head_ = newNode;
    tail_ = newNode;
    length_++;
    return;
  }
  newNode -> next = head_;
  head_ -> prev = newNode;
  head_ = newNode;
  

  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  if(head_ == NULL) {
    head_ = newNode;
    tail_ = newNode;
    length_++;
    return;
  }
  newNode->prev = tail_;
  tail_->next = newNode;
  tail_ = newNode;
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  ListNode * curr = start;

  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }

  if (curr != NULL) {
      if(curr->prev != NULL) {
        curr->prev->next = NULL;
        curr->prev = NULL;
      }
      return curr;
  }

  return NULL;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  int triple_counter = 0;
  ListNode* front = head_;
  ListNode* back = head_;
  while(front != NULL) {
    if(triple_counter == 2) {
      //Hold front's next
      ListNode* ahead = front->next;
      //Redoing ties.
      if(ahead == NULL) {
        tail_ = back;
      } else {
        ahead->prev = back;
      }
      if(back->prev == NULL) {
        head_ = back->next;
      } else {
        back->prev->next = back->next;
      }
      back->next->prev = back->prev;
      back->next = ahead;
      front->next = back;
      back->prev = front;
      //repositioning and advancing
      front = ahead;
      back = ahead;
      triple_counter = 0;
    } else {
      triple_counter++;
      front = front->next;
    }
    //
  }
}


/*   Old code which moved front back to front (erroneously):
//Hold front's next
      ListNode* ahead = front->next;
      //Redoing ties.
      if(ahead == NULL) {
        tail_ = front->prev;
      } else {
        ahead->prev = front->prev;
      }
      if(back->prev == NULL) {
        head_ = front;
      } else {
        back->prev->next = front;
      }
      front->prev->next = ahead;
      front->prev = back->prev;
      back->prev = front;
      front->next = back;
      //repositioning and advancing
      front = ahead;
      back = ahead;
      triple_counter = 0;
    } else {
      triple_counter++;
      front = front->next;
    }
*/

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

//This function is looping into the wrong places.

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  if(empty()) {
    return;
  }
  ListNode* startPointLink = startPoint->prev;
  ListNode* endPointLink = endPoint->next;
  ListNode* traveler = startPoint;
  //Previously looped traveler != NULL. Always went to end of loop.
  //endPoint->next is not always NULL.
  while(traveler != endPointLink) {
    ListNode* next_temp = traveler->next;
    traveler->next = traveler->prev;
    traveler->prev = next_temp;
    traveler = next_temp;
  }
  traveler = startPoint;
  startPoint = endPoint;
  endPoint = traveler;
  //Switched spots back for startPoint and endPoint. Using them to joint to links
  if(startPointLink == NULL) {
    startPoint->prev = NULL;
    head_ = startPoint;
  } else {
    startPointLink->next = startPoint;
    startPoint->prev = startPointLink;
  }
  if(endPointLink == NULL) {
    endPoint->next = NULL;
    tail_ = endPoint;
  } else {
    endPointLink->prev = endPoint;
    endPoint->next = endPointLink;
  }
}

/* Old code that failed:
if(empty()) {
    return;
  }
  if(startPoint->prev == NULL) {
    tail_ = startPoint;
  } else {
    startPoint->prev->next = endPoint;
  }
  if(endPoint->next == NULL) {
    head_ = endPoint;
  } else {
    endPoint->next->prev = startPoint;
  }
  ListNode* traveler = startPoint->next;
  if(traveler == NULL) {
    std::cout << "traveler is null" << std::endl;
  }
  if(traveler->next == NULL) {
    std::cout << "traveler next is null" << std::endl;
  }
  if(endPoint->prev == NULL) {
    //std::cout << "endpoint prev is null" << std::endl;
  }
  startPoint->next = endPoint->next;
  if(traveler->next == NULL) {
    std::cout << "traveler next is null after reassigning startPoint" << std::endl;
  }
  if(startPoint == NULL) {
    std::cout << "traveler next is null after reassigning startPoint" << std::endl;
  }
  endPoint->prev = startPoint->prev;
  if(startPoint == NULL) {
    std::cout << "startPoint is null after reassigning startPoint" << std::endl;
  }
  unsigned counter = 1;
  while(traveler != endPoint) {
    std::cout << counter << std::endl;
    if(traveler->prev == startPoint) {
      startPoint->prev = traveler;
    }
    if(traveler->next == endPoint) {
      endPoint->next = traveler;
    }
    ListNode* temp = traveler->next;
    traveler->next = traveler->prev;
    traveler->prev = temp;
    traveler = temp;
    counter++;
  }
  //Now traveler equals endpoint
  endPoint = startPoint;
  startPoint = traveler;
*/

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  if(n <= 1 || empty()) {
    return;
  }
  int counter = 0;
  ListNode* startPoint = head_;
  ListNode* endPoint = head_;
  while(endPoint != NULL) {
    if(counter == n - 1 || endPoint == tail_) {
      ListNode* temp = endPoint->next;
      reverse(startPoint, endPoint);
      counter = 0;
      startPoint = temp;
      endPoint = temp;
    } else {
      endPoint = endPoint->next;
      counter++;
    }
  }
}
//Note: must reverse incomplete-sized parts as well.

/*   Old code with eternal looping:
if(n <= 1 || empty()) {
    return;
  }
  int counter = 0;
  ListNode* startPoint = head_;
  ListNode* endPoint = head_;
  while(endPoint != NULL) {
    if(counter == n - 1) {
      reverse(startPoint, endPoint);
      counter = 0;
      startPoint = endPoint->next;
      endPoint = endPoint->next;
    } else {
      endPoint = endPoint->next;
      counter++;
    }
  }
*/

/*  Old testing code:
  ListNode* beginning = head_;
  ListNode* end = head_->next->next;
  ListNode* tester = end->next;
  if(head_->next->next->next->next->next != tail_) {
    std::cout << "Not testing loop end right" << std::endl;
  }
  reverse(beginning, end);
  if(head_->prev != NULL) {
    std::cout << "Head is not null" << std::endl;
  }
  if(head_->next == NULL) {
    std::cout << "Head next is null" << std::endl;
  }
  if(end->next != tester) {
    std::cout << "end node pointing to wrong place" << std::endl;
  }
  if(end == head_) {
    std::cout << "end is head" << std::endl;
  }
  if(beginning == head_) {
    std::cout << "beginning is head" << std::endl;
  }
  std::cout << size() << std::endl;
  if(end->next == NULL || end->next == head_ || end->next == end) {
    std::cout << "End is incorrectly linking" << std::endl;
  }
  if(head_->next->next->next->next->next != tail_) {
    std::cout << "Does not loop to end" << std::endl;
  }
  beginning = end->next;
  end = beginning->next->next;
  if(end == NULL) {
    std::cout << "end is null" << std::endl;
  }
  if(beginning != head_->next->next->next) {
    std::cout << "beginning is not fourth element" << std::endl;
  }
  if(end != tail_) {
    std::cout << "end is not tail" << std::endl;
  }
  reverse(beginning, end);
  std::cout << n << std::endl;
  if(tail_->next != NULL) {
    std::cout << "Tail next is not null" << std::endl;
  }
  if(tail_->prev == NULL) {
    std::cout << "Tail prev is null" << std::endl;
  }
*/


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  if(first == NULL) {
    return second;
  }
  if(second == NULL) {
    return first;
  }
  ListNode* combination = NULL;
  if(first->data < second->data) {
    combination = first;
    first = first->next;
  } else {
    combination = second;
    second = second->next;
  }
  ListNode* builder = combination;
  while(first != NULL && second != NULL) {
    if(first->data < second->data) {
      builder->next = first;
      first->prev = builder;
      first = first->next;
    } else {
      builder->next = second;
      second->prev = builder;
      second = second->next;
    }
    builder = builder->next;
  }
  if(first != NULL) {
    builder->next = first;
    first->prev = builder;
  }
  if(second != NULL) {
    builder->next = second;
    second->prev = builder;
  }
  return combination;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if(chainLength <= 1) {
    return start;
  }
  ListNode* left_sorted = mergesort(split(start, chainLength / 2), chainLength - (chainLength / 2));
  ListNode* right_sorted = mergesort(start, chainLength / 2);
  ListNode* merged = merge(left_sorted, right_sorted);
  return merged;
}
