/* 	Program 6 - Unscrambler (no classes, no undo)

	The user is presented with a board that is filled with scrambled words.
	They have to rotate the rows and columns to get the words displayed in the right order.

	Author: Syed Mehdi 
    Date: 11/29/2021
    Class: CS 141, Fall 2021, UIC
    System: CLion on Windows 11

    Running the program looks like:
        Program 6: Unscrambler Undo
        CS 141, Fall 2021, UIC
         
        You will be presented with a board that is filled with scrambled words.
        Rotate the rows and columns to get the words displayed in the right order.
        Press 'U' to undo moves.

        1192 words have been read in from the dictionary.
           Choose board size. It must be a single digit >=4: 4
           Choose single-digit number of times to scramble board: 1

               A   B   C   D         Goal Board
              ----------------     ---------------
           0 | b |   | o | m |    | b | o | o | m |
              ----------------     ---------------
           1 |   | o | o | o |    |   | t | o | o |
              ----------------     ---------------
           2 | c | t | p | i |    |   | p | i | c |
              ----------------     ---------------
           3 | k |   | t | o |    | k |   | t | o |
              ----------------     ---------------
           Board string: b om oooctpik to
            Goal string: boom too pick to

        Enter one of the following:
           R Rotate a row or column
           G Generate a new board with new random words
           Q to quit.
        1. Your choice:
*/

#include <iostream>		// For Input and Output
#include <fstream>		// For file input and output
#include <cassert>		// For the assert statement
#include <vector>		// For vectors
#include <iomanip>		// For setw() and setfill()
using namespace std;


// Class Board should be declared here and should have private data members for:
//    1. The board letters (as a string or vector of char)
//    2. The list of words randomly selected from the dictionary
//    3. What the original unscrambled board looks like (which is also the completed board)
//    4. The size of the board
// Your Board class should not include the dictionary, because if it does then each Node
// would have its own copy, and you only need a single copy of the dictionary.
// ...
//-------------------------------------------------------------------------------------
// Node declaration to implement a linked list to store moves, used to implement
// undo. You should store the old move number, the old board, and a pointer
// to the next Node.  Note that for this program you are not required to use
// a class for the Node.  It could just be a struct without worrying about the
// proper uses of public and private.
class Node {
    // ...
public:
    string aBoard;
    int moveNumber;
    Node *pNext;
};
class Board{
        public: //initalize the board to size zero
                //constucter
                Board(int boardCharsPerSize = 5){// Default number of rows and columns of the board
                        this->boardCharsPerSize = boardCharsPerSize;
			            this->boardSize = this->boardCharsPerSize * this->boardCharsPerSize;

                }
                void setBoardSize(int boardCharsPerSize){this->boardCharsPerSize = boardCharsPerSize; this->boardSize = this->boardCharsPerSize*this->boardCharsPerSize;}
                //sets both sizes that the user gives in the main function
                int getBoardSize(){return boardSize;} // returns the size of the board
                int getBoardCharsPerSize(){return boardCharsPerSize;}
                void setBoardLetters(string letters){this->boardletters = letters;}
		        string getBoardLetters(){return boardletters;}
		        string getSolutionBoard(){return completedBoard;}
                void clearBoardLetters(){this->boardletters = "";}
                void clearBoardSolution(){this->completedBoard = "";}
                void selectRandomWords(vector <string> dictionary);
                void initializeBoard();
                void scrambleBoard();
                void rotateRowOnce(int rowToRotate);
                void rotateColOnce(int colToRotate);



        private:
                vector<string> randomWords;//vector stores the words used in the board
                int boardSize;//stores the size of the board (ex 4 or 5, not the amont of boardletters_
                string boardletters;//the letters being displayed in the board
                string completedBoard;//the letters that are in order according to the solution
		        int boardCharsPerSize;



};//end of Board class


