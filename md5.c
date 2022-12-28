#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*MD5 ALGORITHM
ASSUMES A LITTLE ENDIAN MACHINE
CANNOT HANDLE MORE THAN 448 BITS OF INPUT
OUTPUT IS IN LITTLE ENDIAN*/

#define MAX_BITS 512
#define MAX_TEXT 55

unsigned int aa = 0x67452301;
unsigned int bb = 0xefcdab89;
unsigned int cc = 0x98badcfe;
unsigned int dd = 0x10325476;


unsigned int kValues[] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

unsigned int sValues[] = {7, 12, 17, 22,  7, 12, 17, 22,  7, 
    12, 17, 22,  7, 12, 17, 22 , 5,  9, 14, 20,  5,  9, 
    14, 20,  5,  9, 14, 20, 5, 9, 14, 20 , 4, 11, 
    16, 23,  4, 11, 16, 23, 4, 11, 16, 23,  4, 11,
    16, 23 , 6, 10, 15, 21, 6, 10, 15, 21,  6, 10, 
    15, 21,  6, 10, 15, 21 };

unsigned int getText(char *,int);
int main(){

    char input[MAX_TEXT];
    unsigned int length = getText(input,MAX_TEXT);

    unsigned int *text = (int *)calloc((MAX_BITS)/8,1);
    memcpy(text,input,length);


    //1 in hexadecimal
    //the remaining padding bits are zero
    //find a way of fixing this
    //i.e avoid using strcat so as to avoid casting pointers
    //this could get confusing 
    unsigned int one_hex = 0x80;
    strcat((char *)text,(char *)&one_hex);

    //copy into the last 64 bits the length of the input
    unsigned int length_in_hex = length * 8;
    memcpy((text+14),&length_in_hex,4);
    unsigned int closing_zeros = 0;
    memcpy(text+16,&closing_zeros,4);

    unsigned int a = aa;
    unsigned int b = bb;
    unsigned int c = cc;
    unsigned int d = dd;

    unsigned int g;
    unsigned int function;
    int operation;

    for(operation = 0;operation < 64;operation++){

        if(operation < 16){
            function = ((b & c) | ((~b) & d));
            g = operation;

        }else if(operation >= 16 && operation < 32){
            function = ((b & d) | (c & (~d)));
            g = ((5 * operation) + 1) % 16;

        }else if(operation >= 32 && operation < 48){
            function = (b ^ c ^ d);
            g = ((3 * operation) + 5) % 16;

        }else if(operation >= 48 && operation < 64){
            function = c ^ (b | (~d));
            g = (7 * operation) % 16;
        }

        function = (a + function + kValues[operation] + text[g]);
        
        unsigned int leftRotate = (function << sValues[operation]) | (function >> (32 - sValues[operation]));
        a = d;
        d = c;
        c = b;
        b = (b + leftRotate);

    }
    
    a = a + aa; 
    b = b + bb;
    c = c + cc;
    d = d + dd;

    printf("\n");
    printf("%02x",a);
    printf("%02x",b);
    printf("%02x",c);
    printf("%02x\n",d);

    free(text);

    return 0;
}

unsigned int getText(char *input,int max){

    printf("Enter string to be hashed : \n");
    char *start = input;
    for(;(input < (start+max)) && ((*input = getchar()) != EOF);input++)
        ;
    
    *input = '\0';
    return (input - start);
}

