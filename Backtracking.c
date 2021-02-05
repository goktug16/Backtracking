#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int colors(int ** color_ar,int N,int,char color_array[8][10]);  // Finding if there can be a unique rows and column situation with backtracking method
int is_okey(int **color_ar, int N, int row);   // it checks if duplicate occurs in column return -1 if columns has unique indexes returns 1 , 
//starts from row which given  function  as parameter , if row = 2 it checks all columns starting from 2 
void right_shift(int **color_ar,int N,int row);  // it right shift given row by one
void print_array(int **color_ar,int N,char color_array[8][10]);  // to print array 

int main()
{
	int N,system_flag = 1; // N , and flag for ending the program
	char color_array[8][10] = {{"Red"},{"Yellow"},{"Blue"},{"Purple"},{"Orange"},{"Black"},{"White"},{"Green"}}; // defined colors
	int *selected_colors;  // selected colors indexes which is taken from user
	int i,j,x,z=0;  // loop variables
	int **color_ar; // Array which inputs taken from user
	int index = -1; // to check duplicate color in rows
	int result; // colors return value
	int Nflag = 0; // to check N value is between 3 and 8
	char input[20];  // Color from User
	
	while(system_flag == 1)
	{
		printf("Enter N:  ");
		while(Nflag == 0)   // takes N value
		{
			scanf("%d",&N);
			if(N >= 3 && N <= 8)
				Nflag++;	
			if(Nflag == 0)
			{
				printf("N should be between 3 and 8 \n");
				printf("Enter N:  ");
			}	
		}
		int duplicate = 0;
	
		selected_colors = (int *)malloc(N*sizeof(int)); // dynamic memory allocation for arrays
		color_ar = (int **)malloc(N*sizeof(int *));

		for(i=0 ; i<N ; i++)
		{
			color_ar[i] = (int *)malloc(N*sizeof(int));
		}
	
		
		for(i=0; i<N; i++)
		{
			selected_colors[i] = -2;
			for(j=0; j<N; j++)
				color_ar[i][j]= -2;
		}
	
			
		printf("Colors in system: ");
		for(i=0 ; i<8; i++)
			printf("%s  ",color_array[i]);
			printf("\n");
		i = 0;
		j = 0;
		printf("\nSelect %d different colors for your table : \n",N);
		while(i<N)    // taking inputs(colors) from user
		{
			printf("Enter color %d: ",i);
			scanf("%s",input);
			for(x=0; x<8 ; x++)
			{
				if(strcmp(input,color_array[x]) == 0)
					index = x;
			}
			if(index == -1)
				printf("Select some color from system colors\n");
			else
			{
				for(j=0; j<i ; j++)
				{
					if(selected_colors[j] == index)
						index = -1;
				}
				if(index == -1)
					printf("Duplicate colors in same row\n");
				else
				{
					selected_colors[i] = index;
					i++;
				}
				
			}
		index = -1;
		}	
		printf("\n");
		i=0;
		j=0;
		x=0;
		while(i<N)
		{
			while(j<N)
			{
				z = 0;
				printf("Enter color of Row:%d Column: %d :  ",i,j);
				scanf("%s",input);
				for(x=0; x<8 ; x++)
				{
					if(strcmp(input,color_array[x]) == 0)
						index = x;
				}
				if(index != -1)
				{
					for(x=0; x<N ; x++)
					{
						if(index == color_ar[i][x])
							index = -3;
					}
					if(index == -3)
						printf("Duplicate color error, enter again.\n");
					else
					{
						for(x=0; x<N ; x++)
						{
							if(index == selected_colors[x])
								z = 1;
						}
					}
					if(z == 1)
					{
						color_ar[i][j]= index;
						j++;
					}
					else if(index >= 0)
						printf("This color in system but not among selected colors\n");
				}	
				else
					printf("This color not defined in the system.\n");		
				index = -1;
			}
			i++;
			j=0;		
		}
		result = colors(color_ar,N,0,color_array);
		if(result == 1)
		{
			printf("---------------------- \n");
			printf("Array has solution\n");
			print_array(color_ar,N,color_array);
			printf("\n\n---------------------- \n");
		}
		else
			printf("There is no solution for that array\n");
		
		printf("\n Press 1 if you want to enter new table , press any key other than if you want to exit: ");
		scanf("%d",&system_flag);
		free(selected_colors);
		free(color_ar);	
		Nflag = 0;
		i=0;
		j=0;
		x=0;
		z=0;
		result = -1;
		index = -1;
	}
	
	return 0;
}
void print_array(int **color_ar,int N,char color_array[8][10])
{
	int i,j;
	for(i=0 ; i<N ; i++)
	{
		printf("\n");
		for(j=0; j<N; j++)
		printf("%-4s ",color_array[color_ar[i][j]]);
	}
}
int is_okey(int **color_ar, int N, int row)
{
	int i=0;
	int j;
	int temp_row = row;
	while(i < row)
	{
		for(j=0 ; j<N ; j++)
		{
//			printf("%d %d \n",color_ar[i][j],color_ar[temp_row][j]);
			if(color_ar[i][j] == color_ar[temp_row][j])
				return -1;
		}
		i++;	
	}
	return 1;
}
void right_shift(int **color_ar,int N,int row)
{
	int temp = color_ar[row][N-1];
	int i = N-2;
	while(i >= 0)
	{
		color_ar[row][i+1] = color_ar[row][i];
		i--;
	}
	color_ar[row][0] = temp;
}
int colors(int ** color_ar,int N,int row,char color_array[8][10])
{
	
	int i,j;
	int loop = 0;

	if(row >= N)
		return 1;

	while(loop < N)
	{
		if(is_okey(color_ar,N,row) == 1)
		{
			if(row != 0)
			{
				printf("Row: %d ",row);
				print_array(color_ar,N,color_array);
				printf("\n\n");
			}
			if(colors(color_ar,N,row+1,color_array) == -1)
			{
				right_shift(color_ar,N,row);
				loop++;	
			}
			else
				return 1;
				
		}
		else
		{
			right_shift(color_ar,N,row);
			loop++;
		}
	}
	if(loop == N)
		return -1;
}
	
