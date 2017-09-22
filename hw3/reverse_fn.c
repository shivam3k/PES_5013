/****************************************************************************
* @author - Shivam Khandelwal
* @date - Sept 15, 2017
*
* @file - reverse_fn_main.c
* @brief - function to reverse the elements of an array using pointers
*
* Function Description - reverse(char *str, int length) is a funtion
*                        which reverses the elements of array of
*                        length 'l' using the *str pointer. Another
*                        pointer *l is used to swap the array elements
*                        stored at the memory locations which *str points.

*****************************************************************************/

/**
* @param  - str pointer to an array element
* @param  - length to indicate the length of array
* @return - the function returns 0 if str is not a null pointer and length
*           is greater than zero but return 8 (Non-zero value) if the function fails.
**/


#include <stdio.h>
#include <stdlib.h>

/******************* reverse function declaration **********************/

char reverse(char *str, int length);

/*************** main function *****************************************/

int main()
{
    /****************** string declaration *******************/

    char a[] = "This is a string.";
    char b[] = "some NUMmbers12345";
    char c[] = "Does it reverse \n\0\t correctly?";

    /**************** Printing original strings **************/

    printf("Original Strings - \n\na.\t%s\nb.\t%s\nc.\t%s\n\n",a,b,c);

    /****** Reversing strings using reverse function *********/

    reverse(a,17);
    reverse(b,18);
    reverse(c,30);

    /**************** Printing reversed strings **************/

    printf("Reversed Strings - \n\na.\t%s\nb.\t%s\nc.\t%s\n\n",a,b,c);

    return 12;
}



/******************** Reverse function defintion **************************/

char reverse(char *str, int length)
{
    /**variable k initialized to indicate the length**/
    int k = length - 1;
    /**variable p initialized to zero**/
    int p = 0;
    /**char variable a initialized for *l pointer **/
    char a;
    char *l;
    /**char *l initialized to ve used for swappping **/
    l = &a;
    /**condtion to check null pointer and array length (if zero)**/
    if((str != NULL)&(length >0))
    {
    /**loop condition to swap array elements**/
    while(p < k-p)
    {
        *l = *(str + p); //swapping array elements stored at memory loactions pointed by *str pointer)
        *(str + p) = *(str + k  - p);
        *(str + k  - p) = *l;
        p++; // increment p
    }
    return 0; //return 0 if function is successfully executed
    }

else
    {
    return 8;//return 8 (non-zero)if function fails
    }
}

/******************************* END ******************************************/
