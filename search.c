#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search.h"
#include "valid.h"
#include "turns.h"
#include "tables.h"

char *ida_star(struct Node *root, char *path) {
    int bound = h(root);
    int t;
    for ( ; ; ) {
        t = search(root, 0, bound, path);
        if (t == -1) {
            return path;
        }
        bound = t;
    }
}

int search(struct Node *node, int g, int bound, char *path) {
    int f = g + h(node);
    if (f > bound) {
        return f;
    }
    if (is_goal(node)) {
        memmove(path + 1, path, 1);
        path[0] = node->move[0];
        path[1] = node->move[1];
        return -1;
    }
    int min = 20;
    struct Node children[18];
    int len_children = generate_children(node, children);
    for (int i = 0; i < len_children; i++) {
        int t = search(&children[i], g + 1, bound, path);
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
    int indices[3];
    enumerate(node->cube, indices);
    unsigned char moves[3];

    FILE *corners_file = fopen("corners", "rb");
    fseek(corners_file, indices[0]/2 * sizeof(unsigned char), SEEK_SET);
    fread(&moves[0], sizeof(unsigned char), 1, corners_file);
    fclose(corners_file);
    if (indices[0] % 2) {
        moves[0] = moves[0] << 4;
    }
    moves[0] = moves[0] >> 4;

    FILE *edges1_file = fopen("edges1", "rb");
    fseek(edges1_file, indices[1]/2 * sizeof(unsigned char), SEEK_SET);
    fread(&moves[1], sizeof(unsigned char), 1, edges1_file);
    fclose(edges1_file);
    if (indices[1] % 2) {
        moves[1] = moves[1] << 4;
    }
    moves[1] = moves[1] >> 4;

    FILE *edges2_file = fopen("edges2", "rb");
    fseek(edges2_file, indices[2]/2 * sizeof(unsigned char), SEEK_SET);
    fread(&moves[2], sizeof(unsigned char), 1, edges2_file);
    fclose(edges2_file);
    if (indices[2] % 2) {
        moves[2] = moves[2] << 4;
    }
    moves[2] = moves[2] >> 4;

    for (int i = 0; i < 3; i++) {
        if (moves[0] < moves[i]) {
            moves[0] = moves[i];
        }
    }
    return (int) moves[0];
}

int is_goal(struct Node *node) {
    for (int i = 0; i < 20; i++) {
        if (node->cube[i] != goal_state[i]) {
            return 0;
        }
    }
    return 1;
}

int generate_children(struct Node *node, struct Node *children) {
    for (int i = 1; i <= 3; i++) {
        struct Node red_node = *node;
        make_move(red_node.cube, 'R', i);
        red_node.move[0] = 'R';
        red_node.move[1] = '0' + i;
        children[i - 1] = red_node;
    }
    for (int i = 1; i <= 3; i++) {
        struct Node green_node = *node;
        make_move(green_node.cube, 'G', i);
        green_node.move[0] = 'G';
        green_node.move[1] = '0' + i;
        children[i + 2] = green_node;
    }
    for (int i = 1; i <= 3; i++) {
        struct Node yellow_node = *node;
        make_move(yellow_node.cube, 'Y', i);
        yellow_node.move[0] = 'Y';
        yellow_node.move[1] = '0' + i;
        children[i + 5] = yellow_node;
    }
    for (int i = 1; i <= 3; i++) {
        struct Node blue_node = *node;
        make_move(blue_node.cube, 'B', i);
        blue_node.move[0] = 'B';
        blue_node.move[1] = '0' + i;
        children[i + 8] = blue_node;
    }
    for (int i = 1; i <= 3; i++) {
        struct Node orange_node = *node;
        make_move(orange_node.cube, 'O', i);
        orange_node.move[0] = 'O';
        orange_node.move[1] = '0' + i;
        children[i + 11] = orange_node;
    }
    for (int i = 1; i <= 3; i++) {
        struct Node white_node = *node;
        make_move(white_node.cube, 'W', i);
        white_node.move[0] = 'W';
        white_node.move[1] = '0' + i;
        children[i + 14] = white_node;
    }
    return 18;
}
