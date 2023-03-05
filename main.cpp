#include <iostream>
#include<stack>
#include<string>

using namespace std;

bool isOperand(char x){
    if(x=='+'||x=='-'||x=='*'||x=='/'||x=='^')
        return 1;
    return 0;
}

int prec(char x){
    switch(x){
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
    }
}

string conv(string inf){
    string res;
    stack<char>s;
    for(int i = 0; i < inf.length(); i++){
        if(!isOperand(inf[i]) && inf[i] != ')' && inf[i] != '('){
            res += inf[i];
        }
        else if(inf[i] == '('){
            s.push(inf[i]);
            }
        else if(inf[i] == ')'){
            while(s.top()!='('){
                res+=s.top();
                s.pop();
            }
            s.pop();
        }
        else if(isOperand(inf[i])){
            if(s.empty() || prec(inf[i]) >= prec(s.top())){
                s.push(inf[i]);
            }
            else{
                while(!s.empty() && prec(inf[i]) < prec(s.top())){
                    if(s.top() != '('){
                        res += s.top();
                        s.pop();
                    }
                    s.push(inf[i]);
                }
            }
        }
    }
    while(!s.empty()){
        res += s.top();
        s.pop();
    }
    return res;
}

int evaluatePostFix(string x){
    stack<int>s;
    int oper1, oper2, res;
    for(int i = 0; i < x.length(); i++){
        if(isOperand(x[i])){
            oper2 = s.top();
            s.pop();
            oper1 = s.top();
            s.pop();
            switch(x[i]){
                case '+':
                    res = oper1 + oper2;
                    break;
                case '-':
                    res = oper1 - oper2;
                    break;
                case '*':
                    res = oper1 * oper2;
                    break;
                case '/':
                    res = oper1 / oper2;
                    break;
            }
            s.push(res);
        }
        else{
            s.push(x[i] - '0');
        }
    }
    return s.top();
}

int main(){
    string x;
    cout << "enter an equation: ";
    cin >> x;
    cout << evaluatePostFix(conv(x)) << endl;
    return 0;
}
