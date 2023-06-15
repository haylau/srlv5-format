/**
 * @file srlv5-format.cpp
 * @author Hayden Lauritzen (haydenlauritzen@gmail.com)
 * @brief Implementation for srlv5-format
 * @version 0.1
 * @date 2023-06-15
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../inc/srlv5-format.h"

void SRLv5Format::verifyFiles() {

  if (!inputFile.is_open()) {
    throw std::runtime_error("Failed to open input file");
  }

  if (!outputFile.is_open()) {
    throw std::runtime_error("Failed to open output file");
  }
}

bool SRLv5Format::isEmptyRow(string row) {
  return std::all_of(row.begin(), row.end(), [](char c) { return c == ','; });
}

SRLv5Format::SRLv5Format(string inputPath, string outputPath)
    : inputPath(inputPath), outputPath(outputPath), inputFile(inputPath), outputFile(outputPath, std::ios::trunc) {
  verifyFiles();
}

SRLv5Format::~SRLv5Format() {
  inputFile.close();
  outputFile.close();
}

void SRLv5Format::setPaths(string inputPath, string outputPath) {
  this->inputPath = inputPath;
  this->outputPath = outputPath;
}

void SRLv5Format::convert() {
  if (inputPath.empty() || outputPath.empty()) {
    throw std::logic_error("Input or output paths never supplied");
  }

  SRLv5Format::SRLv5Table table(BOARD_SIZE, std::vector<Goal>());

  // Read the CSV file
  int bucketIdx = 0;
  string line;
  while (!inputFile.eof()) {
    if (!std::getline(inputFile, line)) {
      if (bucketIdx != BOARD_SIZE - 1) {
        throw std::runtime_error("Incorrect number of rows in CSV");
      }
      // end of reading
      break;
    }
    // Next bucket is delinated by a row with only commas
    // ex: ,,,,,
    if (isEmptyRow(line)) {
      ++bucketIdx;
      continue;
    }
    std::stringstream parser(line);
    Goal g;
    std::getline(parser, g.name, ',');
    while (std::getline(parser, line, ',')) {
      if (!line.empty()) {
        g.labels.push_back(line);
      }
    }
    table.at(bucketIdx).push_back(g);
  }

  /*
  bingoList[1] = [
    { name: "Hylian Hood", types: ["Clothes","Hylian Gear","Rupee"] },
    { name: "Hylian Tunic", types: ["Clothes","Hylian Gear","Rupee","Rupee"] },
    { name: "Warm Doublet", types: ["Clothes","Cold Resistance","Hateno"] }
  ];
  */

  // Generate JS file
  outputFile << "var bingoList = [];\n";
  for (int bucketIdx = 0; bucketIdx < BOARD_SIZE; ++bucketIdx) {
    outputFile << "bingoList[" << bucketIdx + 1 << "] = [\n";
    for (const auto& goal : table.at(bucketIdx)) {
      outputFile << "\t{ name: \"" << goal.name << "\", types: [";
      for (const auto& label : goal.labels) {
        outputFile << "\"" << label << "\"";
        if (label != goal.labels.back()) {
          outputFile << ",";
        }
      }
      outputFile << "] }";
      if (goal.name != table.at(bucketIdx).back().name) {
        outputFile << ",";
      }
      outputFile << "\n";
    }
    outputFile << "];\nmodule.exports = bingoList;\n";
  }
  outputFile << "module.exports = bingoList;" << std::endl;
}
