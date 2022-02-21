#include <cstddef>
#include <iostream>
#include <regex>
#include <string>

using namespace std;
// regex
regex ID("[A-Za-z_][A-Za-z0-9_]*");
regex STRLIT("[^\"]*");
regex LBR("[\\(]");
regex RBR("[\\)]");
regex DOT("[\\.]");

// function
void program();                // main program
void stmt(string);             // call primary or STRLIT
void stmts(string);            // stmt stmts or λ
void primary(string);          // ID primary_tail
void primary_tail(string);     // DOT or LBR
string check_validate(string); // check vaildate

int main(void) {
  program();
  return 0;
}

string check_validate(string str) {
  string error_msg = "invalid input";

  regex repPattern("[A-Za-z0-9_ | '“' | '”' | '\"' | '(' | ')' | '.']*",
                   regex_constants::extended);
  match_results<string::const_iterator> rerResult;
  // <string::const_iterator>
  // 迭代->當我們只是遍歷容器元素，而不更改容器元素時或者物件是常量時使用
  bool validate = regex_match(str, rerResult, repPattern);
  if (validate)
    return str;
  else {
    cout << error_msg << endl;
    return error_msg;
  }
}

void program() {
  string input_line, tmp;
  bool empty_flag = false;

  while (true) {
    getline(cin, input_line);
    if (input_line == "")
      empty_flag = true;
    else {
      empty_flag = false;
      tmp = check_validate(input_line);

      if (tmp != "invalid input")
        stmts(tmp);
    }
    if (empty_flag == true)
      break;
  }
}

void stmts(string str) {

  if (str != "") {
    stmt(str);
  } else {
    stmts(str);
  }
}

void stmt(string str) {
  regex STRLIT("\"[^\"]*\"", regex_constants::extended);
  regex ID("[A-Za-z_][A-Za-z0-9_]*", regex_constants::extended);
  match_results<string::const_iterator> rerResult;
  int count = 0;
  if (str == "")
    return;
  else {
    // count " number, if odd return error, if even return ok
    for (int i = 0; i < str.size(); i++) {
      if (str[i] == '\"')
        count++;
    }

    if (count % 2 == 0) {
      if (regex_match(str, rerResult, STRLIT)) {
        cout << "STRLIT " << str << endl;
      } else {
        primary(str);
      }
    } else {
      cout << "invalid input" << endl;
    }
  }
}

void primary(string str) {
  size_t found = str.find_first_of("\\.\\(");
  string tmp_str;

  if (found != -1) {
    tmp_str = str.substr(0, found);
    cout << "ID " << tmp_str << endl;
    primary_tail(str.substr(found, str.length()));
  } else {
    tmp_str = str.substr(0, str.length());
    cout << "ID " << tmp_str << endl;
  }
}

void primary_tail(string str) {
  if (str == "")
    return;
  else {
    int pos_dot, pos_lbr;
    string tmp_str, remain;
    pos_dot = -1;
    pos_lbr = -1;

    pos_dot = str.find("."); // DOT
    pos_lbr = str.find("("); // LBR

    // if dot
    if (pos_dot != -1) {
      cout << "DOT ." << endl;

      remain = str.substr(pos_dot + 1, str.length());

      size_t found = remain.find_first_of("\\.\\(");

      tmp_str = remain.substr(0, found);

      if (found != -1) {
        cout << "ID " << tmp_str << endl;
        primary_tail(str.substr(found + 1, str.length()));
      }
    }
    // if (
    else if (pos_lbr != -1) {
      cout << "LBR (" << endl;

      // primary_tail
      remain = str.substr(pos_lbr + 1, str.length()); // delete (
      size_t RBR = str.find_first_of(")");            // found )
      remain =
          str.substr(pos_lbr + 1, RBR - (pos_lbr + 1)); //(中間內容 = remain)

      stmt(remain);

      cout << "RBR )" << endl;

      if (RBR != -1) {
        remain = str.substr(RBR + 1, str.length());
        primary_tail(remain);
      }
    }
  }
}

/*
| program       - stmts
| stmts         - stmt stmts
| stmts         - λ
| stmt          - primary
| stmt          - STRLIT
| primary       - ID primary_tail
| primary_tail  - DOT ID primary_tail
| primary_tail  - LBR stmt RBR primary_tail
| primary_tail  - λ
*/