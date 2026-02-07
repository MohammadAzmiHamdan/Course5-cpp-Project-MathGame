
#include <iostream>
#include <ctime>
#include<cstdlib>
using namespace std;
enum enQuestionLevel{EasyLevel=1,MidLevel=2,HardLevel=3,Mix=4};
enum enOperationType{Add=1,Sub=2,Mult=3,Div=4,MixOp=5};
struct stQuestion {
	int Number1 = 0;
	int Number2 = 0;
	enOperationType OperationType;
	enQuestionLevel QuestionLevel;
	int CorrectAnswer = 0;
	int PlayerAnswer = 0;
	bool AnswerResult = false;
};
struct stQuizz {
	stQuestion QuestionsList[100];
	short NumberOfQuestions = 0;
	enOperationType OperationType;
	enQuestionLevel QuestionsLevel;
	short NumberOfRightAnswer = 0;
	short NumberOfWrongAnswer = 0;
	bool isPass = false;


};
int ReadHowManyQuestions() {
	short questionNumber = 0;
	do {
		cout << "How Many Questions Do you want to answer ?";
		cin >> questionNumber;
	} while (questionNumber < 1 || questionNumber>10);
	return questionNumber;
}
enQuestionLevel ReadQuestionslevel() {
	short QuestionLevelNumberKey = 0;
	do {
		cout << "Enter Questions level : Easy[1], Mid[2], Hard[3], Mix[4] ";
		cin >> QuestionLevelNumberKey ;

	} while (QuestionLevelNumberKey  < 1 || QuestionLevelNumberKey > 4);
	return (enQuestionLevel)QuestionLevelNumberKey ;
}
enOperationType ReadOpType() {

	short opTypeNumberKey = 0;
	do {
		cout << "Enter operation Type : Add[1], Sub[2], Mult[3], Div[4], Mix[5] ";
		cin >> opTypeNumberKey;

	} while (opTypeNumberKey < 1 || opTypeNumberKey > 5);
	return (enOperationType)opTypeNumberKey;

}
int ReadQuestionAnswer() {
	int num = 0;
	cin >> num;
	return num;
}
string GetOpTypeSymbol(enOperationType OpType) {
	switch (OpType) {
	case enOperationType::Add:
		return "+";
	case enOperationType::Sub:
		return "-";
	case enOperationType::Mult:
		return "x";
	case enOperationType::Div:
		return "/";
	default:
		return "Mix";

	}
}
void PrintQuestion(stQuizz &Quizz, short QuestionNumber) {
	
	
	cout << "\nQuestion [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]\n";
	cout << Quizz.QuestionsList[QuestionNumber].Number1 << " "
		<< GetOpTypeSymbol(Quizz.QuestionsList[QuestionNumber].OperationType) << " "
		<< Quizz.QuestionsList[QuestionNumber].Number2 << " = ";

}
int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}
string GetQuestionLevelText(enQuestionLevel QuestionLevel) {
	string arrQuestionLevelText[4] = { "Easy","Mid","Hard","Mix" };
	return arrQuestionLevelText[QuestionLevel - 1];
}
enOperationType GetRandomOpType() {
	return (enOperationType)RandomNumber(1, 4);
}
void SetScreenColor(bool Right) {
	if (Right)
		system("color 2F");
	else {
		system("color 4f");
		cout << "\a";
	}


}
void RestTheScreen() {
	system("cls");
	system("color 07");
}
int SimpleCalculator(int Number1, int Number2, enOperationType OpType) {
	switch (OpType) {
	case enOperationType::Add:
		return Number1 + Number2;
	case enOperationType::Sub:
		return Number1 - Number2;
	case  enOperationType::Mult:
		return Number1 * Number2;
	case enOperationType::Div:
		return (Number2 != 0) ? (Number1 / Number2) : 0;

	default :return Number1 + Number2;


	}




}
stQuestion GenerateQuestion(enQuestionLevel Questionlevel, enOperationType OpType)
{
	stQuestion Question;
	if (Questionlevel == enQuestionLevel::Mix)
		Questionlevel = (enQuestionLevel)RandomNumber(1, 3);

	if (OpType == enOperationType::MixOp)
		OpType = GetRandomOpType();
	Question.OperationType = OpType;
	switch (Questionlevel) {
	case enQuestionLevel::EasyLevel:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);
		break;
	case enQuestionLevel::MidLevel:
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);
		break;
	case enQuestionLevel::HardLevel:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);
		break;
	}
	Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
	Question.QuestionLevel = Questionlevel;
	return Question;
}
void GenerateQuizzQuestions(stQuizz& Quizz) {
	for (short QuestionNumber = 0;QuestionNumber < Quizz.NumberOfQuestions;QuestionNumber++) 
	{
		Quizz.QuestionsList[QuestionNumber] = GenerateQuestion(Quizz.QuestionsLevel,Quizz.OperationType);
	}
}
void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber) {

	if (Quizz.QuestionsList[QuestionNumber].CorrectAnswer == Quizz.QuestionsList[QuestionNumber].PlayerAnswer) {
		Quizz.QuestionsList[QuestionNumber].AnswerResult = true;
		cout << "Correct!\n";
		SetScreenColor(Quizz.QuestionsList[QuestionNumber].AnswerResult);
		Quizz.NumberOfRightAnswer++;
	}
	else {
		Quizz.QuestionsList[QuestionNumber].AnswerResult = false;
		cout << "Wrong! Correct Answer :" << Quizz.QuestionsList[QuestionNumber].CorrectAnswer << endl;
		SetScreenColor(Quizz.QuestionsList[QuestionNumber].AnswerResult);
		Quizz.NumberOfWrongAnswer++;
	}




}
void AskAndCorrectQuestionListAnswer(stQuizz& Quizz) {

	for (short QuestionNumber = 0;QuestionNumber < Quizz.NumberOfQuestions;QuestionNumber++) {

		PrintQuestion(Quizz, QuestionNumber);
		Quizz.QuestionsList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();
		CorrectTheQuestionAnswer(Quizz, QuestionNumber);



	}


	Quizz.isPass = (Quizz.NumberOfRightAnswer >= Quizz.NumberOfWrongAnswer);



}
string GetFinalResult(bool Pass) {
	if (Pass) {
		SetScreenColor(Pass);
		return "Pass!";
		
	}
	else {
		SetScreenColor(Pass);
		return "Failed!";

	}

}
void PrintQuizzResult(stQuizz &Quizz) {
	cout << "\n";
	cout << "_______________________________\n\n";
	cout << "the Final Result is " << GetFinalResult(Quizz.isPass)<<endl ;
	cout << "_______________________________\n\n";


	cout << "The Number of Question     :" << Quizz.NumberOfQuestions << endl;
	cout << "Questions Level            :" << GetQuestionLevelText(Quizz.QuestionsLevel) << endl;
	cout << " OpType                    :" << GetOpTypeSymbol(Quizz.OperationType)<< endl;
	cout << "The Number of Right Answer :" << Quizz.NumberOfRightAnswer << endl;
	cout << "The Number of Wrong Answer :" << Quizz.NumberOfWrongAnswer << endl;
	cout << "_______________________________\n";


}
void PlayMathGame(){
	stQuizz Quizz;
	Quizz.NumberOfQuestions = ReadHowManyQuestions();
	Quizz.QuestionsLevel = ReadQuestionslevel();
	Quizz.OperationType = ReadOpType();

	GenerateQuizzQuestions(Quizz);
	AskAndCorrectQuestionListAnswer(Quizz);
	PrintQuizzResult(Quizz);


}
void StartGame() {
	char PlayAgain = 'y';
	do {

		RestTheScreen();
		PlayMathGame();
		cout << "Do you want to play again? Y/N?";
		cin >> PlayAgain;

	} while (PlayAgain == 'y' || PlayAgain == 'Y');



}
int main() {
	srand((unsigned)time(NULL));
	StartGame();
	return 0;
}