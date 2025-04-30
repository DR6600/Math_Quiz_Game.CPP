#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

enum enQuestionsLevel { Easy = 1, Medium = 2, Hard = 3, MixLevel = 4 };

enum enQuestionsType { Addition = 1, Subtraction = 2, Multiplication = 3, Division = 4, MixType = 5 };

struct stQuestion
{
	short Number1 = 0;
	short Number2 = 0;
	enQuestionsLevel QuestionLevel = Easy;
	enQuestionsType QuestionType = Addition;
	short Answer = 0;
	short PlayerAnswer = 0;
	bool IsCorrect = false;
};

struct stQuizzResults
{
	short NumberOfQuestions = 0;
	short NumberOfCorrectAnswers = 0;
	short NumberOfWrongAnswers = 0;
	enQuestionsLevel QuestionsLevel = Easy;
	enQuestionsType QuestionsType = Addition;
	short Percentage = 0;
	bool IsPassed = false;
};

string GetQuestionTypeSymbol(enQuestionsType& QuestionType)
{
	string QuestionTypeSymbols[4] = { "+","-", "*", "/" };
	return QuestionTypeSymbols[QuestionType - 1];
}

string GetQuestionTypeText(enQuestionsType& QuestionType)
{
	string QuestionTypeText[5] = { "Addition", "Subtraction", "Multiplication", "Division", "Mix" };
	return QuestionTypeText[QuestionType - 1];
}

string GetQuestionLevelText(enQuestionsLevel& QuestionLevel)
{
	string QuestionLevelText[4] = { "Easy", "Medium", "Hard", "Mix" };
	return QuestionLevelText[QuestionLevel - 1];
}

short RandomNumber(short From, short To)
{
	return rand() % (To - From + 1) + From;
}

short ReadNumber(short From, short To, string Message)
{
	short Number = 0;
	do
	{
		cout << Message;
		cin >> Number;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');
			cout << "That is not a Number, Enter a Number ";
			cin >> Number;
		}
	} while (Number < From || Number > To);
	return Number;
}

short TheCorrectAnswer(stQuestion& Question)
{
	switch (Question.QuestionType)
	{
	case Addition:
		return Question.Number1 + Question.Number2;
	case Subtraction:
		return Question.Number1 - Question.Number2;
	case Multiplication:
		return Question.Number1 * Question.Number2;
	case Division:
		return Question.Number1 / Question.Number2;
	default:
		return 0;
	}
}

void SetScreenColor(bool& IsPassed)
{
	if (IsPassed)
	{
		cout << "Your answer is correct\n\n";
		system("color 2F");
	}
	else
	{
		cout << "Your answer is wrong\n\n";
		system("color 4F");
	}
}

short GetPlayerAnswer(stQuestion& Question)
{
	cout << Question.Number1 << " " << GetQuestionTypeSymbol(Question.QuestionType) << " " << Question.Number2 << " = ? ";
	cin >> Question.PlayerAnswer;

	while (cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');
		cout << "That is not a Number, Enter a Number ";
		cin >> Question.PlayerAnswer;
	}
	return Question.PlayerAnswer;
}

short GenerateNumbers(enQuestionsLevel& QuestionsLevel)
{
	switch (QuestionsLevel)
	{
	case Easy:
		return RandomNumber(1, 10);
	case Medium:
		return RandomNumber(1, 50);
	default:
		return RandomNumber(1, 100);
	}
}

stQuestion FillQuestion(stQuestion& Question)
{
	Question.Number1 = GenerateNumbers(Question.QuestionLevel);
	Question.Number2 = GenerateNumbers(Question.QuestionLevel);
	Question.Answer = TheCorrectAnswer(Question);
	Question.PlayerAnswer = GetPlayerAnswer(Question);
	Question.IsCorrect = (Question.Answer == Question.PlayerAnswer);

	return Question;
}

void ResetScreen()
{
	system("cls");
	system("color 0f");
}

void PrintQuizzResults(stQuizzResults& QuizzResults)
{
	cout << "\n---------------------------------------------";
	cout << "\nFinal Results     :";
	cout << "\nQuestion Level    : " << GetQuestionLevelText(QuizzResults.QuestionsLevel);
	cout << "\nQuestion Type     : " << GetQuestionTypeText(QuizzResults.QuestionsType);
	cout << "\nTotal Questions   : " << QuizzResults.NumberOfQuestions;
	cout << "\nCorrect Answers   : " << QuizzResults.NumberOfCorrectAnswers;
	cout << "\nWrong Answers     : " << QuizzResults.NumberOfWrongAnswers;
	cout << "\nPercentage        : " << QuizzResults.Percentage << "%";
	cout << "\nYou have " << (QuizzResults.IsPassed ? "Passed" : "Failed") << " the quiz.";

	QuizzResults.IsPassed ? system("color 2F") : system("color 4F");

	cout << "\n---------------------------------------------\n";
}

void RunQuestions(stQuizzResults& QuizzResults, stQuestion& Question)
{

	for (short X = 1; X <= QuizzResults.NumberOfQuestions; X++)
	{
		Question.QuestionLevel = (Question.QuestionLevel == MixLevel) ? (enQuestionsLevel)RandomNumber(1, 3) : QuizzResults.QuestionsLevel;
		Question.QuestionType = (Question.QuestionType == MixType) ? (enQuestionsType)RandomNumber(1, 4) : QuizzResults.QuestionsType;

		FillQuestion(Question);

		SetScreenColor(Question.IsCorrect);
		
		(Question.IsCorrect) ? QuizzResults.NumberOfCorrectAnswers++ : QuizzResults.NumberOfWrongAnswers++;
	}
}

void PlayGame()
{
	stQuizzResults QuizzResults;
	stQuestion Question;

	QuizzResults.NumberOfQuestions = ReadNumber(1, 10, "\nHow many questions do you want to answer? (1 - 10): ");
	QuizzResults.QuestionsLevel = (enQuestionsLevel)ReadNumber(1, 4, "\nPlease choose the level of the questions (1\\Easy, 2\\Medium, 3\\Hard, 4\\Mix): ");
	QuizzResults.QuestionsType = (enQuestionsType)ReadNumber(1, 5, "\nPlease choose the type of the questions (1\\Addition, 2\\Subtraction, 3\\Multiplication, 4\\Division, 5\\Mix): ");

	Question.QuestionLevel = QuizzResults.QuestionsLevel;
	Question.QuestionType = QuizzResults.QuestionsType;

	RunQuestions(QuizzResults, Question);

	QuizzResults.Percentage = (QuizzResults.NumberOfCorrectAnswers * 100) / QuizzResults.NumberOfQuestions;
	QuizzResults.IsPassed = (QuizzResults.Percentage >= 60);

	PrintQuizzResults(QuizzResults);
}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ResetScreen();
		PlayGame();

		cout << "\nDo you want to play again? (Y/N): ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');

}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	system("pause>0");

	return 0;
}
