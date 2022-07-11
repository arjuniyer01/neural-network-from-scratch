#include "matrix.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXCHAR 100

/* Basic Functionality */

/*
 * Function: matrix_create
 * ----------------------------
 *   Creates a matrix by mallocing
 *
 *   row: number of rows
 *   col: number of columns
 *
 *   returns: void
 */
Matrix* matrix_create(int row, int col) {
	Matrix *matrix = malloc(sizeof(Matrix));
	matrix->rows = row;
	matrix->cols = col;
	matrix->entries = malloc(row * sizeof(double*));
	for (int i = 0; i < row; i++) {
		matrix->entries[i] = malloc(col * sizeof(double));
	}
	return matrix;
}

/*
 * Function: matrix_free
 * ----------------------------
 *   Frees the memory allocated to the matrix
 *
 *   *m: matrix struct pointer
 *
 *   returns: void
 */
void matrix_free(Matrix *m) {
	for (int i = 0; i < m->rows; i++) {
		free(m->entries[i]);
	}
	free(m);
	m = NULL;
}

/*
 * Function: matrix_fill
 * ----------------------------
 *   Fills the matrix with the value 'n' passed to it
 *
 *   *m: matrix struct pointer
 *   n: the integer value that fills the matrix
 *
 *   returns: void
 */
void matrix_fill(Matrix *m, int n) {
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			m->entries[i][j] = n;
		}
	}
}

/*
 * Function: matrix_print
 * ----------------------------
 *   Prints out the matrix currently being held at the pointer.
 *
 *   *m: matrix struct pointer
 *
 *   returns: void
 */
void matrix_print(Matrix* m) {
	printf("Rows: %d Columns: %d\n", m->rows, m->cols);
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			printf("%1.3f ", m->entries[i][j]);
		}
		printf("\n");
	}
}

/* Data Piping Functionality */

/*
 * Function: matrix_save
 * ----------------------------
 *   Save a Matrix to a file
 *
 *   m*: matrix struct pointer
 *   char*: pointer to string with filename
 *
 *   returns: void
 */
void matrix_save(Matrix* m, char* file_string) {
	FILE* file = fopen(file_string, "w");
	fprintf(file, "%d\n", m->rows);
	fprintf(file, "%d\n", m->cols);
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			fprintf(file, "%.6f\n", m->entries[i][j]);
		}
	}
	printf("Successfully saved matrix to %s\n", file_string);
	fclose(file);
}

/*
 * Function: matrix_load
 * ----------------------------
 *   Load a Matrix from a file
 *
 *   char*: pointer to string with filename
 *
 *   returns: matrix struct pointer
 */
Matrix* matrix_load(char* file_string) {
	FILE* file = fopen(file_string, "r");
	char entry[MAXCHAR]; 
	fgets(entry, MAXCHAR, file);
	int rows = atoi(entry);
	fgets(entry, MAXCHAR, file);
	int cols = atoi(entry);
	Matrix* m = matrix_create(rows, cols);
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			fgets(entry, MAXCHAR, file);
			m->entries[i][j] = strtod(entry, NULL);
		}
	}
	printf("Sucessfully loaded matrix from %s\n", file_string);
	fclose(file);
	return m;
}

/* TODO: Advanced Functionality */ 
