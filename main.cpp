#include <iostream>
#include <time.h> // Used for seeding
#include <iomanip> //added so I could utilize setw, which allows me to set the width of a field.

using namespace std;

const int ROWS = 8;
const int COLUMNS = 8;
int remainingGuesses = 5; // Available guesses for player

int main()
{
    // Declaring methods
    int initializeArray(char guessArray[ROWS][COLUMNS]);
    int displayArray(char guessArray[ROWS][COLUMNS]);
    int populateArray(char guessArray[ROWS][COLUMNS]);
    int coutRules();
    int gameLogic(char guessArray[ROWS][COLUMNS]);


    char guessArray[ROWS][COLUMNS];
    char answer; // Would you like to play again answer


    do
        // do/while loop
    {
        initializeArray(guessArray);
        displayArray(guessArray);
        populateArray(guessArray);
        coutRules();
        gameLogic(guessArray);

        cout << "Would you like to play Again? Enter 'Y' or 'y'" << endl;
        cin >> answer;

        if (answer == 'y' || answer == 'Y')
        {
            remainingGuesses = 5; // Resets the amount guesses a player is allocated if they decide to play again.
        }

    } while (answer == 'Y' || answer == 'y'); // If player decides to play again the code above it executed.

    return 0;

}

// Iterates through array and placing question marks in every position
int initializeArray(char guessArray[ROWS][COLUMNS])
{
    int row, column;

    remainingGuesses = 5; // Need to make sure guesses reset to 5 when array is initialized.


    // Iterate through array and put a ? in every position
    for (row = 0; row < ROWS; row++)
    {
        for (column = 0; column < COLUMNS; column++)
        {
            guessArray[row][column] = '?';
        }
    }
    return 0;
}

// Prints the array to the console
int displayArray(char guessArray[ROWS][COLUMNS])

{
    int row, column;
    cout << endl;
    cout << "   "; // Insert 3 spaces to the top formatting **aesthetic**
    for (column = 0; column < COLUMNS; column++)
    {
        cout << setw(3) << column + 1; // Since we count from zero in programming I've added a one.
    }
    cout << endl;
    cout << "  " << "--------------------------" << endl;

    for (row = 0; row < ROWS; row++)
    {
        cout << " " << row + 1 << "|";
        for (column = 0; column < COLUMNS; column++)
        {
            cout << setw(3) << guessArray[row][column];
        }
        cout << endl;
    }

    cout << "  " << "--------------------------" << endl;

    return 0;

}

// Using Cout to explain the rules to the player
int coutRules()
{
    cout << "**" << " ********************* " << "**" << endl;
    cout << "**" << "                       " << "**" << endl;
    cout << "**" << "      Find Gold!       " << "**" << endl;
    cout << "**" << "                       " << "**" << endl;
    cout << "**" << "  You have 5 guesses!  " << "**" << endl;
    cout << "**" << "                       " << "**" << endl;
    cout << "**" << "  Earn an extra guess  " << "**" << endl;
    cout << "**" << "  when you find gold!  " << "**" << endl;
    cout << "**" << "                       " << "**" << endl;
    cout << "**" << "     There are...      " << "**" << endl;
    cout << "**" << "   5 pieces of gold,   " << "**" << endl;
    cout << "**" << "     and 1 bomb.       " << "**" << endl;
    cout << "**" << "      Good Luck!       " << "**" << endl;
    cout << "**" << "                       " << "**" << endl;
    cout << "**" << " ********************* " << "**" << endl;
    cout << endl;
    cout << endl;

    return 0;
}

// Secretly place gold and bombs in array , but don't show it to "hide" the bombs and gold.
int populateArray(char guessArray[ROWS][COLUMNS])

