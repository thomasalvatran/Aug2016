//----------------------/home/tovantran/Ctest/Aug29ArrayPointer.cpp
//Thinking of C++ media //????Review???? September 01 2016 (Thursday)
#include <stdio.h>

int main()
{
	int a[][4] = {{0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 0, 1}};
	int (*p)[4] = a;
	size_t nrow = sizeof a /sizeof a[0];
	size_t ncol = sizeof a[0] /sizeof a[0][0];
	printf("nrow = %ld, ncol = %ld\n", nrow, ncol);
	printf("sizeof(*p) == %ld\n", sizeof *p);
	for (int i = 0; i < nrow; ++i)
	{
		for (int j = 0; j < ncol; j++)
			printf("%d ", p[i][j]);  //a[i][j]
		printf("\n");
	}
	printf("size row %ld %ld\n", sizeof(a), sizeof(a[0]));
	printf("size col %ld %ld\n", sizeof(a[0]), sizeof(a[0][0]));
	printf("%d %d \n",a[1][0], a[1][1] );

	int** arr = new int*[3]; //row
	// printf("size of **arr %ld\n", sizeof(arr));
	for (int i = 0; i < 3; i++)
		arr[i] = new int[4];  //a row has 4 colums 

	arr[2][3] = 111;
	
	printf("%ld %ld\n", sizeof(arr), sizeof(arr[0])); //size??

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
			printf("%d ", arr[i][j]);
		printf("\n");
	}
	for(int i = 0; i < 3; ++i) {
    	delete [] arr[i]; //3 rows each row has 4 colums
	}
    delete [] arr;
}
