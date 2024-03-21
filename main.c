#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main() {
    FILE *ptr = fopen("C:\\Users\\LENOVO\\Desktop\\odev.txt", "r");
    while (feof(ptr) == 0) {
        char number_str[50];
        fscanf(ptr, "%s", number_str);
        int check = 0;
        int eol = 0;
        for (int i = 0; i < 50; i++) {
            if (number_str[i] == 0) {
                eol= i - 1;
                break;
            }
            else if (number_str[i] == '.') {
                printf("number is float\n");
                int temp_arr2[50];
                for (int h = 0; h < 50; h++) {
                    temp_arr2[h] = -1;
                }

                for (int i = 0; i < 50; i++) {
                    if (number_str[i] == '.') {
                        int num1 = 0;
                        int sign = 0;
                        int power = 1;
                        for (int j = i - 1; j >= 0; j--) {
                            if (j == 0 && number_str[j] == '-') {
                                sign = 1;
                            }
                            else {
                                num1 += (number_str[j] - 48) * power;
                                power *= 10;
                            }
                        }

                        int temp_arr3[50];
                        int k = 0;

                        while (num1 != 0) {
                            temp_arr3[k] = num1 % 2;
                            num1 /= 2;
                            k++;
                        }

                        for (int l = k - 1; l >= 0; l--) {
                            temp_arr2[(k - 1) - l] = temp_arr3[l];
                        }
                    }
                }
                check = 1;
                break;
            }
            else if (number_str[i] == 'u') {
                unsigned short unsigned_num = 0;
                int last_char = i - 1;
                int power = 1;

                while (last_char >= 0) {
                    int digit = number_str[last_char] - '0';
                    unsigned_num = unsigned_num + (digit * power);
                    power = power * 10;
                    last_char = last_char - 1;
                }

                printf("number is unsigned and value is %u\n", unsigned_num);
                check = 1;
                break;
            }
        }
        if (check==0) {
            short decimal_number = 0;
            int power = 1;
            for(int j = eol; j >= 0; j--){
                decimal_number = decimal_number + (number_str[j]-'0') * power;
                power = power * 10;
            }

            printf("number is decimal and the value is %d\n", decimal_number);
        }
    }
}








