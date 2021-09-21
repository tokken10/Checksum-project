/*=====================================================
   Assignment:  pa02 - Calculating an 8, 16, or 32 bit checksum
|                       for a simple ASCII file containing only ASCII
|                       characters. This file is terminated by a NEWLINE
|                       character which has a hexadecimal value of ’0a’.
|
|       Author:  Benjamin Osante
|     Language:  c, c++, Java
|
|   To Compile:  gcc -o pa02 pa02.c|
|     p
|
|   To Execute:  c    -> ./pa02 inputFilename.txt 8
|
|
|         Note:  All input files are simple 8 bit ASCII input
|
|        Class:  CIS3360 - Security in Computing - Summer 2021
|   Instructor:  McAlpin
|     Due Date:  07/26/2021
|
+=============================================================================*/



#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

void print_80(char *str)
{
    for (int i = 0; i < strlen(str); i++)
    {
      if (i % 80 == 0)
       printf("\n");
    printf("%c",str[i]);

    }
  }

unsigned long int calculate_8bit(char *input)
{
    int result = 0;
    for (int i = 0; i < strlen(input); i++)
    {
    result += input[i];
    }

    return result;
}


unsigned long int calculate_16bit(char *input)
{
    int result_16 = 0;
    for (int i = 0; i < strlen(input);)
    {
      result_16 += input[i] << 8;
      result_16 += (input[i + 1]);
      i+=2;
    }

    return result_16;
}


unsigned long int calculate_32bit(char *input)
{
    unsigned long int result_32 = 0;
    for (int i = 0; i < strlen(input);)
    {
        result_32 += input[i] << 24;
        result_32 += (input[i + 1]) << 16;
        result_32 += (input[i + 2]) << 8;
        result_32 += (input[i + 3]);
        i+=4;
    }

        return result_32;
}


int main(int argc, char **argv)
{
    FILE *inputfile;
    char *input, *output, *checksum, c = 'x';

    unsigned long int result = 0;
    unsigned long int result_16 = 0;
    unsigned long int result_32 = 0;

    int i = 0;
    int checksum_size = 0;


    if (argc != 3)
    {
       printf("Error! Insufficient arguments are provided at command line.\n");

    }


    checksum_size = atoi(argv[2]);
    if (checksum_size != 8 && checksum_size != 16 && checksum_size != 32)
    {
      printf("Valid checksum sizes are 8, 16, or 32\n");

    }


    if (!(inputfile = fopen(argv[1],"r")))
    {
      fprintf(stderr, "Could not open \"%s\"\n", argv[1]);

    }


    input = malloc(sizeof(char) * 1000);
    while (fscanf(inputfile, "%c", &c) != EOF && i < 1000)
    {
      input[i] = c;
      i++;
    }
      input[i] = '\0';


    fclose(inputfile);

    switch (checksum_size)
    {
      case 8:
      result = calculate_8bit(input);
      print_80(input);
      printf("\n");

    printf("%2d bit checksum is %8lx for all %4d chars\n", checksum_size, result & 0xff, (int)strlen(input));

    break;


    case 16:
    if(strlen(input) % 2)
    strcat(input,"X");
    print_80(input);
    printf("\n");
    result_16 = calculate_16bit(input);

    printf("%2d bit checksum is %8lx for all %4d chars\n", checksum_size, result_16 & 0xffff, (int)strlen(input));

    break;


    case 32:
    while(strlen(input) % 4)
    strcat(input,"X");
    print_80(input);
    printf("\n");
    result_32 = calculate_32bit(input);

    printf("%2d bit checksum is %8lx for all %4d chars\n", checksum_size, result_32 & 0xffffffff, (int)strlen(input));

    break;
    }

    return 0;
}




// I Benjamin Osante (be940343) affirm that this program is| entirely my own work and that I have neither developed my code together with| any another person, nor copied any code from any other person, nor permitted| my code to be copied  or otherwise used by any other person, nor have I| copied, modified, or otherwise used programs created by others. I acknowledge| that any violation of the above terms will be treated as academic dishonesty.+=============================================================================*/
