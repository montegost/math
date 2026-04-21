#include <climits>
#include <stdexcept>

namespace math
{

inline long addition( long firstValue, long secondValue )
{
     long result;
     if( __builtin_add_overflow( firstValue, secondValue, &result ) )
     {
          throw std::overflow_error( "Addition overflows" );
     }

     return result;
}

inline long subtraction( long firstValue, long secondValue )
{
     long result;
     if( __builtin_sub_overflow( firstValue, secondValue, &result ) )
     {
          throw std::overflow_error( "Subtraction overflows" );
     }

     return result;
}

inline long multiplication( long firstValue, long secondValue )
{
     long result;
     if( __builtin_mul_overflow( firstValue, secondValue, &result ) )
     {
          throw std::overflow_error( "Multiplication overflows" );
     }

     return result;
}

inline long division( long firstValue, long secondValue )
{
     if( secondValue == 0 )
     {
          throw std::invalid_argument( "Division on 0" );
     }

     // Проверка переполнения: LONG_MIN / -1
     // Так как LONG_MIN = -9223372036854775808
     // А LONG_MAX = 9223372036854775807
     // -LONG_MIN не помещается в long
     if( firstValue == LONG_MIN && secondValue == -1 )
     {
          throw std::overflow_error( "Division overflows" );
     }

     return firstValue / secondValue;
}

inline long power( long base, long exponent )
{
     if( exponent == 0 )
     {
          return 1;
     }

     if( exponent < 0 )
     {
          throw std::invalid_argument( "exponent must be not negative" );
     }

     long result = 1;

     for( long i = 0; i < exponent; i++ )
     {
          if( __builtin_mul_overflow( result, base, &result ) )
          {
               throw std::overflow_error( "Power overflows" );
          }
     }

     return result;
}

inline long factorial( long firstValue )
{
     if( firstValue < 0 )
     {
          throw std::invalid_argument( "Factorial argument must be non-negative" );
     }

     if( firstValue == 0 || firstValue == 1 )
     {
          return 1;
     }

     long sub_result = factorial( firstValue - 1 );
     long result;

     if( __builtin_mul_overflow( sub_result, firstValue, &result ) )
     {
          throw std::overflow_error( "Factorial overflows" );
     }

     return result;
}

}// namespace math
