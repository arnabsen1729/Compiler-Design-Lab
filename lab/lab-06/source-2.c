int main()
{
    int a;
    int b = 12;
    int c = 10;
    int d = a + b + c;
    float f;
    b += 2;
    if (b >= c)
    {
        int e = 10;
        f = b / e;
    }
    else
    {
        f = b / c;
    }

    for (int i = 0; i < d; i++)
    {
        f += 1;
    }

    while (f > 0)
    {
        f -= 1;
    }

    callFunction(a, b);
}