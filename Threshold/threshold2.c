#include<stdio.h>
#include<stdbool.h>
#include<math.h>
#include<stdlib.h>



//example x.y    [5,g,7]
//input:[5,7]
//boolean function = xy
//a is given by booleanListGenerator function
bool booleanEvaluator(bool *a, bool val)//val=value of variable which has missing weight, in this case it is y
{
	bool x = a[0];
	bool y = val;
	
	
	return (x && y);//xy
}

//This function calculates ax+cz+..-T or 5x-7 in this example
//In this example weights = [5,7] , n = 2
//a is given by booleanListGenerator function
int weightEvaluator(int *weights, bool *a, int n)
{
	int sum = 0;
	int T=weights[n-1];
	for(int i=0;i<n-1;i++)
	{
		
		if(a[i])
		{
			sum += weights[i];
		}
	}
	
	return T-sum;
}

//This function is to generate all possible combinations of n sized boolean array
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
	bool flag=true;
	for(int i=0;i<pow(2,n-1);i++)
	{
		bool *bl = booleanListGenerator(n-1, i);//bl=bool list
		
		int we = weightEvaluator(weights,bl,n);//we=output of weightEvaluator
		bool y;
		
		//case 1 y=true
		bool be = booleanEvaluator(bl,true);//be=output of boolean expression		
		if (!be)
		{
			//if 'be' is false => we=T-ax.. > g in order to realize the boolean expression (i.e) xy in this example.
			//max is the minimum value of such 'we'			
			
			max = we<max?we:max;
		}
		else
		{
			//if 'be' is true => we=T-ax.. <= g in order to realize the boolean expression (i.e) xy in this example.
			//min is the maximum value of such 'we'
			min = we>min?we:min;
		}
		
		//case 2 y=false
		be = booleanEvaluator(bl,false);//be=output of boolean expression		
		if (!be)
		{
			//if 'be' is false => we=T-ax.. > 0 in order to realize the boolean expression (i.e) xy in this example.
			//max is the minimum value of such 'we'		
			flag=(we>0)?true:false;	
			
			
		}
		else
		{
			//if 'be' is true => we=T-ax.. <= 0 in order to realize the boolean expression (i.e) xy in this example.
			//min is the maximum value of such 'we'
			flag=(we<=0)?true:false;	
		}
		//flag is for validation, if flag is false, then there is no solution to the inequality
		
		
	}
	if(min<max && flag)
		printf("T belongs to [%d,%d)",min,max);
	else
		printf("There is no value of T");
}

int main()
{
	int weights[2]={5,7};
	thresholdRange(weights, 2);
	
	return 0;
}
