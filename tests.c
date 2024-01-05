#include <stdio.h>
#include <assert.h>

void checkAnswer(double expected) {
    FILE *outputFile;
    outputFile = fopen("./result.txt", "r");
    double output = 0;
    fscanf(outputFile, "%lf", &output);
    fclose(outputFile);
    if (output == expected) {
        printf("PASSED ==> Expected: %f Output: %f\n", expected, output);
        assert(output == expected);
    } else {
        printf("FAILED ==> Expected: %f Output: %f\n", expected, output);
    }
}

int main() {
    // Note: All expected answers were provided by fplll
    int system(const char *command);
    system("./runme [1]");
    checkAnswer(1);
    system("./runme [1 0] [0 1]");
    checkAnswer(1);
    system("./runme [86 68] [21 127]");
    checkAnswer(87.783825);
    system("./runme [15 111 70] [117 195 151] [168 179 120]");
    checkAnswer(56.400355);

    return 0;
}
