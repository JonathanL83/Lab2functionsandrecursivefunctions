#include "mbed.h"

// Global variables
InterruptIn button(PC_13);  // Define the button pin as InterruptIn
BufferedSerial pc(USBTX, USBRX);    // Define BufferedSerial for communication
volatile bool print_flag = false;   // Flag to indicate button press


void printFibonacciLoop(int n) {
    int a = 0, b = 1, next;

    for (int i = 0; i < n; ++i) {
        if (i <= 1)
            next = i;
        else {
            next = a + b;
            a = b;
            b = next;
        }
        printf("%d, ", next);
    }
    printf("\n");
}

void button_pressed() {
    print_flag = true; 
}

int main() {
    // Attach the interrupt handler to the button press event
    button.fall(&button_pressed);
    pc.set_baud(9600);

    //int n;
    //printf("Enter the number of terms: ");
    //scanf("%d", &n);

    while (1) {
        if (print_flag) {
            printFibonacciLoop(9);
            print_flag = false; 
        }
        ThisThread::sleep_for(100ms); 
    }
}