//---------------------------------------------------------------------------
// Set up the board based on the random words chosen from the dictionary
void Board::initializeBoard()
{
    // Create the board by concatenating all the words, with a space between them.
    int i;
    for( i=0; i<this->randomWords.size()-1; i++) {
        this->boardletters = this->boardletters + this->randomWords[ i] + " ";
    }
    
    // Separately append the last word, without a following blank, in case the words fit
    // perfectly without any extra blanks at the end.
    this->boardletters = this->boardletters + this->randomWords[ i];
    
    // Append extra spaces if needed so board ends up the right size
    while( this->boardletters.size() < this->boardSize) {
        this->boardletters += " ";
    }
    // Store the completed board, to later allow checking for win
    this->completedBoard = this->boardletters;
} // end initializeBoard()


//---------------------------------------------------------------------------
// Read in all the words from the dictionary file into a vector
void readWordsIntoDictionary(
        vector <string> & dictionary,   // Dictionary where words will be stored
        string fileName)                // File name where words will be read from
{
    ifstream inStream;                  // Declare an input stream for reading
    inStream.open( fileName);            // Open dictionary file
    assert( inStream.fail() == false );  // Ensure file open worked
    
    // Clear vector in case it already had some words in it
    dictionary.clear();
    
    // Keep repeating while input from the file yields a word
    string newWord;                     // Store a single input word
    while( inStream >> newWord) {        // While there is another word to be read
        // Add this new word to the end of the vector, growing it in the process
    	 dictionary.push_back(newWord);
    }
    
    // Close the dictionary file
    inStream.close();
} //end readWordsIntoDictionary()


//---------------------------------------------------------------------------
// Select random words from the dictionary to be used for the board
void Board::selectRandomWords(vector<string> dictionaryWords)			// Max total length of all the words plus spaces
{
	string allWordsPlusSpaces = "";
    int maxTotalLengthOfWords = this->boardSize;
 
    // Clear the random words vector, in case this is not the first time we do this.
    this->randomWords.clear();
	
	while( allWordsPlusSpaces.length() < maxTotalLengthOfWords) {
		// Get a random word from the dictionary
		int randomWordIndex = rand() % dictionaryWords.size();
		string randomWord = dictionaryWords.at( randomWordIndex);
		
		// Verify that this new word will not go past the end of the board
		if( (randomWord.length() + allWordsPlusSpaces.length()) > maxTotalLengthOfWords) {
			continue;
		}
		
		// Length of new word is okay, so add it
		this->randomWords.push_back( randomWord);
		allWordsPlusSpaces += randomWord + " "; // add space at the end to separate words
	} // end while(allWordsPlusSpaces.length()...
} // end selectRandomWords()


//---------------------------------------------------------------------------
// Display the current board.  While we visualize the board as two-dimensional,
// we store it as a single string, with the rows concatenated after each other.
//--------------------------------------------------------------------------------
// Display the move numbers and board letters in each Node on the linked list.
// The pTemp pointer should iterate down the list, being used to display the
// values in each Node.
void displayList( Node *pTemp) {
    // ...
    if (pTemp->pNext == NULL) {
        cout << pTemp->moveNumber << ":" << pTemp->aBoard << endl;
    }
    else {
        while (pTemp->pNext != NULL) {
            cout << pTemp->moveNumber << ":" << pTemp->aBoard << " -> ";
            pTemp = pTemp->pNext;
        }
        cout << pTemp->moveNumber<<":"<< pTemp-> aBoard << endl;
    }



} // end displayList()


