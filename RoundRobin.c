#include <stdio.h>

typedef _Bool bool;
const size_t CPUTime = 1;
const size_t ArraySize = 3;
size_t G_TurnAround = 0;
size_t RefCount = 0;

struct Proc
{
	int Temp;
	size_t WaitTime;
	size_t BurstTime;
	size_t TurnAround;
	bool Finished;
};

void Populate(struct Proc* Array)
{
	RefCount = ArraySize;
	for(int i = 0; i < ArraySize; i++)
	{
		printf("BurstTime : \n");
		scanf("%llu",&Array[i].BurstTime);
		Array[i].TurnAround = 0;
		Array[i].WaitTime = 0;
		Array[i].Finished = 0;
		Array[i].Temp = Array[i].BurstTime;
	}
}

void RoundRobin(struct Proc* Array)
{
	while(RefCount > 0)
	{
		for(int i = 0; i <ArraySize;i++)
		{
			if(!Array[i].Finished)
			{
				Array[i].Temp -= CPUTime;
				G_TurnAround += CPUTime;
				if(Array[i].Temp <= 0)
				{
					Array[i].WaitTime = G_TurnAround - Array[i].BurstTime;
					Array[i].Finished = 1;
					Array[i].TurnAround = G_TurnAround + Array[i].BurstTime - 1;
					RefCount--;
				}
			}	
		}
	}
}

void Print(struct Proc* Array)
{
	printf("Process \t BurstTime \t WaitTime \t TurnAround \n");
	for(int i = 0; i < ArraySize; i++)
	{
		printf("%d \t\t %lu \t\t %lu \t\t %lu \n",i,Array[i].BurstTime,Array[i].WaitTime,Array[i].TurnAround);
	}
}

int main()
{
	struct Proc Array[ArraySize];
	Populate(Array);
	RoundRobin(Array);
	Print(Array);
	return 0;
}
