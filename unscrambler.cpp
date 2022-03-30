/* main.cpp
 Program 5 Unscrammbler
 Author : Syed Mehdi
 CS 141 , Fall 2021, 9 A.M 
 Ububtu on Windows 11
Program Description:
	In this program, we are creating a board game where we have to get random words, scramble them,
	and make the user use the options given to them to solve the board so that it looks like actual 
	words. For extra credit, we can also implelemt the computer trying to solve the board as well.

 */

#include <iostream>   // For Input and Output
#include <fstream>    // For file input and output
#include <cassert>    // For the assert statement
#include <cctype>     // access to tolower() or toupper() function
#include <vector>     // For vectors
#include <string>     // String operations
#include <algorithm>  // use of vector algorithms
#include <cmath>
#include <iomanip>
using namespace std;

//the board class 
class Board{
	public:	//initalize the board to size zero
		//constucter 
		Board(int boardSize = 0){
			this->boardSize = boardSize;
			boardletters = vector<char>(this->boardSize*this->boardSize);
	
		}
		//made a copy constructer if I needed one ( I didn't and it is incomplete )
		Board(const Board &b1){this->boardSize = b1.boardSize; this->randomWords = b1.randomWords; this->boardletters = b1.boardletters;}
		//list of member functions I have used or I thought I needed 
		void fillBoard(vector <string> dictionary);//function to fill the boardletters vector with random words
		void scramble();//this function scrambles the letters in the boardletters vector
		void setScrambleInput();//this function sets the scramble input the user gives 
		int getScrambleInput(){return scrambleInput;} // returns scrambleInput 
		void dashes();//function that calculates and outputs the amount of dashes needed based on the size of the board
		void setBoardSize();//asks for user input for boardSize
		int getBoardSize(){return boardSize*boardSize;} // returns the size of the board
		char getBoardLetter(int index){return boardletters.at(index);}//returns a specific letter from the board
		void displayBoard();//displays board
		void resetBoard();//resets board back to when it was first scrambled 
		void rotate();//the rotate option for the menu
		void solution();//displays the solution 
		void makeMove(vector <string> dictionary);//did not use 
		void clearBoard(){boardletters = vector<char>(this->boardSize*this->boardSize);}//clears 
		bool checkWin();//checks win 
	private:
		vector <string> randomWords;//vector stores the words used in the board
		int boardSize;//stores the size of the board (ex 4 or 5, not the amont of boardletters_
		vector<char> boardletters;//the letters being displayed in the board
		vector<char> solutionBoard;//the letters that are in order according to the solution 
		vector<char> resetboard;//stores the letters as they are after they are first scrambled 
		int scrambleInput;//stores the user input for scramble()
		


};//end of Board class 

void Board::fillBoard(vector<string> dictionary){
	int spacesLeft = this->getBoardSize();//spaces left is equal to the amount of spaces in the board 
	randomWords.clear();//clear the list of words in case it was already in use 
	boardletters.clear();//clear the boardletters vector incase it was already in use 
	boardletters.resize(this->getBoardSize());//re size the board to the boardSize 
	string randomWord;
	int randomIndex;
	int boardIndex = 0;
	while (spacesLeft > 2){//this is because all of the words are at least 3 letters long 
		randomIndex = rand() % dictionary.size();//random index is selected random from the size of the dictionary 
		randomWord = dictionary.at(randomIndex);//string stores the word at that random index
		if (randomWord.length() > spacesLeft){//if the length of the word is greater than the amount of spaces left, search again
			while(randomWord.length() > spacesLeft){
				randomIndex = rand()%dictionary.size();
				randomWord = dictionary.at(randomIndex);
			}
		}
		randomWords.push_back(randomWord);//push the word into the vector is string 
		spacesLeft -= randomWord.length()+1;//subtract spaces left by the length of the word and a space that comes after it
	}
	for (string word : randomWords){
		for (char letter : word){//for every letter in the word in the vector of strings
			boardletters.at(boardIndex) = letter;//put the letter in the board 
			if (boardIndex < boardletters.size()){//if there is space left, go to the next index
				boardIndex++;
			}
		}
		if (boardIndex < boardletters.size()){//if there is space left
			boardletters.at(boardIndex) = ' ';//put a space on the board after the comepleted word 
			boardIndex++;//increment 
		}
	}
	while (boardIndex<boardletters.size()){//if and while there is still space left, put more characters of spaces 
		boardletters.at(boardIndex) = ' ';
		boardIndex++;
	}
	solutionBoard = boardletters;//this is the solution board 
}//end of fillBoard()

