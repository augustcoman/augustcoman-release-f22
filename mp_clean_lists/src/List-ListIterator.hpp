
class ListIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
  private:
    // @TODO: graded in MP3.1
    ListNode* position_;
    ListNode* prev_;

  public:
    ListIterator() : position_(NULL), prev_(NULL) { }
    ListIterator(ListNode* x) : position_(x) {
        if(position_ == NULL) {
            prev_ = NULL;
        } else {
            prev_ = position_->prev;
        }
    }


    // Pre-Increment, ++iter
    ListIterator& operator++() {
        // @TODO: graded in MP3.1
        prev_ = position_;
        if(position_ != NULL) {
            position_ = position_->next;
        }
        return *this;
    }
    
    // Post-Increment, iter++
    ListIterator operator++(int) {
        // @TODO: graded in MP3.1
        ListIterator output(position_);
        output.prev_ = prev_;
        prev_ = position_;
        if(position_ != NULL) {
            position_ = position_->next;
        }
        return output;
    }

    // Pre-Decrement, --iter
    ListIterator& operator--() {
        // @TODO: graded in MP3.1
        position_ = prev_;
        if(position_ == NULL) {
            prev_ = NULL;
        } else {
            prev_ = position_->prev;
        }
        return *this;
    }

    // Post-Decrement, iter--
    ListIterator operator--(int) {
        // @TODO: graded in MP3.1
        ListIterator output(position_);
        output.prev_ = prev_;
        position_ = prev_;
        if(position_ == NULL) {
            prev_ = NULL;
        } else {
            prev_ = position_->prev;
        }
        return output;
    }

    bool operator!=(const ListIterator& rhs) {
        // @TODO: graded in MP3.1
        if(this == &rhs) {
            return false;
        }
        return position_ != rhs.position_ || prev_ != rhs.prev_;
    }

    bool operator==(const ListIterator& rhs) {
        return !(*this != rhs);
    }

    const T& operator*() {
        return position_->data;
    }

    const T* operator->() {
        return &(position_->data);
    }
};
