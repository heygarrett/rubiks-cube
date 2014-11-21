struct Node {
    char g;
    char move[2];
    unsigned char cube[20];
};

char * ida_star(struct Node *root, char *path);
int search(struct Node *node, int g, int bound, char *path);
int h(struct Node *node);
int is_goal(struct Node *node);
int generate_children(struct Node *node, struct Node *children);