void displayBoard(
        Board board, Node *pHead)  // Board words used to create board
{
    // Display the top column letters.  Also clear the fill character, otherwise
    // it could be leftover as '-' from the previous board display.
    cout << endl
         << "    " << setfill(' ');
    for( int i=0; i<board.getBoardCharsPerSize(); i++) {
        cout << setw( 4) << (char)('A'+i);
    }
    // Display the heading above the solved board on the right
    cout << "         Goal Board";
    
	// Display the board character by character, formatted as a square board
	for( int row=0; row<board.getBoardCharsPerSize(); row++) {
        // Display a separator row of dash characters, like: "--------------"
		cout << "  \n      " << setw(board.getBoardCharsPerSize()*4+3) << setfill('-') << "   ";
        // Display a second row of dashes for the right-hand goal board
  		cout << "  " << setw(board.getBoardCharsPerSize()*4+3) << setfill('-') << "\n   ";
        
        // Display the row number
        cout << row << "";
        
        // Display the working board values on the left
		for(int col=0; col<board.getBoardCharsPerSize(); col++) {
			int index = row*board.getBoardCharsPerSize() + col; // compute the index into the 1D board vector
			cout << " | " << board.getBoardLetters()[index];
		}
		cout << " |   ";      // Last '|' at the end of each line.
  
        // Display the solved board values to the right
		for(int col=0; col<board.getBoardCharsPerSize(); col++) {
			int index = row*board.getBoardCharsPerSize() + col; // compute the index into the 1D board vector
			cout << " | " << board.getSolutionBoard()[index];
		}
		cout << " | ";      // Last '|' at the end of each line.
	}
 
    // Display the bottom line on the board
	cout << "\n      " << setw(board.getBoardCharsPerSize()*4) << setfill('-') << "";
    // Display the bottom line on the Goal board to the right
	cout << "     " << setw(board.getBoardCharsPerSize()*4) << setfill('-') << "\n";
   
	// Display the board characters and goal characters as strings.
    if (board.getBoardLetters() == board.getSolutionBoard()) {
        cout << "   Board string: " << board.getBoardLetters() << endl;
        cout << "    Goal string: " << board.getSolutionBoard()
             << endl
             << endl;
    }
    else {
        cout << "   Board string: " << board.getBoardLetters() << endl;
        cout << "    Goal string: " << board.getSolutionBoard()
             << endl
             << "    List is:"; displayList(pHead);
             cout << endl;
    }
} // end displayBoard()


//---------------------------------------------------------------------------
// Rotate characters within a single row of the board
void Board::rotateRowOnce(int rowToRotate)
{
	// Calculate the indices on the board for the start and end of the row
	int rowStartingBoardIndex = rowToRotate * this->boardCharsPerSize;
	int rowEndingBoardIndex = rowStartingBoardIndex + this->boardCharsPerSize - 1;
    // Store the last element on the row, as shifting right will overwrite it
    char lastElement = boardletters.at( rowEndingBoardIndex);
    
    // Shift all row elements to the right by one, starting from the
    // right, working our way back to the left.
    // E.g.      b e l o w
    //  becomes: w b e l o
    for( int i=rowEndingBoardIndex; i>rowStartingBoardIndex; i--) {
        this->boardletters.at(i) = this->boardletters.at( i-1);  // Overwrite element i with its left neighbor
    }
    // Overwrite the left-most element of the row with what used to be the last element
    this->boardletters.at( rowStartingBoardIndex) = lastElement;
} // end rotateRow()


//---------------------------------------------------------------------------
// Rotate characters within a single column of the board
void Board::rotateColOnce( int colToRotate)
{
	// Calculate the indices on the board for the start and end of the column
	int colStartingBoardIndex = colToRotate;
	int colEndingBoardIndex = colStartingBoardIndex + (this->boardCharsPerSize * (this->boardCharsPerSize - 1));
    // Store the last element in the column, as shifting down will overwrite it
    char bottomElement = this->boardletters.at( colEndingBoardIndex);
		
    // Shift all column elements to down by one, starting from the
    // bottom, working our way back up to the top.
	// E.g.  b		w
	//		 e		b
	//		 l	==>	e
	//		 o		l
	//		 w		o
    for( int i=colEndingBoardIndex; i>colStartingBoardIndex; i = i - this->boardCharsPerSize) {
        this->boardletters.at(i) = this->boardletters.at( i-this->boardCharsPerSize);  // Overwrite element i with its above neighbor
    }
    // Overwrite the top-most element of the row with what used to be the last element
    this->boardletters.at( colStartingBoardIndex) = bottomElement;
} // end rotateCol()


