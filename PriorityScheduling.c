#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

const size_t ArraySize = 3;
size_t TurnAround = 0;
size_t RefCount = ArraySize;

struct Proc
{
	size_t BurstTime;
	size_t TurnAround;
	size_t WaitTime;
	size_t Priority;
	_Bool Finished;
};

void Populate(struct Proc* Array)
{
	printf("Enter BurstTime  and Priority\n");
	for(int i = 0; i<ArraySize; i++)
	{
		scanf("%lu",&Array[i].BurstTime);
		scanf("%lu",&Array[i].Priority);
		Array[i].WaitTime = 0;
		Array[i].Finished = 0;
		Array[i].TurnAround = 0;
	}
}

void SJF(struct Proc* Array)
{
	size_t HighestPriority = 0;
	while(RefCount > 0) //ref count maybe off by one creating a infinite loop
	{
		for(int i = 0; i<ArraySize; i++)
		{	
			if((!Array[i].Finished) && (Array[HighestPriority].Priority < Array[i].Priority))
			{
				HighestPriority = i;
			}
		}
		Array[HighestPriority].WaitTime = TurnAround;
		TurnAround += Array[HighestPriority].BurstTime;
		Array[HighestPriority].Finished = 1;
		Array[HighestPriority].TurnAround = TurnAround;
		RefCount --;
		for(int i = 0; i<ArraySize; i++)
		{
			if(!Array[i].Finished)
			{
				HighestPriority = i;
				break; // array reset to a local element to compare
			}
		}
	}
}

void Output(struct Proc* Array)
{
	printf("Process \t TurnAroundTIme \t BurstTime \t WaitTime \t Priority \n");
	for(int i = 0; i<ArraySize; i++)
	{
		printf("%d \t\t\t %d \t\t\t %d \t\t %d \t\t\t %d \n",i,Array[i].TurnAround,Array[i].BurstTime,Array[i].WaitTime,Array[i].Priority);
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
