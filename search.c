#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search.h"
#include "valid.h"
#include "turns.h"

char *ida_star(struct Node *root, char *path) {
    char bound = h(root);
    char t;
    for ( ; ; ) {
        t = search(root, 0, bound, path);
        if (t == -1) {
            return path;
        }
        bound = t;
    }
}

char search(struct Node *node, char g, char bound, char *path) {
    char f = g + h(node);
    if (f > bound) {
        return f;
    }
    if (is_goal(node)) {
        memmove(path + 1, path, 1);
        path[0] = node->move[0];
        path[1] = node->move[1];
        return -1;
    }
    char min = 20;
    struct Node children[18];
    int lenChildren = generateChildren(node, children);
    for (int i = 0; i < lenChildren; i++) {
        char t = search(&children[i], g + 1, bound, path);
        if (t == -1) {
            if (g != 0) {
                memmove(path + 2, path, strlen(path) + 1);
                path[0] = node->move[0];
                path[1] = node->move[1];
            }
            return -1;
        }
        if (t < min) {
            min = t;
        }
    }
    return min;
}
    
int h(struct Node *node) {
    return 0;
}

int is_goal(struct Node *node) {
    for (int i = 0; i < 20; i++) {
        if (node->cube[i] != goal_state[i]) {
            return 0;
        }
    }
    return 1;
}

int generateChildren(struct Node *node, struct Node *children) {
    for (int i = 1; i <= 3; i++) {
        struct Node redNode = *node;
        make_move(redNode.cube, 'R', i);
        redNode.move[0] = 'R';
        redNode.move[1] = '0' + i;
        children[i - 1] = redNode;
    }
    for (int i = 1; i <= 3; i++) {
        struct Node greenNode = *node;
        make_move(greenNode.cube, 'G', i);
        greenNode.move[0] = 'G';
        greenNode.move[1] = '0' + i;
        children[i + 2] = greenNode;
    }
    for (int i = 1; i <= 3; i++) {
        struct Node yellowNode = *node;
        make_move(yellowNode.cube, 'Y', i);
        yellowNode.move[0] = 'Y';
        yellowNode.move[1] = '0' + i;
        children[i + 5] = yellowNode;
    }
    for (int i = 1; i <= 3; i++) {
        struct Node blueNode = *node;
        make_move(blueNode.cube, 'B', i);
        blueNode.move[0] = 'B';
        blueNode.move[1] = '0' + i;
        children[i + 8] = blueNode;
    }
    for (int i = 1; i <= 3; i++) {
        struct Node orangeNode = *node;
        make_move(orangeNode.cube, 'O', i);
        orangeNode.move[0] = 'O';
        orangeNode.move[1] = '0' + i;
        children[i + 11] = orangeNode;
    }
    for (int i = 1; i <= 3; i++) {
        struct Node whiteNode = *node;
        make_move(whiteNode.cube, 'W', i);
        whiteNode.move[0] = 'W';
        whiteNode.move[1] = '0' + i;
        children[i + 14] = whiteNode;
    }
    return 18;
}
