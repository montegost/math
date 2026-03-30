#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cerrno>
#include <cstring>

namespace math {

bool addition( long a, long b, long* res )
{
    long result;
    if (__builtin_add_overflow(a, b, &result))
    {
        printf("Addition %ld + %ld makes overflow!\n", a, b);
        return false;
    }
    if (res == nullptr){
        printf("res must be not nullptr");
        return false;
    }
    
    *res = result;
    
    return true;
}

bool subtraction( long a, long b, long* res )
{
    long result;
    if (__builtin_sub_overflow(a, b, &result))
    {
        printf("Subtraction %ld - %ld makes overflow!\n", a, b);
        return false;
    }
    if (res == nullptr){
        printf("res must be not nullptr");
        return false;
    }
    
    *res = result;
    
    return true;
}

bool multiplication(long a, long b, long* res) {
    long result;
    if (__builtin_mul_overflow(a, b, &result))
    {
        printf("Multiplication %ld * %ld makes overflow!\n", a, b);
        return false;
    }
    if (res == nullptr){
        printf("res must be not nullptr");
        return false;
    }
    
    *res = result;
    
    return true;
}

bool division(long a, long b, long* res) {
    if (b == 0) {
        printf("Division on 0\n");
        return false;  // Ошибка: деление на ноль
    }
    
    // Проверка переполнения: LONG_MIN / -1
    // Так как LONG_MIN = -9223372036854775808
    // А LONG_MAX = 9223372036854775807
    // -LONG_MIN не помещается в long
    if (a == LONG_MIN && b == -1) {
        printf("Division %ld / %ld makes overflow!\n", a, b);
        return false;
    }
    
    if (res == nullptr){
        printf("res must be not nullptr");
        return false;
    }
    
    *res = a / b;
    return true;
}

bool power( long base, long exponent, long* res) {
    if (res == nullptr){
        printf("res must be not nullptr");
        return false;
    }
    
    if (exponent <= 0) {
        printf("exponent must be not negative");
        return false;
    }
    
    if (exponent == 0) {
        *res = 1;
        return true;
    }
    
    long result = 1;
    
    for (unsigned int i = 0; i < exponent; i++) {
        if (__builtin_mul_overflow(result, base, &result))
        {
            printf("Power %ld ^ %ld makes overflow!\n", base, exponent);
            return false;
        }
    }
    

    *res = result;
    
    return true;
}

bool factorial(long a, long* result) {
    if (a < 0)
    {
        printf("factorial must be not negative. %ld\n", a);
        return false;
    }
    
    if (a == 0 || a == 1) {
        *result = 1;
        return true;
    }
    
    long sub_result;
    if (!factorial(a - 1, &sub_result)) {
        return false;  // Переполнение в рекурсивном вызове
    }
    
    if (__builtin_mul_overflow(sub_result, a, result)) {
        printf("Factorial makes overflow!\n");
        return false;
    }
    
    return true;
}


} // namespace math
