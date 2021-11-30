#include "banker.hpp"
#include <iostream>
using namespace std;

int main(){
    cout << "Welcome to the Banker's Algorithm!" << endl;
    cout << "This program is designed to find the Safe Sequence given the computer's current state." << endl;
    cout << "Just include a .txt file of the current state in the appropriate format, similar to the one provided." << endl;
    cout << "The Algorithm will now look for the Safe Sequence from the file." << endl;
    cout << endl;
    
    cout << "Searching for the safe sequence..." << endl;

    vector<vector<int>> state = getState("data.txt");
    std::string safetySeq = getSafeSeq(state);
    
    cout << "The safe sequence is: " << safetySeq ;
    
}