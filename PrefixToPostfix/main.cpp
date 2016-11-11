/**
 *
 * Solution to homework task
 * Data Structures Course
 * Faculty of Mathematics and Informatics of Sofia University
 * Winter semester 2016/2017
 *
 * @author Silviya Yanakieva
 * @idnumber 61881
 * @task 1
 * @compiler GCC
 *
 */

#include "Stack.h"
#include "Operations.h"
#include "DynamicArray.h"
#include <iostream>
#include<fstream>
#include<sstream>
#include<iomanip>
#include <string>
#include <cstring>
using namespace std;

//helper functions
bool isOperand(char c);
bool isOperator(char c, DynamicArray<Operation*> *op);
char findOperator(char c, DynamicArray<Operation*> *op);

int main(int argc, char* argv[])
{
    //operators are held in a dynamic array
    DynamicArray<Operation*> *oper = new DynamicArray<Operation*>;

   //load prefix notation
    std::string workstr;
    ifstream prefix_notation;
    prefix_notation.open(argv[1]);
   // prefix_notation.open("prefix.txt");
    getline(prefix_notation,workstr,'\n');

    prefix_notation.close();

    //helper variables
    int operator_counter = 0, number_counter = 0; // if numbers aren't more than operators, the prefix isn't correct
    char sign;
    size_t sizeofw = workstr.length();
    bool flag = true; // true until problem is found

    //result from calculating
    double result;

    //calculation is made with stack<double> while reversing the string
    Stack<double> res(10);

    // numbers and intermediate results are held in stack
    Stack<std::string> st(sizeofw);

    //load operators
    ifstream oper_loader;
    //oper_loader.open("operators.txt");
    oper_loader.open(argv[2]);
    while(oper_loader.eof() != true)
    {
        char code,sign,asoc;
         while(oper_loader>>code>>sign>>asoc)
        {
            oper->append(new Operation(code,sign,asoc));
        }

    }
    oper_loader.close();


/**
prefix to postfix:
idea for the algorithm took from http://qa.geeksforgeeks.org/6252/it-possible-convert-prefix-expression-postfix-expression
1.Scan each character of the input from right to left.

2.If the character is operand then push it onto the stack.

3.If the character if an operator, then pop two operands from stack and concatenate them as (operand1, operand2, operator).

4.Push this result onto the stack.

5.After parsing the complete input, if still any elements exit in the stack, pop them out and concatenate.
*/

for(int cnt = sizeofw-1; cnt >= 0; cnt--)
{
    if(workstr.at(cnt) == 32) // spaces are being ignored
    {
        continue;
    }
    if (isOperator( workstr.at(cnt), oper)) // operator is found
    {
        if( st.getSize() < 2)               //if the stack is empty, the prefix notation isn't correct
           {
                flag = false; break;        //flag marks problem; break the loop
           }
        else
        {
            operator_counter++;
            std::string op1,op2,temp;
            op1 = st.Top(); st.Pop();
            op2 = st.Top(); st.Pop();
            temp = op1 + " " + op2 + " " + workstr.at(cnt);
            st.Push(temp);

        sign = findOperator(workstr.at(cnt),oper);  //calculations are done here

        double num1 = res.Top(); res.Pop();
        double num2 = res.Top(); res.Pop();
        double tempnum;

        switch(sign)
        {
            case '+': tempnum = num1 + num2; res.Push(tempnum); break;
            case '-': tempnum = num1 - num2; res.Push(tempnum); break;
            case '*': tempnum = num1 * num2; res.Push(tempnum); break;
            case '/':
                {
                    if (num2 == 0)
                    {
                        throw std::overflow_error("Division by zero");
                    }
                    else
                    {
                        tempnum = num1 / num2;
                        res.Push(tempnum);}
                    } break;
                }
        }


    }
    else if( isOperand(workstr.at(cnt)) )           //a number is found
    {
        number_counter++;
        if(workstr.at(cnt-1) == ' ')           //if it's one digit - it's pushed in stack
        {
            std::string temp = "";
            temp=workstr.at(cnt);
            st.Push(temp);

            double num = atof(temp.c_str());    //its value is pushed into the calculation stack
            res.Push(num);
        }
        else
        {
            int from = cnt, to=cnt;         //if its a multi digit number
            std::string temp = "";
            while(workstr.at(cnt-1) != 32)  //find the beginning and the end
               {
                   to--;
                   cnt--;
                }
            for(int i = to; i <= from; i++)    //take the substring from the beginning to the end
            {
                temp+=workstr.at(i);
            }
            st.Push(temp);                     //push it in the calculation stack

            double num = atof(temp.c_str());    //push its numerical value in the calculation stack
            res.Push(num);
            cnt = to;
        }
    }
}

if (number_counter > operator_counter  && flag) //if the prefix notation was ok and no problems were found
{
    //print postfix notation
    std::string postfix="";
    while(!st.isEmpty())
    {
        postfix+=st.Top();st.Pop();
    }
    result = res.Top();

   cout<<postfix<<endl;
   cout<<fixed<<std::setprecision(5)<<result<<endl;

}

else if(!flag)                                  //error message if problem is found
    {
        cout<<"Error - Invalid prefix notation"<<endl;
    }

delete  oper;
return 0;
}

bool isOperand(char c)
{
    if(c >= 48 && c <= 57)
        return true;
    else return false;
}
bool isOperator(char c, DynamicArray<Operation*> *op)
{
    for(int i = 0; i<= ((op->getSize())-1); i++ )
        {
            if(c == op->get(i)->getCode() )
            {return true;}
        }
    return false;
}

char findOperator(char c, DynamicArray<Operation*> *op)
{
    for(int i = 0; i<= ((op->getSize())-1); i++ )
        {
            if(c == op->get(i)->getCode() )
            {return op->get(i)->getOperation() ;}
        }
}
