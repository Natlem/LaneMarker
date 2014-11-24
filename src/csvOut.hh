#ifndef CSVOUT_HH
# define CSVOUT_HH

#include <utility>
#include <dirent.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "convert.hh"
#include "detectEdge.hh"
#include "threshold.hh"
#include "hough.hh"


void parseDir(std::string string, std::string dstFile);
std::pair<double, double> getLanes(std::string str);
void writeLine(std::string& str, std::pair<double, double> pair, std::ofstream& out);
#endif
