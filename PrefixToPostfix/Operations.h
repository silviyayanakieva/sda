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
#ifndef OPERATIONS
#define OPERATIONS

#include<string>

class Operation
{
public:
  Operation(char c, char op, char as);
  Operation();
  char getCode();
  char getOperation();
  char getAsoc();

private:
    char code, operation, asoc;

};

Operation::Operation(char c, char op, char as): code(c), operation(op), asoc(as){}

Operation::Operation(): code(' '), operation(' '), asoc(' '){}

char Operation::getCode()
{
    return code;
}
char Operation::getOperation()
{
    return operation;
}
char Operation::getAsoc()
{
    return asoc;
}

#endif // OPERATIONS

