#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#define USER_INPUT_NUMBER_BUFFER 7
#define USER_INPUT_OPERATION_BUFFER 10

double (*get_operation(char* lib_path, char* fun_name))(double, double) 
{
    void* handle;
    char* error;
    double (*function)(double, double);
    
    handle = dlopen(lib_path, RTLD_LAZY);
    if(!handle)
    {
        fputs(dlerror(), stderr);
        return NULL;
    }
    fprintf(stdout, "Loaded function %s from %s\n", fun_name, lib_path);

    function = dlsym(handle, fun_name);
    if ((error = dlerror()) != NULL)  
    {
        fputs(error, stderr);
        return NULL;
    }
    fprintf(stdout, "Function %s loaded\n", fun_name);

    return function;
}

int main()
{
    printf("Calculator\n");

    for(;;)
    {
        char input_number1[USER_INPUT_NUMBER_BUFFER];
        char input_number2[USER_INPUT_NUMBER_BUFFER];
        char input_operation[USER_INPUT_OPERATION_BUFFER];

        double num1;
        double num2;
        char operation;

        double (*function)(double, double);

        printf("Operations: +, -, *, /\n");
        printf("Input 'e' to exit.\n");

        printf("Operation: ");
        fgets(input_operation, sizeof(input_operation), stdin);
        operation = input_operation[0];
        if(operation == 'e') return 0;

        printf("First number: ");
        fgets(input_number1, sizeof(input_number1), stdin);
        num1 = atof(input_number1);

        printf("Second number: ");
        fgets(input_number2, sizeof(input_number2), stdin);
        num2 = atof(input_number2);


        switch(operation)
        {
            case '+':
                function = get_operation("add.so", "addition");
                break;
            case '-':
                function = get_operation("subtract.so", "subtraction");
                break;
            case '*':
                function = get_operation("multiply.so", "multiplication");
                break;
            case '/':
                function = get_operation("divide.so", "division");
                break;
            default:
                function = NULL;
        }

        printf("%lf %c %lf = ", num1, operation, num2);

        if(function == NULL)
        {
            printf("Error: unknown operation\n");
        }
        else
    {
            printf("%lf", function(num1, num2));
        }
        printf("\n");
    }
}
