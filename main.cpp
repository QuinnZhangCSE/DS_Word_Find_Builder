#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//recursive function to search if word in board 
//b-2D board, w-word, letter-index of specific letter, dir-direction, i-row index, j-colum index
bool contains(vector<vector<string>> & b, string w, int letter, string dir, unsigned int i, unsigned int j)
{
	if (i < 0 || i >= b.size()) { return false; }
	if (j < 0 || j >= b[i].size()) { return false; }
	if (b[i][j] != string(1, w[letter]) && dir == "no") //if not the letter looking for
	{
		if (j == b[i].size() - 1) { return contains(b,w, letter, "no", i + 1, 0); } //if end of row
		else { return contains(b, w, letter, "no", i, j + 1); } //goes to the next letter
	}
	if (b[i][j] == string(1, w[letter]) && dir == "no") //initialize the search
	{
		if (contains(b, w, letter + 1, "ul", i - 1, j - 1) || contains(b, w, letter + 1, "u", i - 1, j) || contains(b, w, letter + 1, "ur", i - 1, j + 1) || contains(b, w, letter + 1, "l", i, j - 1) || contains(b, w, letter + 1, "r", i, j + 1) || contains(b, w, letter + 1, "dl", i + 1, j - 1) || contains(b, w, letter + 1, "d", i + 1, j) || contains(b, w, letter + 1, "dr", i + 1, j + 1) == true) { return true; } //if the function is true
		else { //keep looking
			if (j == b[i].size() - 1) { return contains(b, w, letter, "no", i + 1, 0); } //if end of row
			else { return contains(b, w, letter, "no", i, j + 1); } //goes to the next letter
		}
	}
	if (b[i][j] != string(1, w[letter]) && dir != "no") { return false; } //if gird does not match
	if (b[i][j] == string(1, w[letter]) && letter == w.length() - 1) //if whole word found
	{
		return true;
	}
	if (b[i][j] == string(1, w[letter]) && dir == "ul") { return contains(b, w, letter + 1, "ul", i - 1, j - 1); }
	if (b[i][j] != string(1, w[letter]) && dir == "ul") { return false; }
	if (b[i][j] == string(1, w[letter]) && dir == "u")	{ return contains(b, w, letter + 1, "u", i - 1, j); }
	if (b[i][j] != string(1, w[letter]) && dir == "u")	{ return false; }
	if (b[i][j] == string(1, w[letter]) && dir == "ur") { return contains(b, w, letter + 1, "ur", i - 1, j + 1); }
	if (b[i][j] != string(1, w[letter]) && dir == "ur") { return false; }
	if (b[i][j] == string(1, w[letter]) && dir == "l")	{ return contains(b, w, letter + 1, "l", i, j - 1); }
	if (b[i][j] != string(1, w[letter]) && dir == "l")	{ return false; }
	if (b[i][j] == string(1, w[letter]) && dir == "r")	{ return contains(b, w, letter + 1, "r", i, j + 1); }
	if (b[i][j] != string(1, w[letter]) && dir == "r")	{ return false; }
	if (b[i][j] == string(1, w[letter]) && dir == "dl") { return contains(b, w, letter + 1, "dl", i + 1, j - 1); }
	if (b[i][j] != string(1, w[letter]) && dir == "dl") { return false; }
	if (b[i][j] == string(1, w[letter]) && dir == "d")	{ return contains(b, w, letter + 1, "d", i + 1, j); }
	if (b[i][j] != string(1, w[letter]) && dir == "d")	{ return false; }
	if (b[i][j] == string(1, w[letter]) && dir == "dr") { return contains(b, w, letter + 1, "dr", i + 1, j + 1); }
	if (b[i][j] != string(1, w[letter]) && dir == "dr") { return false; }

	return false;
}

//check if letter can be inserted in the position b[i][j]
bool can_insert(vector<vector<string>> &b, string letter, int i, int j)
{
	if (i < 0 || i >= b.size()) { return false; }
	if (j < 0 || j >= b[i].size()) { return false; }

	if (b[i][j] == letter || b[i][j] == ".") { return true; }

	return false;
}

