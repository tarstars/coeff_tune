// Контейнер vector, циклы:
//  
// 1. Для заданного числа n вывести n строчек треугольника Паскаля.
// 2. Вывести остатки от деления на 2 элементов из первых n строчек треугольника Паскаля
// 3. Для заданного n распечатать таблицу nxn, значение p,q элемента которой определяется правилом: 0, если p&q равно нулю, 1 если p&q не равно нулю
// 4. Сравнить результаты 5.2 и 5.3. При сравнении брать достаточно большое n (>20), нули выводить пробелами, единицы - *. Объяснить результат.
// 5. Пункт 2, но для большого n. n > 200
// 6. Как называется узор из пункта 4 ?
// 7. Какое количество памяти достаточно для решения этой задачи?

#include <vector>
#include <stdio.h>

using ::std::vector;

typedef int (*Fint2int)(int); //  Int -> Int
typedef int (*Fint2int2int)(int, int); //  Int -> Int -> Int

inline  int id(int x){  return  x;  }       //  f x = x
inline  int mod2(int x){  return  x % 2;  } //  f x = x `mod` 2
inline  int mod2Asterisk(int x){  return  (int)((0 == (x % 2)) ? ' ' : '*');  }

inline  int bitAndIsZero(int x, int y){ return  (int)(0 == (x & y)); }
inline  int bitAndIsZeroAsterisk(int x, int y){ return  (int)((0 == (x & y)) ? ' ' : '*'); }

//  Prints first N lines of the Pascal triangle modifying each element with a passed Fint2int function (int -> int).
void
printPascalTriangle(int num_lines, Fint2int mutator = &id, const char* printf_string="%3d ") throw(char*){
  if (num_lines < 1){
    throw "Invalid number of lines passed. Must be positive!";
  }
  
  vector<int> previous_line(num_lines);
  vector<int> current_line(num_lines);
  
  printf("\n");
  
  for (int i = 1; i < num_lines; ++i){
    previous_line[i]  = 0;
  }
  
  for (int i = 0; i < num_lines; ++i){
    current_line[0] = 1;
    current_line[i] = 1;
    
    for (int j = 1; j < i; ++j){
      current_line[j] = previous_line[j] + previous_line[j - 1];
    }
    
    for (int j = 0; j <= i; ++j){
      printf(printf_string, mutator(current_line[j]));
      previous_line[j]  = current_line[j];
    }
    
    printf("\n");
  }
} //  printPascalTriangle


//  Prints N x N square matrix in which (i, j)-th element is calculated
//  via passed Fint2int (int -> int -> int) function.
void
printSquareMatrix(int N, Fint2int2int calculate_element, const char* printf_string="%3d "){
  
  printf("\n");
  
  for (int i = 0; i < N; ++i){
    for (int j = 0; j < N; ++j){
    
      printf(printf_string, calculate_element(i, j));
    }
    
    printf("\n");
  }
  
  printf("\n");
} //  printSquareMatrix

int
main(void){

  // 1. Для заданного числа n вывести n строчек треугольника Паскаля.
  printPascalTriangle(15);
  
  // 2. Вывести остатки от деления на 2 элементов из первых n строчек треугольника Паскаля
  printPascalTriangle(15, &mod2);
  
  // 3. Для заданного n распечатать таблицу nxn, значение p,q элемента которой определяется правилом: 0, если p&q равно нулю, 1 если p&q не равно нулю
  printSquareMatrix(15, &bitAndIsZero);
  
  // 4. Сравнить результаты 5.2 и 5.3. При сравнении брать достаточно большое n (>20), нули выводить пробелами, единицы - *. Объяснить результат.
  printSquareMatrix(25, &bitAndIsZeroAsterisk, "%c ");
  printPascalTriangle(25, &mod2Asterisk, "%c ");
  
  return  0;
} //  main
