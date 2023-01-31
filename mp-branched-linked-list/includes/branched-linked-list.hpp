// #ifndef BRANCHED_LINKED_LIST_HPP
// #define BRANCHED_LINKED_LIST_HPP

// #include <cstddef>
// #include <stdexcept>
// #include <string>

// #include "node.hpp"

// class BLL {
// public:
//   BLL() = default;
//   BLL(const BLL& to_copy) {
//     if (to_copy.head_ == nullptr) {
//       return;
//     }
//     this->head_ = new Node(to_copy.head_->data_);
//     Node* copy = this->head_;
//     Node* temp = to_copy.head_;
//     while (temp->next_node_ != nullptr)  {
//         Node* node = new Node(temp->next_node_->data_);
//         copy->next_node_ = node;
//         if (temp->next_node_->next_bll_ != nullptr) {
//             BLL* bll = new BLL(*temp->next_node_->next_bll_);
//             copy->next_node_->next_bll_ = bll;  //copyBll
//         }
//         copy = copy->next_node_;
//         temp = temp->next_node_;
//     }
//   }

//   ~BLL() {
//     while (head_ != nullptr) {
//       if (head_->next_bll_ != nullptr) {
//         head_->next_bll_->~BLL();
//         delete head_->next_bll_;
//       }
//       Node* temp = head_;
//       head_ = head_->next_node_;
//       delete temp;
//     }
//     head_ = nullptr;
//   }

//   BLL& operator=(const BLL& rhs);
//   Node* PushBack(char dat);
//   char GetAt(size_t idx) const;
//   void SetAt(size_t idx, char dat) const;
//   void Join(size_t idx, BLL* list);
//   std::string ToString() const;
//   size_t Size() const;

//   //helper function
//   Node* Find(size_t index) const;


// private:
//   Node* head_ = nullptr;
//   bool IsBLLAcyclic() const;
// };

// #endif

#ifndef BRANCHED_LINKED_LIST_HPP
#define BRANCHED_LINKED_LIST_HPP

#include <cstddef>
#include <stdexcept>
#include <string>

#include "node.hpp"

class BLL {
public:
  BLL() = default;
  BLL(const BLL& to_copy);
  ~BLL();

  BLL& operator=(const BLL& rhs);
  Node* PushBack(char dat);
  char GetAt(size_t idx) const;
  void SetAt(size_t idx, char dat);
  void Join(size_t idx, BLL* list);
  std::string ToString() const;
  size_t Size() const;
  // helper function for join, set, and get
  Node* Nodehelper(Node* node, size_t& current, size_t idx) const ;

private:
  Node* head_ = nullptr;
  bool IsBLLAcyclic() const;
};

#endif

