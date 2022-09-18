int myconst;

int main() {
    int myvar = 1;
    myconst = 20;

    {
        int a = 10;
    }

    a = 20;

    return 0;
}