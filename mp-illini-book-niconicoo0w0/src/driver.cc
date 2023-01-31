#include "illini_book.hpp"
#include "illini_book.cc"
#include <iostream>

int main() {
  IlliniBook book("/home/vagrant/src/mp-illini-book-niconicoo0w0/example/persons.csv", "/home/vagrant/src/mp-illini-book-niconicoo0w0/example/relations.csv");

  // /////////////////////////////////////

  // // /////////////////////////////////////

  // std::cout << book.GetRelated(1, 2) << std::endl; //1
  // std::cout << book.GetRelated(3, 2) << std::endl;	//2
  // std::cout << book.GetRelated(1, 9) << std::endl;	//-1  

  // // /////////////////////////////////////

  // std::cout << book.GetRelated(1, 2, "128") << std::endl; //1
  // std::cout << book.GetRelated(1, 2, "124") << std::endl; //-1
  // std::cout << book.GetRelated(1, 6, "128") << std::endl; //2
  // std::cout << book.GetRelated(1, 6, "124") << std::endl; //1

  // // /////////////////////////////////////
  std::cout << book.CountGroups() << std::endl; //	3
  std::cout << book.CountGroups("128") << std::endl; //6
  std::cout << book.CountGroups("124")	<< std::endl; //6
  std::cout << book.CountGroups("173")	<< std::endl; //10

  // // /////////////////////////////////////

  std::cout << book.CountGroups(std::vector<std::string>{ "128", "173" })	<< std::endl; //6
  std::cout << book.CountGroups(std::vector<std::string>{ "128", "124", "173" })	<< std::endl; //3

  return 0;
}
