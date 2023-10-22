#include <bitset>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

const int firstColumnWidth = 20;

// Display a 16-bit value in binary format with spaces.
void display16BitBinaryWithSpaces(uint16_t value);

// Display a 17-bit value in binary format with spaces.
void display17BitBinaryWithSpaces(uint32_t value);

void performChecksum(std::vector<uint16_t> &buf);

int main() {
    // Enter your numbers here.
    std::vector<uint16_t> data = {
        0b0111'1111'0010'0000,
        0b1000'1011'0011'0011,
        0b1100'0000'1111'1101,
    };

    performChecksum(data);

    return 0;
}

void display16BitBinaryWithSpaces(uint16_t value) {
    std::bitset<16> binary(value);

    for (int i = 15; i >= 0; i--) {
        std::cout << binary[i];
        if (i % 4 == 0) {
            std::cout << " ";
        }
    }
}

void display17BitBinaryWithSpaces(uint32_t value) {
    std::bitset<32> binary(value);

    for (int i = 16; i >= 0; i--) {
        std::cout << binary[i];
        if (i % 4 == 0 && i != 0) {
            std::cout << " ";
        }
    }
}

void performChecksum(std::vector<uint16_t> &buf) {
    uint32_t sum = 0;

    int currentIndex = 0;

    for (const uint16_t &value : buf) {
        std::cout << std::setw(firstColumnWidth) << std::to_string(currentIndex + 1) + ":"
                  << "   ";
        display16BitBinaryWithSpaces(value);
        std::cout << std::endl;

        sum += value;

        // Check if there is a carry.
        if (sum & 0xFFFF0000) {
            std::cout << std::setw(firstColumnWidth) << "Sum:"
                      << " ";
            display17BitBinaryWithSpaces(sum);
            std::cout << std::endl;
            std::cout << std::setw(firstColumnWidth) << "Incr for the carry:"
                      << "+                    1" << std::endl;

            // Wrap around.
            sum &= 0xFFFF;
            sum++;

            std::cout << std::setw(firstColumnWidth) << " "
                      << "   ";
            display16BitBinaryWithSpaces(sum);
            std::cout << std::endl;
        }
        else {
            // No need to show the sum for the first number.
            if (currentIndex > 0) {
                std::cout << std::setw(firstColumnWidth) << "Sum:"
                          << "   ";
                display16BitBinaryWithSpaces(sum);
                std::cout << std::endl;
            }
        }

        currentIndex++;
    }

    std::cout << std::setw(firstColumnWidth + 23) << std::setfill('-') << " " << std::setfill(' ') << std::endl;

    uint16_t result = static_cast<uint16_t>(~sum & 0xFFFF);

    // Display the final result.
    std::cout << std::setw(firstColumnWidth) << "1's comp:"
              << "   ";
    display16BitBinaryWithSpaces(result);
    std::cout << std::endl;
}
