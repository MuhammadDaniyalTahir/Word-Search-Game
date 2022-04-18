#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class puzzle {
private:
	int startingIndex[2], endingIndex[2], rows, cols, noOfWords;
	char alphabet;
	char** array;
public:
	puzzle();
	void takeInfoFromFile();
	void setSizeOfArray();
	void takePuzzleFromFile();
	void displayThePuzzle();
	void takeInputThenCheck();
	bool searchWord(const char[]);
	int my_strlen(const char[]);
	bool searchUpToDown(const int, const int, const char[]);
	bool searchDownToUp(int, int, const char[]);
	bool searchLeftToRight(int, int, const char[]);
	bool searchRightToLeft(int, int, const char[]);
	bool searchTopLeftToBottomRight(int, int, const char[]);
	bool searchBottomRightToTopLeft(int, int, const char[]);
	bool searchTopRightToBottomLeft(int, int, const char[]);
	bool searchBottomLeftToTopRight(int, int, const char[]);
	~puzzle();
};
puzzle::puzzle() {
	for (int i = 0; i < 2; i++) {
		startingIndex[i] = endingIndex[i] = 0;
	}
	rows = cols = noOfWords = 0;
	array = 0, alphabet = 0;
}
void puzzle::takeInfoFromFile() {
	ifstream fin;
	fin.open("input.txt", ios::in);
	if (!fin)
		clog << "File is not opening for taking information\n", exit(1);
	fin >> rows >> cols >> noOfWords;
	fin.close();
}
void puzzle::setSizeOfArray() {
	array = new char* [rows];
	for (int i = 0; i < rows; i++)
		array[i] = new char[cols];
}
void puzzle::takePuzzleFromFile() {
	int skipIntegers = 0;
	ifstream fin;
	fin.open("input.txt", ios::in);
	fin >> skipIntegers >> skipIntegers >> skipIntegers;
	for (int i = 0; i < rows;i++){
		for (int j = 0; j < cols; j++) {
			fin >> alphabet;
			array[i][j] = alphabet;
		}
	}
	fin.close();
}
void puzzle::displayThePuzzle() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << array[i][j] << " ";
		}
		cout << endl;
	}
}
void puzzle::takeInputThenCheck() {
	ofstream fout;
	fout.open("Output.txt", ios::out);
	char word[20];
	bool find = false;
	for (int i = 0; i < noOfWords; i++) {
		cout << "Enter word you want to search in the puzzle: ";
		cin.getline(word, 19);
		if (searchWord(word)) {
			fout << "{" << startingIndex[0] << "," << startingIndex[1] << "}";
			fout << "{" << endingIndex[0] << "," << endingIndex[1] << "}";
			fout << endl;
			cout << "{" << startingIndex[0] << "," << startingIndex[1] << "}";
			cout << "{" << endingIndex[0] << "," << endingIndex[1] << "}";
			cout << endl;
		}
		else {
			fout << "Not found\n";
			cout << "Not found\n";
		}
	}
	fout.close();
}
bool puzzle::searchWord(const char word[]) {
	bool find = false;
	int size_word = my_strlen(word);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (array[i][j] == word[0] || array[i][j] == word[0]+32 || array[i][j] == word[0]-32) {
				if (searchUpToDown(i, j, word))
					return true;
			    if (searchDownToUp(i, j, word))
					return true;
				if (searchLeftToRight(i, j, word))
					return true;
				if (searchRightToLeft(i, j, word))
					return true;
				if (searchTopLeftToBottomRight(i, j, word))
					return true;
				if (searchBottomRightToTopLeft(i, j, word))
					return true;
				if (searchTopRightToBottomLeft(i, j, word))
					return true;
				if (searchBottomLeftToTopRight(i, j, word))
					return true;
			}
		}
	}
	return false;
}
bool puzzle::searchUpToDown(const int i, const int j,const char word[]) {
	int index = 1;
	int row = i+1;
	if (!(row < rows))
		return false;
	while (word[index] != '\0' && row < rows) {
		if (array[row][j] != word[index])
			return false;
		index++;
		row++;
	}
	startingIndex[0] = i;startingIndex[1] = j;
	endingIndex[0] = row-1;endingIndex[1] = j;
	return true;
}
bool puzzle::searchDownToUp(const int i, const int j, const char word[]) {
	int index = 1;
	int row = i - 1;
	if (!(row >= 0))
		return false;
	while (word[index] != '\0' && row >= 0) {
		if (array[row][j] != word[index])
			return false;
		index++;
		row--;
	}
	startingIndex[0] = i; startingIndex[1] = j;
	endingIndex[0] = row + 1; endingIndex[1] = j;
	return true;
}
bool puzzle::searchLeftToRight(const int i, const int j,const char word[]) {
	int index = 1;
	int col = j+1;
	if (!(col < cols))
		return false;
	while (word[index] != '\0' && col < cols) {
		if (array[i][col] != word[index])
			return false;
		index++;
		col++;
	}
	startingIndex[0] = i; startingIndex[1] = j;
	endingIndex[0] = i; endingIndex[1] = col - 1;
	return true;
}
bool puzzle::searchRightToLeft(const int i, const int j,const char word[]) {
	int index = 1;
	int col = j-1;
	if (!(col >= 0))
		return false;
	while (word[index] != '\0' && col >= 0) {
		if (array[i][col] >= 65 && array[i][col] <= 90) {
			if (array[i][col] != word[index] && array[i][col] != word[index]+32)
				return false;
			index++;
			col--;
		}
		else {
			if (array[i][col] != word[index] && array[i][col] != word[index] - 32)
				return false;
			index++;
			col--;
		}
	}
	startingIndex[0] = i; startingIndex[1] = j;
	endingIndex[0] = i; endingIndex[1] = col + 1;
	return true;
}
bool puzzle::searchTopLeftToBottomRight(const int i, const int j,const char word[]) {
	int index = 1;
	int row = i + 1;
	int col = j + 1;
	if (!(col < cols) || !(row < rows))
		return false;
	while (word[index] != '\0' && col < cols && row < rows) {
		if (array[row][col] != word[index])
			return false;
		index++;
		col++;
		row++;
	}
	startingIndex[0] = i; startingIndex[1] = j;
	endingIndex[0] = row - 1; endingIndex[1] = col - 1;
	return true;
}
bool puzzle::searchBottomRightToTopLeft(const int i, const int j,const char word[]) {
	int index = 1;
	int row = i - 1;
	int col = j - 1;
	if (!(col >= 0) || !(row >= 0))
		return false;
	while (word[index] != '\0' && col >= 0 && row >= 0) {
		if (array[row][col] != word[index])
			return false;
		index++;
		col--;
		row--;
	}
	startingIndex[0] = i; startingIndex[1] = j;
	endingIndex[0] = row + 1; endingIndex[1] = col + 1;
	return true;
}
bool puzzle::searchTopRightToBottomLeft(const int i, const int j,const char word[]) {
	int index = 1;
	int row = i + 1;
	int col = j - 1;
	if (!(col >= 0) || !(row < rows))
		return false;
	while (word[index] != '\0' && col >= 0 && row < rows) {
		if (array[row][col] != word[index])
			return false;
		index++;
		col--;
		row++;
	}
	startingIndex[0] = i; startingIndex[1] = j;
	endingIndex[0] = row - 1; endingIndex[1] = col + 1;
	return true;
}
bool puzzle::searchBottomLeftToTopRight(const int i, const int j,const char word[]) {
	int index = 1;
	int row = i - 1;
	int col = j + 1;
	if (!(col < cols) || !(row >= 0))
		return false;
	while (word[index] != '\0' && col < cols && row >= 0) {
		if (array[row][col] != word[index])
			return false;
		index++;
		col++;
		row--;
	}
	startingIndex[0] = i; startingIndex[1] = j;
	endingIndex[0] = row + 1; endingIndex[1] = col - 1;
	return true;
}
int puzzle::my_strlen(const char word[]) {
	int count = 0;
	for (int i = 0; word[i] != '\0'; i++)
		count++;
	return count;
}
puzzle::~puzzle() {
	for (int i = 0; i < rows; i++)
		delete[]array[i];
	delete[]array;
}
int main() {
	puzzle obj;
	obj.takeInfoFromFile();
	obj.setSizeOfArray();
	obj.takePuzzleFromFile();
	obj.displayThePuzzle();
	obj.takeInputThenCheck();

	return 0;
}