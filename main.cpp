#include <iostream>
#include <omp.h>
#include <stdio.h>

#define VECTOR_LENGTH 15
using namespace std;

int getModulo5(int value);

int main()
{
    int *A; // input vector
    int *B; // output vector
    int i;
    int threadID;

    // A,B are shrared betweeen threads but i,threadID are private for each thread
    #pragma omp parallel shared(A,B) private(i,threadID)
    {
        // single makes the following block executed on a single thread
        #pragma omp single
        {
            A = new int[VECTOR_LENGTH];
            B = new int[VECTOR_LENGTH];

            cout <<"Enter input vector (A) " << VECTOR_LENGTH <<" elements : \n"<<endl;
            cout <<"Please enter an Integer only." << endl;

            // Enter Vector A
            for (i=0; i< VECTOR_LENGTH; i++)
            {
                printf("A[%d] : ",i);
                cin >> A[i];

            }
            threadID = omp_get_thread_num();
            printf("\nThread# %d is used in Single clause\n\n",threadID);
        }

        #pragma omp for
            for (i=0; i< VECTOR_LENGTH; i++)
            {
                B[i] = getModulo5(A[i]);
                threadID = omp_get_thread_num();
                printf("Thread # %d executed iteration #%d\n",threadID,i);
            }

    }
        cout <<"\nInput/Output Pairs : "<<endl;
        // print input/output pairs
        for(i=0; i<VECTOR_LENGTH; i++)
         {
           cout <<"Result of "<< A[i] << "  % 5 is  " << B[i]<<endl;
         }

    return 0;
}
    /**
     * @brief getModulo5
     * @param value
     * @return 0 if value can be devided by 5 or
     *         1 if it isn't
     */
    int getModulo5(int value)
    {
        if((value % 5) == 0)
            return 1;
        else
            return 0;
    }

