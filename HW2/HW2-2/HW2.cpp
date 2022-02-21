#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef struct line {
  string Output;
  vector<string> terminal;
  int num_of_terminal = 0;
  char nonterminal;
  bool is_end = false;
} token;
vector<line> collection;

void input();
void output();
void parse(string input);
void first();
void nonterminal(char nonter);
bool CompareNonterminal(line a, line b);
void deletethesame(int i);

int main() {
  input();
  output();
}

void input() {
  string input;
  string end = "END_OF_GRAMMAR";

  while (true) {
    getline(cin, input);
    if (input == end)
      break;
    else
      parse(input);
  }
}

void parse(string input) {
  line tmp;
  string t;
  int i = 0;
  while (i < input.size()) {
    if (i == 0) {
      tmp.nonterminal = input[0];
      i++;
    }
    if (input[i] == '|' || input[i] == ' ') {
      i++;
      while (i != input.size() && input[i] != '|') {
        t += input[i];
        i++;
      }
      cout << t << endl;
      tmp.terminal.push_back(t);
      tmp.num_of_terminal++;
    }
  }
  collection.push_back(tmp);
}

void first() {}

bool CompareNonterminal(line a, line b) {
  return a.nonterminal > b.nonterminal;
}

void deletetheSame(int i) {
  sort(collection[i].Output.begin(), collection[i].Output.end());
  auto tmp = unique(collection[i].Output.begin(), collection[i].Output.end());
  collection[i].Output.erase(collection[i].Output.end() - tmp);
}

void output() {
  cout << "output: " << endl;
  sort(collection.begin(), collection.end(), CompareNonterminal);

  for (int i = 0; i < collection.size(); i++) {
    deletetheSame(i);
    cout << "nonterminal: " << collection[i].nonterminal << " terminal: " << collection[i].Output << endl;
  }

  cout << "END_OF_FIRST" << endl;
}