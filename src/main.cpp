#include <fstream>
#include <iostream>

#include "../inc/srlv5-format.h"

using std::string;

const string USEAGE = "Useage: ./srlv5-format <input.csv> <output.js>";
const int REQ_ARGS = 3;

int main(int argc, char *argv[]) {

  if (argc != REQ_ARGS) {
    std::cout << "Incorrect arguments passed\n";
    std::cout << USEAGE << std::endl;
    return 1;
  }

  string inputPath = argv[1];
  string outputPath = argv[2];

  SRLv5Format formatter(inputPath, outputPath);
  formatter.convert();
}
