/*
 * =====================================================================================
 *
 *       Filename:  selection.c
 *
 *    Description:  switch statement
 *
 *        Version:  1.0
 *        Created:  07/19/2019 10:32:15 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Fritz Mehner (mn), mehner@fh-swf.de
 *        Company:  FH Südwestfalen, Iserlohn
 *
 * =====================================================================================
 */

#include <stdio.h>


void print_day(int day)
{
    switch (day) {
    case 1:
        printf("Monday\n");
        break;
    case 2:
        printf("Tuesday\n");
        break;
    case 3:
        printf("Wednesday\n");
        break;
    case 4:
        printf("Thursday\n");
        break;
    case 5:
        printf("Friday\n");
        break;
    case 6:
        printf("Saturday\n");
        break;
    case 7:
        printf("Sunday\n");
        break;
    default:
        printf("Illegal day number\n");
        break
    }        
}

int main(void)
{
    print_day(2);
    return 0;
}    
