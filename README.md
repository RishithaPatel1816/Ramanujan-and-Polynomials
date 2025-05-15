# Ramanujan-and-Polynomials
This C++ project implements polynomial operations using Divide and Conquer techniques, including multiplication, evaluation, differentiation
- Multiplication of polynomials
- Evaluation of polynomials
- Differentiation of polynomials

The operations are designed to work with:
- Integer coefficients
- Floating-point coefficients
- Complex number coefficients
- String coefficients (symbolic representation)

---
## Features

## 1. Multiply Polynomial

### Integer Coefficients
```cpp
multiply_poly_int({1, 2}, {3, 4}) 
// Output: {3, 10, 8}
```
### Floating Point Coefficients
```cpp
multiply_poly_float({1.5, 2.0}, {3.0, 4.0}) 
// Output: {4.5, 11.0, 8.0}
```
### Complex Coefficients
```cpp
multiply_poly_complex({{1,2}, {3,4}}, {{5,6}, {7,8}})
// Output: {(-7,16), (-13,50), (-11,52)}
```

## 2. Polynomial Evaluation
### Integer Coefficients
```cpp
evaluate_poly({2, 3, 1}, 2) 
// 2 + 3×2 + 1×2² = 12
```
### String Coefficients
```cpp
evaluate_poly_string({"a", "b", "c"}, 2) 
// Output: "4c + 2b + a"
```

## 3. Differentiate
```cpp
differentiate_poly({2, 3, 1}) 
// Derivative: {3, 2}  (for 2 + 3x + x²)
```

## Design And Approach
- All polynomial operations are implemented using divide-and-conquer techniques, including recursive multiplication.
- The code leverages templates and operator overloading (where needed) to support multiple data types.

## Limitations
- evaluate_poly_string is symbolic only and does not support variable substitution.
- Complex numbers are handled as std::pair<double, double> instead of native complex types









