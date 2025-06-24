// Ensures we can use various necessary functions in our code.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "phase9.h"


int main()
{
    // Calls the welcomeScreen function.
    welcomeScreen();

    // Sets the starting point for randomizing numbers. Necessary for the game to function properly.
    srand((unsigned int)time(NULL));

    // Calls the playGame function.
    playGame();

    // Ensures the program executes successfully.
    return 0;
}

// Displays the welcome screen for the game.
void welcomeScreen()
{
    // Prints the name of the game, "Phase 9", along with a clear definition of all phases of the game.
    printf("PPPP   H  H      A       SSSS  EEEE    9999  \n");
    printf("P   P  H  H     A A     SS     E      9    9 \n");
    printf("PPPP   HHHH    AA AA     SS    EEE     9999  \n");
    printf("P      H  H   A     A      SS  E         9   \n");
    printf("P      H  H  A       A  SSSS   EEEE    99    \n");

    printf("\n");

    printf("PHASE 9 PHASES\n\n");
    printf("1. 2 sets of 3\n");
    printf("2. 1 set of 3 + 1 run of 4\n");
    printf("3. 1 set of 4 + 1 run of 4\n");
    printf("4. 1 run of 7\n");
    printf("5. 1 run of 8\n");
    printf("6. 1 run of 9\n");
    printf("7. 2 sets of 4\n");
    printf("8. 1 set of 5 + 1 set of 2\n");
    printf("9. 1 set of 5 + 1 set of 3\n");
}

