#include <iostream>

#include "circular-linked-list.hpp"

int main() {
  CircularLinkedList<int> cll;
  cll.InsertInOrder(7);
  cll.InsertInOrder(1);
  cll.InsertInOrder(0);
  cll.InsertInOrder(5);
  cll.InsertInOrder(2);
  cll.InsertInOrder(3);
  cll.InsertInOrder(4);
  cll.InsertInOrder(4);
  cll.InsertInOrder(8);
  cll.InsertInOrder(9);
  cll.InsertInOrder(10);
  cll.Reverse();
  cll.Reverse();

  CircularLinkedList<int> cll3;
  cll3 = cll;
  cll3.InsertInOrder(1);
  std::cout << cll3 << std::endl;
  cll3.Reverse();
  std::cout << cll3 << std::endl;
  std::cout << "没有寄";
}

// memcheck command:
// valgrind --tool=memcheck --leak-check=yes --track-origins=yes bin/exec