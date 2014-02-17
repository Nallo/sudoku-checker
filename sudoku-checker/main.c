//
//  main.c
//  sudoku-checker
//
//  Created by stefano on 24/11/13.
//  Copyright (c) 2013 stefano. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define INVALID 0

#pragma mark - prototypes

int **rows_calloc(int N);
int **columns_calloc(int N);
int **sudoku_calloc(int N);
int ***squares_calloc(int N);
int read_sudoku_line(int N, int **rows, int **columns, int ***m_squares, int line);

int check_rows(int row, int number, int N, int **rows);
int check_columns(int col, int number, int N, int **columns);
int check_squares(int row, int col, int number, int N, int ***m_squares);


#pragma mark - main

int main(int argc, const char * argv[])
{
    int T;
    int N;
    int i;
    
    // read the T
    fscanf(stdin,"%d",&T);
    
    for (i=0; i<T; i++) {
        
        // read the N
        fscanf(stdin, "%d", &N);
        
        int **rows = rows_calloc(N);
        int **columns = columns_calloc(N);
        int ***m_squares = squares_calloc(N);
        
        int j;
        
        // read each line of the solution i
        for (j=0; j<N*N; j++) {
        
            if(read_sudoku_line(N,rows,columns,m_squares,j)==INVALID){
                
                fprintf(stdout, "Case #%d: No\n", i+1);
                j++;
                
                // read all the other rows
                while (j<N*N) {

                    char buf[128];
                    fgets(buf, 128, stdin);
                    j++;
                }
                j=-1;
                break;
            }
        }
        if(j==N*N)
            fprintf(stdout, "Case #%d: Yes\n", i+1);

    }
    return 0;
}

#pragma mark - functions

int read_sudoku_line(int N, int **rows, int **columns, int ***m_squares, int line){
    
    int i;
    
    for (i=0; i<N*N; i++) {
    
        int number = 0;
        fscanf(stdin, "%d ", &number);
        
        if (check_rows(line, number, N, rows)==INVALID ||
            check_columns(i, number, N, columns)==INVALID ||
            check_squares(line, i, number, N, m_squares)==INVALID){
            
            // read all the others elements of the row
            i++;
            while (i<N*N) {
                fscanf(stdin, "%d ", &number);
                i++;
            }
            return INVALID;
        }
    }
    
    return !INVALID;
}

int check_squares(int row, int col, int number, int N, int ***m_squares){
    
    if(number==0 || number>N*N)
        return INVALID;
    
    number--;
    
    if (m_squares[row/N][col/N][number]==1) {
        return INVALID;
    } else {
        m_squares[row/N][col/N][number] = 1;
        return !INVALID;
    }
    
}

int check_columns(int col, int number, int N, int **columns){
    
    if(number==0 || number>N*N)
        return INVALID;
    
    number--;

    if (columns[col][number]==1) {
        return INVALID;
    } else {
        columns[col][number] = 1;
        return !INVALID;
    }
    
}

int check_rows(int row, int number, int N, int **rows){
    
    if(number==0 || number>N*N)
        return INVALID;

    number--;
    
    if (rows[row][number]==1) {
        return INVALID;
    } else {
        rows[row][number] = 1;
        return !INVALID;
    }
    
}

#pragma mark - alloc functions

int **rows_calloc(int N){
    
    int i;
    
    int **p = (int**) calloc(N*N, sizeof(int*));

    for (i=0; i<N*N; i++)
        p[i] = (int*) calloc(N*N, sizeof(int));
    
    return p;
}

int **columns_calloc(int N){
    
    int i;
    
    int **p = (int**) calloc(N*N, sizeof(int*));
    
    for (i=0; i<N*N; i++)
        p[i] = (int*) calloc(N*N, sizeof(int));
    
    return p;
}

int **sudoku_calloc(int N){
    
    int i;
    
    int **p = (int**) calloc(N*N, sizeof(int*));
    
    for (i=0; i<N*N; i++)
        p[i] = (int*) calloc(N*N, sizeof(int));
    
    return p;
}

int ***squares_calloc(int N){
    
    int i,j;
    
    int ***p = (int***) calloc(N, sizeof(int**));
    
    for(i=0 ; i<N ; i++){
        
        p[i] = (int**) calloc(N, sizeof(int*));
        
        for(j=0 ; j<N ; j++)
            p[i][j] = (int*) calloc(N*N, sizeof(int));
    }
    return p;
}