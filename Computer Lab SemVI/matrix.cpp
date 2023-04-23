#include <iostream>
#include <pthread.h>

using namespace std;

int first[10][10], second[10][10], ans[10][10];
int m, n, p, q;

void* multiply(void* args)
{
    //multiplying
    for(int i = 0; i < m; i++){
        for(int j = 0; j < q; j++){
            int sum = 0;
            for(int k = 0; k < p; k++)
                sum += first[i][k] * second[k][j];
            ans[i][j] = sum;
            cout << i << " " << j << " = "<< sum << endl;
        }
    }
}

int main(int argc, char const *argv[])
{
    
   
    cout << "Enter the rows and columns of first matrix: ";
    cin >> p >> q;
    cout << "Enter the elements of the first matrix" << endl;
    for(int i = 0; i < p; i++){
        for(int j = 0; j < q; j++){
            cin >> first[i][j];
        }
    }

    cout << "Enter the rows and columns of second matrix: ";
    cin >> m >> n;
    cout << "Enter the elements of the second matrix" << endl;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            cin >> second[i][j];
        }
    }


    //m threads
    pthread_t threads[m];
    for(int i = 0; i < m; i++){
        pthread_create(&threads[i],NULL,multiply,NULL);
    }

    for(int i = 0; i < m; i++){
        pthread_join(threads[i],NULL);
    }

    cout << "Result" << endl;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < q; j++){
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
