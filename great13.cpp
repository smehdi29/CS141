/* ----------------------------------------------------------------------
    Program 2: Great 13
        Peg puzzle. Jump pegs to try and leave only a single peg.

    Course: CS 141, Fall 2021
    System: Windows Laptop using Ubuntu
    Author: Syed Mehdi
    
    Running the program looks like:
        . . .
   ----------------------------------------------------------------------
*/
#include <iostream>
#include <cctype>   // for toupper()
using namespace std;

// Global variables for the pieces are allowed for this program,
// but will generally not be allowed in the future.
// You will likely want to declare global variables at least for the following:
//   - 13 board pieces
//   - The letter positions you are moving from, jumping over, and moving to
//   - The number of pieces on the board (to know when there is a win)
// ...


// ----------------------------------------------------------------------
// Declare global variables
char pA;
char pB;
char pC;
char pD;
char pE;
char pF;
char pG;
char pH;
char pI;
char pJ;
char pK;
char pL;
char pM;


void resetBoard(){//to reset the board, also used to initalize the board

	pA = pB = pC = pD = pE = pF = pH = pI = pJ = pK = pL = pM = '#';//set pieces to #
	pG = '.';//set middle to .


}//end resetBoard()


//Display Instructions
void displayInstructions()
{
    cout << "Class: CS 141             \n"
         << "Program: #2 Great 13      \n"
         << "  \n"
         << "Make a series of jumps until there is a single piece left in the   \n"
         << "middle. On each move you must jump an adjacent piece into an empty \n"
         << "square, jumping horizontally, vertically, or diagonally.           \n"
         << "Input of 'R' resets the board back to the beginning, and input of  \n"
         << "'X' exits the game.'   \n"
         << endl;
} //end displayInstructions()

    
// ----------------------------------------------------------------------
// Display the board, using the global variables pA..pM
void displayBoard()
{
    cout <<"\n "
         <<                 "    Board   " <<            " Position \n"
         <<"       "             << pA <<             "          A    \n"
         <<"     " <<      pB<<" "<<pC<<" "<<pD<<       "      B C D  \n"
         <<"   "<<pE<<" "<<pF<<" "<<pG<<" "<<pH<<" "<<pI<<"  E F G H I\n"
         <<"     " <<      pJ<<" "<<pK<<" "<<pL<<       "      J K L  \n"
         <<"       "             << pM <<             "          M    \n"
         << endl;
} //end displayBoard()
// function that checks if the move has letter that are adjacent
bool isAdjacent( char from, char skip, char dest ){
	if (from == 'A'){
		if (skip == 'B' && dest == 'E'){
			return true;
		}
		else if (skip == 'C' && dest == 'G'){
			return true;
		}
		else if (skip == 'D' && dest == 'I'){
			return true;
		}
		else{
			return false;
		}
	}
	else if (from == 'B'){
		if (skip == 'C' && dest == 'D'){
			return true;
		}
		else if (skip == 'F' && dest == 'J'){
			return true;
		}
		else if (skip == 'G' && dest == 'L'){
			return true;
		}
		else{
			return false;
		}
	}
	else if (from == 'C'){
		if (skip == 'G' && dest == 'K'){
			return true;
		}
		else{
			return false;
		}
	}
	else if (from == 'D'){
		if (skip == 'C' && dest == 'B'){
			return true;
		}
		else if ( skip == 'G' && dest == 'J'){
			return true;
		}
		else if ( skip == 'H' && dest == 'L'){
			return true;
		}
		else {
			return false;
		}
	}
	else if (from == 'E'){
		if (skip == 'B' && dest == 'A'){
			return true;
		}
		else if (skip == 'J' && dest == 'M'){
			return true;
		}
		else if (skip == 'F' && dest == 'G'){
			return true;
		}
		else{
			return false;
		}
	}
	else if (from == 'F'){
		if (skip == 'G' && dest == 'H'){
			return true;
		}
		else{
			return false;
		}
	}
	else if (from == 'G'){
		if (skip == 'C' && dest == 'A'){
			return true;
		}
		else if (skip == 'K' && dest == 'M'){
			return true;
		}
		else if (skip == 'H' && dest == 'I'){
			return true;
		}
		else if (skip == 'F' && dest == 'E'){
			return true;
		}
		else {
			return false;
		}
	}
	else if (from == 'H'){
		if (skip == 'G' && dest == 'F'){
			return true;
		}
		else {
			return false;
		}
	}
	else if (from == 'I'){
		if (skip == 'D' && dest == 'A'){
			return true;
		}
		else if ( skip == 'H' && dest == 'G'){
			return true;
		}
		else if ( skip == 'L' && dest == 'M'){
			return true;
		}
		else {
			return false;
		}
	}
	else if (from == 'J'){
		if (skip == 'F' && dest == 'B'){
			return true;
		}
		else if (skip == 'K' && dest == 'L'){
			return true;
		}
		else if ( skip == 'G' && dest == 'D'){
			return true;
		}
		else {
			return false;
		}
	}
	else if (from == 'K'){
		if (skip == 'G' && dest == 'C'){
			return true;
		}
		else {
			return false;
		}
	}
	else if (from == 'L'){
		if (skip == 'H' && dest == 'D'){
			return true;
		}
		else if (skip == 'K' && dest == 'J'){
			return true;
		}
		else if (skip == 'G' && dest == 'B'){
			return true;
		}
		else{
			return false;
		}
	}
	else if (from == 'M'){
		if (skip == 'J' && dest == 'E'){
			return true;
		}
		else if (skip == 'K' && dest == 'G'){
			return true;
		}
		else if (skip == 'L' && dest == 'I'){
			return true;
		}
		else{
			return false;
		}
	}
	else{
		return false;
	}
}//end isAdjacent()
// checks if jump and from have pieces, function works for both
bool isFromOrJValid(char from){
	if (from == 'A'){
		if (pA == '#'){
			return true;
		}
		else{
			return false;
		}

	}
	else if (from == 'B'){
		if (pB == '#'){
			return true;
		}
		else {
			return false;
		}
	}
	else if (from == 'C'){
		if (pC == '#'){
			return true;
		}
		else{
			return false;
		}
	}
	else if (from == 'D'){
		if (pD == '#'){
			return true;
		}
		else {
			return false;
		}

	}
        else if (from == 'E'){
                if (pE == '#'){
                        return true;
                }
                else {
                        return false;
                }

        }	
	else if (from == 'F'){
		if (pF == '#'){
			return true;
		}
		else{
			return false;
		}
	}
	else if (from == 'G'){
		if (pG == '#'){
			return true;
		}
		else{
			return false;
		}
	}
	else if (from == 'H'){
		if (pH == '#'){
			return true;
		}
		else {
			return false;
		}
	}
	else if (from == 'I'){
		if (pI == '#'){
			return true;
		}
		else {
			return false;
		}
	}
	else if (from == 'J'){
                if (pJ == '#'){
                        return true;
                }
                else {
                        return false;
                }
        }
	else if (from == 'K'){
                if (pK == '#'){
                        return true;
                }
                else {
                        return false;
                }
        }
	else if (from == 'L'){
                if (pL == '#'){
                        return true;
                }
                else {
                        return false;
                }
        }
	else if (from == 'M'){
                if (pM == '#'){
                        return true;
                }
                else {
                        return false;
                }
        }
	else{
		return false;
	}
}//end of isFromOrJValid()
//checks if destination is empty
bool isDestValid(char dest){
	if (dest == 'A'&& pA == '.'){
		return true;
	}
	else if (dest == 'B' && pB == '.'){
		return true;
	}
	else if (dest == 'C' && pC == '.'){
                return true;
        }
	else if (dest == 'D' && pD == '.'){
                return true;
        }
	else if (dest == 'E' && pE == '.'){
                return true;
        }
	else if (dest == 'F' && pF == '.'){
                return true;
        }
	else if (dest == 'G' && pG == '.'){
                return true;
        }
	else if (dest == 'H' && pH == '.'){
                return true;
        }
	else if (dest == 'I' && pI == '.'){
                return true;
        }
	else if (dest == 'J' && pJ == '.'){
                return true;
        }
	else if (dest == 'K' && pK == '.'){
                return true;
        }
	else if (dest == 'L' && pL == '.'){
                return true;
        }
	else if (dest == 'M' && pM == '.'){
                return true;
        }
	else {
		return false;
	}	
	


}//end isDestValid()
// function to change from and jump 
void fromandjump(char from){
	if (from == 'A'){
		 pA = '.';
	 }
        if (from == 'B'){
                pB = '.';
        }
	if (from == 'C'){
               pC = '.';
        }
       	if (from == 'D'){
                pD = '.';

        }
       	if (from == 'E'){
                pE = '.';

        }
       	if (from == 'F'){
                pF = '.';
	}
       	if (from == 'G'){
                pG = '.';
        }       
	if (from == 'H'){
                pH = '.';
        }       
	if (from == 'I'){
                pI = '.';
        }
        if (from == 'J'){
                pJ = '.';
        }
	if (from == 'K'){
                pK = '.';
        }
        if (from == 'L'){
                pL = '.';
        }
        if (from == 'M'){
                pM = '.';
        }

}
void changeDest(char dest){
	if (dest == 'A'){
                 pA = '#';
         }
       	if (dest == 'B'){
                pB = '#';
        }
        if (dest == 'C'){
               pC = '#';
        }
        if (dest == 'D'){
                pD = '#';

        }
        if (dest == 'E'){
                pE = '#';

        }
        if (dest == 'F'){
                pF = '#';
        }
        if (dest == 'G'){
                pG = '#';
        }
        if (dest == 'H'){
                pH = '#';
        }
        if (dest == 'I'){
                pI = '#';
        }
        if (dest == 'J'){
                pJ = '#';
        }
        if (dest == 'K'){
                pK = '#';
        }
        if (dest == 'L'){
                pL = '#';
        }
        if (dest == 'M'){
                pM = '#';
        }
}

