#ifndef BANKER_HPP
#define BANKER_HPP

#include <vector>
#include <fstream>
using namespace std;

vector<vector<int>> getState(const string&);        //Grabs current state from text file
void getData(vector<int>&, ifstream&, char&);       //Organizes file
string getSafeSeq(const vector<vector<int>>&);      //Finds safe sequence

#endif