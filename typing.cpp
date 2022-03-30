//Program 3 by Syed Shaban, Syed Mehdi
//Linux with Ubuntu on Windows 10
#include <bits/stdc++.h>
#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>
#include <cassert>
#include <cctype>
using namespace std;

void readWordsIntoDictionary(vector<string> &dictionary){
	ifstream inStream;
	inStream.open("dictionary.txt");
	assert(inStream.fail() == false);

	//incase we used dictionary as a vector before
	dictionary.clear();

	string currWord;
	//adds words into dictionary vector
	while(inStream >> currWord){
		dictionary.push_back(currWord);
	}
	inStream.close();
}
void readWordsIntoMisspelled(vector<string> &correct, vector<string> &incorrect){
        ifstream inStream;
        inStream.open("misspelledWords.txt");
        assert(inStream.fail() == false);

        //incase we used dictionary as a vector before
        correct.clear();
	incorrect.clear();

        string currLine;
	string secondLine;
	string firstLine;
	int num = 0;
	//reads words into two seperate vectors, misspelled words and correctly spelled words
        while(getline(inStream, currLine)){
                secondLine=currLine.substr(currLine.find(" ")+1);
		firstLine=currLine.substr(0, currLine.find(" "));
		correct.push_back(secondLine);
		incorrect.push_back(firstLine);
		correct.at(num).pop_back();//this is to pop back the invisible character at the end of the line 
		num++;
        }
        inStream.close();
}
int bestScore(vector <int> scores){
	int tempVar = scores.at(0);
	int bestscore;
	for (int i = 0; i < scores.size();i++){
		if (scores.at(i) > tempVar){
			tempVar = scores.at(i);
		}
	}
	return tempVar;
}//function iterates through the vector of scores and returns the best one



