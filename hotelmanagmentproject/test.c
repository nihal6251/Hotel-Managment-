#include <stdio.h> // for printf
#include <stdlib.h> // for itoa

int main() {
    int num = 123;
    char str[20]; // Assuming a maximum length for the string
    
    // Using itoa
    itoa(num, str, 10); // 10 means base 10 (decimal)

    printf("The integer converted to string: %s\n", str);

    return 0;
}
