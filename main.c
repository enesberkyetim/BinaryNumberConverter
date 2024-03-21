#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char* unsignedIntToBinary(unsigned number){
    char* result = (char*) malloc(17 * sizeof(char));
    snprintf(result, 17, "0000000000000000");

    int limitIndex = 15;

    int temp = number;
    int digit;

    while(temp > 0){

        digit = temp % 2;
        temp = temp / 2;

        // assign the changed bit
        if(digit == 1){
            result[limitIndex] = '1';
        }
        //result[limitIndex] = digit + '0';
        limitIndex--;
        //printf("%d\n",temp);
    }

    return result;
}

int mathPow(int base, int power){

    int result = 1;

    int i;
    for(i = 0; i < power;i++){
        result *= base;
    }

    return result;
}

char hexValue(int value){

    if(value == 15){
        return 'F';
    }else if(value == 14){
        return 'E';
    }else if(value == 13){
        return 'D';
    }else if(value == 12){
        return 'C';
    }else if(value == 11){
        return 'B';
    }else if(value == 10){
        return 'A';
    }else if(value <= 9 && value >= 0){
        return value + '0';
    }else{
        return 0;
    }

}

char* binaryToHexadecimal(char* array){

    char* result = (char*) malloc(5 * sizeof(char));
    snprintf(result,5,"0000");

    int value = 0;
    int limitIndex = 0;
    while(limitIndex <= 3){

        int innerLimitIndex = 0;
        while(innerLimitIndex <=3){
            value += ((array[4*limitIndex + innerLimitIndex] - 48)* mathPow(2,3-innerLimitIndex));
            innerLimitIndex++;
        }
        //printf("%d\n",value);
        result[limitIndex] = hexValue(value);
        value = 0;

        limitIndex++;
    }

    return result;
}

char* signedIntToBinary(signed int number){
    if(number >= 0){
        return unsignedIntToBinary((unsigned int) number);
    }else{

        char* result = (char*) malloc(17 * sizeof(char));
        int temp = number * -1;

        snprintf(result,17,signedIntToBinary(temp));

        int counter = 0;
        int i;

        for(i = 15; i >= 0; i--){

            if(result[i] == '1' && counter == 0){
                counter = 1;
                continue;
            }

            if(counter == 1){
                if(result[i] == '0'){
                    result[i] = '1';
                }else{
                    result[i] = '0';
                }
            }

        }

        return result;
    }

}



int main(int argc, char *argv[]) {
    //Argument kısmına file'ın path'ini ilk argument olarak girin
    FILE *ptr = fopen(argv[1], "r");
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

                        double num2 = 0;
                        double power2 = 0.1;

                        for(int m= i + 1;m<50;m++){
                            if (number_str[m] == '\0') {
                                break;
                            }
                            else {
                                num2 += (number_str[m] - 48) * power2;
                                power2 /= 10;
                            }
                        }


                        int temp_arr3[50];
                        int k = 0;

                        if (num1 == 0) {
                            temp_arr3[0] = 0;
                            //k=1; bir sıkıntı çıkarsa icabına bakarız
                        }
                        else {
                            while (num1 != 0) {
                                temp_arr3[k] = num1 % 2;
                                num1 /= 2;
                                k++;
                            }
                        }


                        for (int l = k - 1; l >= 0; l--) {
                            temp_arr2[k - 1 - l] = temp_arr3[l];
                        }

                        for(int n=k;n<50;n++){
                            num2*=2;
                            if(num2>=1){
                                temp_arr2[n]=1;
                                num2=num2-1;
                            }
                            else{
                                temp_arr2[n]=0;
                            }

                        }

                        for (int p = 0; p < 50; p++) {
                            printf("%d", temp_arr2[p]);
                        }
                        break;
                    }
                }
                printf("\n");
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

                char *hex_value = binaryToHexadecimal(unsignedIntToBinary(unsigned_num));

                for (int i = 0; i < 4; i++) {
                    if (i == 1) {
                        printf("%c ", hex_value[i]);
                    }
                    else {
                        printf("%c", hex_value[i]);
                    }
                }
                printf("\n");
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

            char *hex_value = binaryToHexadecimal(signedIntToBinary(decimal_number));

            for (int i = 0; i < 4; i++) {
                if (i == 1) {
                    printf("%c ", hex_value[i]);
                }
                else {
                    printf("%c", hex_value[i]);
                }
            }
            printf("\n");
        }
    }
}








