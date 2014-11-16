#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "valid.h"
#include "search.h"
#include "tables.h"

unsigned char goal_state[20] = {70, 7, 134, 68, 132, 69, 5, 133, 67, 131, 65, 129, 86, 23, 150, 84, 148, 85, 21, 149};

int main(int argc, char *argv[]) {

    /*
    // Check for a passed file
    if (argc != 2) {
        return_false();
    } 

    // Read file in
    FILE *input = fopen(argv[1], "r");
    // Make sure the file can be opened
    if (input == 0) {
        return_false();
    }

    struct Node root;
    root.g = 0;
    generate_cube(input, root.cube);
    char path[40] = "\0";
    ida_star(&root, path);
    printf("%s\n", path);
    */

    struct state goal;
    goal.last_face = 'N';
    memcpy(goal.cube, goal_state, sizeof(goal_state));
    bf_search(goal);

    return 0;
}
