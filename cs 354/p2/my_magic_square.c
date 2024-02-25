////////////////////////////////////////////////////////////////////////////////
// Main File:        my_magic_square.c
// This File:        my_magic_square.c
// Other Files:      
// Semester:         CS 354 Lecture 001      SPRING 2024
// Grade Group:      gg9  
// Instructor:       deppeler
// 
// Author:           Ria Sharma
// Email:            rsharma78@wisc.edu
// CS Login:         ria
//
/////////////////////////// SEARCH LOG //////////////////////////////// 
// Online sources: do not rely web searches to solve your problems, 
// but if you do search for help on a topic, include Query and URLs here.
// IF YOU FIND CODED SOLUTIONS, IT IS ACADEMIC MISCONDUCT TO USE THEM
//                               (even for "just for reference")
// Date:   Query:                      URL:
// --------------------------------------------------------------------- 
// 
// 
// 
// 
// 
// AI chats: save a transcript.  No need to submit, just have available 
// if asked.
/////////////////////////// COMMIT LOG  ////////////////////////////// 
//  Date and label your work sessions, include date and brief description
//  Date:   Commit Message: 
//  -------------------------------------------------------------------
// 	2/15	learned how to create a magic square
// 	2/17	completed and getSize() and started fileOutputMagicSquare()
//  2/18	completed fileOutputMagicSquare()
//  2/19	allocated memory for *generateMagicSquare()
//  2/20	worked on siamese method for for *generateMagicSquare()
//  2/21	finished siamese method for for *generateMagicSquare()
//  2/23	completed main function
///////////////////////// OTHER SOURCES OF HELP ////////////////////////////// 
// Persons:          none
// Date:   Name (email):   Helped with: (brief description)
// ---------------------------------------------------------------------------
// 
//////////////////////////// 80 columns wide ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Copyright 2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission, CS 354 Spring 2024, Deb Deppeler
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure that represents a magic square
typedef struct {
	int size;           // dimension of the square
	int **magic_square; // pointer to heap allocated magic square
} MagicSquare;

/* TODO:
 * Promps the user for the magic square's size, read it,
 * check if it's an odd number >= 3 (if not, display the required
 * error message and exit)
 *
 * return the valid number
 */
int getSize() {
    int size;
    printf("Enter magic square's size (odd integer >=3)\n");
    scanf("%d", &size);
    if (size < 3) {
        if (size % 2 == 0) {
            printf("Magic square size must be odd.\n");
        exit(1);
        }
        printf("Magic square size must be >= 3.\n");
        exit(1);
    } else if (size % 2 == 0) {
        printf("Magic square size must be odd.\n");
        exit(1);
    }
    return size; 
} 

/* TODO:
 * Makes a magic square of size n,
 * and stores it in a MagicSquare (on the heap)
 *
 * It may use the Siamese magic square algorithm 
 * or alternate from assignment 
 * or another valid algorithm that produces a magic square.
 *
 * n - the number of rows and columns
 *
 * returns a pointer to the completed MagicSquare struct.
 */
MagicSquare *generateMagicSquare(int n) {
    //allocate memory for MagicSquare structure
	MagicSquare *ms = (MagicSquare *)malloc(sizeof(MagicSquare));
    if (!ms) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    ms->size = n;
    //allocate memory for the rows
    ms->magic_square = (int **)malloc(n * sizeof(int *));
    if (!ms->magic_square) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    //allocate memory for each row & initialize elements to 0
    for (int i = 0; i < n; i++) {
        *(ms->magic_square + i) = (int *)malloc(n * sizeof(int));
        if (!*(ms->magic_square + i)) {
            printf("Memory allocation failed\n");
            exit(1);
        }
        for (int j = 0; j < n; j++) {
            *(*((ms->magic_square + i)) + j) = 0; 
        }
    }
    //siamese method
    int num = 1;
    int i = 0;
    int j = n / 2; 
    //loop to place all nums 1 to n*n into the magic square
    while (num <= n * n) {
        if (i < 0 && j >= n) {
            i += 2;
            j--;
        } 
        else {
            if (j == n) {
                j = 0;
            }
            if (i < 0) {
                i = n - 1;
            }
        }
        if (*(*((ms->magic_square + i)) + j) != 0) {
            i += 2;
            j--;
            continue;
        } 
        else {
            *(*((ms->magic_square + i)) + j) = num++;
        }
        i--; //move up
        j++; //move right
    }
    return ms;
} 

/* TODO:  
 * Opens a new file (or overwrites the existing file)
 * and writes the magic square values to the file
 * in the specified format.
 *
 * magic_square - the magic square to write to a file
 * filename - the name of the output file
 */
void fileOutputMagicSquare(MagicSquare *magic_square, char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("Error opening file\n");
        exit(1);
    }
    
    fprintf(fp, "%d\n", magic_square->size);
    for (int i = 0; i < magic_square->size; i++) {
        for (int j = 0; j < magic_square->size; j++) {
            fprintf(fp, "%d", *(*(magic_square->magic_square + i) + j));
            if (j < magic_square->size - 1) fprintf(fp, ",");
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

/* TODO:
 * Generates a magic square of the user specified size and
 * outputs the square to the output filename.
 * 
 * Add description of required CLAs here
 */
int main(int argc, char **argv) {
	// TODO: Check input arguments to get output filename
    if (argc != 2) {
        printf("Usage: ./my_magic_square <output_filename>\n");
        return 1;
    }
	// TODO: Get magic square's size from user
    int size = getSize();
	// TODO: Generate the magic square by correctly interpreting 
	//       the algorithm(s) in the write-up or by writing or your own.  
	//       You must confirm that your program produces a 
	//       Magic Sqare as described in the linked Wikipedia page.
    MagicSquare *magic_square = generateMagicSquare(size);
	// TODO: Output the magic square
    fileOutputMagicSquare(magic_square, *(argv + 1));
    //free memory
    for (int i = 0; i < size; i++) {
        free(*(magic_square->magic_square + i)); 
    }
    free(magic_square->magic_square);
    free(magic_square);
    return 0;
} 

// Spring 2024