// Starts the game.
void playGame()
{
    // Array which stores the game deck.
    // The deckIdx variable stores the current index for the deck array.
    int deck[DECK];
    int deckIdx = ZERO;

    // Player struct variables store both players' data.
    // currentPlayer stores the current player using the macro ONE.
    // The turn variable tracks the number of turns taken by both players.
    struct Player playerOne;
    struct Player playerTwo;
    int currentPlayer = ONE;
    int turn          = ZERO;

    // discardOrDraw stores the player's choice to either pick up the discard or draw from the deck.
    // pickUp stores the player's picked up card value.
    // playerDiscard stores the card number selected by the player to discard.
    int discardOrDraw = ZERO;
    int pickUp        = ZERO;
    int playerDiscard = ZERO;

    // Calls the menu and passes the player's selection back.
    int choice = displayMenu();

    // Executes different statements based on the menu choice picked.
    while (choice != EXIT)
    {
        if (choice == PLAY)
        {
            // Asks both players for their names, then updates their Player struct variables.
            printf("\nPlayer One, enter your name:\n");
            scanf("%s", playerOne.playerName);
            playerOne.playerNum = ONE;
            playerOne.currentPhase = ONE;
            playerOne.wins = ZERO;

            printf("\nPlayer Two, enter your name:\n");
            scanf("%s", playerTwo.playerName);
            playerTwo.playerNum = TWO;
            playerTwo.currentPhase = ONE;
            playerTwo.wins = ZERO;

            // Prints a generic "let's play" message with both variables.
            printf("\n%s and %s, let's play Phase 9!\n\n\n", playerOne.playerName, playerTwo.playerName);

            // Creates and then shuffles the deck for the game.
            initializeDeck(deck);
            shuffleDeck(deck);

            // Generates and sorts hands for both players.
            dealHand(deck, &deckIdx, playerOne.playerHand);
            qsort(playerOne.playerHand, HAND, sizeof(playerOne.playerHand[ZERO]), comp);

            dealHand(deck, &deckIdx, playerTwo.playerHand);
            qsort(playerTwo.playerHand, HAND, sizeof(playerTwo.playerHand[ZERO]), comp);

            // Chooses the first card from the shuffled deck to be on top of the discard pile.
            int discard = dealDiscard(deck, &deckIdx);

            // Starts the game at a set rate of four turns and determines the current player.
            while (isGameOver(playerOne, playerTwo) == FALSE)
            {
                if (currentPlayer == playerOne.playerNum)
                {
                    // Displays player one's current phase, their hand, and their discard pile.
                    displayPhase(playerOne.currentPhase);
                    displayPlayerHand(playerOne.playerName, playerOne.playerHand);

                    printf("\nDiscard pile:\n");
                    displaySingle(discard);

                    // After displaying each item, asks what they would like to do for their turn.
                    discardOrDraw = playerOption(playerOne.playerName);

                    // Triggers slightly different actions based on the player's choice.
                    // The player picks up a card from either the discard pile (DISCARD) or the deck (DRAW)
                    // which is stored in pickUp and then displayed by displaySingle.
                    if (discardOrDraw == DISCARD)
                    {
                        printf("\n%s picked up the discard.\n\n", playerOne.playerName);
                        pickUp = discard;

                        printf("\nNew card:\n");
                        displaySingle(pickUp);
                    }
                    else if (discardOrDraw == DRAW)
                    {
                        printf("\n%s drew from the deck.\n\n", playerOne.playerName);
                        pickUp = draw(deck, &deckIdx);

                        printf("New card:\n");
                        displaySingle(pickUp);
                    }

                    // After the choice is made, the player chooses which card in their hand to discard.
                    // The discarded card choice is stored in playerDiscard.
                    // updateHand then updates the player's hand.
                    playerDiscard = discardCard(playerOne.playerName, playerOne.playerHand, pickUp);
                    updateHand(playerOne.playerName, playerOne.playerHand, playerDiscard, &discard, pickUp);

                    // Checks to see if player one completed the current phase.
                    // If they did, the updatePhase() function is used to modify their struct.
                    if (checkPhase(playerOne) == TRUE)
                    {
                        printf("%s has completed the phase.\n\n", playerOne.playerName);
                        updatePhase(&playerOne);
                    }
                    else
                    {
                        printf("%s did not complete the phase.\n\n", playerOne.playerName);
                    }

                    // The currentPlayer is switched to player two, ending player one's turn.
                    currentPlayer = playerTwo.playerNum;
                }
                // The code from before repeats, but now focuses on player two.
                else if (currentPlayer == playerTwo.playerNum)
                {
                    displayPhase(playerTwo.currentPhase);
                    displayPlayerHand(playerTwo.playerName, playerTwo.playerHand);

                    printf("\nDiscard pile:\n\n");
                    displaySingle(discard);

                    discardOrDraw = playerOption(playerTwo.playerName);

                    if (discardOrDraw == DISCARD)
                    {
                        printf("\n%s picked up the discard.\n\n", playerTwo.playerName);
                        pickUp = discard;

                        printf("New card:\n");
                        displaySingle(pickUp);
                    }
                    else if (discardOrDraw == DRAW)
                    {
                        printf("\n%s drew from the deck.\n\n", playerTwo.playerName);
                        pickUp = draw(deck, &deckIdx);

                        printf("New card:\n");
                        displaySingle(pickUp);
                    }

                    playerDiscard = discardCard(playerTwo.playerName, playerTwo.playerHand, pickUp);
                    updateHand(playerTwo.playerName, playerTwo.playerHand, playerDiscard, &discard, pickUp);

                    if (checkPhase(playerTwo) == TRUE)
                    {
                        printf("%s has completed the phase.\n\n", playerTwo.playerName);
                        updatePhase(&playerTwo);
                    }
                    else
                    {
                        printf("%s did not complete the phase.\n\n", playerTwo.playerName);
                    }

                    currentPlayer = playerOne.playerNum;
                }
            }

            // When the game and while loop ends, this message prints.
            printf("Game over! ");
            if (playerOne.currentPhase > NINE)
            {
                playerOne.wins++;
                printf("%s has won.\n", playerOne.playerName);
                printf("%s wins: %d\n\n", playerOne.playerName, playerOne.wins);
            }
            else if (playerTwo.currentPhase > NINE)
            {
                playerTwo.wins++;
                printf("%s has won.\n", playerTwo.playerName);
                printf("%s wins: %d\n\n", playerTwo.playerName, playerTwo.wins);
            }
        }
        else if (choice == LEAD)
        {
            readLeaderboardFile();
        }
        else
        {
            exit(ZERO);
        }

        // Resets the choice made and clears the data saved in the deckIdx and turn variables.
        choice = displayMenu();
        deckIdx = ZERO;
        turn = ZERO;
    }
}

