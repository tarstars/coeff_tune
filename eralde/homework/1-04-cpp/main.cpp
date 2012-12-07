// Работа с двоичным представлением. Шестнадцатеричные константы. Упаковка байтов в целое число.
//
// 1. Написать функцию печати двоичного представления числа
// 2. Написать функцию упаковки байтов в целое число
// 3. Написать функцию распаковки байтов из целого числа
// 4. Написать программу, демонстрирующую работу упаковки/распаковки

#include <climits>
#include <stdio.h>

typedef unsigned char   byte;
typedef unsigned int    uint;

// 1. Написать функцию печати двоичного представления числа
void
printAsBinary(int num, bool leading_zeros = false, bool split_by_byte = false){
    uint    mask        =   1 << 31;
    int     cycle_count =   0;
    bool    one_found   =   leading_zeros;
    

    while (mask > 0){
        one_found   =   one_found   ||  ((num & mask) == mask);
        
        if (one_found){
            printf("%d", (num & mask) == mask);
        }
        
        mask >>= 1;
        
        ++cycle_count;
        
        if (split_by_byte && (0 == cycle_count % 8)){
            printf(" ");
        }
    }   //  while
    
    printf("\n");
}   //  printAsBinary

// 2. Написать функцию упаковки байтов в целое число
int
pack(byte data[], int length)   throw(char*){
    int result  =   0;
    
    if (length > sizeof(int)/sizeof(byte)){
        throw   "Too long array passed";
    }
    
    --length;
    for (int i = length; i >= 0; --i){
        result  <<= sizeof(byte) * 8;   //  size in bits :-)
        result  |=  *(data + i); 
    }   //  for

    return  result;
}   //  pack

// 3. Написать функцию распаковки байтов из целого числа
byte*
unpack(int data){
    int     length  =   sizeof(int)/sizeof(byte);
    byte    *result =   new byte[length];
    uint    mask    =   255;
    
    for (int i = 0; i < length; ++i){
        *(result + i)   =   data & mask;
        data >>= sizeof(byte) * 8;  //  size in bits :-)
    }   //  for

    return  result;
}   //  pack
 
// 4. Написать программу, демонстрирующую работу упаковки/распаковки
int
main(void){

    byte test1[2]   =   {2, 7};
    byte test2[4]   =   {2, 4, 6, 9};
    byte test3[1]   =   {5};
    byte test4[4]   =   {1, 64, 255, 127};
    
    printf("\n>> print\n");
    
    printAsBinary(100);
    printAsBinary(100, true);
    printAsBinary(100, true, true);
    
    printf("\n>> pack\n");
    
    printAsBinary(pack(test1, 2), true, true);
    printAsBinary(pack(test2, 4), true, true);
    printAsBinary(pack(test3, 1), true, true);
    printAsBinary(pack(test4, 4), true, true);
    
    printf("\n>> unpack\n");
    
    printAsBinary(pack(unpack(pack(test1, 2)), 2), true, true);
    printAsBinary(pack(unpack(pack(test2, 4)), 4), true, true);
    printAsBinary(pack(unpack(pack(test3, 1)), 1), true, true);
    printAsBinary(pack(unpack(pack(test4, 4)), 4), true, true);
    
    return  0;
}   //  main