#include "dna_strand.hpp"

#include <stdexcept>

DNAstrand::DNAstrand() {
  tail_ = nullptr;
  head_ = nullptr;
}
DNAstrand::DNAstrand(const DNAstrand& rhs) {
  head_ = nullptr;
  tail_ = nullptr;
  if (rhs.head_ == nullptr) {
    return;
  }
  head_ = new Node(rhs.head_->data);
  Node* new_cur = head_;
  Node* cur = rhs.head_;
  for (; cur != rhs.tail_; cur = cur->next, new_cur = new_cur->next) {
    new_cur->next = new Node(cur->next->data);
  }
  tail_ = new_cur;
}
DNAstrand& DNAstrand::operator=(const DNAstrand& rhs) {
  if (&rhs == this) {
    return *this;
  }
  head_ = nullptr;
  tail_ = nullptr;
  if (rhs.head_ == nullptr) {
    return *this;
  }
  head_ = new Node(rhs.head_->data);
  Node* new_cur = head_;
  Node* cur = rhs.head_;
  for (; cur != rhs.tail_; cur = cur->next, new_cur = new_cur->next) {
    new_cur->next = new Node(cur->next->data);
  }
  tail_ = new_cur;
  return *this;
}

DNAstrand::~DNAstrand() {
  if (head_ == nullptr || tail_ == nullptr) {
    return;
  }
  Node* cur = head_;
  while (cur != nullptr) {
    Node* temp = cur;
    cur = cur->next;
    delete temp;
  }
}

Node* StrEqual(const char* pattern, Node* start) {
  int index = 0;
  Node* it = start;
  while (it != nullptr && pattern[index] != '\0' &&
         it->data == pattern[index]) {
    if (pattern[++index] != '\0') {
      it = it->next;
    }
  }
  if (pattern[index] == '\0') {
    return it;
  }
  return nullptr;
}

void Delete(const Node* start, const Node* end) {
  const Node* prev = start;
  while (prev != end) {
    const Node* temp = prev->next;
    delete prev;
    prev = temp;
  }
  delete end;
}

void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {
  if (this == &to_splice_in) {
    return;
  }
  Node* prev = nullptr;
  Node* end = nullptr;
  Node* start = nullptr;
  Node* start_prev = nullptr;
  for (Node* cur = head_; cur != nullptr; prev = cur, cur = cur->next) {
    if (cur->data == pattern[0]) {
      Node* temp = StrEqual(pattern, cur);
      if (temp != nullptr) {
        end = temp;
        start = cur;
        start_prev = prev;
        cur = temp;
      }
    }
  }
  if (end != nullptr) {
    if (start == head_) {
      head_ = to_splice_in.head_;
    }
    if (end == tail_) {
      tail_ = to_splice_in.tail_;
    }
    if (start_prev != nullptr) {
      start_prev->next = to_splice_in.head_;
    }
    if (to_splice_in.tail_ != nullptr) {
      to_splice_in.tail_->next = end->next;
    }
    to_splice_in.head_ = nullptr;
    to_splice_in.tail_ = nullptr;
    Delete(start, end);
  } else {
    throw std::invalid_argument("No matching pattern");
  }
}

void DNAstrand::Insert(char kPattern) {
  // Create a new node with the given pattern
  Node* new_node = new Node(kPattern);

  if (head_ == nullptr) {
    // The list is empty, so the new node becomes both head and tail
    head_ = new_node;
    tail_ = new_node;
  } else {
    // The list is not empty, append the new node to the end
    tail_->next = new_node;
    tail_ = new_node;
  }
}
