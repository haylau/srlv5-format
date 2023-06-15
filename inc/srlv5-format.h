/**
 * @file srlv5-format.h
 * @author Hayden Lauritzen (haydenlauritzen@gmail.com)
 * @brief Header for srlv5-format
 * @version 0.1
 * @date 2023-06-15
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

using std::string;

class SRLv5Format {

  const int BOARD_SIZE = 25;

private:
  struct Goal {
    string name;
    std::vector<string> labels;
  };
  using SRLv5Table = std::vector<std::vector<Goal>>;

  string inputPath;
  string outputPath;
  std::ifstream inputFile;
  std::ofstream outputFile;

  void verifyFiles();
  static bool isEmptyRow(string row);

public:
  SRLv5Format() = default;
  SRLv5Format(string inputPath, string outputPath);
  ~SRLv5Format();

  void setPaths(string inputPath, string outputPath);
  void convert();
};
