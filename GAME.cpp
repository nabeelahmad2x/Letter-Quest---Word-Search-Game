#include <iostream>
#include <fstream>
using namespace std;

//prototypes..
void read(char** arr, int, int); //read the board/grid for game..
int array_length(char[]);	//to find size of grid..
bool compare_array(char[], char[]); //compare searched word with dictionary..
bool compare(char[]); //compare the searched word
char** dynamic_mem(int row, int col); //creating grid in dyanamic memory..
void display_grid(char** grid, int row, int col);	//to display grid for game on console..
void pattern(char** grid, char* word, int R, int C, int& s);	//display the location of searched word..
bool search_word(char *grid, int row, int col, char word, int R, int C, int& er, int& ec); //search word in grid..
void game(char** grid, int row, int col); //word search game..
int maximum(int* arr, int size); //to find high score..

int main()
{
	char* arr = new char[100];
	int row = 0, col = 0;
	char** grid;

	ifstream fin1("board.txt");
	fin1.getline(arr, 100);

	col = array_length(arr);

	while (fin1)
	{
		fin1.getline(arr, 100);
		row++;

	}
	fin1.close();

	grid = dynamic_mem(row, col);

	read(grid, row, col);

	game(grid, row, col);

	cout << "Exiting Game.." << endl;
	return 0;
}


void display_grid(char** grid, int row, int col)
{

	for (int i = 0; i<row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << grid[i][j] << "  ";

		}
		cout << endl;
	}
}


void read(char** arr, int row, int col)
{
	ifstream fin;
	fin.open("board.txt");
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			fin >> arr[i][j];

		}

	}
	fin.close();
}


int array_length(char arr[])
{
	int c = 0;
	for (int i = 0; arr[i] != '\0'; i++)
		c++;
	return c;
}


bool compare_array(char arr1[], char arr2[])
{
	if (array_length(arr1) != array_length(arr2))
		return false;
	else
	{
		for (int i = 0; arr1[i] != '\0'; i++)
		{
			if (arr1[i] != arr2[i])
				return false;
		}
	}
	return true;
}


bool compare(char arr1[])
{
	char arr2[50];
	ifstream fin("dictionary.txt");
	while (!fin.eof())
	{
		fin >> arr2;
		if (compare_array(arr1, arr2))
			return true;
	}
	return false;
}


char** dynamic_mem(int row, int col)
{
	char** arr = new char*[row];
	for (int i = 0; i < row; i++)
	{
		arr[i] = new char[col];
	}
	return arr;
}

bool search_word(char **grid, int row, int col,	char* word, int R, int C, int& er, int& ec)
{

	int x[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
	int y[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

	if (grid[row][col] != word[0])
		return false;

	int len = array_length(word);

	for (int direction = 0; direction < 8; direction++)
	{
		int i;
		int rd = row + x[direction];
		int cd = col + y[direction];

		for (i = 1; i < len; i++)
		{
			if (rd >= R || rd < 0 || cd >= C || cd < 0)
				break;

			if (grid[rd][cd] != word[i])
				break;
			rd += x[direction];
			cd += y[direction];
		}

		if (i == len)
		{

			rd--;
			er = rd;
			ec = cd;
			return true;
		}
	}
	return false;
}


void pattern(char** grid, char* word, int row, int col, int& s)
{
	int er = 0, ec = 0;
	int count = 0;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (search_word(grid, i, j, word, row, col, er, ec))
			{
				s++;

				cout << "Word starts at " << i + 1 << " row , " << j + 1 << " coloum." << endl;
				cout << "Word ends at " << er + 1 << " row , " << ec + 1 << " coloum." << endl;
				cout << endl << endl;
			}
		}
	}
}


void game(char **grid, int row, int col)
{
	int count = 0, score = 0;
	int* h_score = new int(5);
	char i = 0;
	char user[20];
	char* word = new char(20);

	ofstream fout("high_score.txt");

	cout << " \t\t\t WELCOME TO WORD SEARCH " << endl << endl;

	cout << "Enter player name: ";	cin >> user;

	while (1)
	{
		pattern(grid, word, row, col, score);


		cout << "Press N for new game." << endl << "Press R to resume game." << endl << "Press P to pause game." << endl;
		cout <<	"Press L for level selection." << endl << "Press H for high score." << endl << "Press E to exit game." << endl;
		cout << "Input: "; cin >> i;

		if (i == 'e' || i == 'E')
			break;
		else if (i == 'r' || i == 'R')
		{
			display_grid(grid, row, col);
			cout << "Enter a word to search: ";	cin >> word;
		}
		else if (i == 'h' || i == 'H')
		{
			ifstream fin("high_score.txt");
			for (int j = 0; j < count; j++)
			{

				fin >> h_score[j];
			}
			fin.close();

			cout << "High score is " << maximum(h_score, count) << endl;
		}

		else if (i == 'n' || i == 'N')
		{
			system("cls");
			game(grid, row, col);
		}
		else if (i == 'p' || i == 'P')
		{
			ofstream fout("pause.txt");

			for (int k = 0; k<row; k++)
			{
				for (int j = 0; j < col; j++)
				{
					fout << grid[k][j];

				}
				cout << endl;
			}
			fout << score;
			fout.close();

			cout << "Enter r for resume e for exit: ";	cin >> i;
			if (i == 'e' || i == 'E')
				break;
		}
		else if (i == 'l' || i == 'L')
		{
			int c = 0;
			cout << "Enter 1 for Easy level." << endl;
			cout << "Enter 2 for medium level." << endl;
			cout << "Enter 3 for hard level." << endl;
			cout << "Input: "; cin >> c;
		}
		else
		{
			cout << "Invalid Input." << endl;
		}


		display_grid(grid, row, col);
		cout << "Enter a word to search: ";	cin >> word;
	}

	cout << "Your score was: " << score << endl;
	count++;
}

int maximum(int* arr, int size)
{
	int max = arr[0];
	for (int i = 0; i<size; i++)
	{
		if (max<arr[i])
		{
			max = arr[i];
		}
	}
	return max;
}

//WORD SEARCH PF PROJECT..
//MADE BY NABEEL AHMAD SHAFIQ..
//REG NO. L1F20BSCS0378
//BSCS SECTION A9(S21)