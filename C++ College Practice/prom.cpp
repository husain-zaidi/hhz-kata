/*
// Sample code to perform I/O:

#include <iostream>

using namespace std;

int main() {
	int num;
	cin >> num;										// Reading input from STDIN
	cout << "Input number is " << num << endl;		// Writing output to STDOUT
}

// Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail
*/

// Write your code here
#include <iostream>

using namespace std;

char paired(int boys[], int girls[], int m, int n){
    if(n < m){
        return 'n';
    }else{
        for(int i = 0 ; i < m; i++){
            girls[0] = boys[i];
            int p = 1;
            int flag = 0;
            for(int q = 1; q<n; q++){
                if(girls[q] < girls[p]){
                    flag = 1;
                    break;
                }
            }
            if(flag == 0){
                return 'n';
            }
        }    
        return 'y';
    }
}

int main(){
    int testCases, m, n;
    //input
    cin >> testCases;
    char ans[testCases];
    //loop
    for(int p = 0; p < testCases; p++){
        cin >> m >> n;
        int boys[m];
        int girls[n+1];
        for(int i = 0; i < m; i++){
            cin >> boys[i];
        }
        for(int i = 1; i < n+1; i++){
            cin >> girls[i];
        }
        ans[p] = paired(boys,girls,m,n);
    }
    
    for(int p = 0; p < testCases; p++){
        if(ans[p] == 'y')
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    
    return 0;
}