// ----------------------------------------------------------------------
// Main section of the program, containing the game play loop
int main() {

	
    displayInstructions();
    
    // Set board values to the default starting position
    // ...
    pA = pB = pC = pD = pE = pF = pH = pI = pJ = pK = pL = pM = '#';
    pG = '.';//set board to #s
    // Game play loop
    displayBoard();
    int numberOfPieces = 12;//number of #s
    int moveNumber = 1;
    char from;
    char jump;
    char to;
    string moveFrom;//declares moveFrom

    while( numberOfPieces > 1 ) {
        cout << moveNumber << ". "
             << "Enter positions from, jump, and to (e.g. EFG): ";
        cin >> moveFrom;                // Read just the first user input, handling inputs 'X' or 'R'
         
        
        // If 'X' to exit was chosen, break out of game play loop
        // ...
	if (toupper(moveFrom.at(0)) == 'X'){
		cout << "Exiting" << endl;
		break;
	}

        
        // If 'R' to reset the board was chosen, reinitialize everything
        // display the board, and continue back up to re-run the while(...) loop
        // ...
	else if (toupper(moveFrom.at(0)) == 'R'){
		resetBoard();
		moveNumber = 1;
		numberOfPieces = 12;
		cout<< "\n   *** Restarting" << endl;
		displayBoard();
	}
	else{
		from = toupper(moveFrom.at(0));// Additionally now also read the piece-to-jump and destination inputs.
		jump = toupper( moveFrom.at(1));
		to = toupper(moveFrom.at(2));//uppercase them all so it is easier for the code to read it
	// Ensure set of pieces (from, jump, to) are adjacent.  If they aren't, then
        // continue back up to re-run the while(...) loop.
		if (!isAdjacent(from,jump,to)){
			cout << "\n   *** Pieces must be adjacent. Please retry\n"<< endl;
			continue;
		}
		//ensure that from and jump have pieces
		else if (!isFromOrJValid(from)){
			cout << "\n   *** Source must have a piece. Please retry\n"<<endl;
			continue;
		}
		else if (!isFromOrJValid(jump)){
				cout << "\n   *** Must jump a piece. Please retry\n"<<endl;
				continue;
		}
		else if (!isDestValid(to)){//ensures destination is blank
			cout <<"\n   *** Destination must be blank. Retry\n"<<endl;
			continue;
					
		}
		else{//executes move
			fromandjump(from);
			fromandjump(jump);
			changeDest(to);
			numberOfPieces-=1;
			moveNumber++;
			displayBoard();
			continue;
			

		}
				
	}

    } //end while( numberOfPieces > 1)
    
    // Check for a win
    // ...
    if (numberOfPieces == 1){
	    cout << "\nCongratulations, you did it!"<<endl;
    }
    else{
	    cout << "\nBetter luck next time."<<endl;
    }

    
    cout << "Done." << endl;
    return 0;
} //end main()
