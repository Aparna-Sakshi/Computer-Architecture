#include<stdio.h>
#include<stdbool.h>
#include<math.h>
#include<stdlib.h>



//example 
//weights = 5,-7,10
//boolean function = xy' + z
//a is given by booleanListGenerator function
bool booleanEvaluator(bool *a)
{
	bool x = a[0];
	bool y = a[1];
	bool z = a[2];
	
	return (x && (!y)) || z;//xy'+z
}

//This function calculates ax+by+cz...
//In this example weights = [5,-7,10] , n = 3
//a is given by booleanListGenerator function
int weightEvaluator(int *weights, bool *a, int n)
{
	int sum = 0;
	for(int i=0;i<n;i++)
	{
		if(a[i])
		{
			sum += weights[i];
		}
	}
	
	return sum;
}

//This function is to generate all possible combinations of n sized boolean array
//in this example there are 8 possible combinations : [false, false, false], [false, false, true]........[true, true, true]
//to generate all possible combinations, iterate 'c' from 0 to 2^n-1
bool* booleanListGenerator(int n, int c)
{
	bool *bool_list = (bool*)malloc(sizeof(bool)*n);
	int i,k;
	for(k=c,i=0;i<n;k/=2,i++)
	{
		if(k%2==1)
		{
			bool_list[i] = true;
		}
		else
		{
			bool_list[i] = false;
		}
		
	}
	
	return bool_list;
}

//This function prints the range of values that T can take
void thresholdRange(int *weights, int n)//n is size of weights array
{
	int max=9999;//initializing max to some large positive value
	int min=-9999;//initializing min to some large negative value
	for(int i=0;i<pow(2,n);i++)//to generate all possible combinations, iterate 'i' aka 'c' from 0 to 2^n-1
	{
		bool *bl = booleanListGenerator(n, i);//bl=bool list
		bool be = booleanEvaluator(bl);//be=output of boolean expression
		int we = weightEvaluator(weights,bl,n);//we=output of weightEvaluator
		
		if (be)
		{
			//if 'be' is true => we=ax + by + cz >= T in order to realize the boolean expression (i.e) xy'+z in this example.
			//max is the minimum value of such 'we'			
			
			max = we<max?we:max;
		}
		else
		{
			//if 'be' is true => we=ax + by + cz < T in order to realize the boolean expression (i.e) xy'+z in this example.
			//min is the maximum value of such 'we'
			min = we>min?we:min;
		}
		
	}
	if(min<max)
		printf("T belongs to (%d,%d]",min,max);
	else
		printf("There is no value of T");
}

int main()
{
	int weights[3]={5,-7,10};
	thresholdRange(weights, 3);
	
	return 0;
}
