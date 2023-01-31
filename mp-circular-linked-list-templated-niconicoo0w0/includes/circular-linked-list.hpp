#ifndef CIRCULAR_LINKED_LIST_HPP
#define CIRCULAR_LINKED_LIST_HPP

#include <iostream>
#include "node.hpp"

enum class Order { kASC, kDESC };

template <typename T>
class CircularLinkedList {
public:
  CircularLinkedList() = default;

  CircularLinkedList(const CircularLinkedList<T>& source) {
    *this = source;
  }

  CircularLinkedList<T>& operator=(const CircularLinkedList<T>& source) {
    if (this == &source || source.head_ == nullptr) {
      return *this;
    }

    while (head_ != tail_) {
      Node<T>* temp = head_;
      head_ = head_->next;
      delete temp;
    }
    delete tail_;
    head_ = tail_ = nullptr;

    node_order_ = source.node_order_;
    tail_ = head_ = new Node<T>(source.head_->data);
    Node<T>* temp = source.head_;
    while (temp->next != source.head_) {
      temp = temp->next;
      Node<T>* curr = new Node<T>(temp->data);
      tail_->next = curr;
      tail_ = curr;
    }
    tail_->next = head_;
    return *this;
  }
  

  ~CircularLinkedList() {
    while (head_ != tail_) {
      Node<T>* temp = head_;
      head_ = head_->next;
      delete temp;
    }
    delete tail_;
    head_ = tail_ = nullptr;
  }

  void Ascending(const T& data) {
    if (!head_) {                             //空的 => return data
      head_ = tail_ = new Node<T>(data);
      tail_->next = head_;
      return;
    }
    if (head_->data >= data) {                //第一个最小
      Node<T>* tmp = new Node<T>(data);
      tmp->next = head_;
      head_ = tmp;
      tail_->next = tmp;
      return;
    }
    Node<T>* curr = head_;
    while (curr != tail_ && curr->next->data <= data) {
      curr = curr -> next;
    }
    if (curr == tail_) {                      //data是最大的
      Node<T>* tmp = new Node<T>(data);
      tail_->next = tmp;
      tail_ = tmp;
      tail_->next = head_;
      return;
    }
    Node<T>* tmp = new Node<T>(data);
    tmp->next = curr->next;
    curr->next = tmp;
  }


  void Descending(const T& data) {
    if (!head_) {                            //空的
      head_ = tail_ = new Node<T>(data);
      tail_->next = head_;
      return;
    }
    if (head_->data <= data) {                //第一个最小
      Node<T>* tmp = new Node<T>(data);
      tmp->next = head_;
      head_ = tmp;
      tail_->next = tmp;
      return;
    }
    Node<T>* curr = head_;
    while (curr != tail_ && curr->next->data >= data) {
      curr = curr -> next;
    }
    if (curr == tail_) {                      //data是最大的
      Node<T>* tmp = new Node<T>(data);
      tail_->next = tmp;
      tail_ = tmp;
      tail_->next = head_;
      return;
    }
    Node<T>* tmp = new Node<T>(data);
    tmp->next = curr->next;
    curr->next = tmp;
  }

  void InsertInOrder(const T& data) {
    if (node_order_== Order::kASC) {     //Small => Large
      Ascending(data);
    } else {
      Descending(data);
    }
  }

  void Reverse() {
    if (node_order_ == Order::kASC) {
      node_order_ = Order::kDESC;
    } else {
      node_order_ = Order::kASC;
    }
    if (head_ == nullptr) {
      return;
    }
    if (head_ == tail_) {
      return;
    }
    Node<T>* now = head_;
    Node<T>* after = head_->next;
    while (after != head_) {
      Node<T>* before = after->next;
      after->next = now;
      now = after;
      after = before;
    }
    head_->next = tail_;
    head_ = tail_;
    tail_ = after;
  }

  void Clear();

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os,
                                  const CircularLinkedList<U>& cll);

private:
  Node<T>* head_ = nullptr;
  Node<T>* tail_ = nullptr;
  Order node_order_ = Order::kASC;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const CircularLinkedList<T>& cll) {
  Node<T>* iter = cll.head_;
  // empty list condition
  if (iter == nullptr) {
    os << "Empty list";
    return os;
  }
  // non-empty list condition
  do {
    os << iter->data << '\t';
    iter = iter->next;
  } while (iter != cll.head_);

  return os;
}

#endif


