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

char* binaryToHexadecimalPattern(char* array,int arraySize,char* defaultArray){

    char* result = (char*) malloc(arraySize * sizeof(char));
    snprintf(result,3,defaultArray);

    int value = 0;
    int limitIndex = 0;
    int lengthOfResult = arraySize-2;

    while(limitIndex <= lengthOfResult){

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

    result[limitIndex] = '\0';

    return result;
}

int findCharArraySize(char* array){

    int counter = 0;

    while(array[counter] != '\0'){
        counter++;
    }

    return counter;
}

char* binaryToHexadecimal(char* array){

    if(findCharArraySize(array) == 8){

        return binaryToHexadecimalPattern(array,3,"00");

    }else if(findCharArraySize(array) == 16){

        return binaryToHexadecimalPattern(array,5,"0000");

    }else if(findCharArraySize(array) == 24){

        return binaryToHexadecimalPattern(array,7,"000000");

    }else if(findCharArraySize(array) == 32){

        return binaryToHexadecimalPattern(array,9,"00000000");

    }

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
    FILE *output = fopen("output.txt", "w");
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
                int temp_arr2[16];
                int sign = 0;
                for (int h = 0; h < 15; h++) {
                    temp_arr2[h] = -1;
                }

                for (int i = 0; i < 50; i++) {
                    if (number_str[i] == '.') {
                        int num_before_point = 0;


                        int power = 1;
                        for (int j = i - 1; j >= 0; j--) {
                            if (j == 0 && number_str[j] == '-') {
                                sign = 1;
                            }
                            else {
                                num_before_point += (number_str[j] - 48) * power;
                                power *= 10;
                            }
                        }

                        double num_after_point = 0;
                        double power2 = 0.1;

                        for(int m= i + 1;m<50;m++){
                            if (number_str[m] == '\0') {
                                break;
                            }
                            else {
                                num_after_point += (number_str[m] - 48) * power2;
                                power2 /= 10;
                            }
                        }


                        int temp_arr3[16];
                        int k = 0;

                        if (num_before_point == 0) {
                            temp_arr3[0] = 0;
                        }
                        else {
                            while (num_before_point != 0) {
                                if (k == 16) {
                                    break;
                                }
                                temp_arr3[k] = num_before_point % 2;
                                num_before_point /= 2;
                                k++;
                            }
                        }


                        for (int l = k - 1; l >= 0; l--) {
                            temp_arr2[k - 1 - l] = temp_arr3[l];
                        }

                        for(int n=k;n<16;n++){
                            num_after_point*=2;
                            if(num_after_point>=1){
                                temp_arr2[n]=1;
                                num_after_point=num_after_point-1;
                            }
                            else{
                                temp_arr2[n]=0;
                            }
                        }

                        int exponent = k - 1;
                        int round_arr[17];

                        for (int i = 0; i < 15; i++) {
                            round_arr[i + 1] = temp_arr2[i];
                        }

                        if((round_arr[14+1]==0)&&(round_arr[14+2]==0)) {
                            for(int q = 1; q <= 14; q++) {
                                temp_arr2[q - 1] = round_arr[q];
                            }
                            temp_arr2[14] = 0;
                            temp_arr2[15] = 0;
                        }
                        else if((round_arr[14+1]==1)&&(round_arr[14+2]==1)){
                            for (int q = 14; q >= 0; q--) {
                                if (round_arr[q] == 1) {
                                    round_arr[q] = 0;
                                }
                                else if (round_arr[q] == 0) {
                                    round_arr[q] = 1;
                                    break;
                                }
                            }

                            if (round_arr[0] == 1) {
                                for(int q = 0; q <= 14 - 1; q++) {
                                    temp_arr2[q] = round_arr[q];
                                }
                                temp_arr2[13] = 0;
                                temp_arr2[14] = 0;
                                temp_arr2[15] = 0;
                                exponent++;
                            }
                            else if (round_arr[0] == 0) {
                                for(int q = 1; q <= 14; q++) {
                                    temp_arr2[q - 1] = round_arr[q];
                                }
                                temp_arr2[14] = 0;
                                temp_arr2[15] = 0;
                            }

                        }
                        else if((round_arr[14+1]==0)&&(round_arr[14+2]==1)){
                            for(int q = 1; q <= 14; q++) {
                                temp_arr2[q - 1] = round_arr[q];
                            }
                            temp_arr2[14] = 0;
                            temp_arr2[15] = 0;
                        }
                        else if((round_arr[14+1]==1)&&(round_arr[14+2]==0)) {
                            if (round_arr[14] == 0) {
                                for (int q = 1; q <= 14; q++) {
                                    temp_arr2[q - 1] = round_arr[q];
                                }
                                temp_arr2[14] = 0;
                                temp_arr2[15] = 0;
                            } else if (round_arr[14] == 1) {
                                for (int q = 14; q >= 0; q--) {
                                    if (round_arr[q] == 1) {
                                        round_arr[q] = 0;
                                    } else if (round_arr[q] == 0) {
                                        round_arr[q] = 1;
                                        break;
                                    }
                                }

                                if (round_arr[0] == 1) {
                                    for (int q = 0; q <= 14 - 1; q++) {
                                        temp_arr2[q] = round_arr[q];
                                    }
                                    temp_arr2[13] = 0;
                                    temp_arr2[14] = 0;
                                    temp_arr2[15] = 0;
                                    exponent++;
                                } else if (round_arr[0] == 0) {
                                    for (int q = 1; q <= 14; q++) {
                                        temp_arr2[q - 1] = round_arr[q];
                                    }
                                    temp_arr2[14] = 0;
                                    temp_arr2[15] = 0;
                                }
                            }
                        }



                        int fraction_size = 0;
                        int exponent_size = 0;

                        char arg = *argv[3];

                        switch ((int)(arg)) {
                            case 49 :
                                fraction_size = 4;
                                exponent_size = 3;
                                break;
                            case 50:
                                fraction_size = 7;
                                exponent_size = 8;
                                break;
                            case 51:
                                fraction_size = 13;
                                exponent_size = 10;
                                break;
                            case 52:
                                fraction_size = 19;
                                exponent_size = 12;
                                break;
                        }

                        int special_size = fraction_size + exponent_size;

                        if (fraction_size == 19) {
                            fraction_size = 13;
                        }

                        int final_float[fraction_size + exponent_size + 1];

                        double abs_number = num_before_point + num_after_point;

                        if (abs_number < (1-(pow(2,exponent_size-1)-1)) && abs_number > -(1-(pow(2,exponent_size-1)-1))) {// denormalized

                            final_float[0] = sign;

                            int fraction_arr1[fraction_size + 3];
                            fraction_arr1[0] = 0;

                            for (int q = 0; q <= fraction_size + 1; q++) {
                                fraction_arr1[q + 1] = temp_arr2[q];
                            }
                            int fraction_bits[fraction_size];

                            if((fraction_arr1[fraction_size+1]==0)&&(fraction_arr1[fraction_size+2]==0)) {
                                for(int q = 1; q <= fraction_size; q++) {
                                    fraction_bits[q - 1] = fraction_arr1[q];
                                }

                            }
                            else if((fraction_arr1[fraction_size+1]==1)&&(fraction_arr1[fraction_size+2]==1)){
                                for (int q = fraction_size; q >= 0; q--) {
                                    if (fraction_arr1[q] == 1) {
                                        fraction_arr1[q] = 0;
                                    }
                                    else if (fraction_arr1[q] == 0) {
                                        fraction_arr1[q] = 1;
                                        break;
                                    }
                                }

                                if (fraction_arr1[0] == 1) {
                                    for(int q = 0; q <= fraction_size - 1; q++) {
                                        fraction_bits[q] = fraction_arr1[q];
                                    }
                                }
                                else if (fraction_arr1[0] == 0) {
                                    for(int q = 1; q <= fraction_size; q++) {
                                        fraction_bits[q - 1] = fraction_arr1[q];
                                    }
                                }

                            }
                            else if((fraction_arr1[fraction_size+1]==0)&&(fraction_arr1[fraction_size+2]==1)){
                                for(int q = 1; q <= fraction_size; q++) {
                                    fraction_bits[q - 1] = fraction_arr1[q];
                                }
                            }
                            else if((fraction_arr1[fraction_size+1]==1)&&(fraction_arr1[fraction_size+2]==0)){
                                if (fraction_arr1[fraction_size] == 0) {
                                    for(int q = 1; q <= fraction_size; q++) {
                                        fraction_bits[q - 1] = fraction_arr1[q];
                                    }
                                }
                                else if (fraction_arr1[fraction_size] == 1) {
                                    for (int q = fraction_size; q >= 0; q--) {
                                        if (fraction_arr1[q] == 1) {
                                            fraction_arr1[q] = 0;
                                        }
                                        else if (fraction_arr1[q] == 0) {
                                            fraction_arr1[q] = 1;
                                            break;
                                        }
                                    }

                                    if (fraction_arr1[0] == 1) {
                                        for(int q = 0; q <= fraction_size - 1; q++) {
                                            fraction_bits[q] = fraction_arr1[q];
                                        }
                                        exponent++;
                                    }
                                    else if (fraction_arr1[0] == 0) {
                                        for(int q = 1; q <= fraction_size; q++) {
                                            fraction_bits[q - 1] = fraction_arr1[q];
                                        }
                                    }
                                }

                            }

                            final_float[0] = sign;

                            int exp_value = 0;

                            for (int i = exponent_size; i >= 1; i--) {
                                final_float[i] = exp_value % 2;
                                exp_value /= 2;
                            }

                            for (int i = exponent_size + 1; i <= special_size + 1; i++) {
                                final_float[i] = fraction_bits[i - exponent_size - 1];
                            }

                            char final_char_arr[special_size + 2];

                            for (int i = 0; i <= special_size + 1; i++) {
                                if (i == special_size + 1) {
                                    final_char_arr[i] = '\0';
                                }
                                else {
                                    final_char_arr[i] = (char)(final_float[i] + 48);
                                }
                            }

                            char* final_array = (char*) malloc((special_size + 2) * sizeof(char));
                            snprintf(final_array,(special_size + 2), final_char_arr);



                            char* print_array = binaryToHexadecimal(final_array);

                            char arg2 = *argv[2];

                            switch ((int)(arg2)) {
                                case 108:
                                    for(int i=(special_size + 1)/4-1;i>=0;i--){
                                        if(i%2==0){
                                            fprintf(output, "%c", print_array[i]);
                                            fprintf(output, "%c ", print_array[i + 1]);
                                            printf("%c",print_array[i]);
                                            printf("%c ",print_array[i + 1]);
                                        }
                                    }
                                    break;
                                case 98:
                                    for (int i = 0; i < (special_size + 1) / 4; i++) {
                                        if (i % 2 == 1) {
                                            fprintf(output, "%c ", print_array[i]);
                                            printf("%c ", print_array[i]);
                                        }
                                        else {
                                            fprintf(output, "%c", print_array[i]);
                                            printf("%c", print_array[i]);
                                        }
                                    }
                                    break;
                            }
                        }
                        else { // normalized


                            int fraction_arr1[fraction_size + 3];
                            fraction_arr1[0] = 0;

                            for (int q = 1; q <= fraction_size + 2; q++) {
                                fraction_arr1[q] = temp_arr2[q];
                            }
                            int fraction_bits[fraction_size];

                            if((fraction_arr1[fraction_size+1]==0)&&(fraction_arr1[fraction_size+2]==0)) {
                                for(int q = 1; q <= fraction_size; q++) {
                                    fraction_bits[q - 1] = fraction_arr1[q];
                                }

                            }
                            else if((fraction_arr1[fraction_size+1]==1)&&(fraction_arr1[fraction_size+2]==1)){
                                for (int q = fraction_size; q >= 0; q--) {
                                    if (fraction_arr1[q] == 1) {
                                        fraction_arr1[q] = 0;
                                    }
                                    else if (fraction_arr1[q] == 0) {
                                        fraction_arr1[q] = 1;
                                        break;
                                    }
                                }

                                if (fraction_arr1[0] == 1) {
                                    for(int q = 0; q <= fraction_size - 1; q++) {
                                        fraction_bits[q] = fraction_arr1[q];
                                    }
                                }
                                else if (fraction_arr1[0] == 0) {
                                    for(int q = 1; q <= fraction_size; q++) {
                                        fraction_bits[q - 1] = fraction_arr1[q];
                                    }
                                }

                            }
                            else if((fraction_arr1[fraction_size+1]==0)&&(fraction_arr1[fraction_size+2]==1)){
                                for(int q = 1; q <= fraction_size; q++) {
                                    fraction_bits[q - 1] = fraction_arr1[q];
                                }
                            }
                            else if((fraction_arr1[fraction_size+1]==1)&&(fraction_arr1[fraction_size+2]==0)){
                                if (fraction_arr1[fraction_size] == 0) {
                                    for(int q = 1; q <= fraction_size; q++) {
                                        fraction_bits[q - 1] = fraction_arr1[q];
                                    }
                                }
                                else if (fraction_arr1[fraction_size] == 1) {
                                    for (int q = fraction_size; q >= 0; q--) {
                                        if (fraction_arr1[q] == 1) {
                                            fraction_arr1[q] = 0;
                                        }
                                        else if (fraction_arr1[q] == 0) {
                                            fraction_arr1[q] = 1;
                                            break;
                                        }
                                    }

                                    if (fraction_arr1[0] == 1) {
                                        for(int q = 0; q <= fraction_size - 1; q++) {
                                            fraction_bits[q] = fraction_arr1[q];
                                        }
                                        exponent++;
                                    }
                                    else if (fraction_arr1[0] == 0) {
                                        for(int q = 1; q <= fraction_size; q++) {
                                            fraction_bits[q - 1] = fraction_arr1[q];
                                        }
                                    }
                                }

                            }

                            final_float[0] = sign;

                            int exp_value = exponent + mathPow(2,exponent_size -  1) - 1;

                            for (int i = exponent_size; i >= 1; i--) {
                                final_float[i] = exp_value % 2;
                                exp_value /= 2;
                            }

                            for (int i = exponent_size + 1; i <= special_size + 1; i++) {
                                final_float[i] = fraction_bits[i - exponent_size - 1];
                            }

                            char final_char_arr[special_size + 2];

                            for (int i = 0; i <= special_size + 1; i++) {
                                if (i == special_size + 1) {
                                    final_char_arr[i] = '\0';
                                }
                                else {
                                    final_char_arr[i] = (char)(final_float[i] + 48);
                                }
                            }

                            char* final_array = (char*) malloc((special_size + 2) * sizeof(char));
                            snprintf(final_array,(special_size + 2), final_char_arr);



                            char* print_array = binaryToHexadecimal(final_array);

                            // big endian

                            char arg2 = *argv[2];

                            switch ((int)(arg2)) {
                                case 108:
                                    for(int i=(special_size + 1)/4-1;i>=0;i--){
                                        if(i%2==0){
                                            fprintf(output, "%c", print_array[i]);
                                            fprintf(output, "%c ", print_array[i + 1]);
                                            printf("%c",print_array[i]);
                                            printf("%c ",print_array[i + 1]);
                                        }
                                    }
                                    break;
                                case 98:
                                    for (int i = 0; i < (special_size + 1) / 4; i++) {
                                        if (i % 2 == 1) {
                                            fprintf(output, "%c ", print_array[i]);
                                            printf("%c ", print_array[i]);
                                        }
                                        else {
                                            fprintf(output, "%c", print_array[i]);
                                            printf("%c", print_array[i]);
                                        }
                                    }
                                    break;
                            }


                        }

                        break;


                    }
                }
                fprintf(output, "\n");
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

                char arg2 = *argv[2];

                switch ((int)(arg2)) {
                    case 108:
                        for(int i=3;i>=0;i--){
                            if(i%2==0){
                                fprintf(output, "%c", hex_value[i]);
                                fprintf(output, "%c ", hex_value[i + 1]);
                                printf("%c",hex_value[i]);
                                printf("%c ",hex_value[i + 1]);
                            }
                        }
                        break;
                    case 98:
                        for (int i = 0; i < 4; i++) {
                            if (i % 2 == 1) {
                                fprintf(output, "%c ", hex_value[i]);
                                printf("%c ", hex_value[i]);
                            }
                            else {
                                fprintf(output, "%c", hex_value[i]);
                                printf("%c", hex_value[i]);
                            }
                        }
                        break;
                }
                fprintf(output, "\n");
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

            if (number_str[0] == '-') {
                decimal_number *= -1;
            }

            char *hex_value = binaryToHexadecimal(signedIntToBinary(decimal_number));

            char arg2 = *argv[2];

            switch ((int)(arg2)) {
                case 108:
                    for(int i=3;i>=0;i--){
                        if(i%2==0){
                            fprintf(output, "%c", hex_value[i]);
                            fprintf(output, "%c ", hex_value[i + 1]);
                            printf("%c",hex_value[i]);
                            printf("%c ",hex_value[i + 1]);
                        }
                    }
                    break;
                case 98:
                    for (int i = 0; i < 4; i++) {
                        if (i % 2 == 1) {
                            fprintf(output, "%c ", hex_value[i]);
                            printf("%c ", hex_value[i]);
                        }
                        else {
                            fprintf(output, "%c", hex_value[i]);
                            printf("%c", hex_value[i]);
                        }
                    }
                    break;
            }
            fprintf(output, "\n");
            printf("\n");
        }
    }
}








