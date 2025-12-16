/*
File name: CH7P1.cpp
Github URL: https://github.com/clk2039/CH7P1.git
Programmer: Kit Miller
Date: December 2025
Requirements: Write a modular, procedural program that reads the contents of the CorrectAnswers.txt file into a char array,
then reads the contents of file StudentAnswers.txt into a second char array. The program should determine the number of
questions that the student missed, then diplay the following:
- A list of the questions missed by the student, showing the correct answer and the incorrect answer provided by the student for each missed question.
- The total number of questions missed.
- The percentage of questions answered correctly, calculated by dividing the total number of questions by the correctly answered questions.
- If the percentage of correctly answered questions is 70% or greater, the program should indicate that the student passed the exam.
Otherwise, it should indicate that the student failed the exam.
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

const int NUM_QUESTIONS = 20;

//Function prototypes

void getAnswers(const string& fileName, char answers[], int size);
int gradeExam(const char key[], const char student[], int missedQuestions[], char answerPairs[][2], int size);
void writeReport(const int missedQuestions[], int missedCount, const char answerPairs[][2], int totalQuestions);

int main()
{

	//Stores the correct exam answers
	char correctAnswers[NUM_QUESTIONS];

	//Stores the student's exam answers
	char studentAnswers[NUM_QUESTIONS];

	//Stores the numbers of the questions missed
	int missedQuestions[NUM_QUESTIONS];

	//Stores the pairs of correct and incorrect answers
	char answerPairs[NUM_QUESTIONS][2];

	//Get the answer key from the file
	getAnswers("CorrectAnswers.txt", correctAnswers, NUM_QUESTIONS);

	//Get the student's answers from the file
	getAnswers("StudentAnswers.txt", studentAnswers, NUM_QUESTIONS);

	//Calculate the grade and get the missed questions
	int missedCount = gradeExam(correctAnswers, studentAnswers, missedQuestions, answerPairs, NUM_QUESTIONS);

	//Write the exam report
	writeReport(missedQuestions, missedCount, answerPairs, NUM_QUESTIONS);

	return 0;

}

/*
Function: getAnswers
Purpose: Reads answers from a file into an array
Parameters: fileName - name of the file to read from
			answers - array to store the answers
			size - number of answers to read
Returns: void
Preconditions: The file exists and is accessible
Postconditions: The answers are stored in the provided array
*/
void getAnswers(const string& fileName, char answers[], int size)
{
	ifstream inputFile(fileName);
	if (!inputFile)
	{
		cout << "Error opening file: " << fileName << endl;
		exit(1);
	}

	//Read answers from the file into the array
	for (int questionIndex = 0; questionIndex < size; questionIndex++)
	{
		if (!(inputFile >> answers[questionIndex]))
		{
			cout << "Error reading answer for question " << (questionIndex + 1) << endl;
			exit(1);
		}
	}
	inputFile.close();
}

/*
Function: gradeExam
Purpose: Compares the answer key to the student's answers and identifies which were answered incorrectly
Parameters: key - array of correct answers
			student - array of student's answers
			missedQuestions - array to store the numbers of missed questions
			answerPairs - 2D array to store pairs of correct and incorrect answers
			size - number of questions
Returns: int - number of questions missed
Preconditions: key[] and student[] have valid answers
Postconditions: missedQuestions[] and answerPairs[][] have valid data about missed questions
*/
int gradeExam(const char key[], const char student[], int missedQuestions[], char answerPairs[][2], int size)
{
	int missedCount = 0;

	//Compare each answer
	for (int questionIndex = 0; questionIndex < size; questionIndex++)
	{
		if (student[questionIndex] != key[questionIndex])
		{
			//Record the missed question number (1-based index)
			missedQuestions[missedCount] = questionIndex + 1;

			//Record the correct and incorrect answers
			answerPairs[missedCount][0] = key[questionIndex];
			answerPairs[missedCount][1] = student[questionIndex];
			missedCount++;
		}
	}
	return missedCount;
}

/*
Function: writeReport
Purpose: Calculates the final score and shows the missed questions and if the student passed or failed
Parameters: missedQuestions - array of missed question numbers
			missedCount - number of questions missed
			answerPairs - 2D array of correct and incorrect answers
			totalQuestions - total number of questions on the exam
Returns: void
Preconditions: missedQuestions[] and answerPairs[][] have valid data
Postconditions: The exam report is displayed for the user
*/

void writeReport(const int missedQuestions[], int missedCount, const char answerPairs[][2], int totalQuestions)
{
	//Calculate the number of correct answers
	int correctCount = totalQuestions - missedCount;

	//Calculate the percentage of correct answers
	double percentageCorrect = (static_cast<double>(correctCount) / totalQuestions) * 100.0;

	//Display the missed questions
	if (missedCount > 0)
	{
		cout << "Questions missed:" << endl;
		for (int missIndex = 0; missIndex < missedCount; missIndex++)
		{
			cout << "Question " << missedQuestions[missIndex] << ": Correct Answer = " << answerPairs[missIndex][0]
				<< ", Student's Answer = " << answerPairs[missIndex][1] << endl;
		}
	}
	else
	{
		cout << "No questions were missed." << endl;
	}

	//Display the total number of questions missed
	cout << "Total questions missed: " << missedCount << endl;

	//Display the percentage of correct answers
	cout << fixed << setprecision(2);
	cout << "Final Grade: " << percentageCorrect << "%" << endl;

	//Determine if the student passed or failed
	if (percentageCorrect >= 70.0)
	{
		cout << "The student passed the exam." << endl;
	}
	else
	{
		cout << "The student failed the exam." << endl;
	}

}

