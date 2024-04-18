#ifndef SRC_MODEL_H_
#define SRC_MODEL_H_

#include <cctype>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

namespace s21 {

enum class OperatorType {
  DEFAULT = 0,
  VALUE = 1,
  PLUS = 2,
  MINUS = 3,
  UNMIN = 4,
  MULT = 5,
  DIV = 6,
  POW = 7,
  MOD = 8,
  SIN = 9,
  COS = 10,
  TAN = 11,
  ASIN = 12,
  ACOS = 13,
  ATAN = 14,
  LN = 15,
  LOG = 16,
  SQRT = 17,
  BRACKET_LEFT = 18,
  BRACKET_RIGHT = 19,
};

enum class Priority {
  DEFAULT = 0,
  LOWEST = 1,
  LOW = 2,
  MEDIUM = 3,
  HIGH = 4,
  HIGHEST = 5,
};

class Model {
 public:
  /* validation */
  int Validation(const std::string& str);

  /* rpn */
  double ConvertToRpnAndCalculate(const std::string& expr);

 private:
  /* parsing */
  Priority GetPriority(OperatorType type);
  OperatorType GetOperatorType(char str);
  int FunctionParser(const std::string& expression, OperatorType& opType);
  OperatorType GetFunctionType(const std::string& str);
  int GetNumber(const std::string& str, double& value);
  int GetDots(const std::string& str, int& counter);

  /* validation */
  int CheckOnOperator(char ch);
  int CheckOnOperatorOrDot(char ch);
  int CheckOnOperatorOrBracket(char ch);
  int CheckOnOperatorExceptUnary(char ch);
  int CheckOnOperatorExceptUnaryOrDot(char ch);
  int BracketsValidation(const std::string& str);
  int PointValidation(const std::string& str, size_t j, size_t* out_counter,
                      int& dots);
  int FunctionValidation(const std::string& str, size_t k, size_t* out_counter,
                         OperatorType& type);
  size_t max_string_size = 255;

  /* calculation */
  double UnaryOperation(double number, OperatorType op);
  double BinaryOperation(double right, double left, OperatorType op);
  double Calculation(
      const std::vector<std::pair<double, OperatorType> >& output_stack);
};

}  // namespace s21

#endif  // SRC_MODEL_H_