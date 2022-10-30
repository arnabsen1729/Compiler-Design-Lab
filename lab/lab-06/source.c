int main()
{
    // a) Types of all the sub-expressions in an expression must be of the same type otherwise show a type error message.
    int a = 10;
    int b = 10;
    int c;
    // c = a + b + 20; // CORRECT

    float d;
    // d = a + b + 123; // ERROR

    //-------------------------------------//
    // b) Check whether or not the assignment statement is type correct. The type of left and right side of an assignment statement must be of similar type, if not similar show type-error with line number. Detect an illegal assignment.

    c = a + b + 20; // CORRECT
    // c = a + b + 20.0; // ERROR

    //-------------------------------------//
    // c) Expressions in conditional and while statement, type of all operands must be of the same type. For any type-error show the error message with line number.

    if (a > b) // CORRECT
    {
        // ...
    }

    // if (a > 20.0) // ERROR
    // {
    //     // ...
    // }

    // d) Identify memory errors, such as attempting to use an integer as a pointer

    // e) Type checking for statements like Array declarations.

    return 0;
}