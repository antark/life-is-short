/**
*   author: bjarne stroustrup
*   modified by: 陆仁贾 (http://www.lrj.name)
*   date: 03/12/2013 02/24/2014
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

// ========== 错误处理 ===========
inline void error(const string& s)
{
    throw runtime_error(s);
}

inline void error(const string& s, const string& s2)
{
    error(s + s2);
}

inline void error(const string& s, int i)
{
    ostringstream os;
    os << s <<": " << i;
    error(os.str());
}

// 阶乘函数 factorial
int factorial(int n)
{
    if(n < 0)   return 1;
    int f = 1;
    for(int i = 1; i <= n; ++i)
        f *= i;
    return f;
}

// ========== 一些常量, 和 token 分割符不冲突 ===========
const char let = 'L';
const char quit = 'Q';
const char help = 'H';
const char newline = '\n';
const char print = ';';
const char number = '8';
const char name = 'a';
const string prompt = "> ";
const string result = "= ";

// ========== 语法: Token/Primary/Term/Expression ===========
struct Token {
    char kind;
    double value;
    string name;
    Token(char ch) :kind(ch), value(0), name("") { }
    Token(char ch, double val) :kind(ch), value(val), name("") { }
    Token(char ch, string str) :kind(ch), value(0), name(str) { }
};

class Token_stream{
    bool full;  // 是否有一个缓存的 token ? 
    Token buffer;
public:
    Token_stream() :full(0), buffer(0) { }

    Token get();
    void unget(Token t) { buffer = t; full = true; }    // unget token

    void ignore(char);
};

Token Token_stream::get()
{
    if(full) { full = false; return buffer; }    // 直接使用缓存的 token
    char ch;
    while(cin.get(ch) && isspace(ch) && ch != '\n')    // 跳过空白字符(不包括换行符)
        ;

    switch(ch) {
    case '(':
    case ')':
    case '+':
    case '-':
    case '*':
    case '/':
    case '!':
    case ';':
    case '=':
    case '\n':
        return Token(ch);    // 分隔符
    case '.':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        cin.unget();
        double val;
        cin >> val;
        return Token(number, val);   // 找到一个 number
    default:
        if(isalpha(ch)){  // 命令 or 常量名
            string s;
            s += ch;
            while(cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
            cin.unget();
            if(s == "let") return Token(let);    // 定义常量
            if(s == "quit") return Token(quit);    // 退出
            if(s == "help") return Token(help);    // 帮助
            return Token(name, s);
        }
        error("Bad token"); // oh shit !
    }
}

void Token_stream::ignore(char c)
{
    if(full && c == buffer.kind){
        full = false;
        return;
    }
    full = false;

    char ch;
    while (cin >> ch)
        if (ch == c) return;
}

struct Variable {
    string name;
    double value;
    Variable(string n, double v) :name(n), value(v) { }
};

vector<Variable> names;

double get_value(string s)
{
    int n = names.size();
    for(int i = 0; i < n; ++i)
        if (names[i].name == s) return names[i].value;
    error("get: undefined name ", s);
}

void set_value(string s, double d)
{
    int n = names.size();
    for (int i = 0; i < n; ++i)
        if (names[i].name == s) {
            names[i].value = d;
            return;
        }
    error("set: undefined name ", s);
}

bool is_declared(string s)
{
    for (int i = 0; i<names.size(); ++i)
        if (names[i].name == s) return true;
    return false;
}

Token_stream ts;    // Token input stream

double expression();

// Primary = Number | (Expression) | -Primary | !Primary
double primary()
{
    Token t = ts.get();
    switch (t.kind) {
    case '(':{
        double d = expression();
        t = ts.get();
        if (t.kind != ')') error("')' expected");
        return d;
    }
    case '-':
        return -primary();
    case '!':{
        int n = primary();
        return factorial(n);
    }
    case number:
        return t.value;
    case name:
        return get_value(t.name);
    default:
        ts.unget(t);
        error("primary expected");
    }
}

// Term = Primary | Primary * Primary | Primary / Primary
double term()
{
    double left = primary();
    while(true){
        Token t = ts.get();
        switch(t.kind) {
        case '*':
            left *= primary();
            break;
        case '/': {
            double d = primary();
            if (d == 0) error("divide by zero");
            left /= d;
            break;
        }
        default:
            ts.unget(t);
            return left;
        }
    }
}

// Expression = Term | Term + Term | Term - Term
double expression()
{
    double left = term();
    while(true){
        Token t = ts.get();
        switch(t.kind) {
        case '+':
            left += term();
            break;
        case '-':
            left -= term();
            break;
        default:
            ts.unget(t);
            return left;
        }
    }
}

// 常量定义类似于 abc = 3.14
double declaration()
{
    Token t = ts.get();
    if (t.kind != 'a') error("name expected in declaration");
    string name = t.name;
    if (is_declared(name)) error(name, " declared twice");
    Token t2 = ts.get();
    if (t2.kind != '=') error("= missing in declaration of " , name);
    double d = expression();
    names.push_back(Variable(name, d));
    return d;
}

double statement()
{
    Token t = ts.get();
    switch(t.kind) {
    case let:    // 常量定义
        return declaration();
	default:   // 计算
        ts.unget(t);
        return expression();
    }
}

void clean_up_mess()
{
    ts.ignore(print);
}

// 显示帮助信息
void show_tips()
{
    cout << "\nusage : + - * / \n\n> 1+2\n> 3*4;\n> 5/6; 3.14*2*5.0;\n";
    cout << "\nusage : () \n\n> (1+2)*(3.4+5.6);\n";
    cout << "\nusage : - !\n\n> -2+10; !4; !10;\n";
    cout << "\nusage : let expression \n\n> let a = 10;\n> a+2;\n> let e = 1 + 1/!1 + 1/!2 + 1/!3 + 1/!4 + 1/!5 + 1/!6 + 1/!7 + 1/!8 + 1/!9 + 1/!10;\n";
    cout << "\nusage : built-in cmd\n\n> help;\n> quit;\n" << endl;
}

void calculate()
{
    cout << prompt;
    while(true) try{
        do{
            Token t = ts.get();
            while(t.kind == print) t = ts.get();    // 跳过所有的 print 符
            if(t.kind == quit) return;
            if(t.kind == newline) break;
            if(t.kind == help){ show_tips(); continue;};
            ts.unget(t);
            cout << result << statement() << endl;
        }while(true);
        cout << prompt;
    }catch(runtime_error& e) {
        cerr << e.what() << endl;
        clean_up_mess();
    }
}

int main(int argc, char *argv[])
try{
    calculate();
    return 0;
}catch(exception& e){
    cerr << "exception: " << e.what() << endl;
    char c;
    while(cin >> c && c != ';') ;
    return 1;
}catch(...){
    cerr << "exception\n";
    char c;
    while(cin >>c && c != ';');
    return 2;
}
