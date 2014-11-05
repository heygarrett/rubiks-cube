#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "valid.h"
#include "search.h"

unsigned char goalState[20] = {70,7,134,68,132,69,5,133,67,131,65,129,86,23,150,84,148,85,21,149};

int main(int argc, char *argv[]) {

    // Check for a passed file
    if (argc != 2) {
        returnFalse();
    } 

    // Read file in
    FILE *input = fopen(argv[1], "r");
    // Make sure the file can be opened
    if (input == 0) {
        returnFalse();
    }

    // Generate valid cube representation
    // unsigned char inputCube[20];

    struct Node root;
    root.g = 0;

    generateCube(input, root.cube);

    char *path = ida_star(root);
    printf("%c\n", *path);

    return 0;
}
