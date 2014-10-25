void returnFalse();
void returnTrue();
unsigned char tileColor(char t);
unsigned char z2TileColor(unsigned char x, unsigned char y, unsigned char z);
unsigned char z4TileColor(unsigned char other, unsigned char z);
unsigned char generateCube(char tiles[], int x, int y, int z);
unsigned char calcGoalValue(unsigned char cubie);
int calcRotations(int index, int corner[], char tiles[]);
int findIncorrectEdges(int index, int edge[], char tiles[]);
