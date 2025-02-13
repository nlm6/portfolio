#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <map>
#include <string>
#include <vector>

#include "utilities.hpp"

std::string ProfileDNA(const std::string& dna_database,
                       const std::string& dna_sequence);
std::vector<std::string> ParseShortTandemRepeats(const std::string& line);
int LongestConsecutiveSubSequence(const std::string& short_tandem_repeat,
                                  const std::string& sequence);
void CleanUpDuplicates(std::map<std::string, std::map<std::string, int>>& map);
#endif