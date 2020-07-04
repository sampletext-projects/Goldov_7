#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void open_file(fstream& f, const char* def_file)
{
	int k;
	cout << "Использовать свой файл(1) или исходный(любое число)?: ";
	cin >> k;
	if (k == 1)
	{
		cin.ignore();
		char file[50];
		cout << "Введите название файла: ";
		cin.getline(file, 50);

		f.open(file);
	}
	else
	{
		f.open(def_file);
	}
}

string* split(string& line, int& n)
{
	string* words = new string[line.length()];
	int index = 0;
	int start = 0;
	while (start < line.length())
	{
		int next_space = line.find(' ', start);
		if (next_space == -1)
		{
			next_space = line.length();
		}

		string word = line.substr(start, next_space - start);
		words[index] = word;
		index++;
		start = next_space + 1;
	}
	n = index;
	return words;
}

void remove_at(string* words, int index, int n)
{
	for (int i = index; i < n - 1; i++)
	{
		words[i] = words[i + 1];
	}
}

void remove_even_length_words(string* words, int& n)
{
	for (int i = 0; i < n; i++)
	{
		if (words[i].length() % 2 == 0)
		{
			remove_at(words, i, n);
			n--;
			i--;
		}
	}
}

int main()
{
	setlocale(LC_ALL, "russian");

	fstream f1;

	cout << "Инициализация файла ввода\n";
	open_file(f1, "f1.txt");

	fstream f2;

	cout << "Инициализация файла вывода\n";
	open_file(f2, "f2.txt");

	while (!f1.eof())
	{
		string line;
		getline(f1, line);
		int n;
		string* words = split(line, n);
		remove_even_length_words(words, n);

		for (int i = 0; i < n; i++)
		{
			f2 << words[i] << " ";
		}
		f2 << "\n";

		delete[] words;
	}

	f1.close();
	f2.close();

	system("pause");
}