// Displays a menu for the player to choose from.
int displayMenu()
{
    // Variable that stores the player's choice.
    // The valid variable determines whether the menu choice is valid.
    int choice = ZERO;
    int valid = FALSE;

    // Variable created specifically to prevent an infinite loop in the while loop below.
    char invalid;

    // Continuously prints out the menu options while the menu choice is invalid, forcing the player to make a valid choice.
    while (valid == FALSE)
    {
        printf("\nSelect a menu option:\n");
        printf("1. Play Phase 9\n");
        printf("2. View Leaderboard\n");
        printf("3. Exit Game\n\n");

        // Asks for the player's choice.
        scanf("%d", &choice);

        // If the player does not pick a valid option, valid is assigned as false and the loop repeats.
        // If they do, valid is set to true and the loop ends.
        if ((choice == PLAY) || (choice == LEAD) || (choice == EXIT))
        {
            valid = TRUE;
        }
        else
        {
            // Without this to clear the input of the choice variable, inputting an alphabetic character would cause an infinite loop in the code.
            while ((invalid = getchar()) != '\n' && invalid != EOF);
            {
                valid = FALSE;
            }
        }
    }

    // Returns the player's choice to playGame.
    return(choice);
}

// Generates the deck of cards for the game (108 cards total).
void initializeDeck(int deck[DECK])
{
    // Variable will be used as the index for the deck array.
    int idx = ZERO;

    // Defining for loop variables that we are about to use.
    int i = ZERO;
    int t = ONE;
    int w = ZERO;
    int s = ZERO;

    // Adds 96 cards numbered 1-12 into the deck array.
    for (i = ZERO; i < EIGHT; i++)
    {
        for (t = ONE; t <= TWELVE; t++)
        {
            deck[idx] = t;
            idx++;
        }
    }

    // Adds 8 wild cards to the deck array.
    for (w = ZERO; w < EIGHT; w++)
    {
        deck[idx] = WILD;
        idx++;
    }

    // Adds 4 skip cards to the deck array.
    for (s = ZERO; s < FOUR; s++)
    {
        deck[idx] = SKIP;
        idx++;
    }
}

// Shuffles the deck so that each card is randomized.
void shuffleDeck(int deck[DECK])
{
    // Defines the variable for the upcoming for loop.
    int d = ZERO;

    // Shuffles cards randomly by swapping the elements within the indexes.
    for (d = ZERO; d < DECK; d++)
    {
        int c = (rand()) % DECK;
        int card = deck[d];
        deck[d] = deck[c];
        deck[c] = card;
    }
}

// Displays the deck array for code testing purposes.
void displayDeck(int deck[DECK])
{
    // Displays every element within the array in order using the for loop variable as the index.
    // The if-else statement serves no functional purpose; it is purely for improved readability and aesthetic appeal.
    int test = ZERO;
    for (test = ZERO; test < DECK; test++)
    {
        if (test != (DECK - ONE))
        {
            printf("%d - ", deck[test]);
        }
        else
        {
            printf("%d\n", deck[test]);
        }
    }
}

// Deals a randomized hand to each player.
void dealHand(int deck[DECK], int* deckIdx, int playerHand[HAND])
{
    // Defining variable for the upcoming for loop.
    int h = ZERO;

    //
    for (h = ZERO; h < HAND; h++)
    {
        playerHand[h] = deck[*deckIdx];
        (*deckIdx)++;
    }
}

// Shows the selected player's hand.
void displayPlayerHand(char player[NAME], int playerHand[HAND])
{
    // Declares looping variable.
    int h;

    // Prints out the first part of the player's hand.
    printf("\n%s's hand:\n\n", player);
    printf("+---------------------------------------------------------------------+\n");
    printf("|      |      |      |      |      |      |      |      |      |      |\n");
    printf("|");

    // Prints out the actual cards owned by the player.
    // If the card is a wild card (13) or a skip card (14), the output will be "W" and "S" respectively.
    for (h = ZERO; h < HAND; h++)
    {
        if (playerHand[h] == WILD)
        {
            printf("   W  |");
        }
        else if (playerHand[h] == SKIP)
        {
            printf("   S  |");
        }
        else
        {
            printf("  %2d  |", playerHand[h]);
        }
    }

    // Prints out the last part of the player's hand.
    printf("\n|      |      |      |      |      |      |      |      |      |      |\n");
    printf("+---------------------------------------------------------------------+\n\n");
}

