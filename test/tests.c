#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void checkAnswer(double expected) {
    FILE *outputFile;
    outputFile = fopen("./output.txt", "r");
    double output = 0;
    fscanf(outputFile, "%lf", &output);
    fclose(outputFile);
    if(output == expected){
        printf("PASSED ==> Expected: %f Output: %f\n", expected, output);
        assert(output == expected);
    } else {
        printf("FAILED ==> Expected: %f Output: %f\n", expected, output);
    }
}

int main() {

    //Note: All expected answers were provided by fplll, as well as the test cases.
    int system(const char *command);
    system("./runme [1]");
    checkAnswer(1);
    system("./runme [1 0] [0 1]");
    checkAnswer(1);
    
    system("./runme [86 68] [21 127]");
    checkAnswer(87.783825);
    system("./runme [68 103 202 129 220] [27 196 78 15 85] [151 178 21 134 12] [211 107 144 165 117] [243 203 165 145 152]");
    checkAnswer(56.868269);
    system("./runme [181 55 156 133 47 161 5 26] [120 146 127 140 205 150 246 19] [127 153 189 126 130 75 1 49] [79 114 95 215 131 204 137 61] [179 227 135 42 209 129 252 73] [188 255 114 96 84 55 28 59] [193 138 147 63 190 113 165 207] [253 227 4 26 196 169 234 136]");
    checkAnswer(123.292336);

    return 0;
}