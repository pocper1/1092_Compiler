#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct line {
  char nonterminal;             // store nonterminal
  vector<string> terminal;      // store terminal
  string final_result;          // the final result of line
  int terminal_counter = 0;     // cal how many separate terminal
  bool finish_progress = false; // is there any left
  bool reach_output_end = true; // end of output
  bool reach_file_end = true;   // find is there ";"
};

void input();                      // input to vector
void parse_the_line(string input); // parse single line
void first(line l);                // find first set
void findnonterminal(char nonter); // find nonterminal from firstset
bool CompareNonterminal(line,
                        line);     // Compare nonterminal in ASCII
void output_sort_delete(int i);    // sort output and delete the same char
bool determine_EOF(string output); // find is there a EOF(;)
void printresult();                // print result

vector<line> result; // store all the line
int operating_line;  // store current operate line
int end_line;

int main() {
  input();       // input
  printresult(); // print result
  return 0;
}

void input() {
  string endOfString = "END_OF_GRAMMAR";
  string input;

  while (getline(cin, input)) {
    if (input == endOfString)
      break;
    else
      parse_the_line(input);
  }
}
void parse_the_line(string input) {
  string singleterminal;
  int index = 0;
  struct line single;

  while (index < input.length()) {
    if (index == 0) {
      single.nonterminal = input[index]; // nonterminal
      index++;
    }
    if (input[index] == ' ' || input[index] == '|') { // separate teminal set
      index++;
      while (index <= input.length() && input[index] != '|') {
        // find next separate terminal set
        singleterminal += input[index];
        index++;
      }
      single.terminal.push_back(singleterminal);
      single.terminal_counter++;
      singleterminal = "";
    }
  }
  result.push_back(single);
}

void first(line in_l) {
  for (auto i = 0; i < in_l.terminal_counter; i++) {
    for (auto j = 0; j < in_l.terminal[i].size(); j++) {
      if (in_l.terminal[i][j] >= 'a' && in_l.terminal[i][j] <= 'z') {
        // nonterminal
        result[operating_line].final_result += in_l.terminal[i][j];

        if (in_l.terminal_counter == 1)
          result[operating_line].reach_file_end = false;

        break;
      } else if (in_l.terminal[i][j] == ';') {
        result[operating_line].final_result += in_l.terminal[i][j];
        break;
      } else if (in_l.terminal[i][j] == '$') {
        result[operating_line].final_result += in_l.terminal[i][j];

        if (in_l.terminal_counter == 1)
          result[operating_line].reach_file_end = false;

        break;
      } else if (in_l.terminal[i][j] >= 'A' && in_l.terminal[i][j] <= 'Z') {

        findnonterminal(in_l.terminal[i][j]); // terminal go back to find
        if (result[end_line].reach_output_end)
          break;
      }
    }
    if (result[operating_line].reach_file_end == false) {
      output_sort_delete(operating_line);

      if (determine_EOF(result[operating_line].final_result)) {
        result[operating_line].final_result.erase(
            result[operating_line].final_result.begin() +
            result[operating_line].final_result.find(";"));
        result[operating_line].reach_file_end = true;
      }
    }
  }

  for (int j = 0; j < result.size(); j++) {
    if (result[j].nonterminal == in_l.nonterminal) {
      result[j].finish_progress = true;
      int output_i = 0;
      while (output_i < result[j].final_result.size()) {
        if ('a' <= result[j].final_result[output_i] &&
            result[j].final_result[output_i] <= 'z') {
          output_i++;
        } else {
          result[j].reach_output_end = false;
          break;
        }
      }
    }
  }
}

void findnonterminal(char nonter) {

  for (int i = 0; i < result.size(); i++) {
    if (result[i].nonterminal == nonter) {
      if (result[i].finish_progress) {
        if (result[i].final_result != ";") {
          result[operating_line].final_result += result[i].final_result;
          end_line = i;
        }
      } else if (!result[i].finish_progress) {
        int tmp_current = operating_line;
        operating_line = i;
        first(result[i]);
        if (result[i].finish_progress) {
          operating_line = tmp_current;
          if (result[i].final_result != ";") {
            result[operating_line].final_result += result[i].final_result;
            end_line = i;
          }
        }
      }
    }
  }
}
void printresult() {
  sort(result.begin(), result.end(),
       CompareNonterminal); // sorted by nonterminal
  for (auto i = 0; i < result.size(); i++) {
    if (!result[i].finish_progress) {
      operating_line = i;
      first(result[i]);
    }
  }

  for (int i = 0; i < result.size(); i++) {
    output_sort_delete(i); // sorted by output
    cout << result[i].nonterminal << " " << result[i].final_result << endl;
  }
  cout << "END_OF_FIRST" << endl;
}

bool CompareNonterminal(line a, line b) {
  return a.nonterminal < b.nonterminal;
}
void output_sort_delete(int i) {
  sort(result[i].final_result.begin(), result[i].final_result.end());
  string::iterator tmp =
      unique(result[i].final_result.begin(), result[i].final_result.end());
  result[i].final_result.erase(tmp, result[i].final_result.end());
}
bool determine_EOF(string output) {
  for (int i = 0; i < output.size(); i++) {
    if (output[i] == ';')
      return true;
  }
  return false;
}