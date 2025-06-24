#ifndef PHASE9_H_INCLUDED
#define PHASE9_H_INCLUDED

// Macros; global constants needed for the application.
// Assignment 2 macros.
#define ZERO 0
#define ONE 1
#define TWO 2
#define FOURTEEN 14
#define NAME 20
#define PLAY 1
#define LEAD 2

// Assignment 3 macros.
#define EXIT 3
#define FALSE 0
#define TRUE 1
#define HAND 10
#define DECK 108
#define FOUR 4
#define EIGHT 8
#define TWELVE 12
#define WILD 13
#define SKIP 14

// Assignment 4 macros.
#define LINE 100
#define FIELDS 3
#define DATA 45
#define DISCARD 1
#define DRAW 2
#define THREE 3
#define FIVE 5
#define SIX 6
#define SEVEN 7
#define NINE 9
#define TEN 10
#define ELEVEN 11

// Assignment 5 macro.
#define THIRTEEN 13


// Struct for Phase 9 players.
struct Player{
    int  playerNum;
    char playerName[NAME];
    int  playerHand[HAND];
    int  currentPhase;
    int  wins;
};


// Prototypes for the Phase 9 functions which will be called in the main function.
// Assignment 1 & 2 prototypes.
void welcomeScreen();
void playGame();
int  displayMenu();

// Assignment 3 prototypes.
void initializeDeck(int deck[DECK]);
void shuffleDeck(int deck[DECK]);
void displayDeck(int deck[DECK]);
void dealHand(int deck[DECK], int *deckIdx, int playerHand[HAND]);
void displayPlayerHand(char player[NAME], int playerHand[HAND]);
int  dealDiscard(int deck[DECK], int *deckIdx);
int  comp(const void *a, const void *b);

// Assignment 4 prototypes.
void readLeaderboardFile();
int  playerOption(char player[NAME]);
void displaySingle(int discard);
int  draw(int deck[DECK], int *deckIdx);
int  discardCard(char player[NAME], int playerHand[HAND], int pickUp);
void updateHand(char player[NAME], int playerHand[HAND], int discardIdx, int *discard, int newCard);
char *trim(char *str);

// Assignment 5 prototypes.
int  checkPhase(struct Player player);
int  countRuns(int playerHand[HAND], int size, int runSize);
int  countSets(int playerHand[HAND], int size, int setSize);
void updatePhase(struct Player *player);
void displayPhase(int currentPhase);

// Assignment 6 prototype.
int isGameOver(struct Player player1, struct Player player2);

#endif // PHASE9_H_INCLUDED