//check if the board is full
bool full(vector<vector<string>> & b)
{
	for (unsigned int i = 0; i < b.size(); i++)
	{
		for (unsigned int j = 0; j < b[i].size(); j++)
		{
			if (b[i][j] == ".") { return false; }
		}
	}
	return true;
}

//check if board already exist in the collection of solutions
bool exist(vector<vector<string>> & b, vector<vector<vector<string>>> & col)
{
	bool ans = false;
	for (unsigned int k = 0; k < col.size(); k++)
	{
		bool equal = true;
		for (unsigned int i = 0; i < b.size(); i++)
		{
			for (unsigned int j = 0; j < b[i].size(); j++)
			{
				if (b[i][j] != col[k][i][j]) { equal = false; }
			}
		}
		if (equal == true) { ans = true; }
	}
	return ans;
}

//fills the board if there is an empty space
//b-2D board, m-vector of word that cannot appear, col-collection of solutions
void fill(vector<vector<string>> b, vector<string> & m, vector<vector<vector<string>>> & col)
{
	if (full(b)) 
	{
		bool valid = true;
		for (unsigned int i = 0; i < m.size(); i++)
		{
			if (contains(b, m[i], 0, "no", 0, 0) == true) { valid = false; }
		}
		if (valid && exist(b, col) == false) { col.push_back(b); }
	}
	else
	{
		vector<string> option{ "a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z" };
		for (unsigned int i = 0; i < m.size(); i++) { option.erase(remove(option.begin(), option.end(), m[i]), option.end()); } //erases letter if letter not allowed
		for (unsigned int i = 0; i < b.size(); i++)
		{
			for (unsigned int j = 0; j < b[i].size(); j++)
			{
				if (b[i][j] == ".")
				{
					for (unsigned int k = 0; k < option.size(); k++)
					{
						b[i][j] = option[k];
						fill(b, m, col);
					}
				}
			}
		}
	}
}

