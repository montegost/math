#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cerrno>
#include <cstring>

namespace math {

inline bool addition( long firstValue, long secondValue, long* res )
{
    long result;
    if (__builtin_add_overflow(firstValue, secondValue, &result))
    {
        printf("Addition %ld + %ld makes overflow!\n", firstValue, secondValue);
        return false;
    }
    if (res == nullptr){
        printf("res must be not nullptr");
        return false;
    }
    
    *res = result;
    
    return true;
}

inline bool subtraction( long firstValue, long secondValue, long* res )
{
    long result;
    if (__builtin_sub_overflow(firstValue, secondValue, &result))
    {
        printf("Subtraction %ld - %ld makes overflow!\n", firstValue, secondValue);
        return false;
    }
    if (res == nullptr){
        printf("res must be not nullptr");
        return false;
    }
    
    *res = result;
    
    return true;
}

inline bool multiplication(long firstValue, long secondValue, long* res) {
    long result;
    if (__builtin_mul_overflow(firstValue, secondValue, &result))
    {
        printf("Multiplication %ld * %ld makes overflow!\n", firstValue, secondValue);
        return false;
    }
    if (res == nullptr){
        printf("res must be not nullptr");
        return false;
    }
    
    *res = result;
    
    return true;
}

inline bool division(long firstValue, long secondValue, long* res) {
    if (secondValue == 0) {
        printf("Division on 0\n");
        return false;  // Ошибка: деление на ноль
    }
    
    // Проверка переполнения: LONG_MIN / -1
    // Так как LONG_MIN = -9223372036854775808
    // А LONG_MAX = 9223372036854775807
    // -LONG_MIN не помещается в long
    if (firstValue == LONG_MIN && secondValue == -1) {
        printf("Division %ld / %ld makes overflow!\n", firstValue, secondValue);
        return false;
    }
    
    if (res == nullptr){
        printf("res must be not nullptr");
        return false;
    }
    
    *res = firstValue / secondValue;
    return true;
}

inline bool power( long base, long exponent, long* res) {
    if (res == nullptr){
        printf("res must be not nullptr");
        return false;
    }

    if (exponent == 0) {
        *res = 1;
        return true;
    }
    
    if (exponent < 0) {
        printf("exponent must be not negative");
        return false;
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

inline bool factorial(long firstValue, long* result) {
    if (firstValue < 0)
    {
        printf("factorial must be not negative. %ld\n", firstValue);
        return false;
    }
    
    if (firstValue == 0 || firstValue == 1) {
        *result = 1;
        return true;
    }
    
    long sub_result;
    if (!factorial(firstValue - 1, &sub_result)) {
        return false;  // Переполнение в рекурсивном вызове
    }
    
    if (__builtin_mul_overflow(sub_result, firstValue, result)) {
        printf("Factorial makes overflow!\n");
        return false;
    }
    
    return true;
}


} // namespace math
