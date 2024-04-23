#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

// Generate a random number between 0 and 255
uint8_t generate_random_byte() {
    return (uint8_t)rand();
}

// Generate a UUID version 4
void generate_uuid_v4(char uuid_str[37]) {
    // Set version (4) and variant (10xx)
    sprintf(uuid_str, "%02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X",
            generate_random_byte(), generate_random_byte(), generate_random_byte(), generate_random_byte(),
            generate_random_byte(), generate_random_byte(),
            0x40 | (generate_random_byte() & 0x0F), generate_random_byte() & 0x3F,
            generate_random_byte(), generate_random_byte(),
            generate_random_byte(), generate_random_byte(), generate_random_byte(), generate_random_byte(), generate_random_byte(), generate_random_byte());
}

int main() {
    // Initialize random number generator with current time
    srand((unsigned int)time(NULL));

    // Generate and store UUID in a character array
    char uuid_str[37]; // 36 characters + 1 for null terminator
    generate_uuid_v4(uuid_str);

    char fileName[37+6];
    sprintf(fileName, "B-%s.txt", uuid_str);
    // Print UUID
    printf("UUID: %s\n", uuid_str);
    printf("fileName : %s\n", fileName);

    return 0;
}