//---------------------------------------------------------------------------
// Do the user-selected board rotation consisting of the row number or column
// letter, followed by the number of rotations, which can be negative.
// E.g. 2 1 would rotate row 2 to the right by 1
//      a -2 would rotate the first column (column A) up by 2
void handleRotation( Board &board)
{
	char rowOrCol = ' ';
	int numPositionsToRotate = 0;
	
    // Infinite loop to handle user input validation
    while( true) {
        cout << "   Enter the row/column to rotate, and # of (+/-) rotations: ";
        cin >> rowOrCol >> numPositionsToRotate;
        rowOrCol = toupper(rowOrCol);   // Convert rowOrCol value to upper-case.  Numbers don't end up changing.
        
        // See if rowOrCol is not within the valid range
        if( !( (rowOrCol >= '0' && rowOrCol <= '0'+board.getBoardCharsPerSize() - 1) ||   // Row is within valid row range
               (rowOrCol >= 'A' && rowOrCol <= 'A'+board.getBoardCharsPerSize() - 1)      // Column is within valid column range
             )
          ) {
            // It is not within the valid ragne
            cout << "   *** Row/column value is not within the valid range.  Retry." << endl;
            continue;
        }
        // Validate numeric shift amount is within range
        if( abs( numPositionsToRotate) > board.getBoardCharsPerSize() - 1) {
            cout << "   *** Shift value should be between -" << board.getBoardCharsPerSize() - 1
                 << " and " << board.getBoardCharsPerSize() - 1 << ". Retry."
                 << endl;
            continue;
        }
        
        // Now that row/col and # of rotations validation tests have passed, break out of the loop
        break;
    } //end while( true)
    
    // If the number of rotations is negative, translate it to the corresponding positive amount.
    // E.g. In a 4x4 board, rotating a column up 1 (-1) is equivalent to shifting it down 4-1 = 3 times.
    //		In a 5x5 board, rotating a row left 3 (-3) is equivalent to shifting right 5-3 = 2 times
    if( numPositionsToRotate < 0) {
        numPositionsToRotate = board.getBoardCharsPerSize() + numPositionsToRotate;
    }
    
    // User input has been validated and converted to a positive number of shifts.  Do this many shifts.
    for( int i=0; i<numPositionsToRotate; i++) {
        if( rowOrCol >= '0' && rowOrCol <= '0'+9) {
            // Convert the row value '0'..'9' to a numeric value 0..9
            board.rotateRowOnce(rowOrCol-'0');
        }
        else {
            // Convert the column value 'A'..'I' to a numeric value 0..9
            board.rotateColOnce(rowOrCol-'A');
        }
    } //end for( int i...
} //end handleRotation()


//---------------------------------------------------------------------------
// Scramble the board, based on the selected difficulty level
void Board::scrambleBoard()      // Size per side of the board
{
    // Prompt for and get the number of board scrambling steps.  Each step does a random row
    // rotation and then a random column rotation.
    int numberOfScrambles = -1;
    // Loop to validate user input
    do {
        cout << "   Choose single-digit number of times to scramble board: ";
        cin >> numberOfScrambles;
        
        // Validate user input, reprompting if not one of the valid options
        if ( numberOfScrambles < 1 || numberOfScrambles > 9) {
            cout << "   *** The number of times must be a single digit >= 1. Retry." << endl;
        }
    } while( numberOfScrambles < 1 || numberOfScrambles > 9);

	// Rotate random rows and then a random column. Repeat this <numScrambles> times.
	for( int i=0; i < numberOfScrambles; i++) {
		// Rotate a random row
		int randRow = rand() % this->boardCharsPerSize;
		this->rotateRowOnce(randRow);
		
		// Rotate a random column
		int randCol = rand() % this->boardCharsPerSize;
		this->rotateColOnce(randCol);
	}
}// end scrambleBoard()


