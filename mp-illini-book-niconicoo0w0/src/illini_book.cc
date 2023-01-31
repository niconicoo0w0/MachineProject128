#include "illini_book.hpp"
 
std::vector<std::string> IlliniBook::Split(const std::string& str, char delimiter) {
  size_t last = 0;
  std::vector<std::string> substrs;
  for (size_t i = 0; i != str.length(); ++i) {
    if (str.at(i) == delimiter || str.at(i) == '\r') {
      std::string substr = str.substr(last, i - last);
      last = i + 1;
      substrs.push_back(substr);
    }
  }
  if (last != str.size()) {
    std::string substr = str.substr(last, str.length() - last);
    substrs.push_back(substr);
  }
  return substrs;
}
 
bool IlliniBook::AreRelated(int uin_1, int uin_2) const {
  for (size_t i = 0; i < relations_.size(); i++) {
    if (std::stoi(relations_[i][0]) == uin_1 && std::stoi(relations_[i][1]) == uin_2) {
        return true;
    }
    if (std::stoi(relations_[i][0]) == uin_2 && std::stoi(relations_[i][1]) == uin_1) {
      return true;
    }
    if (GetRelated(uin_1, uin_2) != -1) {
      return true;
    }
  }
  return false;
}
 
bool IlliniBook::AreRelated(int uin_1, int uin_2, const std::string &relationship) const {
    if (!AreRelated(uin_1, uin_2)) {
      return false;
    }
    int index = 0;
    for (size_t i = 0; i < relations_.size(); i++) {
        if (std::stoi(relations_[i][0]) == uin_1 && std::stoi(relations_[i][1]) == uin_2) {
            index = i;
        }
        if (relations_[index][3] == relationship) {
          return true;
        }
    }
    return GetRelated(uin_1, uin_2, relationship) != -1;
}
 
int IlliniBook::GetRelated(int uin_1, int uin_2) const {
    std::map<int, int> steps = BFS(uin_1);
    if (steps.find(uin_2) != steps.end()) {
        return steps[uin_2];
    }
    return -1;
}
 
int IlliniBook::GetRelated(int uin_1, int uin_2, const std::string &relationship) const {
    if (!AreRelated(uin_1, uin_2)) {
        return -1;
    }
    std::vector<std::string> input; input.push_back(relationship);
    std::map<int, int> steps = BFS(uin_1, input);
    if (steps.find(uin_2) != steps.end()) {
        return steps[uin_2];
    }
    return -1;
}
 
std::vector<int> IlliniBook::GetSteps(int uin, int n) const {
    std::vector<int> returnit;
    std::map<int, int> steps = BFS(uin);
    for (auto s : steps) {
        if (s.second == n) {
            returnit.push_back(s.first);
        }
    }
    return returnit;
}
 
size_t IlliniBook::CountGroups() const{
    size_t count = 0;
    std::map<int, bool> visited;
    for (const auto& iter : map_) {
      visited[iter.first] = false;
    }
    for (const auto& iter : map_) {
      if (!visited[iter.first]) {
        visited[iter.first] = true;
        auto steps = BFS(iter.first);
        for (const auto& s : steps) {
            visited[s.first] = true;
        }
        count = count + 1;
      } else {
        continue;
      }
    }
    return count;
}
 
  size_t IlliniBook::CountGroups(const std::string &relationship) const {
    size_t count = 0;
	  std::map<int, bool> visited;
    for (const auto& iter : map_) {
      visited[iter.first] = false;
    }
    for (const auto& iter : map_) {
      if (!visited[iter.first]) {
        visited[iter.first] = true;
        std::vector<std::string> input; input.push_back(relationship);
        auto steps = BFS(iter.first, input);
        for (const auto& s : steps) {
          visited[s.first] = true;
        }
        count = count + 1;
      } else {
        continue;
      }
    }
    return count;
  }
 
  size_t IlliniBook::CountGroups(const std::vector<std::string> &relationships) const {
    size_t count = 0;
    std::map<int, bool> visited;
    for (const auto& iter : map_) {
      visited[iter.first] = false;
    }
    for (const auto& iter : map_) {
      if (!visited[iter.first]) {
        visited[iter.first] = true;
        auto steps = BFS(iter.first, relationships);
        for (const auto& s : steps) {
          visited[s.first] = true;
        }
        count = count + 1;
      } else {
        continue;
      }
    }
    return count;
  }
 
  //helper function
  std::map<int, int> IlliniBook::BFS(int uin) const {
    std::map<int, int> returnit;
    std::queue<int> q;
    q.push(uin);   //<uin>
    returnit[uin] = 0;      //{(uin,0)}
    while (!q.empty()) {
      int top = q.front();  //top = uin
      int point = returnit[top]; //point = 0
      q.pop(); //<>
      for (const std::pair<int, std::string>& pairs : map_.at(top)) {  //没有一样的pairs
        if (returnit.find(pairs.first) == returnit.end()) {
          returnit[pairs.first] = point + 1;
          q.push(pairs.first);
        }
      }
    }
    return returnit;
  }
 
  //helper function
  std::map<int, int> IlliniBook::BFS(int uin, const std::vector<std::string>& relationships) const {
    std::map<int, int> returnit;
    std::queue<int> q;
    q.push(uin);   //<uin>
    returnit[uin] = 0;      //{(uin,0)}
    while (!q.empty()) {
      int top = q.front();  //curr = uin
      int point = returnit[top]; //point = 0
      q.pop(); //<>
      for (const std::pair<int, std::string>& pairs : map_.at(top)) {  //uin是0的时候的所有pair
        bool found = true;
        for (const std::string& relation : relationships) {
          if (pairs.second != relation) {
            continue;
          } 
          found = false;                 
          break;
        }
        if (returnit.find(pairs.first) != returnit.end() || found) {
          continue;
        }
        returnit[pairs.first] = point + 1;
        q.push(pairs.first);
      }
    }
    return returnit;
  }