void Board::setScrambleInput(){//gets user input for scramble 
	int input;
	cout << "Choose the number of times you would like the board to be scrambled (must be a single number >= 1): ";
	cin >> input;
	if (input < 1){
		cout << "The number of times you select must be at least 1. Retry."<<endl;
		this->setScrambleInput();//called again if unsatisfactory
	}
	else{
		this->scrambleInput = input;
	}
	
		
}//end of setScrambledInput()
	

void Board::scramble(){//scrambles the board
	int randRow;
	int randCol;
    	char temp;
	char swap;	
	for (int i = 0; i < this->scrambleInput; i++){//scrambles based on the user input
		randRow = rand() % boardSize;//random rows and columns 
		randCol = rand() % boardSize;
		for (int j = boardSize-1; j >0; j--){//start from the end of the row ; loops based on how many rows/columns there are 
			temp = boardletters.at((randRow*boardSize)+j);//swaps last letter and the letter before that 
			swap = boardletters.at((randRow*boardSize)+(j-1));
			boardletters.at((randRow*boardSize)+j) = swap;
			boardletters.at((randRow*boardSize)+(j-1)) = temp;
		
		}
		for (int k = boardSize-1; k > 0; k--){//start from bottom of column
			temp = boardletters.at((k*boardSize)+randCol);//swaps bottom letter with letter above
			swap = boardletters.at(((k-1)*boardSize)+(randCol));
			boardletters.at((k*boardSize)+randCol) = swap;
			boardletters.at(((k-1)*boardSize)+randCol) = temp;
		}

	}
	resetboard = boardletters;//this is the reset board 
	
}//end of scramble()


void Board::setBoardSize(){//function gets user input for the board size
	cout << "Choose your board size (must be a number greater than or equal to 4): ";
	cin >> boardSize;
	if (boardSize < 4){//if unsatisfactory
		cout << "The board size must be at least 4. Retry."<<endl;
		this->setBoardSize();//called again if unsatisfactory
	}
	else{
		boardletters.resize(boardSize*boardSize);//size the board to the boardsize squared 
		boardletters.reserve(this->getBoardSize());//precautiionary so it is the same size when cleared (not sure if it works like that)
	}
	
}// end of setBaordSize()

void Board::dashes(){
	int dashes = ((this->boardSize)*15)/4;//15:4 ratio of dashes : boardSize 
	int quotient = boardSize/4;
	if (quotient>1){
		dashes+=quotient-1;	
	}
	else if (quotient == 1){
		dashes++;
		
	}
	if (boardSize == 10){
		dashes++;
	}
	for (int i = 0; i < dashes; i++){
		cout <<'-';
	}
}

void Board::displayBoard(){
	//top of the board 
	if (!this->checkWin()){//if the user has not won yet
		cout << "These are the words that you should try to spell out using the board, in order:"<<endl;
		cout <<"\t";
		for (int p = 0; p < randomWords.size()-1; p++){
			cout << randomWords.at(p) << ", ";
		}
		cout<< randomWords.at(randomWords.size()-1) << '.' <<endl<<endl;
		cout << "Current board: "<< endl;
		cout << "\t ";
	}
	//the board
	for (int i = 0; i < boardSize;i++){
		cout <<"   "<<i;
	}
	cout << endl;

	cout <<"\t   ";
	this->dashes(); 
	cout<<endl;
	for (int row = 0; row < boardSize; row++){
		cout << "\t"<<row;
		for (int column = 0; column < boardSize; column++){
			cout <<" | "<< boardletters.at((row*boardSize)+column);
		}
		cout << " |"<<endl;
		cout <<"\t   "; 
		this->dashes(); 
		cout<<endl;
	}
	//board words
	cout << "Current board words: ";
	for (char letter : boardletters){
		cout << letter;
	}
	cout <<endl;
}//end of displayBoard()

