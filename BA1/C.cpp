#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

enum Token_type
{
    TAG_OPEN_SLASH,
    TAG_OPEN,
    TAG_CLOSE,
    TAG_EQUALS,
    SINGLE_QUOTE_STRING,
    DOUBLE_QUOTE_STRING,
    TAG_NAME,
    HTML_TEXT,
    eof
};

struct Token
{
    Token_type type;
    string value;
};

string input = "";
vector<Token> tokens;
Token now;
Token getNextToken();
int i = 0;

void scanner();
bool htmlDocument();
bool htmlElement();
bool htmlAttributeList();
bool htmlAttribute();
bool attribute();
bool htmlContent();
bool htmlChardata();
int main()
{
    getline(cin, input);
    scanner();
    // for (int i = 0; i < tokens.size(); i++)
    // {
    //     cout << tokens[i].type << " " << tokens[i].value << endl;
    // }
    // cout << endl;
    if (htmlDocument())
    {
        cout << "valid" << endl;
    }
    else
    {
        cout << "invalid" << endl;
    }
}
void scanner()
{
    bool inTagDef = false;
    bool inSingleQuote = false;
    bool inDoubleQuote = false;
    string tag = "";
    string text = "";
    string single_text = "";
    string double_text = "";
    for (int i = 0; i < input.length(); i++)
    {
        if (i < input.length() - 1 && input[i] == '<' && input[i + 1] == '/')
        {
            if (text == " ")
                text = "";
            if (text == "  ")
                text = "";
            if (text.size() != 0)
            {
                Token token;
                token.type = HTML_TEXT;
                token.value = text;
                tokens.push_back(token);
                // cout << "HTML_TEXT " << text << endl;
                text = "";
            }
            Token token;
            token.type = TAG_OPEN_SLASH;
            token.value = "</";
            tokens.push_back(token);
            // cout << "TAG_OPEN_SLASH </" << endl;
            inTagDef = true;
        }
        else if (input[i] == '<')
        {
            if (text.size() != 0)
            {
                Token token;
                token.type = HTML_TEXT;
                token.value = text;
                tokens.push_back(token);
                // cout << "HTML_TEXT " << text << endl;
                text = "";
            }
            Token token;
            token.type = TAG_OPEN;
            token.value = "<";
            tokens.push_back(token);
            // cout << "TAG_OPEN <" << endl;
            inTagDef = true;
        }
        else if (input[i] == '>')
        {
            if (tag != "")
            {
                Token token;
                token.type = TAG_NAME;
                token.value = tag;
                tokens.push_back(token);
                // cout << "TAG_NAME " << tag << endl;
                tag = "";
            }

            Token token;
            token.type = TAG_CLOSE;
            token.value = ">";
            tokens.push_back(token);
            // cout << "TAG_CLOSE >" << endl;
            inTagDef = false;
        }
        else if (input[i] == '=')
        {
          if (tag != "")
            
            
            {
                Token token;
                token.type = TAG_NAME;
                token.value = tag;
                tokens.push_back(token);
                // cout << "TAG_NAME " << tag << endl;
                tag = "";
            }
            Token token;
            token.type = TAG_EQUALS;
            token.value = "=";
            tokens.push_back(token);
            // cout << "TAG_EQUALS =" << endl;
        }
        else if (input[i] == '\'' && inTagDef == true)
        {
            if (inSingleQuote)
            {
                Token token;
                token.type = SINGLE_QUOTE_STRING;
                token.value = single_text;
                tokens.push_back(token);
                // cout << "SINGLE_QUOTE_STRING " << single_text << endl;
                inSingleQuote = false;
            }
            else
            {
                inSingleQuote = true;
            }
        }
        else if (input[i] == '"' && inTagDef == true)
        {
            if (inDoubleQuote)
            {
                Token token;
                token.type = DOUBLE_QUOTE_STRING;
                token.value = double_text;
                tokens.push_back(token);
                // cout << "DOUBLE_QUOTE_STRING " << double_text << endl;
                inDoubleQuote = false;
            }
            else
            {
                inDoubleQuote = true;
            }
        }
        else if (input[i] == ' ')
        {
            if (tag != "")
            {
                Token token;
                token.type = TAG_NAME;
                token.value = tag;
                tokens.push_back(token);
                // cout << "TAG_NAME " << tag << endl;
                tag = "";
            }
            if (inTagDef)
            {
            }
            else
            {
                text += input[i];
            }
            continue;
        }
        else if (inTagDef)
        {
            if (input[i] != '/')
                if (inSingleQuote == true)
                {
                    single_text += input[i];
                }
                else if (inDoubleQuote == true)
                {
                    double_text += input[i];
                }
                else
                {
                    tag += input[i];
                }
        }
        else
        {
            if (input[i] != '/')
                text += input[i];
        }
    }
}

Token getNextToken()
{
    if (i < tokens.size())
    {
        Token token = tokens[i];
        i++;
        return token;
    }
    else //$
    {
        Token token;
        token.type = eof;
        token.value = "";
        return token;
    }
}
void htmlDocument() {
    if(token.front()=="TAG_OPEN"){
        htmlElement();
        htmlDocument();
        if(isValid){
            process.push_back("htmlDocument");            
        }
    }
}

void htmlElement() {
    token.erase(token.begin());
    if(token.front()!="TAG_NAME"){
        isValid=0;
    }
    else{
        token.erase(token.begin());
        htmlAttributeList();
        if(token.front()!="TAG_CLOSE"){
            isValid=0;
        }
        else{
            token.erase(token.begin());
            htmlContent();
            if(token.front()!="TAG_OPEN_SLASH"){
                isValid=0;
            }
            else{
                token.erase(token.begin());
                if(token.front()!="TAG_NAME"){
                    isValid=0;
                }
                else{
                    token.erase(token.begin());
                    if(token.front()!="TAG_CLOSE"){
                        isValid=0;
                    }
                    else{
                        token.erase(token.begin());
                        if(isValid){
                            process.push_back("htmlElement");
                        }                       
                    }
                }
            }
        }
    }
}

void htmlContent(){
    if(token.front()=="HTML_TEXT"){
        htmlChardata();
        htmlContent();
        if(isValid){
            process.push_back("htmlContent");
        }
    }
    else if(token.front()=="TAG_OPEN"){
        htmlElement();
        htmlContent();
        if(isValid){
            process.push_back("htmlContent");
        }
    }
}

void htmlAttributeList(){
    if(token.front()=="TAG_NAME"){
        htmlAttribute();
        htmlAttributeList();
        if(isValid){
            process.push_back("htmlAttributeList");  
        }    
    }
}

void htmlAttribute(){
    token.erase(token.begin());
    if(token.front()!="TAG_EQUALS"){
        isValid=0;
    }
    else{
        token.erase(token.begin());
        attribute();
        if(isValid){
            process.push_back("htmlAttribute");     
        }  
    }
}
void htmlChardata(){
    token.erase(token.begin());
    if(isValid){
        process.push_back("htmlCharData");
    }    
}
void attribute(){
    if(token.front()!="SINGLE_QUOTE_STRING" && token.front()!="DOUBLE_QUOTE_STRING"){
        isValid=0;
    }
    else{
        token.erase(token.begin());
        if(isValid){
            process.push_back("attribute");
        }    
    }
}