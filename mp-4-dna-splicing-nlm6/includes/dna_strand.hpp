#ifndef DNA_STRAND_HPP
#define DNA_STRAND_HPP
#include <iostream>

#include "node.hpp"
class DNAstrand {
public:
  DNAstrand();
  DNAstrand(const DNAstrand& rhs);
  DNAstrand& operator=(const DNAstrand& rhs);
  friend std::ostream& operator<<(std::ostream& os, const DNAstrand& rhs);

  ~DNAstrand();

  void SpliceIn(const char* pattern, DNAstrand& to_splice_in);
  void Insert(char kPattern);

private:
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
};
void Delete(const Node* start, const Node* end);
Node* StrEqual(const char* pattern, const Node* start);
#endif