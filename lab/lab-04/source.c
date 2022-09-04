int myconst = 100;

int helloWorld() {
    printf("helo world");
    return 0;
}

int add(int n, int m) {
    return (n + m);
}

int main() {
    int a = 10;
    float b = (a + 10.0) * 100;
    char c = 'a';
    c = 'b';
    if (a == 10) {
        printf("a is 10");
    } else if (a > 10) {
        printf("a is greater than 10");
    } else {
        printf("a is less than 10");
    }

    for (int i = 10; i < 10; i++) {
        printf("Iterative statements");
    }

    int counter = 0;
    while (counter < 10) {
        printf("Iterative statements");
        counter = counter + 1;
    }

    helloWorld();
    int x = add(10, 20);
    return 0;
}