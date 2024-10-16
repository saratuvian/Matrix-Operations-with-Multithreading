#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complex.h>
#include <ctype.h>

#define MAX_SIZE 100
int isInteger=0;

typedef struct {
    int rows;
    int cols;
    double complex data[MAX_SIZE][MAX_SIZE];
} Matrix;


Matrix parse_matrix(char *input) {
    Matrix mat;
    sscanf(input, "(%d,%d:", &mat.rows, &mat.cols);
    char *values = strchr(input, ':') + 1;
    char *token = strtok(values, ",)");
    int i = 0, j = 0;
    while (token != NULL) {
        double real, imag;
        if (sscanf(token, "%lf%lfi", &real, &imag) == 2) {
            mat.data[i][j] = real + imag * I;
        }
        else if (sscanf(token, "%lfi", &imag) == 1) {
            if(strstr(token,"i")!=NULL) {//check if regular number
                mat.data[i][j] = imag * I;
            }
            else{
                mat.data[i][j] = real;
                isInteger=1;
            }
        }
        token = strtok(NULL, ",)");
        j++;
        if (j == mat.cols) {
            j = 0;
            i++;
        }
    }
    return mat;
}


void print_matrix(Matrix mat) {
    printf("(%d,%d:", mat.rows, mat.cols);

    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) {
            double real = creal(mat.data[i][j]);
            double imag = cimag(mat.data[i][j]);

            // Print the matrix elements
            if(real!=0) {
                if(isInteger) {
                    if (imag == 0) {
                        if (real == (int) real) {
                            // Print integer values without decimal point
                            printf("%.0f", real);
                        } else {
                            // Print floating point values with one decimal place
                            printf("%.1f", real);
                        }
                    }
                    else{
                        if (imag < 0) {
                            if (real == (int) real) {
                                printf("%.0f-%.0fi", real, imag);
                            } else {
                                printf("%.1f-%.1fi", real, imag);
                            }
                        }
                        else {
                            if (real == (int) real) {
                                printf("%.0f+%.0fi", real, imag);
                            } else {
                                printf("%.1f+%.1fi", real, imag);
                            }
                        }
                    }
                }
                else {
                    if (imag < 0) {
                        if (real == (int) real) {
                            printf("%.0f-%.0fi", real, imag);
                        } else {
                            printf("%.1f-%.1fi", real, imag);
                        }
                    } else if(imag==0){
                        if (real == (int) real) {
                            // Print integer values without decimal point
                            printf("%.0f", real);
                        } else {
                            // Print floating point values with one decimal place
                            printf("%.1f", real);
                        }
                    }
                    else {
                        if (real == (int) real) {
                            printf("%.0f+%.0fi", real, imag);
                        } else {
                            printf("%.1f+%.1fi", real, imag);
                        }
                    }
                }
            }
            else {
                if(imag!=0) {
                    if (imag == (int) imag) {
                        // Print integer values without decimal point
                        printf("%.0fi", imag);
                    } else {
                        // Print floating point values with one decimal place
                        printf("%.1fi", imag);
                    }
                }
                else{//for regular number
                    if (imag == (int) imag) {
                        // Print integer values without decimal point
                        printf("%.0f", imag);
                    } else {
                        // Print floating point values with one decimal place
                        printf("%.1f", imag);
                    }
                }
            }

            if (i != mat.rows - 1 || j != mat.cols - 1) {
                printf(",");
            }

        }
    }
    printf(")");
}

Matrix add_matrices(Matrix a, Matrix b) {
    Matrix result = a;
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }
    return result;
}

Matrix sub_matrices(Matrix a, Matrix b) {
    Matrix result = a;
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[i][j] = a.data[i][j] - b.data[i][j];
        }
    }
    return result;
}

Matrix mul_matrices(Matrix a, Matrix b) {
    Matrix result = {a.rows, a.cols, {{0}}};
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < b.cols; j++) {
            for (int k = 0; k < a.cols; k++) {
                result.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }
    return result;
}

Matrix transpose_matrix(Matrix a) {
    Matrix result = {a.rows, a.cols, {{0}}};
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[j][i] = a.data[i][j];
        }
    }
    return result;
}

Matrix and_matrices(Matrix a, Matrix b) {
    Matrix result = a;
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            if ((creal(a.data[i][j]) != 0 && creal(a.data[i][j]) != 1) ||
                (creal(b.data[i][j]) != 0 && creal(b.data[i][j]) != 1)) {
                printf("ERR\n");
                return result;
            }
            result.data[i][j] = ((int)creal(a.data[i][j]) & (int)creal(b.data[i][j])) + 0.0 * I;
        }
    }
    return result;
}

Matrix or_matrices(Matrix a, Matrix b) {
    Matrix result = a;
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            if ((creal(a.data[i][j]) != 0 && creal(a.data[i][j]) != 1) ||
                (creal(b.data[i][j]) != 0 && creal(b.data[i][j]) != 1)) {
                printf("ERR\n");
                return result;
            }
            result.data[i][j] = (int)creal(a.data[i][j]) | (int)creal(b.data[i][j]);
        }
    }
    return result;
}

Matrix not_matrix(Matrix a) {
    int flag = 0;
    Matrix result = {a.rows, a.cols, {{0}}};  // Initialize result with zeroes

    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            if (creal(a.data[i][j]) != 0 && creal(a.data[i][j]) != 1) {
                flag = 1;  // Set the flag to indicate an error
                break;  // Break out of the inner loop
            }
            result.data[i][j] = !(int)creal(a.data[i][j]) + 0.0*I;  // Perform the NOT operation
            if(flag){
                printf("ERR\n");
                break;
            }
        }
        if (flag){
            result.rows = 0;  // Set rows to 0 to indicate an error
            result.cols = 0;  // Set cols to 0 to indicate an error
        }
    }
    return result;  // Return the result or error matrix
}

int main() {
    char input1[128], input2[128], operation[16];
    while (1) {
        scanf("%s", input1);
        if (strcmp(input1, "END") == 0) break;
        Matrix mat1 = parse_matrix(input1);
        scanf("%s", input2);
        if (strcmp(input2, "TRANSPOSE") == 0) {
            Matrix result = transpose_matrix(mat1);
            print_matrix(result);
        }
        else if (strcmp(input2, "NOT") == 0) {
            Matrix result = not_matrix(mat1);
            // Check if result indicates an error
            if (result.rows > 0 && result.cols > 0) {
                print_matrix(result);  // Print the result only if there was no error
            }
        }
        else {
            Matrix mat2 = parse_matrix(input2);
            scanf("%s", operation);
            if (strcmp(operation, "ADD") == 0) {
                Matrix result = add_matrices(mat1, mat2);
                print_matrix(result);
            } else if (strcmp(operation, "SUB") == 0) {
                Matrix result = sub_matrices(mat1, mat2);
                print_matrix(result);
            } else if (strcmp(operation, "MUL") == 0) {
                Matrix result = mul_matrices(mat1, mat2);
                print_matrix(result);
            } else if (strcmp(operation, "AND") == 0) {
                Matrix result = and_matrices(mat1, mat2);
                print_matrix(result);
            } else if (strcmp(operation, "OR") == 0) {
                Matrix result = or_matrices(mat1, mat2);
                print_matrix(result);
            }
        }
    }
    return 0;
}