#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search.h"
#include "valid.h"
#include "turns.h"

char * ida_star(struct Node root) {
    char *path = malloc(sizeof(char) * 40);
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

char search(struct Node node, char g, char bound, char *path) {
    char f = g + h(node);
    if (f > bound) {
        return f;
    }
    if (is_goal(node)) {
        path[0] = node.move[0];
        path[1] = node.move[1];
        return -1;
    }
    char min = 20;
    struct Node children[18];
    int lenChildren = generateChildren(node, children);
    for (int i = 0; i < lenChildren; i++) {
        char t = search(children[i], g + 1, bound, path);
        // printf("%c\n", t);
        // free(&children[i]);
        if (t == -1) {
            memcpy(&path[2], &path[0], 2);
            path[0] = node.move[0];
            path[1] = node.move[0];
            return -1;
        }
        if (t < min) {
            min = t;
        }
    }
    return min;
}
    
char h(struct Node node) {
    return 0;
}

int is_goal(struct Node node) {
    for (int i = 0; i < 20; i++) {
        if (node.cube[i] != goalState[i]) {
            return 0;
        }
    }
    return 1;
}

int generateChildren(struct Node node, struct Node *children) {
    for (int i = 1; i < 3; i++) {
        struct Node *redNode = malloc(sizeof(node));
        redNode->g = node.g + 1;
        turnRed(redNode->cube, i);
        redNode->move[0] = 'R';
        redNode->move[1] = '0' + i;
        children[i - 1] = *redNode;
    }
    for (int i = 1; i < 3; i++) {
        struct Node *greenNode = malloc(sizeof(node));
        greenNode->g = node.g + 1;
        turnGreen(greenNode->cube, i);
        greenNode->move[0] = 'R';
        greenNode->move[1] = '0' + i;
        children[i + 2] = *greenNode;
    }
    for (int i = 1; i < 3; i++) {
        struct Node *yellowNode = malloc(sizeof(node));
        turnYellow(yellowNode->cube, i);
        yellowNode->move[0] = 'R';
        yellowNode->move[1] = '0' + i;
        children[i + 5] = *yellowNode;
    }
    for (int i = 1; i < 3; i++) {
        struct Node *blueNode = malloc(sizeof(node));
        turnBlue(blueNode->cube, i);
        blueNode->move[0] = 'R';
        blueNode->move[1] = '0' + i;
        children[i + 8] = *blueNode;
    }
    for (int i = 1; i < 3; i++) {
        struct Node *orangeNode = malloc(sizeof(node));
        turnOrange(orangeNode->cube, i);
        orangeNode->move[0] = 'R';
        orangeNode->move[1] = '0' + i;
        children[i + 11] = *orangeNode;
    }
    for (int i = 1; i < 3; i++) {
        struct Node *whiteNode = malloc(sizeof(node));
        turnWhite(whiteNode->cube, i);
        whiteNode->move[0] = 'R';
        whiteNode->move[1] = '0' + i;
        children[i + 15] = *whiteNode;
    }
    return 18;
}