//finds all the solution
//b-2D board, p-vector of words that has to appear, index-index of whihc word the function is up to with the vector p, m-vector of words that cannot appear, col-collection of solutions
void all(vector<vector<string>> b, vector<string> p, int index, vector<string> m, vector<vector<vector<string>>> & col)
{
	if (index == p.size()) 
	{ 
		bool valid = true;
		for (unsigned int i = 0; i < m.size(); i++)
		{
			if (contains(b, m[i], 0, "no", 0, 0) == true) { valid = false; }
		}
		if (valid && full(b) && exist(b,col) == false) { col.push_back(b); }
		if (valid && full(b) == false)
		{
			fill(b, m, col);
		}
	}
	else {
		for (unsigned int i = 0; i < b.size(); i++)
		{
			for (unsigned int j = 0; j < b[i].size(); j++)
			{
				if (can_insert(b, string(1, p[index][0]), i, j) == true) //if first letter can be inserted
				{
					//up-left
					for (int l = 1; l < p[index].length(); l++)
					{
						if (can_insert(b, string(1, p[index][l]), i - l, j - l) == false) { break; }
						if (l == p[index].length() - 1) //if end of loop and everything fits
						{
							vector<string> temp;
							for (int k = 0; k < p[index].length(); k++) //replace the board witht the letter
							{
								temp.push_back(b[i - k][j - k]);
								b[i - k][j - k] = string(1, p[index][k]);
							}
							all(b, p, index + 1, m, col);
							for (unsigned int k = 0; k < temp.size(); k++) { b[i - k][j - k] = temp[k]; }
							temp.clear();
						}
					}

					//up
					for (int l = 1; l < p[index].length(); l++)
					{
						if (can_insert(b, string(1, p[index][l]), i - l, j) == false) { break; }
						if (l == p[index].length() - 1) //if end of loop and everything fits
						{
							vector<string> temp;
							for (int k = 0; k < p[index].length(); k++)
							{
								temp.push_back(b[i - k][j]);
								b[i - k][j] = string(1, p[index][k]);
							}
							all(b, p, index + 1, m, col);
							for (unsigned int k = 0; k < temp.size(); k++) { b[i - k][j] = temp[k]; }
							temp.clear();
						}
					}

					//up-right
					for (int l = 1; l < p[index].length(); l++)
					{
						if (can_insert(b, string(1, p[index][l]), i - l, j + l) == false) { break; }
						if (l == p[index].length() - 1) //if end of loop and everything fits
						{
							vector<string> temp;
							for (int k = 0; k < p[index].length(); k++)
							{
								temp.push_back(b[i - k][j + k]);
								b[i - k][j + k] = string(1, p[index][k]);
							}
							all(b, p, index + 1, m, col);
							for (unsigned int k = 0; k < temp.size(); k++) { b[i - k][j + k] = temp[k]; }
							temp.clear();
						}
					}

					//left
					for (int l = 1; l < p[index].length(); l++)
					{
						if (can_insert(b, string(1, p[index][l]), i, j - l) == false) { break; }
						if (l == p[index].length() - 1) //if end of loop and everything fits
						{
							vector<string> temp;
							for (int k = 0; k < p[index].length(); k++)
							{
								temp.push_back(b[i][j - k]);
								b[i][j - k] = string(1, p[index][k]);
							}
							all(b, p, index + 1, m, col);
							for (unsigned int k = 0; k < temp.size(); k++) { b[i][j - k] = temp[k]; }
							temp.clear();
						}
					}

					//right
					for (int l = 1; l < p[index].length(); l++)
					{
						if (can_insert(b, string(1, p[index][l]), i, j + l) == false) { break; }
						if (l == p[index].length() - 1) //if end of loop and everything fits
						{
							vector<string> temp;
							for (int k = 0; k < p[index].length(); k++)
							{
								temp.push_back(b[i][j + k]);
								b[i][j + k] = string(1, p[index][k]);
							}
							all(b, p, index + 1, m, col);
							for (unsigned int k = 0; k < temp.size(); k++) { b[i][j + k] = temp[k]; }
							temp.clear();
						}
					}

					//down-left
					for (int l = 1; l < p[index].length(); l++)
					{
						if (can_insert(b, string(1, p[index][l]), i + l, j - l) == false) { break; }
						if (l == p[index].length() - 1) //if end of loop and everything fits
						{
							vector<string> temp;
							for (int k = 0; k < p[index].length(); k++)
							{
								temp.push_back(b[i + k][j - k]);
								b[i + k][j - k] = string(1, p[index][k]);
							}
							all(b, p, index + 1, m, col);
							for (unsigned int k = 0; k < temp.size(); k++) { b[i + k][j - k] = temp[k]; }
							temp.clear();
						}
					}

					//down
					for (int l = 1; l < p[index].length(); l++)
					{
						if (can_insert(b, string(1, p[index][l]), i + l, j) == false) { break; }
						if (l == p[index].length() - 1) //if end of loop and everything fits
						{
							vector<string> temp;
							for (int k = 0; k < p[index].length(); k++)
							{
								temp.push_back(b[i + k][j]);
								b[i + k][j] = string(1, p[index][k]);
							}
							all(b, p, index + 1, m, col);
							for (unsigned int k = 0; k < temp.size(); k++) { b[i + k][j] = temp[k]; }
							temp.clear();
						}
					}

					//down-right
					for (int l = 1; l < p[index].length(); l++)
					{
						if (can_insert(b, string(1, p[index][l]), i + l, j + l) == false) { break; }
						if (l == p[index].length() - 1) //if end of loop and everything fits
						{
							vector<string> temp;
							for (int k = 0; k < p[index].length(); k++)
							{
								temp.push_back(b[i + k][j + k]);
								b[i + k][j + k] = string(1, p[index][k]);
							}
							all(b, p, index + 1, m, col);
							for (unsigned int k = 0; k < temp.size(); k++) { b[i + k][j + k] = temp[k]; }
							temp.clear();
						}
					}

				}
			}
		}
	}
}


