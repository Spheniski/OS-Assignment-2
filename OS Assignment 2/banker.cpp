// Banker's Algorithm
// Alex Hill
// 11/29/2021
#include "banker.hpp"
#include <string>
#include <iostream>
using namespace std;

vector<vector<int>> getState(const string& input){
    ifstream file(input);

    if(!file){
        cerr << "Unable to open file." << endl;
        exit(1);
    }

    char ch;
    vector<int> available;
    vector<vector<int>> state;

    while(file >> ch){
        if (ch == ' '){
            vector<int> resource;
            getData(resource, file, ch);
            state.push_back(resource);
        } else if (ch == '(') {
            getData(available, file, ch);
        }
    }
    for(int i = 1; i < state.size(); i+=2){
        for (int j = 0; j < state[0].size(); ++j) {

            // Finds the need of process
            state[i][j] = state[i][j] - state[i - 1][j];
        }
    }

    state.push_back(available);

    file.close();
    return state;
}

void getData(vector<int> &v, ifstream& file, char &ch){
    while ((ch != ')') && (ch != '}') && (file >> ch)) {

        // Looks for integer
        if ((ch >= int('0')) && (ch <= int('9'))) {

            // Convert char to int
            int tempInt = ch - '0';
            file >> ch;

            // if next char is an integer, the integer is 2 digits or more long
            while ((ch >= int('0')) && (ch <= int('9'))) {
                tempInt *= 10;
                tempInt += (ch - '0');
                file >> ch;
            }
            v.push_back(tempInt);
        }
    }
}

string getSafeSeq(const vector<vector<int>>& state) {
    int finishAmt = 0;
    int prevFinishAmt = 0;
    string safetySeq = "<";
    vector<int> work = state[state.size() - 1];            
    vector<bool> finish(((state.size() - 1) / 2), false);

    for (int i = 1; i < (state.size() - 1);) {
        for (int j = 0; ((j < state[0].size()) && !finish[(i - 1) / 2]); ++j) {

            // Process waits if Need <= Work
            if (state[i][j] > work[j]) {
                break;
            } else if (j == (state[0].size() - 1)) {

                ++finishAmt;
                for (int k = 0; k < state[0].size(); ++k) {

                    work[k] += state[i - 1][k];
                }

                finish[(i - 1) / 2] = true;
                safetySeq += char(((i - 1) / 2) + '0');
                if (finishAmt != finish.size()) { safetySeq += ", "; } 
                else { safetySeq += '>'; }
            }
        }

        i += 2;
        // if finishAmt == prevFinishAmt after one full traversal of the state, the system is unsafe
        if ((i > (state.size() - 1)) && (prevFinishAmt == finishAmt)) {
            std::cerr << "Error(2): This system state has no safe sequence." << std::endl;
            exit(2);
        } else if ((i > (state.size() - 1)) && (prevFinishAmt != finishAmt)) {    // reset and attempt the search again
            i = 1;
            prevFinishAmt = finishAmt;
        } else if (finishAmt == finish.size()) {
            break;
        }
    }

    return safetySeq;
}