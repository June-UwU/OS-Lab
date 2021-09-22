#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("Parent Proc");
	fork();
	printf("Parent and Child Proc");//the no of proc is 2^(n-1)
	return 0;
}