{

    int x;
    int y;
    int bombInputCounter = 0;
    int goldInputCounter = 0;
    srand(time(NULL)); // Using a seed to ensure everything is random

    // Using a do while loop to place gold until all 5 nuggets are placed on board.
    do {
        x = rand() % ROWS; // Get a random Row #
        y = rand() % COLUMNS; // Get a random Column #

        if (guessArray[x][y] != 'G')
        {
            guessArray[x][y] = 'G'; // Put 'G' for Gold at the random Coordinate
            goldInputCounter++;
        }

    } while (goldInputCounter < 5);// guessArray contains <= 5 'G' characters

    //Places bomb at random coordinate
    do
    {
        x = rand() % ROWS; // Get a random Row #
        y = rand() % COLUMNS; // Get a random Column #

        if (guessArray[x][y] != 'G')
            // This if statement determines if random row nd columns are equal to 'G'. If it's equal to 'G' then it goes
            // back to the beginning of the loop and selects another random row and column. This is in place to prevent
            // a bomb from covering gold pieces.
        {
            guessArray[x][y] = 'B'; // Put 'B' for Bomb at the random (X,Y) coordinate
            bombInputCounter++;
        }


    } while (bombInputCounter < 1);



    return 0;

}



// This is where the brains of the game lives.
int gameLogic(char guessArray[ROWS][COLUMNS])
{
    int points = 0;
    int gRow; //gRow = guessRow;
    int gColumn; // gColumn = guessColumn

    do
    {
        // Requesting coordinates from player
        cout << "Enter an X coordinate between 1 and 8: ";
        cin >> gRow;

        //Prompts user to enter a whole number between 1-8.
        while (!cin || gRow > 8 || gRow < 1)
        {
            cout << "Please enter a whole number that is between 1 and 8: ";
            cin.clear();
            cin.ignore();
            cin >> gRow;
        }

        gRow--;
        cout << endl;
        cout << "Enter a Y coordinate between 1 and 8: ";
        cin >> gColumn;

        //Prompts user to enter a whole number between 1-8.
        while (!cin || gColumn > 8 || gColumn < 1)
        {
            cout << "Please enter a whole number that is between 1 and 8: ";
            cin.clear();
            cin.ignore();
            cin >> gColumn;
        }

        gColumn--;
        cout << endl;

        // When a user finds the gold they are rewarded with another guess.
        if (guessArray[gRow][gColumn] == 'G')
        {
            cout << "You Found Gold!! You've gained an extra guess and now have " << remainingGuesses << " guesses left!";
            guessArray[gRow][gColumn] = 'F';
            // This makes it so player knows where they found gold at the end of the game
            // Prevents player from cheating by guessing the same coordinate.

            points += 1; // Give player a point if they find gold!
            cout << endl;
            cout << endl;
            continue; // Go back to beginning of loop
        }
            // If they find bomb, break out of loop and terminate game.
        else if (guessArray[gRow][gColumn] == 'B')
        {
            cout << endl;
            cout << "BOMB! Oh no! You have lost the game." << endl << endl; // You lose message.
            break; // Lose Game
        }
            // If nothing is found then move to else section
        else
        {
            cout << "Too bad..." << endl;
            remainingGuesses--;
            // Decrement guessesLeft by 1
            cout << "You have " << remainingGuesses << " guesses left!" << endl << endl;

        }


    } while (remainingGuesses > 0);
    // Runs this loop until player runs out of guesses.

    cout << "You've earned " << points << " points!" << endl;
    cout << "Better luck next time!" << endl;
    // Display array at the end where all of the gold and bombs were placed at the end
    cout << "Here's your board:" << endl << endl;

    // Removes ? from array
    for (gColumn = 0; gColumn < COLUMNS; gColumn++)
    {
        for (gRow = 0; gRow < ROWS; gRow++)
        {
            if (guessArray[gRow][gColumn] == '?')
            {
                guessArray[gRow][gColumn] = ' ';
            }
        }
    }

    // The logic below displays the guessArray to the player but adds the hidden bombs and hidden gold.
    cout << "   "; // Insert 3 spaces to the top formatting **aesthetic**
    for (gColumn = 0; gColumn < COLUMNS; gColumn++)
    {
        cout << setw(3) << gColumn + 1; // Since arrays start at 0, we add 1.
    }
    cout << endl;
    cout << "  " << "--------------------------" << endl;

    for (gRow = 0; gRow < ROWS; gRow++)
    {
        cout << " " << gRow + 1 << "|"; // Since arrays start at 0, we add 1
        for (gColumn = 0; gColumn < COLUMNS; gColumn++)
        {
            cout << setw(3) << guessArray[gRow][gColumn]; // Helps display the array with spacing to be more readable
        }
        cout << endl;
    }

    cout << "  " << "--------------------------" << endl;


    return 0;
}

