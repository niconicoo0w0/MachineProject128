// #include "branched-linked-list.hpp"


// bool BLL::IsBLLAcyclic() const {
//     if (head_ == nullptr) {
//         return true;
//     }
//     Node* slow = head_;
//     Node* fast = head_->next_node_;
//     while (fast != nullptr && slow != nullptr) {
//         if (fast == slow) {
//             return false;
//         }
//         for (int i = 0; i < 2; i++) {
//             if (fast == nullptr) {
//                 return true;
//             }
//             if (fast->next_bll_ != nullptr) {
//                 fast = fast->next_bll_->head_;
//             } else {
//                 fast = fast->next_node_;
//             }
//         }
//         if (slow->next_bll_ != nullptr) {
//             slow = slow->next_bll_->head_;
//         } else {
//             slow = slow->next_node_;
//         }
//     }
//     return true;
// }

// BLL& BLL::operator=(const BLL& rhs) {
//     if (this == &rhs || rhs.head_ == nullptr) {
//         return *this;
//     }
//     //return一模一样的✅
//     this->~BLL();
//     //delete✅
//     this->head_ = new Node(rhs.head_->data_);
//     Node* copy = this->head_;
//     Node* temp = rhs.head_;
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
//     return *this;
// }


// Node* BLL::PushBack(char dat) {
//     Node* data = new Node(dat);
//     if (head_ == nullptr) {
//         head_ = data;
//         return data;
//     }
//     Node* curr = head_;
//     while (curr->next_node_ != nullptr) {
//         curr = curr->next_node_;
//     }
//     curr->next_node_ = data;
//     return data;
// }

// Node* BLL::Find(size_t index) const {
//     Node* curr = head_;
//     for (size_t i = 0; i < index; i++) {
//         if (curr == nullptr) {
//             throw std::runtime_error("out of bound!");
//         }
//         if (curr->next_bll_ != nullptr) {
//             curr = curr->next_bll_->head_;
//         } else if (curr->next_node_ != nullptr) {
//             curr = curr->next_node_;
//         } else {
//             throw std::runtime_error("out of bound!");
//         }
//     }
//     return curr;
// }

// char BLL::GetAt(size_t idx) const {
//     if (idx >= Size()) {
//         throw std::runtime_error("out of bound!");
//     }
//     Node* curr = Find(idx);
//     return curr->data_;
// }

// void BLL::SetAt(size_t idx, char dat) const {
//     if (idx >= Size()) {
//         throw std::runtime_error("out of bound!");
//     }
//     Node* curr = Find(idx);
//     curr->data_ = dat;
// }

// void BLL::Join(size_t idx, BLL* list) {
//     if (idx >= Size()) {
//         throw std::runtime_error("out of bound!");
//     }
//     Node* curr = Find(idx);
//     if (curr == nullptr || curr->next_bll_ != nullptr) {
//         throw std::runtime_error("already exists");
//     }
//     curr->next_bll_ = list;
//     if (!IsBLLAcyclic()) {
//         throw std::runtime_error("cycle");
//     }
// }

// std::string BLL::ToString() const {
//     if (head_ == nullptr) {
//         return std::string();
//     }
//     std::string returnit;
//     Node* temp = head_;
//     while (temp != nullptr) {
//         returnit += temp->data_;
//         if (temp->next_bll_ != nullptr) {
//             returnit += temp->next_bll_->ToString();
//         }
//         temp = temp->next_node_;
//     }
//     return returnit;   
// }

// size_t BLL::Size() const {
//     if (head_ == nullptr) {
//         return 0;
//     }
//     size_t returnit = 0;
//     Node* temp = head_;
//     while (temp != nullptr) {
//         returnit++;
//         if (temp->next_bll_ != nullptr) {
//             returnit += temp->next_bll_->Size();
//         }
//         temp = temp->next_node_;
//     }
//     return returnit;   
// }
#include "branched-linked-list.hpp"

