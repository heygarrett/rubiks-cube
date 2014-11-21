#define LEN(a) (sizeof(a)) / (sizeof(a[0]))

extern unsigned char goal_state[20];
void return_false();
void returnTrue();
void generate_cube(FILE *input, unsigned char *input_cube);
void validate(unsigned char *input_cube);
unsigned char tile_color(char t);
unsigned char z2_tile_color(unsigned char x, unsigned char y, unsigned char z);
unsigned char z4_tile_color(unsigned char other, unsigned char z);
unsigned char set_cubie_colors(unsigned char x, unsigned char y, unsigned char z);
void get_cubie_colors(unsigned char cubie, unsigned char *colors);
unsigned char calc_goal_value(unsigned char cubie);
int calc_rotations(int index, unsigned char cubie);
int calc_orientation(int index, unsigned char cubie);
