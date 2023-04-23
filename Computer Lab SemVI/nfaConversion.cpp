#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <string.h>

using namespace std;

int numStates, numSymbols;
vector<int> nullState;


class State
{
public:
    vector<int> stateId;
    vector<vector<int>> nextState;
};

char* convStrToChar(string str){
    char *cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    return cstr;
}

State createState(vector<int> nextState, State states[])
{
    State s;
    s.stateId = nextState;
    //union
    for(int i = 0; i < numSymbols; i++){
        vector<int> temp;
        for(int j = 0; j < s.stateId.size(); j++){
            //this line is gonna be epic
            for(int k = 0; k < states[j].nextState[i].size(); k++){
                if(states[j].nextState[i][k] != -1)
                    temp.push_back(states[j].nextState[i][k]);
            }
        }
        //add null
        if(temp.size() == 0){
            temp.push_back(-1);
        }
        s.nextState[i] = temp;
    }
    return s;
}

void buildDFA(State n, vector<State> dfaStates, State states[]){
    for(int i = 0; i < numSymbols; i++){
        //find if nextState is in dfa or not, ignore null
        for(int j = 0; j < dfaStates.size(); j++){
            if(dfaStates[j].stateId == n.nextState[i] || n.nextState[i] == nullState)
                return;
        }
        State s = createState(n.nextState[i], states);
        dfaStates.push_back(s);
        buildDFA(s,dfaStates,states);
        
    }
}

int main(int argc, char const *argv[])
{
    string line;
    
    fstream fio;
    fio.open("sample.txt");

    fio >> numStates;
    fio >> numSymbols;
    char symbols[numSymbols];
    State *states = new State[numStates];
    nullState.push_back(-1);
    int initialState,finalState;
    for(int i = 0; i < numSymbols; i++){
        fio >> symbols[i];
    }
    stringstream ss;
    for(int i = 0; i < numStates; i++){
        for(int j = 0; j < numSymbols; j++){
            getline(fio,line);
            // cout << line <<"blue"<< endl;
            // ss << line;
            // string c;
            // int f;
            // while(!ss.eof()){
            //     ss >> c;
            //     // cout << c << "   sadsada    " << endl;
            //     if (stringstream(c) >> f){
            //         cout << f << " hwghhr"; 
            //         states[i].nextState[j].push_back(f);

            //     } 
            // }
            vector<int> internal;

            char *cstr = convStrToChar(line);

            char* pch = strtok (cstr," ");
            while (pch != NULL){
                internal.push_back(atoi(pch));
                pch = strtok (NULL, " ");
            }
            states[i].nextState[j] = internal;            
        }
    }
cout << "EYYY" << endl;
    fio >> initialState >> finalState;
    vector<State> dfaStates;
    State initial;
    initial.stateId.push_back(initialState);
    cout<<"hello\n";
    initial.nextState = states[initialState].nextState;
    dfaStates.push_back(initial);
    
    buildDFA(initial,dfaStates,states);
    

    cout << "RESULT" << endl;
    for(int i = 0; i < dfaStates.size(); i++){
        for(int j = 0; j < dfaStates[i].stateId.size(); j++){
            cout << dfaStates[i].stateId[j];
        }
        cout << "      ";
        for(int j = 0; j < dfaStates[i].nextState.size(); j++){
            for(int k = 0; k < dfaStates[i].nextState[j].size(); k++)
                cout << dfaStates[i].nextState[j][k];
            cout << "    ";
        }
        cout << endl;
    }

    return 0;
}


