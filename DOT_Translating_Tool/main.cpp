#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <vector>
#include <string>

using namespace std;

enum Operation
{
	None,
	ExtractOldLines,
	ExtractNewLines,
	ExtractBothLines,
	CompileNewLines,
	Cancel
};

ifstream br_file_old;
ifstream en_file_old;

char c211 = 211;
char c227 = 227;
char c202 = 202;
char c237 = 237;
char c243 = 243;
char c245 = 245;
char c250 = 250;

string s211 = "" + c211;

void printHeader();
int isAllReady();
Operation getOptionCode();
int extractOldLines();

int main(int argc, const char** argv)
{
	Operation opt = None;

	if (!isAllReady()) return EXIT_FAILURE;
	
	opt = getOptionCode();

	if (opt == ExtractOldLines) return extractOldLines();



	return EXIT_SUCCESS;
}

/// <summary>
/// Prints program's header.
/// </summary>
void printHeader()
{
	cout << endl;
	cout << "\t\tDOT Translating Tool" << endl;
	cout << endl;
}

/// <summary>
/// Checks if all files are in place.
/// </summary>
int isAllReady()
{
	br_file_old = ifstream("DOT_BR_OLD.txt");
	en_file_old = ifstream("DOT_EN_OLD.txt");

	if (!br_file_old.good() || !en_file_old.good())
	{
		cout << "ERROR: Files are not in place!" << endl;
		cout << "Please put DOT_BR_OLD.txt and DOT_EN_OLD.txt in this same folder!" << endl;
		return false;
	}

	return true;
}

/// <summary>
/// Gets operation's code.
/// </summary>
Operation getOptionCode()
{
	Operation opt = None;
	int input;

	while (opt == None)
	{
		system("CLS");
		printHeader();

		cout << "Please enter with the desired operation..." << endl;
		cout << endl;
		cout << "(1) Extract lines from the classic edition." << endl;
		cout << "(2) Extract lines from the remastered edition." << endl;
		cout << "(3) Extract lines from both versions." << endl;
		cout << "(4) Compile lines to the remastered edition." << endl;
		cout << "(5) Cancel." << endl;
		cout << endl;
		cout << "What to do? ";

		scanf("%d", &input);

		if (input >= 1 && input <= 5)
			opt = (Operation)input;

	}

	return opt;
}

/// <summary>
/// Extracts dialog lines from both BR and EN file from the classic version.
/// </summary>
int extractOldLines()
{
	// Buffers to analyze lines
	string br_buffer;
	string en_buffer;
	// Filtered lines from old files.
	vector<string> br_lines_old = {};
	vector<string> en_lines_old = {};

	while (!br_file_old.eof() || !en_file_old.eof())
	{
		br_buffer.clear();
		en_buffer.clear();

		getline(br_file_old, br_buffer);
		getline(en_file_old, en_buffer);

		// Lots of lines are the same across both files, 
		//this filter helps adding only those which were
		//translated.
		if (br_buffer != en_buffer)
		{
			br_lines_old.push_back(br_buffer);
			en_lines_old.push_back(en_buffer);
		}
	}

	return EXIT_SUCCESS;
}

void replace(std::string& str, const std::string& from, const std::string& to)
{
	if (from.empty()) return;

	size_t start_pos = 0;

	while ((start_pos = str.find(from, start_pos)) != std::string::npos)
	{
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
}

/// <summary>
/// Removes string marks used in Scumm engine from the extracted lines.
/// </summary>
void removeOutEngineMarks(vector<string> lines)
{
	string buffer;

	for (int i = 0; i < lines.size(); i++)
	{
		buffer = lines[i];


	}
}

void removeStartMarks(string& line)
{
	int i = 0;
	int size;

	while (line[i] == '\\') i += 4;

	size = line.size() - i - 1;
	line = line.substr(i, size);

	replace(line, "\\211", );
}