//---------------------------------------------------------------------------
// Clear the board, generate random words, initialize the board, store copy
// of completed board to use in checking for a win, scramble the initial
// board and store a copy to allow resetting the board.
//    All this is done in this function because it is done once at the
// beginning of the game, and is also done again if 'G' to generate a new
// board is chosen.
//
void setUpBoards(vector<string> dictionaryWords, Board &board)
{
    // Prompt for and get board size
    int boardCharsPerSide = 0;
    do {
        cout << "   Choose board size. It must be a single digit >=4: ";
        cin >> boardCharsPerSide;
        
        // Validate input to be >= 4 and <= 9
        if( boardCharsPerSide < 4 || boardCharsPerSide > 9) {
            cout << "   *** The board size must be a single digit >=4. Retry." << endl;
        }
    } while( boardCharsPerSide < 4 || boardCharsPerSide > 9);


    board.setBoardSize(boardCharsPerSide);
    // Total number of chars on the board

	// Blank out all initial boards, in case this is not the first time doing setup.
    board.clearBoardLetters();// Playing board
    board.clearBoardSolution(); // Completed board, used to check for win
    
    // Generate the random words, store a copy of the completed board, create and store
    // a copy of the initial scrambled board.
    board.selectRandomWords(dictionaryWords);
    // Append the words onto the board, with spaces in between
    board.initializeBoard();
    // Scramble the board, prompting for the number of desired rotations, which sets the difficulty.
    board.scrambleBoard();
} //end setUpBoards()


// ******  IMPORTANT!!!  READ THIS!!!  ******
//
// FIRST get the program working using classes BEFORE implementing the linked-list portion
// outlined in the code below.
//
// Once your classes version of program 5 is working also implement a Node struct or class
// used to store each move.  Your Node class should have private data members for:
//       1. A Board  (of type Board defined above)
//       2. A moveNumber
//       3. A pointer to the next Node
// Implement class Board here
// ...







//--------------------------------------------------------------------------------
// Undo the move represented by the front node on the list, then delete this node.
// Parameters should be:
//  - pointer to the head of the list, which could change, so should be: Node *&pHead
//  - the old game Board to be restored from what is initially the second
//    Node on the list, before the front Node is deleted.
//  - the old moveNumber, which should be restored again from what is initially
//    the second Node on the list, before the front Node is deleted
void deleteFrontNodeFromList(Node *&pHead, Board &board, int &moveNumber ) {
	// There should always be at least one Node (the starting board) on the list.
    // If there is only this single Node, then give an error message and don’t {done in main}
    // do the undo, since we are already at the beginning of the game.
    // . . .
    Node *pTemp;
    // Keep track of the node to be deleted
    // . . .
    pTemp = pHead;

    // Advance the head pointer to the next node on the list
    // . . .
    pHead = pHead->pNext;
    // Restore the previous board and the old move number from what used
    // to be the second node on the list, but is now the first node
    // . . .
    board.setBoardLetters(pHead->aBoard);
    moveNumber = pHead->moveNumber;
    // Delete the old head of the list
    // . . .
    delete pTemp;

} //end deleteFrontNodeFromList()

//function clears the entire linked list except for the NULL in the beginning
void clearNode(Node *&pHead){
    Node *pTemp;
    while(pHead != NULL){
        pTemp = pHead;
        pHead = pHead->pNext;
        delete pTemp;
    }
}


//--------------------------------------------------------------------------------
// Create a new node and prepend it to the beginning of the list.
// Parameters should be:
//  - pointer to the head of the list, which could change, so should be Node *&pHead.
//  - the Board to be added to the new Node at the front of the list
//  - the current moveNumber to be added to the new Node at the front of the list
void prependNodeToList(Node *&pHead, int moveNumber, Board board) {
	// Create a new node and store current values into it
	// ...
    Node *newNode = new Node;
    newNode->aBoard = board.getBoardLetters();
    newNode->moveNumber = moveNumber;
    newNode->pNext = pHead;

      
	// Prepend it onto the front of the list
	// ...
    pHead = newNode;
}//end of prependNodeToList(...)