bool BLL::IsBLLAcyclic() const {
  if (head_ == nullptr) {
    return true;
  }
  Node* oogway = head_;
  Node* shifu = head_->next_node_;
  while (oogway != nullptr && shifu != nullptr) {
    if (oogway == shifu) {
      return false;
    }
    for (int i = 0; i < 2; i++) {
      if (shifu == nullptr) {
        return true;
      }
      if (shifu->next_bll_ != nullptr) {
        shifu = shifu->next_bll_->head_;
      } else {
        shifu = shifu->next_node_;
      }
    }
    if (oogway->next_bll_ != nullptr) {
      oogway = oogway->next_bll_->head_;
    } else {
      oogway = oogway->next_node_;
    }
  }
  return true;
}


BLL::BLL(const BLL& to_copy) {
  head_ = nullptr;
  *this = to_copy;
}

BLL::~BLL() {
  Node* node = head_;
  while (head_ != nullptr) {
    if (head_->next_bll_ != nullptr) {
      head_->next_bll_->~BLL();
      head_->next_bll_ = nullptr;
    }
    node = head_;
    head_ = head_->next_node_;
    delete node;
  }
  head_ = nullptr;
}

BLL& BLL::operator=(const BLL& rhs) {
  if (this == &rhs) {
    return *this;
  }
  this->~BLL();
  if (rhs.head_ == nullptr) {
    return *this;
  }
  head_ = new Node(rhs.head_->data_);
  auto* node = head_;
  auto* rhs_temp = rhs.head_;
  if (rhs_temp->next_bll_ != nullptr) {
    node->next_bll_ = new BLL(*rhs_temp->next_bll_);
  }
  while (rhs_temp->next_node_ != nullptr) {
    rhs_temp = rhs_temp->next_node_;
    Node* newnode = new Node(rhs_temp->data_);
    if (rhs_temp->next_bll_ != nullptr) {
      newnode->next_bll_ = new BLL;
      *newnode->next_bll_ = *rhs_temp->next_bll_;
    }
    node->next_node_ = newnode;
    node = node->next_node_;
  }
  return *this;
}

Node* BLL::Nodehelper(Node* node, size_t& current, size_t idx) const {
  if (current > idx) {
    return nullptr;
  }
  auto* curr = node;
  while (current!=idx){
    if (curr == nullptr) {
        return nullptr;
    }
    if (curr->next_bll_ != nullptr) {
      current++;
      auto* ret = Nodehelper(curr->next_bll_->head_, current, idx);
      if (ret != nullptr) {return ret;}
    }
    curr = curr->next_node_;
    if (curr == nullptr) {
        return nullptr;
    }
    current++;
  }
  return curr;
}

Node* BLL::PushBack(char dat) {
    if (head_ == nullptr) {
        head_ = new Node(dat);
        return head_;
    }
    auto* node = head_;
    while (node->next_node_ != nullptr) {
        node = node->next_node_;
    }
    node->next_node_ = new Node(dat);
    return node->next_node_;
}

char BLL::GetAt(size_t idx) const {
    if (idx >= Size()) {
        throw std::runtime_error("invalid index");
    }
    size_t i = 0;
    return this->Nodehelper(head_,i,idx)->data_;
}

void BLL::SetAt(size_t idx, char dat) {
    if (idx >= Size()) {
        throw std::runtime_error("invalid index");
    }
    size_t i = 0;
    auto* node = this->Nodehelper(head_,i,idx);
    node->data_ = dat;
}

void BLL::Join(size_t idx, BLL* list) {
  if (idx >= Size()) {
    throw std::runtime_error("invalid index");
  }
  size_t i = 0;
  auto* node = this->Nodehelper(head_, i, idx);

  if (node->next_bll_!=nullptr || node == nullptr) throw std::runtime_error("");
  node->next_bll_ = list;

  if (!IsBLLAcyclic()) {
    node->next_bll_ = nullptr;
    throw std::runtime_error("cycle occures");
  }
}

std::string BLL::ToString() const {
    if (head_ == nullptr) {
        return std::string();
    }
    auto* node = head_;
    std::string str;
    while (node != nullptr) {
        str+=node->data_;
        if (node->next_bll_ !=  nullptr) {
            str+=node->next_bll_->ToString();
        }
        node = node->next_node_;
    }
    return str;
}

size_t BLL::Size() const {
    if (head_ == nullptr) {
      return 0;
    }
    return ToString().size();
}