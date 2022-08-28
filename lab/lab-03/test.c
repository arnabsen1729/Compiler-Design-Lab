int main() {
    int a = 10;
    float b = -1.23;
    char c = 80;

    if (a == b) {
        b = 0;
    } else {
        b = 1;
    }

    for (int i = 0; i < 10; i += 1) {
        if (i == 0) {
            b = 0;
        } else {
            b = 1;
        }
    }

    int d = 0;
    while (d < 10) {
        d += 1;
        b += 1;
    }

    char s = 'a';
    char p[] = "hello world";

    return 0;
}