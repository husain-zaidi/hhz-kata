#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int numStates, numSymbols;
vector<int> nullState;


class State
{
public:
    vector<int> stateId;
    vector<vector<int>> nextState;
};

int main(int argc, char const *argv[])
{
    string line;
    
    fstream fio;
    fio.open("sample.txt");

    fio >> numStates;
    fio >> numSymbols;
    char symbols[numSymbols];
    State states[numStates];
    nullState.push_back(-1);
    int initialState,finalState;
    for(int i = 0; i < numSymbols; i++){
        fio >> symbols[i];
    }
    stringstream ss;
    for(int i = 0; i < numStates; i++){
        for(int j = 0; j < numSymbols; j++){
            getline(fio,line);
            
            ss << line;
            int c;
            while(!ss.eof()){
                ss >> c;
                states[i].nextState[j].push_back(c);
            cout << "ewewew" << endl;
            }
                
        }
    }
    return 0;
}
