/*
of sections and display
        an ASCII gladiolus flower, with the sections centered
        above each other.

    Course: CS 141, Fall 2021. Tues 5pm lab
    System: Windows on Ubuntu
    Author: Syed Mehdi
    
    Original ASCII graphics gives:
    	------------------------------------------
           __     __     ________          _________             
          |  |   |  |    |__  __|         {   _____/  
          |  |   |  |      |  |    ^     {   {         
          |  |___|  |      |  |  < * >  {   {     ___  
          |         |    __|  |__  V     {   {___/  /     
          \_________/   |________|       {_________/             

        ------------------------------------------

   ---------------------------------------------
*/

#include <iostream>   // for cin and cout
#include <iomanip>    // for setw. The number in setw(...) is the total of blank spaces including the printed item.
#include <math.h>
using namespace std;  // so that we don't need to preface every cin and cout with std::

// Entire program is given inside of main(), which is acceptable since this is the first program.
int main() {

    // Display the menu and get the user choice
    int menuOption = 0;
    cout << "Program 1: Gladiolus            \n"
         << "Choose from among the following options:  \n"
         << "   1. Display original graphic  \n"
         << "   2. Display Gladiolus         \n"
         << "   3. Exit the program          \n"
         << "Your choice -> ";
    cin >> menuOption;
    
    // Handle menu option of 3 to exit
    if( menuOption == 3) {
        exit( 0);
    }
    // Handle menu option of 1 to display custom ASCII graphics
    else if( menuOption == 1) {
        // My own graphic.  You must create your own.
        cout << setw( 8) << " ";
        // Display a line across the top
        for( int i=0; i<42; i++) {
           cout << "-";
        }
        cout << endl;
        // Display ASCII graphics for "CS 141".  Yours must be different!
        cout << setw( 8) << " " << "   __     __     ________          _________             \n"
             << setw( 8) << " " << "  |  |   |  |    |__  __|         {   _____/  \n"
             << setw( 8) << " " << "  |  |   |  |      |  |    ^     {   {         \n"
             << setw( 8) << " " << "  |  |___|  |      |  |  < * >  {   {     ___  \n"
             << setw( 8) << " " << "  |         |    __|  |__  V     {   {___/  /     \n"
             << setw( 8) << " " << "  \\_________/   |________|       {_________/             \n"
             << endl;
        cout << setw( 8) << " ";
        // Display a line across the bottom
        for( int i=0; i<42; i++) {
            cout << "-";
        }
        cout << endl;
    } //end if( menuOption == 1)  // menu option to display custom graphic

    else if( menuOption == 2) {
        // Prompt for and get the number of flower sections.
        int numberOfSections = 0;
        cout << "Number of sections -> ";
        cin >> numberOfSections;
        
        // Place your code starting here
        // ...
	// variables I may or may not use 
	int numberOfSpaces;
        	
        int counter = 1;//number of parenthesees in each section
	int currentSection;//current section
	int currentRow;//current row
	char symbol = '@'; //symbol in the middle of each section
        if (numberOfSections > 0){
		cout<<setw( numberOfSections)<<" ";
		cout<<"---"<<endl;
	      for (int i = 0; i < numberOfSections; i++){//iterates through each section
		      numberOfSpaces = numberOfSections;
		      currentSection = i;
		      for (int j = 0;j < counter;j++){//iterates through each row in each section
			      currentRow = j;
			      if (currentSection < numberOfSections-1){
			     	 if (currentRow < (counter / 2 + 1)){//the middle and everything before that
				     	 numberOfSpaces--;
				     	 cout<<setw( numberOfSpaces)<<" ";
					 
			      }
			      	else if (currentRow > (counter / 2)){//after the middle

				     	 numberOfSpaces++;
				     	 cout<<setw( numberOfSpaces)<<" ";
			      }
			      
				      

			      
			     // cout<<"("<<endl;
		      }
			      else if(currentSection == numberOfSections-1){//when the loop is a the last section of the flower
				      if (currentRow < (counter / 2 + 1)){
					      numberOfSpaces--;
					      for (int s = 0; s< numberOfSpaces; s++){
						      cout<<" ";
					      }
				      }
				      else if(currentRow > (counter/2)){
					      numberOfSpaces++;
					      for (int t = 0; t<numberOfSpaces;t++){
						      cout<<" ";
					      }
				      }
			      }
			     
			      cout<<"(";
			      
			      if (currentRow == (counter/2)){//when you are in the middle row
				      cout << setw( currentSection +2);
				      cout<<symbol;//prints the @ symbol
				      cout<<setw( currentSection+2);
				      cout<<")";
			      }
			      else if(currentRow>(counter/2)){//after the middle row

				      cout<<setw( 2*(((counter-1)-currentRow)+2));

				      cout<<")";	      
			      }
			      else{
				      cout<<setw( 2*(currentRow+2));
				      cout<<")";
			      }
			      cout << endl;//new line
		      }//end iteration of rows

		      cout<< setw( numberOfSections)<<" "; 
		      cout << "---"<< endl;
		      counter+=2;

	      }//end iteration of sections

//Loop for the stem
	      for (int f = 1;f<numberOfSections+1;f++){
		      if (f%2 == 1){
			      cout<<setw( numberOfSections+1)<<" ";
			      cout<<"|/"<<endl;
			      cout<<setw( numberOfSections+1)<<" ";
			      cout<<"|"<<endl;
		      }
		      else{
			      cout<<setw( numberOfSections)<<" ";
			      cout<<"\\|"<<endl;
			      cout<<setw( numberOfSections+1)<<" ";
			      cout<<"|"<<endl;
		      }
	      }
	      


      }//end if( numberOfSections>0)

        
    } //end if( menuOption == 2) // menu option to display building
            
    cout << "Exiting" << endl;
    return 0;
}// end main()

