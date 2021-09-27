//totally weird behaviour that may come up, gcc defines size_t as unsigned long so %d or %ul make work while clang does unsigned long long
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

const size_t ArraySize = 10;
size_t TurnAround = 0;
size_t RefCount = ArraySize;

struct Proc
{
	size_t BurstTime;
	size_t TurnAround;
	size_t WaitTime;
	_Bool Finished;
};

void Populate(struct Proc* Array)
{
	printf("Enter BurstTime \n");
	for(int i = 0; i<ArraySize; i++)
	{
		scanf("%lu",&Array[i].BurstTime);
		Array[i].WaitTime = 0;
		Array[i].Finished = 0;
		Array[i].TurnAround = 0;
	}
}

void SJF(struct Proc* Array)
{
	size_t largest = 0;
	while(RefCount > 0)
  {
		for(int i = 0; i<ArraySize; i++)
		{	
			if((!Array[i].Finished) && (Array[largest].BurstTime < Array[i].BurstTime))
			{
				largest = i;
			}
		}
		Array[largest].WaitTime = TurnAround;
		TurnAround += Array[largest].BurstTime;
		Array[largest].Finished = 1;
		Array[largest].TurnAround = TurnAround;
		RefCount --;
		for(int i = 0; i<ArraySize; i++)
		{
			if(!Array[i].Finished)
			{
				largest = i;
				break; // array reset to a local element to compare
			}
		}
	}
}

void Output(struct Proc* Array)
{
	printf("Process \t TurnAroundTIme \t BurstTime \t WaitTime \t \n");
	for(int i = 0; i<ArraySize; i++)
	{
		printf("%d \t\t\t %d \t\t\t %d \t\t\t %d \n",i,Array[i].TurnAround,Array[i].BurstTime,Array[i].WaitTime);
	}
}

int main()
{
	struct Proc* Array = malloc((sizeof(struct Proc)* ArraySize));
	Populate(Array);
	SJF(Array);
	Output(Array);
	return 0;
}
