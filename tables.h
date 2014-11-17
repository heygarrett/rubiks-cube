struct list {
    int size;
    struct state *cubes;
};

struct state {
    unsigned char cube[20];
    unsigned char last_face;
};

void bf_search(struct state root);
int create_children(struct state node, struct list *new_frontier, int nodeNumber, int depth, unsigned char **hash_table);
int hash(struct state node, int depth, unsigned char **hash_table);
void enumerate(unsigned char *cube, int *indices);
