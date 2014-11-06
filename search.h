struct Node {
    char g;
    char move[2];
    unsigned char cube[20];
};

char * ida_star(struct Node *root, char *path);
char search(struct Node *node, char g, char bound, char *path);
int h(struct Node *node);
int is_goal(struct Node *node);
int generateChildren(struct Node *node, struct Node *children);
