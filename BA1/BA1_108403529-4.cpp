#include <algorithm>
#include <cctype>
#include <iostream>
#include <regex>
#include <stdio.h>
#include <string>

using namespace std;
bool htmlDocument();
bool htmlElement();
bool htmlContent();
bool htmlAttributeList();
bool htmlAttribute();
bool htmlChardata();
bool attribute();
void html_lexer();

enum tok_type {
  TAG_OPEN_SLASH,
  TAG_OPEN,
  TAG_CLOSE,
  TAG_EQUALS,
  SINGLE_QUOTE_STRING,
  DOUBLE_QUOTE_STIRNG,
  TAG_NAME,
  HTML_TEXT,
  EOS
};

struct tok {
  tok_type type;
  string content;
};
int input_pointer = 0;
string input = "";
string val = "valid";
string inval = "invalid";
vector<tok> storage;
tok getter();
tok current;

int main() {

  bool flag;
  getline(cin, input);
  html_lexer();

  if (htmlDocument())
    cout << "valid" << endl;
  else
    cout << "invalid" << endl;

  // return 0;
}

bool htmlDocument() {

  current = getter();
  if (current.type == EOS)
    return true;

  if (htmlElement()) {

    if (htmlDocument()) {
      cout << "htmlDocument" << endl;
    }
    return htmlDocument();
  } else {
    return false;
  }
}
tok getter() {
  if (input_pointer < storage.size()) {
    tok tok = storage[input_pointer++];
    return tok;
  } else {
    tok tok;
    tok.type = EOS;
    tok.content = "";
    return tok;
  }
}
void html_lexer() {
  bool inTagDef = false;
  string tmp, tmp_str, tmp_htmlstr, tag_name;

  for (int i = 0; i < input.length(); i++) {
    if (i < input.length() - 1 && input[i] == '<' && input[i + 1] == '/') {
      inTagDef = true;
      // ... generate TAG_OPEN_SLASH token

      tmp_htmlstr = "";
      // cout << "TAG_OPEN_SLASH </" << endl;
      tok tok;
      tok.type = TAG_OPEN_SLASH;
      tok.content = "</";
      storage.push_back(tok);
      tmp = "";

      i++;
    } else if (input[i] == '<') {
      // ... generate TAG_OPEN token
      inTagDef = true;
      // cout << "TAG_OPEN <" << endl;
      // if (tmp.size() != 0) {
      tok tok;
      tok.type = TAG_OPEN;
      tok.content = "<";
      storage.push_back(tok);
      tmp = "";
      // }
    } else if (input[i] == '>') {
      inTagDef = false;
      // ... generate TAG_CLOSE token

      // cout << "TAG_CLOSE >" << endl;
      tok tok;
      tok.type = TAG_CLOSE;
      tok.content = ">";
      storage.push_back(tok);

    } else if (input[i] == '=') {
      // ... generate TAG_EQUALS token
      // cout << "TAG_EQUALS =" << endl;
      tok tok;
      tok.type = TAG_EQUALS;
      tok.content = "=";
      storage.push_back(tok);
    } else if (input[i] == '\'' && inTagDef == true) {
      // ... generate SINGLE_QUOTE_STRING token
      size_t fi = input.find_first_of("\'", i + 1);

      if (fi != -1) {
        // cout << "SINGLE_QUOTE_STRING " << input.substr(i + 1, fi - i - 1)
        //  << endl;
        tok tok;
        tok.type = SINGLE_QUOTE_STRING;
        tok.content = input.substr(i + 1, fi - i - 1);
        storage.push_back(tok);

        i = fi;
      }
    } else if (input[i] == '"' && inTagDef == true) {
      // ... generate DOUBLE_QUOTE_STRING token
      size_t fi = input.find_first_of("\"", i + 1);

      if (fi != -1) {
        // cout << "DOUBLE_QUOTE_STRING " << input.substr(i + 1, fi - i - 1)
        //      << endl;
        tok tok;
        tok.type = DOUBLE_QUOTE_STIRNG;
        tok.content = input.substr(i + 1, fi - i - 1);
        storage.push_back(tok);
        i = fi;
      }

    } else if (input[i] == ' ') {
      continue;
    } else if (inTagDef) {
      // ... generate TAG_NAME token

      char tmp = input[i];
      while (true) {

        if (tmp == ' ' || tmp == '>' || tmp == '=') {
          tmp_str[tmp_str.size()] = '\0';
          --i;
          break;
        } else {
          tmp_str += tmp;
          tmp = input[++i];
        }
      }
      tok tok;
      tok.type = TAG_NAME;
      tok.content = tmp_str;
      storage.push_back(tok);
      // cout << "TAG_NAME " << tmp_str << endl;
      tmp_str = "";
    } else {
      // ... generate HTML_TEXT token
      // htmlChardata(str);

      char tmp_htmlchr = input[i];
      while (true) {
        if (tmp_htmlchr == '<') {
          tmp_htmlstr[tmp_htmlstr.size()] = '\0';
          --i;
          break;
        } else {
          tmp_htmlstr += tmp_htmlchr;
          tmp_htmlchr = input[++i];
        }
      }
      tok tok;
      tok.type = HTML_TEXT;
      tok.content = tmp_htmlstr;
      storage.push_back(tok);

      // cout << "HTML_TEXT " << tmp_htmlstr << endl;
      tmp_htmlstr = "";
    }
  }
}
bool htmlElement() {
  // TAG_OPEN TAG_NAME htmlAttributeList TAG_CLOSE htmlContent TAG_OPEN_SLASH
  // TAG_NAME TAG_CLOSE
  cout << "HTMLELEMENT" << endl;
  bool isvalid;
  bool op1 = false, op2 = false, op3 = false, op4 = false, op5 = false,
       op6 = false, check_attr_correct = false,
       check_htmlContent_correct = false, op7 = false;
  // cout << "htmlelement" << endl;

  if (current.type == TAG_OPEN) {
    current = getter();
    op1 = true;
    if (current.type == TAG_NAME) {

      if (htmlAttributeList()) {

        if (current.type == TAG_CLOSE) {

          if (htmlContent()) {
            if (current.type == TAG_OPEN_SLASH) {
              current = getter();

              if (current.type == TAG_NAME) {
                current = getter();

                if (current.type == TAG_CLOSE) {

                  cout << "htmlElement" << endl;
                  isvalid = true;
                } else {
                  isvalid = false;
                }
              } else {
                isvalid = false;
              }

            } else {
              isvalid = false;
            }
          } else {
            isvalid = false;
          }

        } else {
          isvalid = false;
        }
      } else {
        isvalid = false;
      }
    } else {
      isvalid = false;
    }
  } else {
    isvalid = false;
  }

  return isvalid;
}