//choice 1: Spell commonly misspelled words (timed)
void firstChoice(vector<string> wrongWords, vector<string> rightWords,vector <int> &scores){
	//initialized all of the variables being used
	int bonus=0;
	int penalty=0;
	int ppw = 3;//points per word
	int numberOfSecondsOver15 = 0;
	int numberOfSecondsUnder15 = 0;
	int score = 0;
	string tempVar;
        int tempIndex;
        cout << "Using commonly misspelled words" << endl;
        vector<int> indexes;//vector to store the indexes of the randomly generated words
        indexes.clear();//clears indexes if it was already used
        int i;
        for (i = 0; i < 5; i++){//loops 5 times for 5 words
                tempIndex = rand() % wrongWords.size();
                tempVar = wrongWords[tempIndex];
                indexes.push_back(tempIndex);//pushes the index of the word into the vector
                cout << tempVar << " ";
        }
        cout << endl;
        cout << "Type in those words within goal of 15 seconds: " << endl;
        string currLine;
        int counter;
        vector<string> correctWords, incorrectWords;//2 seperate vectors for the user's input, depending on if it's spelled correctly
        vector<int> incorrectWordsIndexes;//indexes of the misspelled words
        string word;
        int startTime = time(NULL);//timer starts
        for (counter = 0; counter < 5; counter++){//loops 5 times for 5 inputs
                cin >> word;//input
		//compare word to the correctly spelled version of the word 
                if (word.compare(rightWords.at(indexes.at(counter)))){//if it's incorrect, push it into incorrectWords 
			incorrectWords.push_back(word);
                        incorrectWordsIndexes.push_back(indexes.at(counter));//pushes the index of the incorrect word into the vector
                }
                else{
                        correctWords.push_back(word);//pushes the input into correctWords if it is correctly spelled
                }
        }
	if (incorrectWords.size()>0){//if there are any incorrect words

        	cout << endl << "\tMisspelled words: " << endl;
        	for (int x = 0; x < incorrectWords.size(); x++){
			//states what the correct spelling of the word should be
                	cout << "\t\t" << incorrectWords.at(x) << " should be: " << rightWords.at(incorrectWordsIndexes.at(x))  << endl;
        }
	}
	else{
		cout << endl << "\tNo misspelled words!"<<endl;
	}

        //counts time since start time.
        int elapsedSeconds = difftime(time(NULL), startTime);
        cout << "\tElapsed time: " << elapsedSeconds << " seconds. ";
	//sets penalty if the user takes more than 15 seconds
	if (elapsedSeconds > 15){
		numberOfSecondsOver15 = elapsedSeconds - 15;
		penalty = -3*(numberOfSecondsOver15);
		score += penalty;
		cout << penalty << " for finishing "<< numberOfSecondsOver15 <<" seconds late."<<endl;
	}//sets bonus if user takes less than 15 seconds
	else if (elapsedSeconds < 15){ 
		numberOfSecondsUnder15 = 15 - elapsedSeconds;
		bonus = numberOfSecondsUnder15*2;
		score += bonus;
		cout << bonus << " point bonus for finishing " << numberOfSecondsUnder15 << " seconds early." << endl;
	}
	score += (correctWords.size()*ppw) - (incorrectWords.size()*ppw*2);//calculates remaining score
	scores.push_back(score);//pushes score into a vector of scores for the game
	
	cout << "\t";
	//points for correctly spelled words
	cout << correctWords.size()*ppw << " points: " << correctWords.size() << " spelled correctly x "<<ppw<<" points each"<<endl;
	//checks if there are any incorrect words
	if (incorrectWords.size()>0){
		cout<<"\t";
		//outputs the penalty for spelling incorrectly 
		cout << incorrectWords.size()*ppw*2 << " point penalty: " << incorrectWords.size() << " spelled incorrectly x "<<ppw*2<<" points each"<< endl;
	}
	//outputs score
	cout << "\tScore: " << score << endl;


}//end of firstChoice()
//Type random words from full dictionary
//					word length changes after every call
void secondChoice(vector<string> dictionary, int &wordAmount, vector <int> &scores){
	//variable declarations(same as firstChoice())
	string tempVar;
	int tempIndex;
	int ppw = wordAmount-4;//points per word
	int bonus=0;
	int penalty=0;
	int score=0;
	int numberOfSecondsOver15 = 0;
	int numberOfSecondsUnder15 = 0;
	cout << "Using full dictionary" << endl;
	vector<int> indexes;
	indexes.clear();
	int i;
	for (i = 0; i < 5; i++){//randomly generates words from dictionary
		tempIndex = rand() % dictionary.size();
		while (dictionary.at(tempIndex).length() != wordAmount){//keeps going if it doesn't match the word length
			tempIndex = rand() % dictionary.size();
		}
		tempVar = dictionary[tempIndex];
		indexes.push_back(tempIndex);
		cout << tempVar << " ";
	}
	cout << endl;
	cout << "Type in those words within goal of 15 seconds: " << endl;
	string currLine;
	int counter;
	vector<string> correctWords, incorrectWords;
	vector<int> incorrectWordsIndexes;//same as firstChoice()
	string word;
	int startTime = time(NULL);//starts timer
	for (counter = 0; counter < 5; counter++){
                cin >> word;
		//if the word is spelled incorrectly
                if (word.compare(dictionary.at(indexes.at(counter)))){
                        incorrectWords.push_back(word);
			incorrectWordsIndexes.push_back(indexes.at(counter));
			
                }
                else{
                	correctWords.push_back(word);
		}
        }//ends loop
	//if there are any incorrect words
	if (incorrectWords.size()>0){

        	cout << endl << "\tMisspelled words: " << endl;
        	for (int x = 0; x < incorrectWords.size(); x++){
                	cout << "\t\t" << incorrectWords.at(x) << " should be: " << dictionary.at(incorrectWordsIndexes.at(x)) << endl;
        	}
	}
	else{
		cout << endl << "\tNo misspelled words!"<<endl;
	}


        //counts time since start time.
        int elapsedSeconds = difftime(time(NULL), startTime);
        cout << "\tElapsed time: " << elapsedSeconds <<  " seconds. ";
        //penalty and bonus
	if (elapsedSeconds > 15){
                numberOfSecondsOver15 = elapsedSeconds - 15;
                penalty = -3*(numberOfSecondsOver15);
                score += penalty;
                cout << penalty << " for finishing "<< numberOfSecondsOver15 <<" seconds late."<<endl;
        }
        else if (elapsedSeconds < 15){
                numberOfSecondsUnder15 = 15 - elapsedSeconds;
                bonus = numberOfSecondsUnder15*2;
                score += bonus;
                cout << bonus << " point bonus for finishing " << numberOfSecondsUnder15 << " seconds early." << endl;
        }
        
	
        cout << "\t";
	int correctPoints = correctWords.size()*ppw;//stores the points into a variable so it outputs correctly
        cout << correctPoints << " points: " << correctWords.size() << " spelled correctly x "<<ppw<<" points each"<<endl;
        int incorrectPoints = incorrectWords.size()*ppw*2;
        if (incorrectPoints!=0){
                cout<<"\t";
                cout << incorrectPoints << " point penalty: " << incorrectWords.size() << " spelled incorrectly x "<<ppw*2<<" points each"<< endl;
        }
	score += correctPoints - incorrectPoints;//calculates remaining score
	scores.push_back(score);//stores the score into a vector
        cout << "\tScore: " << score << endl;//outputs score
	wordAmount++;//increments word length by 1

}//end secondChoice()
//Display a range of words from any list 
void thirdChoice(vector<string> dictionary, vector<string> rightWords, vector<string> wrongWords, int wordAmount){
	char choiceOne;
	cout << "\tDisplaying word list entries." << endl << "\tWhich words do you want to display?" << endl;
	cout << "\t\tA. Dictionary of all words" << endl << "\t\tB. Wrongly spelled common misspelled words" << endl;
	cout << "\t\tC. Correctly spelled common misspelled words" << endl;
	cout << "Your choice --> ";
	cin >> choiceOne;// user input of letter choice
	int i;
	choiceOne = tolower(choiceOne);// sets choice to lowercase
	if (choiceOne == 'a'){
		cout << "Enter the start and end indices between 0 and " << dictionary.size()-1 << ": ";	
	}
	else if (choiceOne == 'b'){
		cout << "Enter the start and end indices between 0 and " << wrongWords.size()-1<<": ";
	}
	else if (choiceOne == 'c'){
		cout << "Enter the start and end indices between 0 and " << rightWords.size()-1<<": ";
	}
	cout << " ";
	int startIndex, endIndex;
	// user inputted ranges
	cin >> startIndex;
	cin >> endIndex;
	//outputs based on choice of user
	if (choiceOne == 'a'){
        	for (int count = startIndex; count < endIndex + 1; count++){
                	cout << "\t" << count << ". " << dictionary.at(count) << endl;
        	}
	}
        else if (choiceOne == 'b'){
                for (int count = startIndex; count < endIndex + 1; count++){
                        cout << "\t" << count << ". " << wrongWords.at(count) << endl;
                }
        }
        else if (choiceOne == 'c'){
                for (int count = startIndex; count < endIndex + 1; count++){
                        cout << "\t" << count << ". " << rightWords.at(count) << endl;
                }
        }

}//end of thirdChoice
//------------------------------------------------------------------------
//Binary search
//							user's word
int fourthChoice(vector<string> dictionary, int endIn, string searchWord){
	int startIn = 0;
	int counter = 1;
	//execute until start and end index are equivilent
	while (startIn <= endIn){
		int mid = (startIn + endIn) / 2;//midpoint of data
		//displays word being compared 
		cout << counter << ". Comparing to: " << dictionary.at(mid) << endl;
		//if the word matches the input
		if (dictionary.at(mid) == searchWord) {
			return mid;
		}
		//if the word is less than the input, change the start index to halfway+1
		if (dictionary.at(mid) < searchWord){
			startIn = mid+1; 
		}
		//else change the end index to halfway-1
		else{
			endIn = mid-1; 
		}
		counter++;//increments counter
		
	}
	return -1;

}//end of fourthChoice()
//------------------------------------------------------------------------
//The menu
void displayMenu(){
	cout << "Select a menu option:" << endl;
	cout << "\t1. Spell commonly misspelled words (timed)" << endl;
	cout << "\t2. Type random words from full dictionary (timed)" << endl;
    	cout << "\t3. Display some words from one of the lists" << endl;
	cout << "\t4. Use binary search to lookup a word in full dictionary" << endl;
	cout << "\t5. Set word length to use with full dictionary" << endl;
	cout << "\t6. Exit the program" << endl;	
}//end of displayMenu()
//-----------------------------------------------------------------------

