#include <bits/stdc++.h> 
using namespace std; 
  
char *removeDuplicate(char str[], int n) 
{ 
    // create a set using string characters 
    // excluding '\0' 
    set<char>s (str, str+n-1); 
  
    // print content of the set 
    int i = 0; 
    for (char x : s) 
       str[i++] = x; 
    str[i] = '\0'; 
  
    return str; 
} 
  
// Driver code 
int main() 
{ 
   char str[]= "geeksforgeeks"; 
   int n = sizeof(str) / sizeof(str[0]); 
   cout << removeDuplicate(str, n); 
   return 0; 
} 