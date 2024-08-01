#include "mbed.h"

InterruptIn button(PC_13);
BufferedSerial pc(USBTX, USBRX);
volatile bool print_flag = false;
int n;

int fib(int n) {
    if (n <= 1) {
        return n;
    } else {
        return fib(n - 1) + fib(n - 2);
    }
}

void printFib(int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d, ", fib(i));
    }
    printf("\n");
}

void button_pressed() {
    print_flag = true;
}

int main() {
    button.fall(&button_pressed);
    pc.set_baud(9600);

    while (1) {
        if (print_flag) {
            printFib(9);
            print_flag = false;
        }
        ThisThread::sleep_for(100ms);
    }
}
