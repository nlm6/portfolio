#include <iostream>

#include "dna_strand.hpp"

std::ostream& operator<<(std::ostream& os, const DNAstrand& rhs) {
  if (rhs.head_ == nullptr || rhs.tail_ == nullptr) {
    return os;
  }
  Node* cur = rhs.head_;
  while (cur != nullptr) {
    os << cur->data << " , ";
    cur = cur->next;
  }
  os << std::endl;
  os << "HEAD: " << rhs.head_->data << std::endl;
  os << "TAIL: " << rhs.tail_->data << std::endl;
  return os;
}

int main() {
  DNAstrand strand;
  strand.Insert('z');
  strand.Insert('c');
  strand.Insert('t');
  strand.Insert('g');
  strand.Insert('a');
  strand.Insert('a');
  strand.Insert('t');
  strand.Insert('t');
  strand.Insert('c');
  strand.Insert('g');
  std::cout << strand;
  DNAstrand splice;
  splice.Insert('t');
  splice.Insert('g');
  splice.Insert('a');
  splice.Insert('t');
  splice.Insert('c');
  std::cout << splice;
  strand.SpliceIn("z", splice);
  std::cout << strand;
}