#include <iostream>
using namespace std;

void passFunc(int **a)
{
    for (int i = 0; i < 10; i++)
     	for (int j = 0; j < 10; j++)
     		cout << a[i][j] << " ";
     	cout << endl;
}
int main()
{
	int **array;
	array = new int *[10];
	for(int i = 0; i <10; i++)
		array[i] = new int[10];
	passFunc(array);


	char c[] = "ABC";
	int *ip = (int *)&c;
	// char **ipp = &ip;
	//int i = 7, *ip = &i, **ipp = &ip;


}