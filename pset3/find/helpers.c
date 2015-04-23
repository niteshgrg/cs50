/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    int beg,end,mid;
    beg=0;
    end=n-1;
    
    while(end>=beg)
    {
        mid=(beg+end)/2;
        if(value==values[mid])
        {
            return true;
        }
        else if(value<values[mid])
        {
            end=mid-1;
        }
        else
        {
            beg=mid+1;
        }

    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    int i,temp,j,swap=0;
    for(j=0;j<n-1;j++)
    {
        for(i=0;i<n-1;i++)
        {
           if(values[i+1]<values[i])
            {
                temp=values[i+1];
                values[i+1]=values[i];
                values[i]=temp;
                swap=1;
            }   
        }
        if(swap==0)
        {
            break;
        }
    }
    
}
