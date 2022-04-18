#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

class grid {
private:
	char** arr; //Array to make grid.
	int size;
	int totalWords;
	string word;
	int* sizeOfEachWord;  //Pointer to array having size of each word.
public:
	
	grid();
	void CheckSizeOfGrid();
	void MakeGrid();
	void initializeGridWithZero();
	void set_sizeof_sizeOfEachWord();
	void PutElementsToGrid();
	bool putElementIfAnyLetterisinGrid(int, int, int, string);
	int decideOrderOfWord();
	bool upToBottom(string);
	bool bottomToUp(string);
	bool leftToRight(string);
	bool rightToLeft(string);
	bool topLeftToBottomRight(string);
	bool bottomRightToTopLeft(string);
	bool topRightToBottomLeft(string);
	bool bottomLeftToTopRight(string);
	void fillEmptyPlaces();
	void randomAlpha_ToFillEmptySpaces(int, int);
	void printGridInFile();
	void printGrid();
	~grid();
};
grid::grid() {
	arr = 0;
	size = 0;
	sizeOfEachWord = 0;
	totalWords = 0;
}
void grid::CheckSizeOfGrid() {
	ifstream fin;
	int calSize = 0, maxSize = 0, index = 0;
	fin.open("grid.txt");
	if (!fin)
		clog << "File named grid is not opened for taking size of grid\n";
	while (getline(fin, word)) {
		calSize = 0;
		for (int i = 0; word[i] != '\0'; i++) {//loop to check the size of every word.
			if (word[i] == 32)
				continue;
			else
				calSize++;
		}
		sizeOfEachWord[index++] = calSize;
		if (calSize > maxSize)
			maxSize = calSize;
	}
	if (totalWords > maxSize) {
		if (maxSize + 3 <= totalWords)
			size = totalWords+3;
		else
			size = totalWords;
	}
	else if (totalWords <= maxSize) {
		if (totalWords + 3 == maxSize)
			size = maxSize + 3;
		else
			size = maxSize;
	}
	else
		size = maxSize + 3;
	/*if (totalWords > maxSize)
		size = totalWords;
	else
		size = maxSize;*/
	fin.close();
	cout << size << endl;
}
void grid::MakeGrid() {
	arr = new char*[size];
	for (int i = 0; i < size; i++)
		arr[i] = new char[size];
}
void grid::initializeGridWithZero() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			arr[i][j] = '0';
		}
	}
}
void grid::PutElementsToGrid() {
	ifstream fin;
	int order = 0;
	bool wordInserted = false, stop = false;
	fin.open("grid.txt");
	while (getline(fin, word)) {
		cout << "Word taken from file " << word << endl;
		stop = false;
		wordInserted = false;
		for (int i = 0; i < size && !wordInserted ; i++) {
			for (int j = 0; j < size && !wordInserted; j++) {
				for (int k = 0; word[k] != '\0' && !wordInserted; k++) {
					if (arr[i][j] == word[k] && word[k] != 32 && !wordInserted) {
						wordInserted = putElementIfAnyLetterisinGrid(i, j, k, word);
						if (wordInserted) {
							cout << "Word match and inserted successively\n";
							printGrid();
						}
					}
				}
			}
		}
		if (wordInserted) {
			continue;
		}
		while (!stop) {
			order = decideOrderOfWord();
			switch (order) {
			case 1:
				stop = upToBottom(word);
				if (stop) {
					printGrid();
					break;
				}
			case 2:
				stop = bottomToUp(word);
				if (stop) {
					printGrid();
					break;
				}
			case 3:
				stop = leftToRight(word);
				if (stop) {
					printGrid();
					break;
				}
			case 4:
				stop = rightToLeft(word);
				if (stop) {
					printGrid();
					break;
				}
			case 5:
				stop = topLeftToBottomRight(word);
				if (stop) {
					printGrid();
					break;
				}
			case 6:
				stop = bottomRightToTopLeft(word);
				if (stop) {
					printGrid();
					break;
				}
			case 7:
				stop = topRightToBottomLeft(word);
				if (stop) {
					printGrid();
					break;
				}
			case 8:
				stop = bottomLeftToTopRight(word);
				if (stop) {
					printGrid();
					break;
				}
			default:
				cout << "This word can not been placed anywhere in the grid\n";
			}
		}
	}
	fin.close();
	fillEmptyPlaces();
	printGrid();
}
bool grid::putElementIfAnyLetterisinGrid(int i, int j, int indexFind, string word) {
	int calPreSpaces = 0, calPostSpaces = 0;
	int pre_spaces = 0, post_spaces = 0;
	//from left to right.
	for (int k = indexFind - 1; k >= 0; k--) {
		pre_spaces++;
	}
	for (int k = indexFind + 1; word[k] != '\0'; k++) {
		post_spaces++;
	}
	for (int k = j - 1; k >= 0 && arr[i][k] == '0'; k--) {
		calPreSpaces++;
	}
	for (int k = j + 1; k < size && arr[i][k] == '0'; k++) {
		calPostSpaces++;
	}
	if (calPreSpaces >= pre_spaces && calPostSpaces >= post_spaces) {
		for (int col = j - 1, index = indexFind - 1; index >= 0; col--, index--) {
			if (word[index] == 32) {
				col++;
				continue;
			}
			arr[i][col] = word[index];
		}
		for (int col = j + 1, index = indexFind + 1; word[index] != '\0'; col++, index++) {
			if (word[index] == 32) {
				col--;
				continue;
			}
			arr[i][col] = word[index];
		}
		return true;
	}
	//right to left				
	if (calPreSpaces >= post_spaces && calPostSpaces >= pre_spaces) {
		for (int col = j - 1, index = indexFind + 1; word[index] != '\0' && col >= 0; col--, index++) {
			if (word[index] == 32) {
				col++;
				continue;
			}
			arr[i][col] = word[index];
		}
		for (int col = j + 1, index = indexFind - 1; index >= 0; col++, index--) {
			if (word[index] == 32) {
				col--;
				continue;
			}
			arr[i][col] = word[index];
		}
		return true;
	}
	//up to bottom.
	calPreSpaces = 0;
	calPostSpaces = 0;
	for (int k = i - 1; k >= 0 && arr[k][j] == '0'; k--) {
		calPreSpaces++; //Checking spaces up that index.
	}
	for(int k = i + 1;k < size && arr[k][j] == '0';k++){
		calPostSpaces++;     //Checking spaces down that index.
	}
	if (calPreSpaces >= pre_spaces && calPostSpaces >= post_spaces) {
		for (int row = i - 1, index = indexFind - 1; index >= 0; index--, row--) {
			if (word[index] == 32) {
				row++;
				continue;
			}
			arr[row][j] = word[index];
		}
		for (int row = i + 1, index = indexFind + 1; word[index] != '\0'; index++, row++) {
			if (word[index] == 32) {
				row--;
				continue;
			}
			arr[row][j] = word[index];
		}
		return true;
	}
	//bottom to up
	if (calPreSpaces >= post_spaces && calPostSpaces >= pre_spaces) {
		for (int row = i - 1, index = indexFind+1; word[index] != '\0'; row--, index++) {
			if (word[index] == 32) {
				row++;
				continue;
			}
			arr[row][j] = word[index];
		}
		for (int row = i + 1, index = indexFind - 1; index >= 0; index--, row++) {
			if (word[index] == 32) {
				row--;
				continue;
			}
			arr[row][j] = word[index];
		}
		return true;
	}
	calPreSpaces = 0;
	calPostSpaces = 0;
	//top left to bottom right.
	for (int row = i - 1, col = j - 1; row >= 0 && col >= 0 && arr[row][col] == '0'; row--, col--) {
		calPreSpaces++;
	}
	for (int row = i + 1, col = j + 1; row < size && col < size && arr[row][col] == '0'; row++, col++) {
		calPostSpaces++;
	}
	if (calPreSpaces >= pre_spaces && calPostSpaces >= post_spaces) {
		for (int row = i - 1, col = j - 1, index = indexFind - 1; index >= 0; index--, row--, col--) {
			if (word[index] == 32) {
				row++;
				col++;
				continue;
			}
			arr[row][col] = word[index];
		}
		for (int row = i + 1, col = j + 1, index = indexFind + 1; word[index] != '\0'; index++, row++, col++) {
			if (word[index] == 32) {
				row--;
				col--;
				continue;
			}
			arr[row][col] = word[index];
		}
		return true;
	}
	//bottom right to top left.
	if (calPreSpaces >= post_spaces && calPostSpaces >= pre_spaces) {
		for (int row = i - 1, col = j - 1, index = indexFind + 1; word[index] != '\0'; index++, row--, col--) {
			if (word[index] == 32) {
				row++;
				col++;
				continue;
			}
			arr[row][col] = word[index];
		}
		for (int row = i + 1, col = j + 1, index = indexFind - 1; index >= 0; index--, col++, row++) {
			if (word[index] == 32) {
				row--;
				col--;
				continue;
			}
			arr[row][col] = word[index];
		}
		return true;
	}
	calPreSpaces = 0;
	calPostSpaces = 0;
	//top right to bottom left.
	for (int row = i - 1, col = j + 1; row >= 0 && col < size && arr[row][col] == '0'; row--, col++) {
		calPreSpaces++;
	}
	for (int row = i + 1, col = j - 1; row < size && col >= 0 && arr[row][col] == '0'; row++, col--) {
		calPostSpaces++;
	}
	if (calPreSpaces >= pre_spaces && calPostSpaces >= post_spaces) {
		for (int row = i - 1, col = j + 1, index = indexFind - 1; index >= 0; index--, row--, col++) {
			if (word[index] == 32) {
				row++;
				col--;
				continue;
			}
			arr[row][col] = word[index];
		}
		for (int row = i + 1, col = j - 1, index = indexFind + 1; word[index] != '\0'; index++, row++, col--) {
			if (word[index] == 32) {
				row--;
				col++;
				continue;
			}
			arr[row][col] = word[index];
		}
		return true;
	}
	//bottom left to top right.
	if (calPreSpaces >= post_spaces && calPostSpaces >= pre_spaces) {
		for (int row = i - 1, col = j + 1, index = indexFind + 1; word[index] != '\0'; index++, row--, col++) {
			if (word[index] == 32) {
				row++;
				col--;
				continue;
			}
			arr[row][col] = word[index];
		}
		for (int row = i + 1, col = j - 1, index = indexFind - 1; index >= 0; index--, col--, row++) {
			if (word[index] == 32) {
				row--;
				col++;
				continue;
			}
			arr[row][col] = word[index];
		}
		return true;
	}
	return false;
}
void grid::set_sizeof_sizeOfEachWord() {
	ifstream fin;
	fin.open("grid.txt");
	if(!fin)
		clog << "File named grid is not opened for taking size of grid\n";
	while (getline(fin, word)) {
		totalWords++;
	}
	sizeOfEachWord = new int[totalWords];
	fin.close();
}
int grid::decideOrderOfWord() {
	int num;
	num = (rand() % 8) + 1;	
	cout << "Random number generated is " << num << endl;
	return num;
}
bool grid::upToBottom(string word) {
	int wordLength = word.length();
	int calSpaces = 0, start_coloumn_index = 0;
	bool find = false;
	for (int j = 0; j < size; j++) {
		int k = 0;
		if (arr[k][j] == '0') {
			k = 0;
			while (k < size && arr[k][j] == '0') {
				calSpaces = 0;
				start_coloumn_index = k;
				while (k < size && arr[k][j] == '0') {
					calSpaces++;
					if (calSpaces == wordLength) {
						find = true;
						break;
					}
					k++;
				}
				if (find)
					break;
				k++;
			}
			if (calSpaces >= wordLength) {
				for (int l = start_coloumn_index, index = 0; index <= wordLength - 1; l++, index++) {
					if (word[index] == 32) {
						l--;
						continue;
					}
					arr[l][j] = word[index];
				}
				return true;
			}
		}
	}
	return false;
}
bool grid::bottomToUp(string word) {
	int wordLength = word.length();
	int calSpaces = 0, start_coloumn_index = 0;
	bool find = false;
	for (int j = 0; j < size; j++) {
		int k = size - 1;
		if (k >= 0 && arr[k][j] == '0') {
			k = size - 1;
			while (k >= 0 && arr[k][j] == '0') {
				calSpaces = 0;
				start_coloumn_index = k;
				while (k >= 0 && arr[k][j] == '0') {
					calSpaces++;
					if (calSpaces == wordLength) {
						find = true;
						break;
					}
					k--;
				}
				if (find)
					break;
				k--;
			}
			if (calSpaces >= wordLength) {
				for (int l = start_coloumn_index, index = 0; index <= wordLength - 1; l--, index++) {
					if (word[index] == 32) {
						l++;
						continue;
					}
					arr[l][j] = word[index];
				}
				return true;
			}
		}
	}
	return false;
}
bool grid::leftToRight(string word) {
	int wordLength = word.length();
	int calSpaces = 0, start_coloumn_index = 0;
	bool find = false;
	for (int j = 0; j < size; j++) {
		int k = 0;
		if (arr[j][k] == '0') {
			k = 0;
			while (k < size && arr[j][k] == '0') {
				calSpaces = 0;
				start_coloumn_index = k;
				while (arr[j][k] == '0' && k < size) {
					calSpaces++;
					if (calSpaces == wordLength) {
						find = true;
						break;
					}
					k++;
				}
				if (find)
					break;
				k++;
			}
			if (calSpaces >= wordLength) {
				for (int l = start_coloumn_index, index = 0; index <= wordLength - 1; l++, index++) {
					if (word[index] == 32) {
						l--;
						continue;
					}
					arr[j][l] = word[index];
				}
				return true;
			}
		}
	}
	return false;
}
bool grid::rightToLeft(string word) {
	int wordLength = word.length();
	int calSpaces = 0, start_coloumn_index = 0;
	bool find = false;
	for (int j = 0; j < size; j++) {
		int k = size - 1;
		if (k >= 0 && arr[j][k] == '0') {
			k = size - 1;
			while (arr[j][k] == '0' && k >= 0 && !find) {
				calSpaces = 0;
				start_coloumn_index = k;
				while (arr[j][k] == '0' && k >= 0 && !find) {
					calSpaces++;
					k--;
					if (calSpaces == wordLength)
						find = true;
				}
				k--;
			}
			if (calSpaces >= wordLength) {
				for (int l = start_coloumn_index, index = 0; index <= wordLength - 1; l--, index++) {
					if (word[index] == 32) {
						l++;
						continue;
					}
					arr[j][l] = word[index];
				}
				return true;
			}
		}
	}
	return false;
}
bool grid::topLeftToBottomRight(string word) {
	int wordLength = word.length();
	int calSpaces = 0, start_coloumn_index = 0;
	bool find = false;
	int j = 0;
	while (j < size && !find && arr[j][j] == '0') {
		calSpaces = 0;
		start_coloumn_index = j;
		while (j < size && arr[j][j] == '0' && !find) {
			calSpaces++;
			j++;
			if (calSpaces == wordLength)
				find = true;
		}
		j++;
	}
	if (calSpaces >= wordLength) {
		for (int l = start_coloumn_index, index = 0; index <= wordLength - 1; l++, index++) {
			if (word[index] == 32) {
				l--;
				continue;
			}
			arr[l][l] = word[index];
		}
		return true;
	}
	return false;
}
bool grid::bottomRightToTopLeft(string word) {
	int wordLength = word.length();
	int calSpaces = 0, start_coloumn_index = 0;
	bool find = false;
	int j = size - 1;
	while (!find && j >= 0 && arr[j][j] == '0') {
		calSpaces = 0;
		start_coloumn_index = j;
		while (!find && j >= 0 && arr[j][j] == '0') {
			calSpaces++;
			j--;
			if (calSpaces == wordLength)
				find = true;
		}
		j--;
	}
	if (calSpaces >= wordLength) {
		for (int l = start_coloumn_index, index = 0; index <= wordLength - 1; l--, index++) {
			if (word[index] == 32) {
				l++;
				continue;
			}
			arr[l][l] = word[index];
		}
		return true;
	}
	return false;
}
bool grid::topRightToBottomLeft(string word) {
	int wordLength = word.length();
	int calSpaces = 0, start_coloumn_index = 0, start_row_index = 0;
	bool find = false;
	int j = size - 1, i = 0;
	while (i < size && j >= 0 && !find && arr[i][j] == '0') {
		calSpaces = 0;
		start_coloumn_index = j;
		start_row_index = i;

		while (j >= 0 && i < size && arr[i][j] == '0' && !find) {
			calSpaces++;
			j--;
			i++;
			if (calSpaces == wordLength)
				find = true;
		}
		j--;
		i++;
	}
	if (calSpaces >= wordLength) {
		for (int l = start_row_index, index = 0, m = start_coloumn_index; index <= wordLength - 1; l++, m--, index++) {
			if (word[index] == 32) {
				l--;
				m++;
				continue;
			}
			arr[l][m] = word[index];
		}
		return true;
	}
	return false;
}
bool grid::bottomLeftToTopRight(string word) {
	int wordLength = word.length();
	int calSpaces = 0, start_coloumn_index = 0, start_row_index = 0;
	bool find = false;
	int i = size - 1, j = 0;
	while (j < size && i >= 0 && !find && arr[i][j] == '0') {
		calSpaces = 0;
		start_coloumn_index = j;
		start_row_index = i;

		while (i >= 0 && j < size && arr[i][j] == '0' && !find) {
			calSpaces++;
			j++;
			i--;
			if (calSpaces == wordLength)
				find = true;
		}
		j++;
		i--;
	}
	if (calSpaces >= wordLength) {
		for (int l = start_row_index, index = 0, m = start_coloumn_index; index <= wordLength - 1; l--, m++, index++) {
			if (word[index] == 32) {
				l++;
				m--;
				continue;
			}
			arr[l][m] = word[index];
		}
		return true;
	}
	return false;
}
void grid::fillEmptyPlaces() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (arr[i][j] == '0') 					
				randomAlpha_ToFillEmptySpaces(i, j);
		}
	}
}
void grid::randomAlpha_ToFillEmptySpaces(int i, int j) {
	int rand_num = (rand() % 26) + 1;
	switch (rand_num) {
	case 1:arr[i][j] = 'A'; break;
	case 2:arr[i][j] = 'B'; break;
	case 3:arr[i][j] = 'C'; break;
	case 4:arr[i][j] = 'D'; break;
	case 5:arr[i][j] = 'E'; break;
	case 6:arr[i][j] = 'F'; break;
	case 7:arr[i][j] = 'G'; break;
	case 8:arr[i][j] = 'H'; break;
	case 9:arr[i][j] = 'I'; break;
	case 10:arr[i][j] = 'J'; break;
	case 11:arr[i][j] = 'K'; break;
	case 12:arr[i][j] = 'L'; break;
	case 13:arr[i][j] = 'M'; break;
	case 14:arr[i][j] = 'N'; break;
	case 15:arr[i][j] = 'O'; break;
	case 16:arr[i][j] = 'P'; break;
	case 17:arr[i][j] = 'Q'; break;
	case 18:arr[i][j] = 'R'; break;
	case 19:arr[i][j] = 'S'; break;
	case 20:arr[i][j] = 'T'; break;
	case 21:arr[i][j] = 'U'; break;
	case 22:arr[i][j] = 'V'; break;
	case 23:arr[i][j] = 'W'; break;
	case 24:arr[i][j] = 'X'; break;
	case 25:arr[i][j] = 'Y'; break;
	case 26:arr[i][j] = 'Z'; break;
	default:
		clog << "None of alphabet is inserted in the empty index of grid\n";
	}
}
void grid::printGridInFile() {
	ofstream fout;
	fout.open("OutputGrid.txt", ios::out);
	if (!fout)
		clog << "Output file is not opening\n";
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			fout << arr[i][j] << " ";
		}
		fout << endl;
	}
	fout.close();
}
void grid::printGrid() {
	cout << "\nGrid is given in the following\n";
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
grid::~grid() {
	for (int i = 0; i < size; i++)
		delete[]arr[i];
	delete[]arr;
	delete[]sizeOfEachWord;
}
int main() {
	srand(time(0));
	grid obj1;
	obj1.set_sizeof_sizeOfEachWord();
	obj1.CheckSizeOfGrid();
	obj1.MakeGrid();
	obj1.initializeGridWithZero();
	obj1.PutElementsToGrid();
	obj1.printGridInFile();
	return 0;
}