//---------------------------------------------------------------------------
//
int main()
{
	// For random number generation seed the random number generator to 1, so that results
    // are predictable.  To make results different every time instead you would
    // use srand( time( NULL));   Don't do this if you want your code to match test cases!
    srand( 1);
	
	vector<string> dictionaryWords;	// Vector to store the words from the dictionary

	/*
    vector<string> boardWords; // Vector to store the random words chosen to be included in the board
	int boardCharsPerSize = 5;		// Default number of rows and columns of the board
	int boardSize = boardCharsPerSize * boardCharsPerSize;		// Total number of characters on the board
	string theBoard;			    // The board, that changes as moves are made
	string completedBoard;// The completed board, used to check for a win
    */


    //above is all done with this object declaration
    Board board;
    // declare the pointer to the head of the list
    Node *pHead = NULL;

    char userInput = ' ';			// Character to read in the user input
    int moveNumber = 1;             // Move number, incremented after each valid move
      
    // Display program identification and overview.
    cout << "Program 6: Unscrambler Undo \n"
         << "CS 141, Fall 2021, UIC	     \n"
         << " \n"
         << "You will be presented with a board that is filled with scrambled words.    \n"
         << "Rotate the rows and columns to get the words displayed in the right order. \n"
         << "Press 'U' to undo moves.   \n"
         << endl;
    
    // Read in all the words from dictionary file into a vector.
    // Word list adapted from https://www.ef.com/wwen/english-resources/english-vocabulary/top-3000-words/
    readWordsIntoDictionary( dictionaryWords, "commonWords.txt");
    cout << dictionaryWords.size() << " words have been read in from the dictionary." << endl;
    
    // Select random words and setup all the boards
    setUpBoards(dictionaryWords, board);
    //Prepended as first move
    prependNodeToList(pHead, moveNumber, board);

	// Loop to prompt for and process user input
    while(true) {
    	displayBoard( board, pHead);//change parameters
    	
    	cout << "Enter one of the following: \n"
    		 << "   R Rotate a row or column \n"
    		 << "   G Generate a new board with new random words \n"
             << "   U Undo most recent move\n"
    		 << "   Q to quit. \n"
             << moveNumber << ". Your choice: ";
    	cin >> userInput;
    	userInput = toupper(userInput);
    	
        // Handle menu options
    	switch( userInput) {
            // 'Q' for Quit
    		case 'Q': {
    			cout << "Thank you for playing! Exiting program... \n" << endl;
                exit( 0);      // Exit the program.
				break;
			}
            // 'R' to rotate
			case 'R': {
				handleRotation( board);
                //increment the move number
                moveNumber++;
                //prepend this move to the list
                prependNodeToList(pHead, moveNumber, board);
				break;
			}
            // 'G' to generate a new board with new random words
            //have to clear the node
			case 'G': {
                clearNode(pHead);
                // reset moveNumber
                moveNumber = 1;
                //generate a new board and scramble it
                setUpBoards( dictionaryWords, board);
                //prepend it to the list
                prependNodeToList(pHead, moveNumber, board);
				break;
			}
            case 'U':
                //Check if it is the first move
                if (pHead->pNext == NULL){
                    cout<<"*** You cannot undo past the beginning of the game. Retry. ***"<<endl;
                    break;
                }
                else{
                    cout << "* Undoing move *"<<endl;
                    //delete the head node
                    deleteFrontNodeFromList(pHead, board, moveNumber);
                    break;
                }

            default: {
				cout << "You did not enter one of the valid options. Try again." << endl;
				break;
			}
		} //end switch( userInput)
        
        // Check for a win
    	if( board.getBoardLetters() == board.getSolutionBoard()) {
    		displayBoard( board, pHead);
    		cout << "Congratulations, you won! \n"
                 << "Exiting program... \n"
                 << endl;
    		return 0;
		}
  

	} // end while(true)
		
	return 0;
} //end main()

