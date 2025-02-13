#include "functions.hpp"

#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>
#include <vector>
int LongestConsecutiveSubSequence(const std::string& short_tandem_repeat,
                                  const std::string& sequence) {
  int end_before =
      static_cast<int>(sequence.length() - short_tandem_repeat.length()) + 1;
  int max_count = 0;
  int running_count = 0;
  for (int i = 0; i < end_before;) {
    if (sequence.substr(i, short_tandem_repeat.length()) ==
        short_tandem_repeat) {
      running_count++;
      max_count = std::max(max_count, running_count);
      i += static_cast<int>(short_tandem_repeat.length());
    } else {
      running_count = 0;
      i++;
    }
  }
  return max_count;
}

std::vector<std::string> ParseShortTandemRepeats(const std::string& line) {
  std::vector<std::string> sub_strings = utilities::GetSubstrs(line, ',');
  sub_strings.erase(sub_strings.begin());
  return sub_strings;
}

void CleanUpDuplicates(std::map<std::string, std::map<std::string, int>>& map) {
  std::vector<std::map<std::string, int>> duplicate_tracker;
  std::vector<std::map<std::string, int>> duplicates;
  for (const auto& item : map) {
    if (std::find(duplicate_tracker.begin(),
                  duplicate_tracker.end(),
                  item.second) != duplicate_tracker.end()) {
      duplicates.push_back(item.second);
    }
    duplicate_tracker.push_back(item.second);
  }
  std::vector<std::string> to_delete;
  for (const auto& item : map) {
    if (std::find(duplicates.begin(), duplicates.end(), item.second) !=
        duplicates.end()) {
      to_delete.push_back(item.first);
    }
  }
  for (const auto& name : to_delete) {
    map.erase(name);
  }
}

std::string ProfileDNA(const std::string& dna_database,
                       const std::string& dna_sequence) {
  std::cout << "Input dna_database : " << dna_database << std::endl;
  std::cout << "Input dna_sequence : " << dna_sequence << std::endl;
  std::ifstream ifs{dna_database};
  std::string line;
  std::getline(ifs, line);
  std::map<std::string, std::map<std::string, int>> people;
  std::vector<std::string> short_tandem_repeats = ParseShortTandemRepeats(line);
  for (; std::getline(ifs, line); line = "") {
    std::vector<std::string> sub_strings = utilities::GetSubstrs(line, ',');
    std::string name = sub_strings[0];
    sub_strings.erase(sub_strings.begin());
    int index_of_short_tandem_repeat = 0;
    for (const std::string& short_tandem_repeat_count : sub_strings) {
      people[name][short_tandem_repeats[index_of_short_tandem_repeat]] =
          std::stoi(short_tandem_repeat_count);
      index_of_short_tandem_repeat++;
    }
  }
  CleanUpDuplicates(people);
  std::map<std::string, int> person_sequence;
  for (const std::string& short_tandem_repeat : short_tandem_repeats) {
    person_sequence[short_tandem_repeat] =
        LongestConsecutiveSubSequence(short_tandem_repeat, dna_sequence);
  }
  for (const auto& person : people) {
    if (person.second == person_sequence) {
      return person.first;
    }
  }
  return "No match";
}
// write your implementation here... we strongly encourage that you leverage
// additional functions to define this behavior.
