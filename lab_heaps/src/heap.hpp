
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */
#include <cstddef>

template <class T, class Compare>
class heap;

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    return currentIdx * 2;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    return currentIdx * 2 + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    return currentIdx / 2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
    return leftChild(currentIdx) < _elems.size();
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    if(rightChild(currentIdx) >= _elems.size()) {
        return leftChild(currentIdx);
    }
    if(higherPriority(_elems.at(leftChild(currentIdx)), _elems.at(rightChild(currentIdx)))) {
        return leftChild(currentIdx);
    }
    return rightChild(currentIdx);
    //return higherPriority(_elems.at(leftChild(currentIdx), rightChild(currentIdx)))?leftChild(currentIdx):rightChild(currentIdx);
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.
    if(!hasAChild(currentIdx)) {
        return;
    }
    size_t min_idx = 0; 
    size_t current_idx = currentIdx;
    while(hasAChild(current_idx)) {
        min_idx = maxPriorityChild(current_idx);
        if(higherPriority(_elems.at(min_idx), _elems.at(current_idx))) {
            std::swap(_elems.at(current_idx), _elems.at(min_idx));
            current_idx = min_idx;
        } else {
            return;
        }
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap(): _elems(std::vector<T>(1, T()))
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems): _elems((std::vector<T>(1, T()))) 
{
    // @TODO Construct a heap using the buildHeap algorithm
    for(size_t i = 0; i < elems.size(); i++) {
        _elems.push_back(elems.at(i));
    }
    for(size_t j = parent(_elems.size() - 1); j > 0; j--) {
        heapifyDown(j);
    }
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    T top = _elems.at(1);
    _elems.at(1) = _elems.back();
    _elems.pop_back();
    if(!empty()) {
        heapifyDown(1);
    }
    return top;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    if(!empty()) {
        return _elems.at(1);
    }
    return T();
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    _elems.push_back(elem);
    heapifyUp(_elems.size() - 1);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
    // basically a modifier
    T original = _elems.at(idx);
    _elems.at(idx) = elem;
    if(higherPriority(elem, original)) {
        heapifyUp(idx);
    } else {
        heapifyDown(idx);
    }

}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    return _elems.size() <= 1;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