void Board::resetBoard(){
	this->boardletters = this->resetboard;
}//end of resetBoard()

//displays soltuion, same as display board except for inital statement, and the vector used 
void Board::solution(){

	cout << "The completed board should look like:"<< endl;
	cout << "\t ";
	for (int i = 0; i < boardSize;i++){
		cout <<"   "<<i;
	}
	cout << endl;

	cout <<"\t   ";
	this->dashes(); 
	cout<<endl;
	for (int row = 0; row < boardSize; row++){
		cout << "\t"<<row;
		for (int column = 0; column < boardSize; column++){
			cout <<" | "<< this->solutionBoard.at((row*boardSize)+column);
		}
		cout << " |"<<endl;
		cout <<"\t   "; 
		this->dashes(); 
		cout<<endl;
	}
	cout << "Current board words: ";
	for (char letter : solutionBoard){
		cout << letter;
	}
	cout <<endl;

}
void Board::rotate(){
	char choice;
	int number;
	int positions;
	char temp;
	char swap;
	bool bad = true;
	//while the inputs are unsatisfactory
	while (bad){
		cout <<"Enter the row/column you would like to rotate, and the number of positions to rotate by. \nThis should be in the format of <R or C> <row/column number> <number of positions to rotate>, where valid row and column numbers are between 0 and "<< this->boardSize-1<<", \nE.g. R 0 1 would rotate the top row (row 0) of the board to the right once, c 1 -2 would rotate the second column (col 1) of the board upwards twice.\nYour choice:";
    	cout << endl;
		cin >> choice >> number >> positions;
	
		if (tolower(choice) != 'r' && tolower(choice) != 'c'){
			cout << "First input must be 'R' or 'C'. Try again."<<endl<<endl;
		}
		else if (number > this->boardSize-1 || number<0){
			cout << "Number must be between 0 and "<<this->boardSize-1 << ". Try again." << endl << endl;
		}

		else{
			bad = false;
		}
	}
	
	switch(tolower(choice)){
		case 'r'://if users selects to rotate row
			if (positions > 0){//if the number of rotations is positive 
				for (int i = 0; i < positions; i++){//rotate number of times user selects to rotate; keeps the row consistent, changes the column 
					for (int j = (boardSize-1); j >0; j--){//same logic from scramble()
						temp = boardletters.at((number*boardSize)+j);
						swap = boardletters.at((number*boardSize)+j-1);
						boardletters.at((number*boardSize)+j) = swap;
						boardletters.at((number*boardSize)+j-1) = temp;	
					}
				}
				
			}
			
			else if (positions < 0){//if negative 
				positions*= -1;//change it to positive 
				for (int i = 0; i < positions; i++){//loop forwards instead of backwards 
					for (int j = 0; j < boardSize-1; j++){
						temp = boardletters.at((number*boardSize)+j);
						swap = boardletters.at((number*boardSize)+(j+1));
						boardletters.at((number*boardSize)+j) = swap;
						boardletters.at((number*boardSize)+(j+1)) = temp;
		
					}
				}
				
			}
			break;
		case 'c'://if user selects to rotate column 
			if (positions > 0){
				for (int l = 0; l < positions; l++){
					for (int k = boardSize-1; k > 0; k--){//keeps the column consistent, changes the row
						temp = boardletters.at((k*boardSize)+number);
						swap = boardletters.at(((k-1)*boardSize)+(number));
						boardletters.at((k*boardSize)+number) = swap;
						boardletters.at(((k-1)*boardSize)+number) = temp;
					}
				}
			}
			if (positions<0){
				positions*=-1;
				for (int m = 0; m < positions; m++){
					for (int p = 0; p < boardSize-1; p++){
						temp = boardletters.at((p*boardSize)+number);
						swap = boardletters.at(((p+1)*boardSize)+(number));
						boardletters.at((p*boardSize)+number) = swap;
						boardletters.at(((p+1)*boardSize)+number) = temp;
					}
				}

			}
			break;

	}
	




}//end of rotate()
bool Board::checkWin(){//checks for win
	if (boardletters == solutionBoard){//if the board is equivilent to the solution
		return true;
	}
	else{
		return false;
	}
}//end of checkWin()


