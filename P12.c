/*
Name: Anurag Goyal
ID  : 1096870
Date: March 13, 2023
Assignment Number: 3
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef struct Interval {
  int a;
  char b;
}Interval;

int ReadFile(int * open_interval_array,int * close_interval_array,FILE * fptr);
void Sort_interval(int * arr,int left,int right);
void Sort_call(int * arr,int left,int mid,int right);
void create_interval(struct Interval * interval_array,int * start, int * end, int num_intervals);
void Total_Sort(struct Interval * interval_array,int left,int right);
void Total_Sort_call(struct Interval * arr,int left,int mid,int right);
void Find_Interval(struct Interval * intervals,int num_intervals);

int main()
{
    char f_name[30];
    long int now_1=0, now_2 =0, diff =0;
	struct timespec now1;
	struct timespec now2;
    printf("Welcome to the Program.\nPlease enter the name of the file to read data intervals: ");
    scanf(" %s",f_name);

    FILE* fp = fopen(f_name,"r");
    if(fp == NULL)
    {
        printf("\nFile could not be opened\n");
        return 0;
    }
    struct Interval intervals[60000];
    int Start_interval_arr[30000];
    int End_interval_arr[30000];
    int num_intervals = ReadFile(Start_interval_arr,End_interval_arr,fp);

    timespec_get( &now1, TIME_UTC );
	now_1 = ((long int) now1.tv_sec) * 1000 + ((long int) now1.tv_nsec)/1000000;

    Sort_interval(Start_interval_arr,0,num_intervals-1);
    Sort_interval(End_interval_arr,0,num_intervals-1);
    create_interval(intervals,Start_interval_arr, End_interval_arr,num_intervals);
    Total_Sort(intervals,0,(2*num_intervals)-1);
    Find_Interval(intervals,num_intervals);

    timespec_get( &now2, TIME_UTC );
	now_2 = ((long int) now2.tv_sec) * 1000 + ((long int) now2.tv_nsec)/1000000;

	diff = now_2 - now_1;  //difference stores the time taken to run the program
    printf("Time for finding the maximum number: %ld ms\n",diff);
    return 0;
}

void Find_Interval(struct Interval * intervals,int num_intervals)
{
    int max = 0;
    int sum = 0;
    int max_i =0;
    for(int i=0;i<((2*num_intervals)-1);i++)
    {
        if(intervals[i].b == 's')
        {
            sum++;
        }
        if(intervals[i].b == 'e')
        {
            sum--;
        }
        if(sum > max)
        {
            max = sum;
            max_i = i;
        }
    }
    printf("Maximum number of intervals %d\n",max-1);
    printf("The intervals include the point %d \n",intervals[max_i+1].a);
}

void Total_Sort(struct Interval * interval_array,int left,int right)
{
    if(left<right)
    {
        int mid = left + (right-left)/2;
        Total_Sort(interval_array,left,mid);
        Total_Sort(interval_array,mid+1,right);
        Total_Sort_call(interval_array,left,mid,right);
    }
}

void Total_Sort_call(struct Interval * arr,int left,int mid,int right)
{
    int i,j,k;
    int num1 = mid-left+1;
    int num2 = right-mid;
    struct Interval L[num1],R[num2];

    for(i=0;i<num1;i++)
    {
        L[i] = arr[left+i];
    }
    for(j=0;j<num2;j++)
    {
        R[j] = arr[mid+1+j];
    }
    i=0;
    j=0;
    k=left;

    while(i<num1 && j<num2)
    {
        if(L[i].a <= R[j].a)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while(i<num1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while(j<num2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void create_interval(struct Interval * interval_array,int * start, int * end, int num_intervals)
{
    for(int i=0;i<num_intervals;i++)
    {
        interval_array[i].a = end[i];
        interval_array[i].b = 'e';
    }
    for(int i=0;i<num_intervals;i++)
    {
        interval_array[i+num_intervals].a = start[i];
        interval_array[i+num_intervals].b = 's';
    }
}

//Function to read the file and store interval points
int ReadFile(int * open_interval_array,int * close_interval_array,FILE * fptr)
{
    char lines[50];
    int num_point =0;
    while(fgets(lines,sizeof(lines),fptr) != NULL)  //Lines are read from the file one at a time
    {
        char *line_content;
        line_content = strtok(lines, "    ");  //file is broken into 2 parts using string token function
        open_interval_array[num_point] = atof(line_content);

        line_content = strtok(NULL, "    \n");
        close_interval_array[num_point] = atof(line_content);

        //First token is stored as starting point and 2nd token as ending point of interval
        num_point++;
    }
    return num_point;
}

void Sort_interval(int * arr,int left,int right)
{
    if(left<right)
    {
        int mid = left + (right-left)/2;
        Sort_interval(arr,left,mid);
        Sort_interval(arr,mid+1,right);
        Sort_call(arr,left,mid,right);
    }
}

void Sort_call(int * arr,int left,int mid,int right)
{
    int i,j,k;
    int num1 = mid - left + 1;
    int num2 = right - mid;
    int L[num1],R[num2];

    for(i = 0;i<num1;i++)
    {
        L[i] = arr[left+i];
    }
    for(j=0;j<num2;j++)
    {
        R[j] = arr[mid+1+j];
    }

    i=0;
    j=0;
    k=left;

    while(i<num1 && j<num2)
    {
        if(L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while(i<num1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while(j<num2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}