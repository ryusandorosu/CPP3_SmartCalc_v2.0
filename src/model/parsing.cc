#include "backend.h"

namespace s21 {

Priority Model::GetPriority(OperatorType type) {
  Priority priority = Priority::DEFAULT;
  if (type >= OperatorType::SIN && type <= OperatorType::LOG) {
    priority = Priority::HIGHEST;
  } else if (type == OperatorType::SQRT || type == OperatorType::POW) {
    priority = Priority::HIGH;
  } else if (type == OperatorType::MULT || type == OperatorType::DIV ||
             type == OperatorType::MOD) {
    priority = Priority::MEDIUM;
  } else if (type == OperatorType::PLUS || type == OperatorType::MINUS ||
             type == OperatorType::UNMIN) {
    priority = Priority::LOW;
  } else if (type == OperatorType::BRACKET_LEFT) {
    priority = Priority::LOWEST;
  }
  return priority;
}

OperatorType Model::GetOperatorType(char str) {
  OperatorType type = OperatorType::DEFAULT;
  if (str == '+') {
    type = OperatorType::PLUS;
  } else if (str == '-') {
    type = OperatorType::MINUS;
  } else if (str == '*') {
    type = OperatorType::MULT;
  } else if (str == '/') {
    type = OperatorType::DIV;
  } else if (str == '%') {
    type = OperatorType::MOD;
  } else if (str == '^') {
    type = OperatorType::POW;
  } else if (str == '(') {
    type = OperatorType::BRACKET_LEFT;
  } else if (str == ')') {
    type = OperatorType::BRACKET_RIGHT;
  }
  return type;
}

int Model::FunctionParser(const std::string& expression, OperatorType& opType) {
  size_t i = 0;
  std::string func;
  while (std::isalpha(expression[i])) {
    func += expression[i];
    i++;
  }
  opType = GetFunctionType(func);
  return i;
}

OperatorType Model::GetFunctionType(const std::string& str) {
  OperatorType type = OperatorType::DEFAULT;
  if (str == "sin") {
    type = OperatorType::SIN;
  } else if (str == "cos") {
    type = OperatorType::COS;
  } else if (str == "tan") {
    type = OperatorType::TAN;
  } else if (str == "asin") {
    type = OperatorType::ASIN;
  } else if (str == "acos") {
    type = OperatorType::ACOS;
  } else if (str == "atan") {
    type = OperatorType::ATAN;
  } else if (str == "sqrt") {
    type = OperatorType::SQRT;
  } else if (str == "ln") {
    type = OperatorType::LN;
  } else if (str == "log") {
    type = OperatorType::LOG;
  } else if (str == "mod") {
    type = OperatorType::MOD;
  }
  return type;
}

int Model::GetNumber(const std::string& str, double& value) {
  std::string::size_type i = 0;
  std::string number_s;
  double number = 0;
  while (i < str.size() && (std::isdigit(str[i]) || str[i] == '.')) {
    number_s += str[i];
    i++;
  }
  if (sscanf(number_s.c_str(), "%lf", &number) == 1) {
    value = number;
  }
  return i;
}

int Model::GetDots(const std::string& str, int& counter) {
  std::string::size_type i = 0;
  counter = 0;
  while (i < str.size() && (std::isdigit(str[i]) || str[i] == '.')) {
    if (str[i] == '.') {
      counter++;
    }
    i++;
  }
  return i;
}

}  // namespace s21
