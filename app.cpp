#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

const int arraySize = 20;

struct studentRecord{
	string studentLastName;
    string studentFirstName;
    int numericGrade;
    char letterGrade;
};

studentRecord studentRecords[arraySize]; // set array variable of studentRecord struct

void getAndStoreData() {
    // read in the student data from a file
    ifstream  ifs("Ch9_Ex2Data.txt");
    string studentLastName;
    string studentFirstName;
    int numericGrade;

    if(ifs.fail()) {
        cout << "Error opening student data file: (Ch9_Ex2Data.txt)" << endl;
        exit(1);
    }

	int i = 0;
	while(! ifs.eof()){
     	ifs >> studentLastName >> studentFirstName >> numericGrade;
		studentRecords[i].studentLastName = studentLastName;
		studentRecords[i].studentFirstName = studentFirstName;
		studentRecords[i].numericGrade = numericGrade;
		i++;
	}
}

void calculateLetterGrade() {
    char grade;
    int count = 0;

    while (count < arraySize){
        if(studentRecords[count].numericGrade > 90) {
            studentRecords[count].letterGrade = 'A';
        }
        else if(studentRecords[count].numericGrade > 80){
            studentRecords[count].letterGrade = 'B';
        }
        else if(studentRecords[count].numericGrade > 70) {
            studentRecords[count].letterGrade =  'C';
        }
        else if(studentRecords[count].numericGrade > 60) {
            studentRecords[count].letterGrade =  'D';
        }
        else studentRecords[count].letterGrade =  'F';
        count++;
    }
}

int determineHighestScore() {
    int largest = 0;
    int count = 0;

    while (count < arraySize){
        if (largest < studentRecords[count].numericGrade)
            largest = studentRecords[count].numericGrade;
        count++;
    }

    return largest;
}

void printResults() {

    int count = 0;
    int largest = determineHighestScore(); // Pull in largest numeric grade score

    // Output the labels for the data with formatting
    cout
    << left
    << setw(30)
    << "Student Name"
    << setw(20)
    << "Test Score"
    << setw(9)
    << "Grade"
    << endl;

    // Loop through studentRecord data and display/format results
    for(int j = 0; j < arraySize; j++){
		cout
		<< left
		<< setw(30)
		<< studentRecords[j].studentLastName + ", " + studentRecords[j].studentFirstName
		<< setw(20)
		<< studentRecords[j].numericGrade
		<< setw(30)
		<< studentRecords[j].letterGrade
		<< endl;
	}

    cout << endl << "Highest Test Score: " << largest << endl; // Output label and highest numeric grade score
    cout << endl << "Students having the highest test score: " << endl; // Output label and highest numeric grade score

    while (count < arraySize){
        if (studentRecords[count].numericGrade == largest)
            cout << studentRecords[count].studentFirstName << ", " << studentRecords[count].studentLastName << endl;
        count++;
    }
}

int main()
{
    getAndStoreData();
    calculateLetterGrade();
    determineHighestScore();
    printResults(); // Output data to screen

    // Output data to file
    if(std::freopen("output.txt", "w", stdout)) {
        printResults();
        std::fclose(stdout);
    }

    return 0;
}