// Generates the discard pile.
int dealDiscard(int deck[DECK], int* deckIdx)
{
    // Sets the discarded card as the value within the index provided by the function call.
    int discard = deck[*deckIdx];
    (*deckIdx)++;

    return discard;
}

// Provided function that enables qsort.
int comp(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

// Reads and outputs the leaderboard.txt file.
void readLeaderboardFile()
{

    // The line array will store one line at a time from the txt file.
    // fieldIdx tracks the element in the array data and is used for storage purposes.
    char line[LINE];
    int fieldIdx = ZERO;
    char *data[DATA];

    // Opens the leaderboard.txt file in reading mode.
    FILE *fp = fopen("leaderboard.txt", "r");

    // Prints out the leaderboard header.
    printf("\n------------------------------\n");
    printf("\n     Phase 9 Leaderboard\n");
    printf("\n------------------------------\n");
    printf("\nPosition     Player       Wins\n");
    printf("\n--------    --------      ----\n");

    // Ensures if the file is empty that the function returns with an error.
    if (fp == NULL)
    {
        perror("Error opening file");
        return;
    }

    // While there is data to read in the file, stores the data in the field variable.
    // Trim is used to remove whitespace.
    while (fgets(line, LINE, fp) != NULL)
    {
        char *field = strtok(line, ",");
        field = trim(field);

        // While there is data stored in the field variable, copy that data into the array named data.
        while (field != NULL)
        {
            data[fieldIdx] = malloc(strlen(field) + 1);
            strcpy(data[fieldIdx], field);

            field = strtok(NULL, ",");
            field = trim(field);
            fieldIdx++;
        }
    }

    // Closes the leaderboard.txt file, now having copied all its data.
    fclose(fp);

    // For loop which prints out the data obtained from leaderboard.txt.
    int i = ZERO;
    for (i = ZERO; i < DATA; i += FIELDS)
    {
        printf("\n  %2s       %8s        %2s\n", data[i], data[i + 1], data[i + 2]);
    }

    // New line added for the sake of the menu looking neater.
    printf("\n");
}

// Asks the current player what they would like to do during their turn.
int playerOption(char player[NAME])
{
    int choice = ZERO;
    int valid = FALSE;

    // If the player's choice is invalid, the loop will repeat and ask them for their choice again.
    while (valid == FALSE)
    {
        printf("%s, select an option:\n", player);
        printf("1. Pick up discard\n");
        printf("2. Draw from deck\n\n");

        scanf("%d", &choice);

        if ((choice != DISCARD) && (choice != DRAW))
        {
            valid = FALSE;
        }
        else
        {
            valid = TRUE;
        }
    }

    return choice;
}

// Displays the given card.
void displaySingle(int discard)
{
    // Displays the provided value.
    // If it is a wild or skip card, the respective letter is output instead.
    printf("\n+------+\n");
    printf("|      |\n");

    if (discard == WILD)
    {
        printf("|   W  |\n");
    }
    else if (discard == SKIP)
    {
        printf("|   S  |\n");
    }
    else
    {
        printf("|  %2d  |\n", discard);
    }

    printf("|      |\n");
    printf("+------+\n\n");
}

// Draws a random card from the deck.
int draw(int deck[DECK], int* deckIdx)
{
    // Assigns the drawn card with the value of the card at the deckIdx index of deck.
    // Increments deckIdx by one.
    int card = deck[*deckIdx];
    (*deckIdx)++;

    return card;
}

// Prompts the player to choose which card in their hand or discard pile to discard.
int discardCard(char player[NAME], int playerHand[HAND], int pickUp)
{
    int choice = ZERO;
    int valid  = FALSE;

    // Prints out the player's hand and discard pile with numbers indicating which choice they can make.
    displayPlayerHand(player, playerHand);
    printf("   (1)    (2)    (3)    (4)    (5)    (6)    (7)    (8)    (9)    (10)\n\n");

    displaySingle(pickUp);
    printf("  (11)\n\n");

    // Asks the player for their choice and determines whether the choice is valid.
    // If invalid, they will be prompted until they give a valid answer.
    while (valid == FALSE)
    {
        printf("Select which card (1-11) to discard.\n");
        scanf("%d", &choice);
        printf("\n");

        if ((choice >= ONE) && (choice <= ELEVEN))
        {
            valid = TRUE;
        }
        else
        {
            valid = FALSE;
        }
    }

    // Returns the player's choice.
    return choice;
}

// Updates the player's hand based on their selections.
void updateHand(char player[NAME], int playerHand[HAND], int discardIdx, int* discard, int newCard)
{
    // If the player is discarding the card they just picked up, no update to the deck is needed.
    if (discardIdx == ELEVEN)
    {
        printf("%s has selected the drawn card to discard.\n\n", player);
        return;
    }
    else
    {
        // The card variable is assigned the value of the card the player is discarding.
        // Then, the player's card is replaced with a new card.
        int card = playerHand[discardIdx - ONE];
        playerHand[discardIdx - ONE] = newCard;

        // Sorts the player's updated deck.
        qsort(playerHand, HAND, sizeof(playerHand[ZERO]), comp);

        // The discard variable is assigned the card the player is discarding.
        // The player's newly sorted deck is displayed.
        *discard = card;
        displayPlayerHand(player, playerHand);

        // Displays the card the player has just discarded.
        printf("Discarded card:\n\n");
        displaySingle(*discard);
    }
}

// Provided function that trims leading and trailing whitespace.
char *trim(char *str)
{
    // check if the string is empty
    if (str == NULL || *str == '\0')
    {
        return str;
    }

    // trim leading white space
    char *start = str;

    while (isspace((unsigned char)*start))
    {
        start++;
    }

    // trim trailing white space
    char *end = str + strlen(str) - 1;

    while (end > start && isspace((unsigned char)*end))
    {
        end--;
    }

    // add the null terminator
    end[1] = '\0';

    // return the updated string
    return start;
}

// Checks the player's current phase and determines if they have finished it or not.
int checkPhase(struct Player player)
{
    // These variables are used to count whether the phase has been met.
    int sets    = ZERO;
    int setsTwo = ZERO;
    int runs    = ZERO;

    // Determines which phase the player is on.
    // Based on their current phase, different actions are executed.
    switch (player.currentPhase)
    {
        case ONE:
            sets = countSets(player.playerHand, HAND, THREE);

            if (sets >= TWO)
            {
                return TRUE;
            }
            else
            {
                return FALSE;
            }

            break;

        case TWO:
            sets = countSets(player.playerHand, HAND, THREE);
            runs = countRuns(player.playerHand, HAND, FOUR);

            if ((sets >= ONE) && (runs >= ONE))
            {
                return TRUE;
            }
            else
            {
                return FALSE;
            }

            break;

        case THREE:
            sets = countSets(player.playerHand, HAND, FOUR);
            runs = countRuns(player.playerHand, HAND, FOUR);

            if ((sets >= ONE) && (runs >= ONE))
            {
                return TRUE;
            }
            else
            {
                return FALSE;
            }

            break;

        case FOUR:
            runs = countRuns(player.playerHand, HAND, SEVEN);

            if (runs >= ONE)
            {
                return TRUE;
            }
            else
            {
                return FALSE;
            }

            break;

        case FIVE:
            runs = countRuns(player.playerHand, HAND, EIGHT);

            if (runs >= ONE)
            {
                return TRUE;
            }
            else
            {
                return FALSE;
            }

            break;

        case SIX:
            runs = countRuns(player.playerHand, HAND, NINE);

            if (runs >= ONE)
            {
                return TRUE;
            }
            else
            {
                return FALSE;
            }

            break;

        case SEVEN:
            sets = countSets(player.playerHand, HAND, FOUR);

            if (sets >= TWO)
            {
                return TRUE;
            }
            else
            {
                return FALSE;
            }

            break;

        case EIGHT:
            sets    = countSets(player.playerHand, HAND, FIVE);
            setsTwo = countSets(player.playerHand, HAND, TWO);

            if ((sets >= ONE) && (setsTwo >= ONE))
            {
                return TRUE;
            }
            else
            {
                return FALSE;
            }

            break;

        case NINE:
            sets    = countSets(player.playerHand, HAND, FIVE);
            setsTwo = countSets(player.playerHand, HAND, THREE);

            if ((sets >= ONE) && (setsTwo >= ONE))
            {
                return TRUE;
            }
            else
            {
                return FALSE;
            }

            break;

        default:
            return ZERO;
            break;
    }
}

// Checks to see if the player has any runs of cards for the phase requirements.
int countRuns(int playerHand[HAND], int size, int runSize)
{
    int runs = ZERO;

    // Checks the player's deck to see if there are any runs.
    for (int i = ZERO; i < size; i++)
    {
        int currentRun = ONE;

        for (int j = i + ONE; j < size; j++)
        {
            if (playerHand[j] == (playerHand[i] + currentRun))
            {
                currentRun++;

                if (currentRun == runSize)
                {
                    runs++;
                    break;
                }
            }
        }
    }

    return runs;
}

// Checks to see if the player has any sets of cards for the phase requirements.
int countSets(int playerHand[HAND], int size, int setSize)
{
    // These variables are used to store and count any sets found in the player's deck.
    int counts[THIRTEEN] = {ZERO};
    int setCount = ZERO;

    // Iterates through the player's deck to check for any sets and stores them in the counts array.
    // If the card is a wild or skip card, it will be ignored.
    for (int i = ZERO; i < size; i++)
    {
        if ((playerHand[i] >= ONE) && (playerHand[i] <= TWELVE))
        {
            counts[playerHand[i] - ONE]++;
        }
    }

    // Checks if the sets in the counts array matches the amount of sets needed for the phase.
    for (int i = ZERO; i < THIRTEEN; i++)
    {
        if (counts[i] >= setSize)
        {
            setCount++;
        }
    }

    return setCount;
}

// Updates the player's current phase when called.
void updatePhase(struct Player *player)
{
    if (player->currentPhase < TEN)
    {
        (player->currentPhase)++;
    }
}
void displayPhase(int currentPhase);

// Prints out the current phase with an explanation.
void displayPhase(int currentPhase)
{
    switch (currentPhase)
    {
        case ONE:
            printf("+----------------------------------+\n");
            printf("| CURRENT PHASE: One - 2 sets of 3 |\n");
            printf("+----------------------------------+\n\n");
            break;

        case TWO:
            printf("+----------------------------------------------+\n");
            printf("| CURRENT PHASE: Two - 1 set of 3 + 1 run of 4 |\n");
            printf("+----------------------------------------------+\n\n");
            break;

        case THREE:
            printf("+------------------------------------------------+\n");
            printf("| CURRENT PHASE: Three - 1 set of 4 + 1 run of 4 |\n");
            printf("+------------------------------------------------+\n\n");
            break;

        case FOUR:
            printf("+----------------------------------+\n");
            printf("| CURRENT PHASE: Four - 1 run of 7 |\n");
            printf("+----------------------------------+\n\n");
            break;

        case FIVE:
            printf("+----------------------------------+\n");
            printf("| CURRENT PHASE: Five - 1 run of 8 |\n");
            printf("+----------------------------------+\n\n");
            break;

        case SIX:
            printf("+---------------------------------+\n");
            printf("| CURRENT PHASE: Six - 1 run of 9 |\n");
            printf("+---------------------------------+\n\n");
            break;

        case SEVEN:
            printf("+------------------------------------+\n");
            printf("| CURRENT PHASE: Seven - 2 sets of 4 |\n");
            printf("+------------------------------------+\n\n");
            break;

        case EIGHT:
            printf("+------------------------------------------------+\n");
            printf("| CURRENT PHASE: Eight - 1 set of 5 + 1 set of 2 |\n");
            printf("+------------------------------------------------+\n\n");
            break;

        case NINE:
            printf("+-----------------------------------------------+\n");
            printf("| CURRENT PHASE: Nine - 1 set of 5 + 1 set of 3 |\n");
            printf("+-----------------------------------------------+\n\n");
            break;
    }
}

// This function checks if the game is over.
int isGameOver(struct Player player1, struct Player player2)
{
    // This variable is later returned, telling the function call whether the game has ended or not.
    int gameOver = FALSE;

    // gameOver will return true if either player has completed all 9 phases.
    // Otherwise, gameOver returns false and the game continues.
    if ((player1.currentPhase > NINE) || (player2.currentPhase > NINE))
    {
        gameOver = TRUE;
    }
    else
    {
        gameOver = FALSE;
    }

    return gameOver;
}