//finds one solution
//variable represent the same thing as before
void one(vector<vector<string>> b, vector<string> p, int index, vector<string> m, vector<vector<vector<string>>> & col)
{
	if (col.size() >= 1) { return; } //stops if found one or more solution
	if (index == p.size())
	{
		bool valid = true;
		for (unsigned int i = 0; i < m.size(); i++)
		{
			if (contains(b, m[i], 0, "no", 0, 0) == true) { valid = false; }
		}
		if (valid && full(b)) { col.push_back(b); }
		if (valid && full(b) == false)
		{
			fill(b, m, col);
		}
	}
	else {
		for (unsigned int i = 0; i < b.size(); i++)
		{
			for (unsigned int j = 0; j < b[i].size(); j++)
			{
				if (can_insert(b, string(1, p[index][0]), i, j) == true) //if first letter can be inserted
				{
					//up-left
					for (int l = 1; l < p[index].length(); l++)
					{
						if (can_insert(b, string(1, p[index][l]), i - l, j - l) == false) { break; }
						if (l == p[index].length() - 1) //if end of loop and everything fits
						{
							vector<string> temp;
							for (int k = 0; k < p[index].length(); k++) //replace the board witht the letter
							{
								temp.push_back(b[i - k][j - k]);
								b[i - k][j - k] = string(1, p[index][k]);
							}
							all(b, p, index + 1, m, col);
							for (unsigned int k = 0; k < temp.size(); k++) { b[i - k][j - k] = temp[k]; }
							temp.clear();
						}
					}

					//up
					for (int l = 1; l < p[index].length(); l++)
					{
						if (can_insert(b, string(1, p[index][l]), i - l, j) == false) { break; }
						if (l == p[index].length() - 1) //if end of loop and everything fits
						{
							vector<string> temp;
							for (int k = 0; k < p[index].length(); k++)
							{
								temp.push_back(b[i - k][j]);
								b[i - k][j] = string(1, p[index][k]);
							}
							all(b, p, index + 1, m, col);
							for (unsigned int k = 0; k < temp.size(); k++) { b[i - k][j] = temp[k]; }
							temp.clear();
						}
					}

					//up-right
					for (int l = 1; l < p[index].length(); l++)
					{
						if (can_insert(b, string(1, p[index][l]), i - l, j + l) == false) { break; }
						if (l == p[index].length() - 1) //if end of loop and everything fits
						{
							vector<string> temp;
							for (int k = 0; k < p[index].length(); k++)
							{
								temp.push_back(b[i - k][j + k]);
								b[i - k][j + k] = string(1, p[index][k]);
							}
							all(b, p, index + 1, m, col);
							for (unsigned int k = 0; k < temp.size(); k++) { b[i - k][j + k] = temp[k]; }
							temp.clear();
						}
					}

					//left
					for (int l = 1; l < p[index].length(); l++)
					{
						if (can_insert(b, string(1, p[index][l]), i, j - l) == false) { break; }
						if (l == p[index].length() - 1) //if end of loop and everything fits
						{
							vector<string> temp;
							for (int k = 0; k < p[index].length(); k++)
							{
								temp.push_back(b[i][j - k]);
								b[i][j - k] = string(1, p[index][k]);
							}
							all(b, p, index + 1, m, col);
							for (unsigned int k = 0; k < temp.size(); k++) { b[i][j - k] = temp[k]; }
							temp.clear();
						}
					}

					//right
					for (int l = 1; l < p[index].length(); l++)
					{
						if (can_insert(b, string(1, p[index][l]), i, j + l) == false) { break; }
						if (l == p[index].length() - 1) //if end of loop and everything fits
						{
							vector<string> temp;
							for (int k = 0; k < p[index].length(); k++)
							{
								temp.push_back(b[i][j + k]);
								b[i][j + k] = string(1, p[index][k]);
							}
							all(b, p, index + 1, m, col);
							for (unsigned int k = 0; k < temp.size(); k++) { b[i][j + k] = temp[k]; }
							temp.clear();
						}
					}

					//down-left
					for (int l = 1; l < p[index].length(); l++)
					{
						if (can_insert(b, string(1, p[index][l]), i + l, j - l) == false) { break; }
						if (l == p[index].length() - 1) //if end of loop and everything fits
						{
							vector<string> temp;
							for (int k = 0; k < p[index].length(); k++)
							{
								temp.push_back(b[i + k][j - k]);
								b[i + k][j - k] = string(1, p[index][k]);
							}
							all(b, p, index + 1, m, col);
							for (unsigned int k = 0; k < temp.size(); k++) { b[i + k][j - k] = temp[k]; }
							temp.clear();
						}
					}

					//down
					for (int l = 1; l < p[index].length(); l++)
					{
						if (can_insert(b, string(1, p[index][l]), i + l, j) == false) { break; }
						if (l == p[index].length() - 1) //if end of loop and everything fits
						{
							vector<string> temp;
							for (int k = 0; k < p[index].length(); k++)
							{
								temp.push_back(b[i + k][j]);
								b[i + k][j] = string(1, p[index][k]);
							}
							all(b, p, index + 1, m, col);
							for (unsigned int k = 0; k < temp.size(); k++) { b[i + k][j] = temp[k]; }
							temp.clear();
						}
					}

					//down-right
					for (int l = 1; l < p[index].length(); l++)
					{
						if (can_insert(b, string(1, p[index][l]), i + l, j + l) == false) { break; }
						if (l == p[index].length() - 1) //if end of loop and everything fits
						{
							vector<string> temp;
							for (int k = 0; k < p[index].length(); k++)
							{
								temp.push_back(b[i + k][j + k]);
								b[i + k][j + k] = string(1, p[index][k]);
							}
							all(b, p, index + 1, m, col);
							for (unsigned int k = 0; k < temp.size(); k++) { b[i + k][j + k] = temp[k]; }
							temp.clear();
						}
					}

				}
			}
		}
	}
}
//sorting function to sort the vector by length
bool len(string a, string b)
{
	return a.length() > b.length();
}

