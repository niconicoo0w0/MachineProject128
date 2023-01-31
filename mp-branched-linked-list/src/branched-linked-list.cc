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
