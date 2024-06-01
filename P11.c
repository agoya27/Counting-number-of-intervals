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

//Struct Interval represents each input Interval
typedef struct Interval {
  int a;
  int b;
}Interval;

int ReadFile(struct Interval * interval_array, FILE * fptr);
int LeftEnd(struct Interval * interval_array,int num_intervals);
int RightEnd(struct Interval * interval_array,int num_intervals);
void CountInterval(struct Interval * interval_array,int left_end,int right_end,int num_intervals);

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
    struct Interval intervals[30000];
    int num_intervals = ReadFile(intervals,fp);

    timespec_get( &now1, TIME_UTC );
	now_1 = ((long int) now1.tv_sec) * 1000 + ((long int) now1.tv_nsec)/1000000;

    int left_end = LeftEnd(intervals,num_intervals);
    int right_end = RightEnd(intervals,num_intervals);
    CountInterval(intervals,left_end,right_end,num_intervals);

    timespec_get( &now2, TIME_UTC );
	now_2 = ((long int) now2.tv_sec) * 1000 + ((long int) now2.tv_nsec)/1000000;

	diff = now_2 - now_1;  //difference stores the time taken to run the program
    printf("Time for finding the maximum number: %ld ms\n",diff);

    return 0;
}

void CountInterval(struct Interval * interval_array,int left_end,int right_end,int num_intervals)
{
    int max_count =0;
    int max_point = 0;
    for(int i=left_end+1;i<right_end;i++)
    {
        int l_count = 0;
        for(int j=0;j<num_intervals;j++)
        {
            if((i > interval_array[j].a) && (i < interval_array[j].b))
            {
                l_count++;
                if(l_count > max_count)
                {
                    max_count = l_count;
                    max_point = i;
                }
            }
        }
    }
    printf("\nBrute force program for finding max number of intervals\nMaximum number of intervals: %d\n",max_count);
    printf("The intervals include the point: %d\n",max_point);
}

int RightEnd(struct Interval * interval_array,int num_intervals)
{
    int max_point = interval_array[0].b;
    for(int i=1;i<num_intervals;i++)
    {
        if(interval_array[i].b > max_point)
        {
            max_point = interval_array[i].b;
        }
    }
    return max_point;
}

int LeftEnd(struct Interval * interval_array,int num_intervals)
{
    int min_point = interval_array[0].a;
    for(int i=1;i<num_intervals;i++)
    {
        if(interval_array[i].a < min_point)
        {
            min_point = interval_array[i].a;
        }
    }
    return min_point;
}

//Function to read the file and store interval points
int ReadFile(struct Interval * interval_array, FILE * fptr)
{
    char lines[50];
    int num_point =0;
    while(fgets(lines,sizeof(lines),fptr) != NULL)  //Lines are read from the file one at a time
    {
        char *line_content;
        line_content = strtok(lines, "    ");  //file is broken into 2 parts using string token function
        interval_array[num_point].a = atof(line_content);

        line_content = strtok(NULL, "    \n");
        interval_array[num_point].b = atof(line_content);

        //First token is stored as starting point and 2nd token as ending point of interval
        num_point++;
    }
    return num_point;
}