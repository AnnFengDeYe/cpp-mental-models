int check_and_count(int value) {
    int count = 0;
    if (value % 2 == 0) {
        count++;
    }

    return count;
}

int main() {

    // context ...

    check_and_count(1);

    // context ...

    check_and_count(2);
}