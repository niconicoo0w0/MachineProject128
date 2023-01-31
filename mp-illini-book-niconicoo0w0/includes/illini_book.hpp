#ifndef ILLINI_BOOK_HPP
#define ILLINI_BOOK_HPP

#include "utilities.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <list> 
#include <set>
#include <map>

class IlliniBook {
public:

  IlliniBook(const std::string &people_fpath, const std::string &relations_fpath) {
    std::fstream file1(people_fpath);
    std::string line1;
    if (file1.is_open()) {
      while (std::getline(file1, line1)) {
        person_.push_back(std::stoi(line1));
      }
    } else {
      throw std::runtime_error("can not open file");
    }
    //<1,2,3,6,7,8,9,11,13,15>

    std::fstream file2(relations_fpath);
    std::string line2;
    if (file2.is_open()) {
      while (std::getline(file2, line2)) {
        relations_.push_back(Split(line2, ','));
      }
    } else {
      throw std::runtime_error("can not open file");
    }
    //<<1,3,128>, <3,8,128>, <3,6,128>, <1,2,128>, <2,7,124>, <1,6,124>, <11,13,124>, <13,15,124>, <11,15,124>>

    std::list<std::pair<int, std::string>> list;
    for (size_t i = 0; i < person_.size(); i++) {
      for (size_t j = 0; j < relations_.size(); j++) {
        if (person_[i] == std::stoi(relations_[j][0])) {
          list.push_back(std::make_pair(std::stoi(relations_[j][1]), relations_[j][2]));
        } else if (person_[i] == std::stoi(relations_[j][1])) {
          list.push_back(std::make_pair(std::stoi(relations_[j][0]), relations_[j][2]));
        }
      }
      map_.insert({person_[i], list});
      list.clear();
    }
  }

  void Adj() {
    std::list<int> adj;
    for (size_t i = 0; i < person_.size(); i++) {
      for (size_t j = 0; j < relations_.size(); j++) {
        if (person_[i] == std::stoi(relations_[j][0])) {
          adj.push_back(std::stoi(relations_[j][1]));
        }
      }
      adjacent_.push_back(adj);
      adj.clear();
    }
  }

  std::vector<std::string> Split(const std::string& str, char delimiter);
  IlliniBook(const IlliniBook &rhs) = delete;
  IlliniBook &operator=(const IlliniBook &rhs) = delete;
  ~IlliniBook() = default;

  bool AreRelated(int uin_1, int uin_2) const;
  bool AreRelated(int uin_1, int uin_2, const std::string &relationship) const;
  int GetRelated(int uin_1, int uin_2) const;
  int GetRelated(int uin_1, int uin_2, const std::string &relationship) const;
  std::vector<int> GetSteps(int uin, int n) const;
  void Helper(int index, bool visited[]) const;
  size_t CountGroups() const;
  size_t CountGroups(const std::string &relationship) const;
  size_t CountGroups(const std::vector<std::string> &relationships) const;
  
  //helper function
  std::map<int, int> BFS(int uin) const;
  //helper function
  std::map<int, int> BFS(int uin, const std::vector<std::string>& relationships) const;


private:
  std::vector<int> person_;
  std::vector<std::vector<std::string>> relations_;
  std::map<int, std::list<std::pair<int, std::string>>> map_;
  std::vector<std::list<int>> adjacent_;
};

#endif
