#include <iostream>

using namespace std;

struct Process
{
    int cylinder;
    int toa;
    int processTime;
};

int seekTime = 0;
int processingTime = 0;
Process user_request[8];
int reqArray[200];
int headPos;
bool moveLeft = true;

int findByCylinder(int cylinder){
    for(int i = 0; i < 8; i++){
        if(cylinder == user_request[i].cylinder)
        {
            return user_request[i].processTime;
        }
    }
}

int main(int argc, char const *argv[])
{
    //init req array
    for(int i = 0; i < 200; i++){
        reqArray[i] = 0;
    }

    //user input
    for(int  i = 0; i < 8; i++)
    {
        cout << "Enter Cylinder Number, Time of Arrival, Process Time: "<< endl;
        Process p;
        cin >> p.cylinder >> p.toa >> p.processTime;
        user_request[i] = p;
    }
    headPos = user_request[0].cylinder;
    processingTime += user_request[0].processTime;
    int j = 0;
    int processed = 1;
    //run scan
    for(int i = 0; i < 200; i++)
    {
        //keep in queue if arrived
        if(processingTime >= user_request[j].toa)
        {
            reqArray[user_request[j].cylinder] = 1;
            j++;
        }
        //move 
        if(headPos == 0){
            moveLeft = false;
        }
        if(moveLeft)
            headPos--;
        else
        {
            headPos++;
        }
        if(reqArray[headPos]){
            //process
            reqArray[headPos] = 0;
            processingTime += findByCylinder(headPos);
            processed++;
        }else
        {
            processingTime++;
        }
        if(processed == 8)
            break;
        
    }
    cout << endl;
    cout << processingTime << " ms" << endl;
    cout << processed << endl;
    
    return 0;
}
