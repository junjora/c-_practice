#include <iostream>
#include <iostream>
#include <stack>
#include <vector>
#include <iterator>
#include <algorithm>
#include <math.h>

//проверка на то, что элемент символ
bool is_symbol(char sym)
{
    switch(sym)
    {
        case '+': return true;
        case '-': return true;
        case '(': return true;
        case '^': return true;
        // ---------- //
        case '/': return true;
        case '*': return true;
    }
    return false;
}

//назначение средненго приоритета
bool is_mid_priority(char sym)
{
    switch(sym)
    {
        case '/': return true;
        case '*': return true;
    }
    return false;
}

//назначение низкого приоритета
bool is_low_priority(char sym)
{
    switch(sym)
    {
        case '-': return true;
        case '+': return true;
    }
    return false;
}

//назначение высокого приоритета
bool is_high_priority(char sym)
{
    return sym == '^' ? true : false;
}

int main() {
	
    std::string expression("2 ^ 3 * 2 + 1");  //инициализация выражения-строки
    std::stack<char> symbols;  		      //объявление стека, которое будет хранить символы
    std::vector<char> exit_string;   	      //объявление вектора, которое будет хранить выходную строку
    std::stack<double> result;		      //объявление стека
    double buffer = 0;
 	//проход по символам в выражении
    for(std::string::iterator it = expression.begin(); it != expression.end(); ++it)
    {
        if(::isdigit(*it)) exit_string.push_back(*it); // Если это цифра, то помещаем элемент в конец вектора
        else if(is_symbol(*it)) // Если это символ
        {
            if(is_low_priority(*it))
            {
                if(symbols.size() && !is_low_priority(symbols.top()))
                {
                    exit_string.push_back(symbols.top());
                    symbols.pop();
                }
                symbols.push(*it);
            }
            else if(is_mid_priority(*it))
            {
                
		if(symbols.size() && (is_mid_priority(symbols.top()) || is_high_priority(symbols.top())))
                {
                    exit_string.push_back(symbols.top());
                    symbols.pop();
                }
                symbols.push(*it);
            }
            else if(is_high_priority(*it))
            {
                symbols.push(*it);
            }
            else symbols.push(*it);
        }
        else if(*it == ')')
        {
            while(symbols.top() != '(')
            {
                std::cout << "\n1";
                exit_string.push_back(symbols.top());
                symbols.pop();
            }
            if(symbols.size()) { symbols.pop(); }
        }
    }
    while(symbols.size()) { exit_string.push_back(symbols.top()); symbols.pop(); }
    std::copy(exit_string.begin(), exit_string.end(), std::ostream_iterator<char>(std::cout, " "));
 
    for(std::vector<char>::iterator it = exit_string.begin(); it != exit_string.end(); ++it)
    {
        if(::isdigit(*it)) result.push(*it - '0');
        else
            switch(*it)
            {
            case '+': { buffer = result.top(); result.pop(); result.top() += buffer; break; }
            case '-': { buffer = result.top(); result.pop(); result.top() -= buffer; break; }
            case '*': { buffer = result.top(); result.pop(); result.top() *= buffer; break; }
            case '/': { buffer = result.top(); result.pop(); result.top() /= buffer; break; }
            case '^': { buffer = result.top(); result.pop(); result.top() = pow(result.top(), buffer); break; }
            }
    }
    std::cout << "\nANSWER: " << result.top();
    return 0;
}
