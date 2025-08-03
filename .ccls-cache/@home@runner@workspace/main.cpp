#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

const int NUM_QUESTIONS = 20;

void getAnswers(const string &filename, char answers[]);
int gradeExam(const char correct[], const char student[], int missed[], char incorrect[][2]);
void writeReport(int missed[], int numMissed, char incorrect[][2]);

int main() {
    char correct[NUM_QUESTIONS];
    char student[NUM_QUESTIONS];
    int missed[NUM_QUESTIONS];
    char incorrect[NUM_QUESTIONS][2]; // 0 = correct answer, 1 = student answer

    // Read files
    getAnswers("CorrectAnswers.txt", correct);
    getAnswers("StudentAnswers.txt", student);

    // Grade the exam
    int numMissed = gradeExam(correct, student, missed, incorrect);

    // Write the report
    writeReport(missed, numMissed, incorrect);

    return 0;
}

void getAnswers(const string &filename, char answers[]) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "Error: Could not open " << filename << endl;
        exit(1);
    }

    for (int i = 0; i < NUM_QUESTIONS; i++) {
        inFile >> answers[i];
    }
    inFile.close();
}

int gradeExam(const char correct[], const char student[], int missed[], char incorrect[][2]) {
    int numMissed = 0;

    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (student[i] != correct[i]) {
            missed[numMissed] = i + 1;  // store question number
            incorrect[numMissed][0] = correct[i]; // correct answer
            incorrect[numMissed][1] = student[i]; // student answer
            numMissed++;
        }
    }

    return numMissed;
}

void writeReport(int missed[], int numMissed, char incorrect[][2]) {
    int numCorrect = NUM_QUESTIONS - numMissed;
    double percentage = (static_cast<double>(numCorrect) / NUM_QUESTIONS) * 100;

    cout << "Total Questions Missed: " << numMissed << endl;
    cout << fixed << setprecision(2);
    cout << "Percentage Correct: " << percentage << "%" << endl;

    if (percentage >= 70.0)
        cout << "Result: PASS" << endl;
    else
        cout << "Result: FAIL" << endl;

    if (numMissed > 0) {
        cout << "\nQuestions Missed:\n";
        for (int i = 0; i < numMissed; i++) {
            cout << "Question " << missed[i] 
                 << " | Correct: " << incorrect[i][0] 
                 << " | Your Answer: " << incorrect[i][1] << endl;
        }
    }
}
