#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

int numStates, numSymbols, numFinalStates;


struct State
{
    vector<char> stateId;
    vector<vector<char>> nextState;
};

State findbyChar(char c, State states[]){
    for(int i = 0; i < numStates; i++){
        for(int j = 0; j < states[i].stateId.size(); j++){
            if(states[i].stateId[j] == c)
                return states[i];
        }
    }
    //return NULL;
}

State findbyChar(char c, vector<State> states){
    for(int i = 0; i < states.size(); i++){
        for(int j = 0; j < states[i].stateId.size(); j++){
            if(states[i].stateId[j] == c)
                return states[i];
        }
    }
    //return NULL;
}

vector<State> equivalents[5];


bool inSet(char a, State s){
    for(char b: s.stateId){
        if(a == b)
            return true;
    }
    return false;
}

bool isEqual(State a, State b){
    
    for(int i = 0; i < a.stateId.size(); i++){
        if(a.stateId[i] != b.stateId[i])
            return false;
    }
    return true;
}

void printState(State s){
    for(char c: s.stateId){
        cout << c << ",";
    }
    cout << endl;
}

bool equivalence(char a, char b, State states[], vector<State> prev){
    State p = findbyChar(a,states);
    State q = findbyChar(b,states);
    for(int i = 0; i < numSymbols; i++){
        char k = p.nextState[i][0];
        State kState = findbyChar(k,prev);
        char l = q.nextState[i][0];
        if(!inSet(l,kState)){
            return false;
        }
    }
    return true;
}

bool inArray(char a, char arr[], int n){
    for(int i = 0; i < n; i++){
        if(arr[i] == a){
            return true;
        }
    }
    return false;
}

int main(int argc, char const *argv[])
{
    
    FILE *fp;
    //parse input
    fp = fopen("dfa.txt","r");
    fscanf(fp,"%d",&numStates);
    State states[numStates];
    for(int i = 0; i<numStates; i++){
        State s;
        char c = ' ';
        while (c == ' ' || c == '\n')
            fscanf(fp,"%c",&c);
        s.stateId.push_back(c);
        states[i] = s;
    }

    fscanf(fp,"%d",&numSymbols);
    char symbols[numSymbols];
    for(int i = 0; i < numSymbols; i++)
    {
        char c = ' ';
        while (c == ' ' || c == '\n')
            fscanf(fp,"%c",&c);
        symbols[i] = c;
    }

    //transition table
    for(int i = 0; i < numStates; i++){
        states[i].nextState = vector<vector<char>>(numSymbols);
        for(int j = 0; j < numSymbols; j++)
        {
            char c = ' ';
            while (c == ' ' || c == '\n')
                fscanf(fp,"%c",&c);
            vector<char> nextStates;
            while (c != '\n'){
                if(c != ' ' || c != '\n'){
                    nextStates.push_back(c);
                }
                fscanf(fp,"%c",&c);
            }
            states[i].nextState[j] = nextStates;
        }
    }
    
    //debug print
    for(int i = 0; i < numStates; i++){
        for(int j = 0; j < numSymbols; j++)
        {
            for(int k = 0; k < states[i].nextState[j].size(); k++)
                cout <<  states[i].nextState[j][k];
            
        }
            cout << endl;
    }

    //final states
    fscanf(fp,"%d",&numFinalStates);
    char finalStates[numFinalStates];
    for(int i = 0; i < numFinalStates; i++)
    {
        char c = ' ';
        while (c == ' ' || c == '\n')
            fscanf(fp,"%c",&c);
        finalStates[i] = c;
    }

    //minimize
    vector<State> p;
    State nonFinal,Final;
    for(int i = 0; i < numStates; i++){
        if(!inArray(states[i].stateId[0],finalStates,numFinalStates))
            nonFinal.stateId.push_back(states[i].stateId[0]);
    }
    for(int i = 0; i < numFinalStates; i++){
        Final.stateId.push_back(finalStates[i]);
    }
    p.push_back(nonFinal);
    p.push_back(Final);

    equivalents[0] = p;

    // for(State s: p){
    //     for(char c: s.stateId)
    //         cout << c << ',';
    //     cout << endl;
    // }

    //kth partition

    vector<State> prev = p;
    bool loop = true;
    while(loop){
        vector<State> k;
        for(State s: prev){
            State n;
            n.nextState = vector<vector<char>>(numSymbols);
            char a = s.stateId[0];
            n.stateId.push_back(a);
            for(char b: s.stateId){
                if(a != b && !inSet(b,n)){
                    if(equivalence(a,b,states,prev)){
                        n.stateId.push_back(b);
                        // cout << "Equivalent: " << a << " " << b << " " << endl;
                    }
                }
            }
            // for(char c: n.stateId)
            //     cout << c << ',';
            // cout << endl;

            k.push_back(n);
        }

        //push remaining
        for(State s: prev){
            for(char c : s.stateId){
                int flag = 1;
                for(State r:k){
                    if(inSet(c,r)){
                        flag = 0;
                    }
                }
                if(flag){
                    
                    State n;
                    n.stateId.push_back(c);
                    k.push_back(n);
                }
            }
        }
        bool unequal = false;
        //check equal to prev
        for(State p: prev){
            int flag = 0;
        
            for(State q: k){
                if(isEqual(p,q))
                    flag = 1;
            }
            if(flag == 0){
                unequal = true;
                break;
            }
        }
        if(!unequal){

            loop = false;
        }
        prev = k;
    }
   
    //print prev
    // for(State p: prev){
    //     for(char c: p.stateId)
    //         cout << c << ',';
    //     cout << endl;
    // }

    //assign next states
    for(State p: prev){
        //p.nextState = vector<vector<char>>(numSymbols);
        for(int i = 0; i < numSymbols; i++){
            State s = findbyChar(p.stateId[0], states);
            State next = findbyChar(s.nextState[i][0], prev);
            
            for(char a: next.stateId){
                p.nextState[i].push_back(a);
            }
            // for(char k : p.nextState[i]){
            //     cout << k;
            // }
            // cout << endl;
        }
    }
    for(State s: prev){
        for(int i = 0; i < numSymbols; i++){
            for(char a: s.nextState[i]){
        cout << "EYY" << endl;

                cout << a <<',';
            }
            cout << endl;
        }
    }

    //print result
    for(State p: prev){
        cout << "State ";
        for(char a: p.stateId){
            cout << a << ",";
        }
        cout << endl;
        for(int i = 0; i < numSymbols; i++){
            cout << "On "<<i<<": ";
            for(char a: p.nextState[i]){
                cout << a << ",";
            }
            cout << endl;
        }
        cout << endl;
    }

    return 0;
}