void readWordsIntoDictionary(vector<string> &dictionary){
	ifstream inStream;
	inStream.open("dictionary-3to5-letters.txt");
	assert(inStream.fail() == false);

	//incase we used dictionary as a vector before
	dictionary.clear();

	string currWord;
	while(inStream >> currWord){
		dictionary.push_back(currWord);
	}
	inStream.close();
}//end of readWordsIntoDictionary


int main(){
	srand(1);//seeds the random so the output is consistent with test
	char input;//first input
	char nextInput;//second input
	int scrambleInput = -1;//input for scramble
	vector<string> dictionary;//the dictionary
	readWordsIntoDictionary(dictionary);//read the words into dictionary 
	Board board;//the board 
	cout <<"Program 5: Unscrambler\nCS 141, Fall 2021, UIC\n"<<endl<<
		"You will be presented with a board that is filled with scrambled words. Rotate the rows and columns\nto get the words displayed in the right order.\n"<<endl<<
		dictionary.size()<< " words have been read in from the dictionary.\n"<<endl
		<<"Enter Q to quit or B to begin: ";
	cin >> input;
	
	switch (tolower(input)){
		case 'q'://if q, quit
			
			cout << "Thank you for playing!"<<endl;
			cout << "Exiting program..."<<endl;
			exit(0);
		case 'b'://begin 
			board.setBoardSize();//call for input for board size
			board.fillBoard(dictionary);//fill the board 
			board.setScrambleInput();//get scramble input from user 
			board.scramble();//scramble the baord 
			while(tolower(nextInput) != 'q'){//while the user doesn't quit 
	       			board.displayBoard();//display board and menu
				cout << "Enter one of the following:"<<endl;
				cout <<"\tR to rotate a row or column,"<<endl;
				cout <<"\tC to view what the completed board should look like,"<<endl;
				cout <<"\tB to reset the board back to the beginning,"<<endl;
				cout <<"\tG to generate a new board with new random words,"<<endl;
				cout <<"\tS to have the computer automatically solve a board that you enter (5 points extra credit),"<<endl;
				cout<<"\tQ to quit."<<endl;
				cout<<"Your choice: ";
				cin >> nextInput;//get input
				switch(tolower(nextInput)){
					case 'q'://if user quits
						cout<<"Thank you for playing!"<<endl;
						cout<<"Exiting program..."<<endl;
						exit(0);
					case 'r'://if user chooses to rotate 
						board.rotate();
						if (board.checkWin()){//if the user has won
							board.displayBoard();
							cout<<endl;
							cout << "Congratulations, you won! Thank you for playing!"<<endl;
							cout<<"Exiting program..."<<endl;
							exit(0);//exit
						}
						break;
					case 'c'://display complete board 
						board.solution();//displays solution
						break;
					case 'b'://reset board 
						board.resetBoard(); //resets board back to beginning 
						break;
					case 'g'://generate new board 
						board.clearBoard();//clear the vectors 
						board.fillBoard(dictionary);//fill the board again 
						board.scramble();//scramble the board again 
						break;
					default://if input not valid 
						cout << "You did not enter one of the valid options. Try again." << endl;

				}
			}
			break;
		default://if input not valid 
			cout << "Not valid" <<endl;
			
	}
	

	return 0;
}//end of main()
