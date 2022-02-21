#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include <string>
using namespace std;
#define ending "END_OF_GRAMMAR"
// #define ending "/"
typedef struct
{
    char ID;
    int first_now = 0;
    string rule;
    bool down = false;
    bool null = false;
    string Output;
    vector<string> tokens;
    vector<string> firsts; //存多個
} line;

vector<line> lines;
void input();
void getTerminal();
void sortNonterminal();
void initial();
void first();
int searchDowns(char Terminal);
void deleteNull(int i);
void nullOrNot();
bool check(line x);
void sort();
void output();

int main()
{
    //讀取輸入
    input();
    //set tokens and origin firsts
    getTerminal();
    // 把nonterminal排序
    sortNonterminal();
    // 初始化
    initial();
    //find first set
    first();
    // S包含$就不會有;
    if (lines[lines.size() - 1].rule.find('$') != std::string::npos)
    {
        lines[lines.size() - 1].Output += '$';

        string tmp = "";
        for (int j = 0; j < lines[lines.size() - 1].Output.size(); j++)
        {
            if (lines[lines.size() - 1].Output[j] != ';')
            {
                tmp += lines[lines.size() - 1].Output[j];
            }
        }
        lines[lines.size() - 1].Output = tmp;
        // deleteNull(lines.size() - 1);
    }
    //firsts 整理 unique + sort
    sort();
    // output
    output();
}
void input()
{
    string input = "";
    do
    {
        getline(cin, input);
        if (input != ending)
        {
            line new_line;
            new_line.ID = input[0];
            new_line.rule = input.substr(2, input.length() - 1);
            lines.push_back(new_line);
        }
    } while (input != ending);
}
void getTerminal()
{
    string tmp;
    int i = 0;
    for (int i = 0; i < lines.size(); i++)
    {
        for (int j = 0; j < lines[i].rule.size(); j++)
        {
            if (lines[i].rule[j] != '|')
            {
                tmp += lines[i].rule[j];
            }
            if (lines[i].rule[j] == '|' || j == lines[i].rule.size() - 1)
            {
                lines[i].firsts.push_back(tmp);
                // cout << tmp << endl;
                tmp = "";
            }
        }
    }
}
void sortNonterminal()
{
    for (int i = 0; i < lines.size(); i++)
    {
        for (int j = i + 1; j < lines.size(); j++)
        {
            if (lines[i].ID >= lines[j].ID)
            {
                line tmp;
                tmp = lines[i];
                lines[i] = lines[j];
                lines[j] = tmp;
            }
        }
    }
}
void initial()
{
    int flag = 1;
    for (int i = 0; i < lines.size(); i++)
    {
        flag = 1;
        for (int j = 0; j < lines[i].firsts.size(); j++)
        {
            for (int k = 0; k < lines[i].firsts[j].size(); k++)
            {
                if (lines[i].firsts[j][k] >= 'a' && lines[i].firsts[j][k])
                {
                    lines[i].Output += lines[i].firsts[j][k];
                    break;
                }
                else if (lines[i].firsts[j][k] == ';')
                {
                    lines[i].Output += lines[i].firsts[j][k];
                }
                else if (lines[i].firsts[j][k] == '$')
                {
                    lines[i].Output += lines[i].firsts[j][k];
                }
                else if (lines[i].firsts[j][k] >= 'A' && lines[i].firsts[j][k] <= 'Z')
                {
                    break;
                }
            }
        }
    }
}
void first()
{
    int test = 0;
    nullOrNot();
    while (test < 10) //最多10次 避免無限迴圈
    {
        // 判斷是否包含;
        test++;
        int down_count = 0;
        for (int i = 0; i < lines.size(); i++)
        {
            check(lines[i]);
            if (check(lines[i]) == true)
            {
                down_count++;
            }
            cout << "check now:" << lines[i].ID << endl;
            cout << "downs: " << down_count << endl;
        }
        if (down_count == lines.size())
        {
            break;
        }
        for (int i = 0; i < lines.size(); i++)
        {
            if (check(lines[i]) == false) //未完成的
            {
                cout << "------------" << lines[i].ID << "----------" << endl;
                for (int j = 0; j < lines[i].firsts.size(); j++)
                {
                    int count = 0;
                    int size = lines[i].firsts[j].size();
                    cout << "now handle:" << lines[i].firsts[j] << endl;
                    if (lines[i].firsts[j][count] >= 'a' && lines[i].firsts[j][count] <= 'z')
                    {
                        lines[i].Output += lines[i].firsts[j][count];
                        cout << "erase " << lines[i].firsts[j] << endl;
                        lines[i].firsts[j].erase();
                        cout << "now j" << j << endl;
                        break;
                    }
                    else if (lines[i].firsts[j][count] >= 'A' && lines[i].firsts[j][count] <= 'Z')
                    {
                        cout << "in A-Z" << endl;
                        if (searchDowns(lines[i].firsts[j][count]) != -1)
                        {
                            int notDown = 0;
                            cout << "in A-Z and find down" << endl;
                            cout << "add " << lines[searchDowns(lines[i].firsts[j][count])].ID << " output " << lines[searchDowns(lines[i].firsts[j][count])].Output << endl;
                            lines[i].Output += lines[searchDowns(lines[i].firsts[j][count])].Output;
                            for (int k = 0; k < lines[searchDowns(lines[i].firsts[j][count])].Output.size(); k++)
                            {
                                if (lines[searchDowns(lines[i].firsts[j][count])].Output[k] == ';')
                                {
                                    cout << "if not ; set null " << lines[i].ID << endl;
                                    if (k != 0)
                                        lines[i].null = true;
                                }
                            }
                            count++;
                            while (true)
                            {
                                cout << "now first char in while true " << lines[i].firsts[j][count] << endl;
                                if (lines[i].firsts[j][count] >= 'a' && lines[i].firsts[j][count] <= 'z')
                                {
                                    cout << "judge in a-z" << endl;
                                    cout << "delete null: " << lines[i].ID << endl;
                                    deleteNull(i);
                                    if (lines[searchDowns(lines[i].firsts[j][count - 1])].null == true)
                                        cout << lines[searchDowns(lines[i].firsts[j][count - 1])].ID << " is true" << endl;
                                    else
                                        cout << lines[searchDowns(lines[i].firsts[j][count - 1])].ID << " is false" << endl;
                                    if (lines[searchDowns(lines[i].firsts[j][count - 1])].null == true)
                                    {
                                        cout << "delete ; and add" << lines[i].firsts[j][count] << endl;
                                        lines[i].Output += lines[i].firsts[j][count];
                                    }
                                    break;
                                }
                                else if (lines[i].firsts[j][count] >= 'A' && lines[i].firsts[j][count] <= 'Z')
                                {
                                    cout << "judge in A-Z" << endl;
                                    if (searchDowns(lines[i].firsts[j][count]) != -1) //f前一項是null
                                    {
                                        check(lines[i]);
                                        cout << lines[searchDowns(lines[i].firsts[j][count - 1])].ID << " is " << lines[searchDowns(lines[i].firsts[j][count - 1])].null << endl;
                                        if (lines[searchDowns(lines[i].firsts[j][count - 1])].null == true)
                                        {
                                            if (lines[searchDowns(lines[i].firsts[j][count])].Output != ";")
                                            {
                                                cout << " output add " << lines[searchDowns(lines[i].firsts[j][count])].ID << "'s " << lines[searchDowns(lines[i].firsts[j][count])].Output << endl;
                                                lines[i].Output += lines[searchDowns(lines[i].firsts[j][count])].Output;
                                                if (lines[searchDowns(lines[i].firsts[j][count])].null == true)
                                                    lines[i].null = true;
                                            }
                                            if (lines[searchDowns(lines[i].firsts[j][count])].null == false)
                                            {

                                                deleteNull(i);
                                            }
                                        }
                                        else
                                        {
                                            cout << "set down " << lines[i].ID << endl;
                                            lines[i].down = true;
                                        }
                                    }
                                    else
                                    {
                                        notDown = 1;
                                        cout << lines[i].firsts[j][count] << " not down or not null" << endl;
                                    }
                                    if (lines[i].null == false)
                                        break;
                                    count++;
                                }
                                else
                                {
                                    cout << count << endl;
                                    break;
                                }
                            }
                            if (notDown == 0)
                                lines[i].firsts[j].erase();
                        }
                        else
                        {
                            cout << "not found" << endl;
                            cout << "now output " << lines[i].Output << endl;
                        }
                    }
                    else if (lines[i].firsts[j][count] == ';')
                    {
                        cout << "set null " << lines[i].ID << endl;
                        lines[i].Output += lines[i].firsts[j][count];
                        lines[i].null = true;
                    }
                    else
                    {
                        cout << "not above:" << lines[i].firsts[i][count] << endl;
                    }
                }
                cout << lines[i].ID << " output " << lines[i].Output << endl;
            }
            else
            {
                cout << lines[i].ID << " output " << lines[i].Output << endl;
                lines[i].down = true;
            }
        }
        sort();
        cout << "-----------one while---------" << endl;
    }
}
int searchDowns(char Terminal)
{
    for (int i = 0; i < lines.size(); i++)
    {
        if (lines[i].down == true)
            if (lines[i].ID == Terminal)
                return i;
    }
    return -1;
}
void nullOrNot()
{
    for (int i = 0; i < lines.size(); i++)
    {
        for (int j = 0; j < lines[i].firsts.size(); j++)
        {
            if (lines[i].firsts[j] == ";")
            {
                cout << "void set null: " << lines[i].ID << endl;
                lines[i].null = true;
            }
        }
    }
}
bool check(line x)
{
    bool down = true;
    int null = 0;
    for (int j = 0; j < x.firsts.size(); j++)
    {
        if (x.firsts[j] >= "A" && x.firsts[j] <= "Z")
            down = false;
    }
    if (down == true)
    {
        x.down = true;
    }
    return down;
}
void sort()
{
    for (int i = 0; i < lines.size(); i++)
    {
        sort(lines[i].firsts.begin(), lines[i].firsts.end());
        auto last = unique(lines[i].firsts.begin(), lines[i].firsts.end());
        lines[i].firsts.erase(last, lines[i].firsts.end());

        sort(lines[i].Output.begin(), lines[i].Output.end());
        auto endOfUni = unique(lines[i].Output.begin(), lines[i].Output.end());
        lines[i].Output.erase(endOfUni, lines[i].Output.end());
    }
}
void output()
{
    for (int i = 0; i < lines.size(); i++)
    {

        cout << lines[i].ID << " ";
        if (lines[i].firsts.size() != 0)
        {
            cout << lines[i].Output << endl;
        }
    }
    cout << "END_OF_FIRST" << endl;
}
void deleteNull(int i)
{
    string tmp = "";
    for (int j = 0; j < lines[i].Output.size(); j++)
    {
        if (lines[i].Output[j] != ';')
        {
            tmp += lines[i].Output[j];
        }
    }
    if (lines[i].null == true)
    {
        // cout << lines[i].ID << " still has null" << endl;
        tmp += ';';
    }
    lines[i].Output = tmp;
}
/*
S ABC
A a|Cb|;
B C|dA|;
C e|f|;
END_OF_GRAMMAR
*/
/*
E TA$
A aTA|;
T FB
B bFB|;
F cEd|i
END_OF_GRAMMAR

*/

//大寫判斷是否有;再加入後面