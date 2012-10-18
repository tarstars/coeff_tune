// Возврат из функции нескольких значений:
//  
// 1. Написать функцию enc, которая на входе принимает число n, возвращает остатки от деления на 7, 11, 13
// 2. Написать функцию dec, которая принимает три числа 0<=a<7, 0<=b<11, 0<=c<13 и выдаёт число 0<=n<1001,
//    которое даёт остатки a, b, c при делении на 7, 11, 13
// 3. Корректно ли поставлена задача в задании 2 ?
// 4. Написать функции add(+), mul(*), subs(-), которые принимают на входе два набора a1, b1, c1 и a2, b2, c2
//    и выполняют соответствующие операции. Например add должна вернуть (a1 + a2, b1 + b2, c1 + c2).
//    Часть функций реализовать через ссылки, часть - через указатели.
// 5. Написать программу, запрашивающую со стандартного потока n1, n2 и код операции: 0 - add, 1 - mul, 2 - subs,
//    кодирующую n1 в (a1, b1, c1) , n2 в (a2, b2, c2), выполняющую соответствующую операцию над тройками
//    и декодирующую результат обратно.
// 6. Объяснить результат пункта 5
// 7. Насколько эффективно можно реализовать пункт 2 ?

#include <iostream>
#include <tuple>

using ::std::ostream;
using ::std::cout;
using ::std::endl;

using ::std::tuple;
using ::std::get;

typedef tuple<int, int, int>  tupleInt3;

//  Pretty printing
ostream&  operator<<(ostream& os, const tupleInt3& data) {
  cout << "tuple<int, int, int>: "
       << get<0>(data) << " "
       << get<1>(data) << " "
       << get<2>(data) << endl;
       
  return os;
}

// 1. Написать функцию enc, которая на входе принимает число n, возвращает остатки от деления на 7, 11, 13
tupleInt3 enc(int num) {
  return  tupleInt3(num % 7, num % 11, num % 13);
} //  enc

// 2. Написать функцию dec, которая принимает три числа 0<=a<7, 0<=b<11, 0<=c<13 и выдаёт число 0<=n<1001,
//    которое даёт остатки a, b, c при делении на 7, 11, 13
int dec(tupleInt3 remainders) throw(const char*){
  if (tupleInt3(0, 0, 0) == remainders) {
    return  0;
  }

  //  7 * 11 * 13 = 1001
  int rem13 = get<2>(remainders);
  int rem11 = get<1>(remainders);
  int rem7 = get<0>(remainders);
  
  if (0 > rem7 or 6 < rem7
        or 0 > rem11 or 10 < rem11
          or 0 > rem13 or 12 < rem13) {
    throw "Invalid remainders tuple passed";
  }
  
  int num = rem13;
  
  while (num < 1001){
    
    if (rem11 == num % 11 and rem7 == num % 7) {
      return  num;
    }
  
    num += 13;
  }
  
  return -1;
} //  dec

// 7. Насколько эффективно можно реализовать пункт 2 ?
int decFast(tupleInt3 remainders) throw(const char*){
  if (tupleInt3(0, 0, 0) == remainders) {
    return  0;
  }
  
  int rem13 = get<2>(remainders);
  int rem11 = get<1>(remainders);
  int rem7 = get<0>(remainders);
  
  if (0 > rem7 or 6 < rem7
        or 0 > rem11 or 10 < rem11
          or 0 > rem13 or 12 < rem13) {
    throw "Invalid remainders tuple passed";
  }
  
  //  7, 11, 13 are coprime
  int N = 7 * 11 * 13; //  == 1001
  
  int n7 = (11 * 13); //  3
  int n11 = (7 * 13); //  3
  int n13 = (7 * 11); //  12
  
  int y7 = 5; //  m7 * n7 = 1 (mod 7)
  int y11 = 4; //  ...
  int y13 = 12; //  ...
  
  return ((rem7 * n7 * y7) + (rem11 * n11 * y11) + (rem13 * n13 * y13)) % N;
} //  decFast

int main(void) {
  cout << enc(21);
  cout << dec(enc(21)) << endl << endl;
  
  cout << dec(tupleInt3(1, 2, 3)) << endl;
  cout << dec(tupleInt3(3, 2, 1)) << endl;
  cout << dec(tupleInt3(1, 1, 0)) << endl << endl;
  
  cout << decFast(tupleInt3(1, 2, 3)) << endl;
  cout << enc(decFast(tupleInt3(1, 2, 3)));
  cout << decFast(tupleInt3(3, 2, 1)) << endl;
  cout << enc(decFast(tupleInt3(3, 2, 1)));
  cout << decFast(tupleInt3(1, 1, 0)) << endl;
  cout << enc(decFast(tupleInt3(1, 1, 0))) << endl;
  
  return  0;
} //  main