//========================================================================

bool htmlContent() {
  // 4 htmlContent->htmlChardata htmlContent
  // 5 htmlContent->htmlElement htmlContent
  // 6 htmlContent->λ
  cout << "htmlCOntern" << endl;
  bool isvalid = false;
  current = getter();
  // ==================== condition 4 ====================
  if (htmlChardata()) {
    isvalid = htmlContent();
    if (isvalid)
      cout << "htmlContent" << endl;
    return isvalid;
  }
  // ==================== condition 5 ====================
  if (htmlElement()) {
    isvalid = htmlContent();
    if (isvalid)
      cout << "htmlContent" << endl;
    return isvalid;
  }

  // ==================== condition 6 ====================
  return true;
}

bool htmlAttributeList() {
  // 7 htmlAttributeList -> htmlAttribute htmlAttributeList
  // 8 htmlAttributeList -> λ
  bool isvalid = false, flag1, flag2;
  current = getter();
  // ==================== condition 7 ====================
  if (current.type == EOS)
    isvalid = true;

  // ==================== condition 8 ====================
  flag1 = htmlAttribute();

  if (flag1) {
    flag2 = htmlAttributeList();
    if (flag2) {
      cout << "htmlAttributeList" << endl;
      isvalid = true;
    }
  }
  return isvalid;
}

bool htmlAttribute() {
  // 9 htmlAttribute -> TAG_NAME TAG_EQUALS attribute
  // ==================== condition 9 ====================
  bool flag1 = false, isvalid = false;
  if (current.type == TAG_NAME) {
    current = getter();
    flag1 = true;
  }
  if (flag1 == true && current.type == TAG_EQUALS) {
    current = getter();
    isvalid = attribute();
    if (isvalid)
      cout << "htmlAttribute" << endl;
  }

  return isvalid;
}

bool htmlChardata() {
  // 10 htmlChardata -> HTML_TEXT
  // ==================== condition 10 ====================
  bool isvalid = false;
  if (current.type == HTML_TEXT) {
    cout << "htmlCharData" << endl;
    isvalid = true;
  }
  return isvalid;
}

bool attribute() {
  // 11 attribute -> DOUBLE_QUOTE_STRING
  // 12 attribute -> SINGLE_QUOTE_STRING
  bool isvalid = false;

  // ==================== condition 11 ====================
  if (current.type == SINGLE_QUOTE_STRING) {
    cout << "attribute" << endl;
    isvalid = true;
  }
  // ==================== condition 12 ====================
  if (current.type == DOUBLE_QUOTE_STIRNG) {
    cout << "attribute" << endl;
    isvalid = true;
  }

  return isvalid;
}

/*
example:
<html> <div class='red'>text in div</div> </html>

TAG_OPEN <
TAG_NAME html
TAG_CLOSE >
TAG_OPEN <
TAG_NAME div
TAG_NAME class
TAG_EQUALS =
SINGLE_QUOTE_STRING red
TAG_CLOSE >
HTML_TEXT text in div
TAG_OPEN_SLASH </
TAG_NAME div
TAG_CLOSE >
TAG_OPEN_SLASH </
TAG_NAME html
TAG_CLOSE >

<div>"test"</div>
*/

/*
1 htmlDocument -> htmlElement htmlDocument $
2 htmlDocument -> λ
3 htmlElement -> TAG_OPEN TAG_NAME htmlAttributeList TAG_CLOSE htmlContent
TAG_OPEN_SLASH TAG_NAME TAG_CLOSE

4 htmlContent -> htmlChardata htmlContent
5 htmlContent -> htmlElement htmlContent
6 htmlContent -> λ

7 htmlAttributeList -> htmlAttribute htmlAttributeList
8 htmlAttributeList -> λ

9 htmlAttribute -> TAG_NAME TAG_EQUALS attribute

10 htmlChardata -> HTML_TEXT

11 attribute -> DOUBLE_QUOTE_STRING
12 attribute -> SINGLE_QUOTE_STRING
*/