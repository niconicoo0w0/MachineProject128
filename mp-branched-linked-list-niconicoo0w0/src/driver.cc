#include <iostream>

#include "branched-linked-list.hpp"

int main() {
  /* EXAMPLE INTERACTIONS WITH BLL */
  BLL* first = new BLL();
  first->PushBack('h');
  first->PushBack('i');

  std::cout << first->ToString() << std::endl; // hi
  std::cout << first->Size() << std::endl; // 2

  /////////////////////////////////////

  BLL* second = new BLL();
  second->PushBack('i');
  second->PushBack('!');
  second->PushBack('@');

  std::cout << second->ToString() << std::endl; // i!@
  std::cout << second->Size() << std::endl; // 3

  /////////////////////////////////////

  first->Join(1, second);

  std::cout << first->ToString() << std::endl; // hii!@
  std::cout << first->Size() << std::endl; // 5

  std::cout << second->ToString() << std::endl; // i!@
  std::cout << second->Size() << std::endl; // 3

  /////////////////////////////////////

  BLL* first_clone = new BLL();
  *first_clone = *first;

  std::cout << first_clone->ToString() << std::endl; // hii!@
  std::cout << first_clone->Size() << std::endl; // 5

  std::cout << first_clone->GetAt(0) << std::endl;
  std::cout << first_clone->GetAt(1) << std::endl;
  std::cout << first_clone->GetAt(2) << std::endl;
  std::cout << first_clone->GetAt(3) << std::endl;
  std::cout << first_clone->GetAt(4) << std::endl;
  // std::cout << first_clone->GetAt(5) << std::endl;

  first_clone->SetAt(0, '!');
  std::cout << first_clone->ToString() << std::endl;
  first_clone->SetAt(2, '?');
  std::cout << first_clone->ToString() << std::endl;
  first_clone->SetAt(4, '&');
  std::cout << first_clone->ToString() << std::endl;


  return 0;
}