int main(){
	//sets start time
        time_t startTime = time(NULL);
	srand(1);//seeds random
	int i;
	int wordAmt = 5;//word length
	//vecotors of dictionary, correctly spelled words, incorrectly spelled words
	vector<string> dictionary;
	vector<string> CCMwords;
	vector<string> ICMwords;
	// vector for scores
	vector<int> scores;
	//reads the words from the files to the vectors
	readWordsIntoDictionary(dictionary);
	readWordsIntoMisspelled(CCMwords, ICMwords);
	//outputs the sizes
	cout << "There are " << dictionary.size() << " words in the full dictionary." << endl;
	cout << "There are " << CCMwords.size() << " commonly misspelled words." << endl;
	
	//stores number of seconds elapsed since start time.
	int elapsedSeconds = 0;
	string choice;
	string input;
	int ending;
	int lengthOfWords;
	
	choice = "0";
	//while user doesn't choose "6"
	while (choice != "6"){
		cout << endl;
		displayMenu();
		cout << "Your choice --> ";
		cin >> choice;//user input
		//executes functions based on choice
		if (choice == "1"){
			firstChoice(ICMwords, CCMwords,scores);
		}
		else if (choice == "2"){
			secondChoice(dictionary, wordAmt,scores);
			
		}
		else if (choice == "3"){
			thirdChoice(dictionary, CCMwords, ICMwords, wordAmt);
		}
		else if (choice == "4"){
			cout << endl << "Enter the word to lookup: ";
			cin >> input;//user input for word to lookup
			if (fourthChoice(dictionary, dictionary.size()-1, input) == -1){
				cout << input << " was NOT found." << endl << endl;
			}
			else {
				cout << input << " was found." << endl << endl;
			}
	
		}
		//sets new word length for choice 2
		else if (choice == "5"){
			cout << "Enter new wordLength: ";
			cin >> lengthOfWords;
			wordAmt = lengthOfWords;
		}
	}
	//if user chose to exit
	if (choice == "6"){
		
		cout << endl << "Exiting program" << endl;
		if (scores.size()>0){//if there were any scores

			cout << "Best score was " << bestScore(scores)<<endl;
		}
		else{
			cout << "Best score was 0"<<endl;
		}
		exit(0);
	}
	return 1;//to keep c happy
}//end of main()