int main(int argc, char* argv[]) 
{
	ifstream in_str(argv[1]); //read the file
	ofstream out_str(argv[2]);

	//checks if the file is good
	if (!in_str.good()) {
		std::cerr << "Can't open " << argv[1] << " to read.\n";
		exit(1);
	}

	//variables to store the information in
	string sign;
	string word;
	string s;

	//the col and the row
	in_str >> s;
	int col = atoi(s.c_str());
	in_str >> s;
	int row = atoi(s.c_str());

	//vector to store the words
	vector<string> plus;
	vector<string> minus;

	//loop to sotre the words in vector
	while (in_str >> sign) {
		in_str >> word;
		if (sign == "+") { plus.push_back(word); }
		if (sign == "-") { minus.push_back(word); }
	}

	//sorts the vector by length
	sort(plus.begin(), plus.end(), len);

	//checks if any word length is bigger than the grid
	unsigned int max = 0;
	for (unsigned int i = 0; i < plus.size(); i++)
	{
		if (plus[i].length() > max)
		{
			max = plus[i].length();
		}
	}
	if (max > col && max > row) 
	{ 
		out_str << "No solutions found";
		return 0;
	}
	//checks if any word in plus in contained in minus
	for (unsigned int i = 0; i < plus.size(); i++)
	{
		for (unsigned int j = 0; j < minus.size(); j++)
		{
			if (plus[i].find(minus[j]) != std::string::npos)
			{
				out_str << "No solutions found";
				return 0;
			}
		}
	}

	if (string(argv[3]) == "one_solution")
	{
		vector<vector<vector<string>>> sol; //solution collection		vector<vector<string>> b; //a board
		vector<string> colum; //a colum		for (int i = 0; i < col; i++)
		{
			colum.push_back(".");
		}
		for (int i = 0; i < row; i++)
		{ 			b.push_back(colum); 		}		one(b, plus, 0, minus, sol); //finds one solution

		out_str << "Board:" << endl;		for (int i = 0; i < row; i++)		{			out_str << "  ";			for (int j = 0; j < col; j++)			{				out_str << sol[0][i][j]; //only output the first one within the solution collection			}			out_str << endl;		}
	}

	if (string(argv[3]) == "all_solutions")	{		vector<vector<vector<string>>> sol; //solution collection		vector<vector<string>> b; //a board
		vector<string> colum; //a colum		for (int i = 0; i < col; i++) //initalize the board
		{
			colum.push_back(".");
		}
		for (int i = 0; i < row; i++)
		{
			b.push_back(colum);
		}		all(b, plus, 0, minus, sol); //fins all the solution and adds it to the sol		out_str << sol.size() << " solution(s)" << endl;		for (unsigned int b = 0; b < sol.size(); b++) //output everything from solution collection		{			out_str << "Board:" << endl;			for (int i = 0; i < row; i++)			{				out_str << "  ";				for (int j = 0; j < col; j++)				{					out_str << sol[b][i][j];				}				out_str << endl;			}		}	}
	return 0;
}