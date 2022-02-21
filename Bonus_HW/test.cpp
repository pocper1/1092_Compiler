void followSet()
{
    // rule 1
    int find = 0;
    tokens[0].Output += '$';
    do
    {
        for (int i = 0; i < tokens.size(); i++) // tokens
        {
            bool allNull = false;
            cout << "- terminals: " << tokens[i].ID << endl;
            for (int j = 0; j < tokens[i].nonterminals.size(); j++) // tokens[i].nonterminals
            {
                cout << "-- rule:" << tokens[i].nonterminals[j] << endl;
                for (int k = 0; k < tokens[i].nonterminals[j].size(); k++) // find [A-Z]
                {
                    if (tokens[i].nonterminals[j][k] >= 'A' && tokens[i].nonterminals[j][k] <= 'Z')
                    {
                        int now_AZ = 0;
                        for (int l = 0; l < tokens.size(); l++)
                        {
                            if (tokens[l].ID == tokens[i].nonterminals[j][k])
                            {
                                now_AZ = l;
                            }
                        }
                        bool allNull = true;
                        cout << "--- find " << tokens[i].nonterminals[j][k] << " index: " << k << endl;
                        for (int l = k + 1; l < tokens[i].nonterminals[j].size(); l++) // run C after [A-Z]
                        {
                            for (int n = 0; n < tokens.size(); n++)
                            {
                                if (tokens[n].ID == tokens[i].nonterminals[j][l]) // find tokens[i] == C after [A-Z]
                                {
                                    string tmp = "";
                                    // get first()-;
                                    cout << getToken(tokens[i].nonterminals[j][l]).ID << "'s first " << getFirst_ID(getToken(tokens[i].nonterminals[j][l]).ID) << endl;
                                    for (int o = 0; o < getFirst_ID(getToken(tokens[i].nonterminals[j][l]).ID).size(); o++)
                                    {
                                        if (getFirst_ID(getToken(tokens[i].nonterminals[j][l]).ID)[o] != ';')
                                            tmp += getFirst_ID(getToken(tokens[i].nonterminals[j][l]).ID)[o];
                                    }
                                    if (tokens[n].Output.find(tmp) == string::npos)
                                    { //不存在的話再加
                                        cout << "---- add first(" << getToken(tokens[i].nonterminals[j][l]).ID << ") into follow(" << getToken(tokens[i].nonterminals[j][k]).ID << ")" << endl;
                                        cout << getToken(tokens[i].nonterminals[j][k]).ID << " + " << getFirst_ID(getToken(tokens[i].nonterminals[j][l]).ID) << endl;
                                        // cout << tmp << endl;
                                        tokens[now_AZ].Output += tmp;
                                        // tokens[n].Output += tmp;
                                    }
                                }
                                else if (tokens[i].nonterminals[j][l] >= 'a' && tokens[i].nonterminals[j][l] <= 'z')
                                {
                                    cout << "---- add char " << tokens[i].nonterminals[j][l] << " into follow(" << getToken(tokens[i].nonterminals[j][k]).ID << ")" << endl;
                                    cout << getToken(tokens[i].nonterminals[j][k]).ID << " + " << tokens[i].nonterminals[j][l] << endl;
                                    tokens[now_AZ].Output += tokens[i].nonterminals[j][l];
                                    // cout << "---- break" << endl;
                                    allNull = false;
                                    break;
                                }
                            }
                            cout << "----- " << getToken(tokens[i].nonterminals[j][k]).ID << " follow: " << getToken(tokens[i].nonterminals[j][k]).Output << endl;

                            // check all null

                            for (int n = 0; n < tokens.size(); n++)
                            {
                                if (tokens[n].ID == tokens[i].nonterminals[j][l]) // find tokens[i] == C after [A-Z]
                                {
                                    // getToken(tokens[n])
                                }
                            }
                            if (getFirst_ID(tokens[i].nonterminals[j][l])[0] != ';')
                            {
                                allNull = false;
                            }
                        }
                        if (allNull)
                        {
                            cout << "all null add follow" << endl;
                            cout << "follow(" << tokens[i].ID << "): " << tokens[i].Output << " add to follow(" << tokens[i].nonterminals[j][k] << ")" << endl;
                            for (int n = 0; n < tokens.size(); n++)
                            {
                                if (tokens[n].ID == tokens[i].nonterminals[j][k])
                                {
                                    tokens[n].Output += tokens[i].Output;
                                }
                            }
                        }
                    }
                }
            }
        }
    } while (checkChange());
}