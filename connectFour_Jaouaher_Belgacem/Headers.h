// Global variables

char playerColor, aiColor;
// const int rowsLength = 6;
// const int columnsLength = 7;
#define rowsLength 6
#define columnsLength 7
#define connectLengthToWin 4
#define treeDepth 2

int matrix[rowsLength][columnsLength];
int playerIndex = 0; // player 1 or player 2 turn depends on playerIndex % 2 + 1
int playMode = -1;   // 1 means solo mode vs Bot | 2 means two player mode

// AI Bot related variables
// const int treeDepth = 2;
//int treeDepth = 0;
//#define treeDepthbasic 0
//#define treeDepthAdvanced 5
int difLevel=0;



// AI Bot related variables
// const int treeDepth = 2;

int evaluatedDecisionArray[treeDepth][columnsLength];
int auxMatrix[rowsLength][columnsLength];
int simulatedMatrix[rowsLength][columnsLength];

// Functions prototypes

void welcome_screen();
void display_matrix();
void check_winner(int isBotVariable);
int occ_num_horiz(int x, int y, int playerIndex);
int occ_num_vert(int x, int y, int coinIndex);
int occ_num_diag(int x, int y, int playerIndex);
int occ_num_diag_2(int x, int y, int playerIndex);
int get_coin_placement_row(int matrixToTest[rowsLength][columnsLength], int coinIndex);
int win_case(int row, int inputColumn);
void input_coin();
int take_decision_min_max_based(int depth);
void copy_matrix();
void copy_to_simulated_matrix();
void back_to_normal_matrix_from_simulated();
void back_to_normal_matrix();
void evaulate_games(int depth);
int simulate_games_min_max_based();
void play_bot();
void play();
