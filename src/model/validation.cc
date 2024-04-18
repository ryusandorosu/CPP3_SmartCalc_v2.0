#include "backend.h"

namespace s21 {

int Model::Validation(const std::string& str) {
  int error = 0, dots = 0;
  OperatorType type = OperatorType::DEFAULT;
  size_t i = 0, j = 0, k = 0;
  size_t size = str.size();

  if (BracketsValidation(str)) {
    error = 1;
  }
  while (i < size) {
    if (size > max_string_size) {
      error = 1;
    }
    if (std::isalpha(str[i]) && str[i] != 'x' && i + 1 == size) {
      error = 1;
    }
    if (str[i] == '(' && (CheckOnOperatorExceptUnary(str[i + 1]))) {
      error = 1;
    }
    if (str[i] == ')' && (std::isalnum(str[i + 1]))) {
      error = 1;
    }
    if (CheckOnOperatorOrDot(str[i]) && CheckOnOperatorOrDot(str[i + 1])) {
      error = 1;
    }
    if (str[i] == '.' &&
        (!(std::isdigit(str[i - 1])) || !(std::isdigit(str[i + 1])))) {
      error = 1;
    }
    if ((str[0] == '+' || str[0] == '-') && str[1] == '\0') {
      error = 1;
    }
    if (CheckOnOperatorExceptUnaryOrDot(str[0])) {
      error = 1;
    }
    if (str[i] == 'x' &&
        (std::isalnum(str[i - 1]) || std::isalnum(str[i + 1]))) {
      error = 1;
    }
    if (str[i] == 'd' && CheckOnOperatorOrDot(str[i + 1])) {
      error = 1;
    }
    if (std::isdigit(str[i]) && std::isalpha(str[i + 1]) && str[i + 1] != 'm') {
      error = 1;
    }
    if (std::isdigit(str[i + 1]) && std::isalpha(str[i]) && str[i] != 'd') {
      error = 1;
    }
    i++;
  }
  while (j < size) {
    if (PointValidation(str, j, &j, dots)) {
      error = 1;
    }
  }
  while (k < size) {
    if (FunctionValidation(str, k, &k, type)) {
      error = 1;
    }
  }
  return error;
}

int Model::CheckOnOperator(char ch) {
  return ch == '+' || ch == '-' || ch == '*' || ch == '^' || ch == '/' ||
         ch == '%';
}

int Model::CheckOnOperatorOrDot(char ch) {
  return CheckOnOperator(ch) || ch == '.';
}

int Model::CheckOnOperatorOrBracket(char ch) {
  return CheckOnOperator(ch) || ch == '(' || ch == ')';
}

int Model::CheckOnOperatorExceptUnary(char ch) {
  return ch == '*' || ch == '^' || ch == '/' || ch == '%' || ch == 'm';
}

int Model::CheckOnOperatorExceptUnaryOrDot(char ch) {
  return CheckOnOperatorExceptUnary(ch) || ch == '.';
}

int Model::BracketsValidation(const std::string& str) {
  int error = 0;
  int brackets = 0;
  for (size_t i = 0; i < str.size(); ++i) {
    if (str[i] == '(') {
      brackets++;
      if (str[i + 1] == ')') {
        error = 1;
      }
    }
    if (str[i] == ')') {
      if (brackets == 0) {
        error = 1;
      }
      if (str[i + 1] == '(') {
        error = 1;
      }
      brackets--;
    }
  }
  if (brackets != 0) {
    error = 1;
  }
  return error;
}

int Model::PointValidation(const std::string& str, size_t j,
                           size_t* out_counter, int& dots) {
  int counter = 0;
  int error = 0;
  if (std::isdigit(str[j])) {
    if (dots == 0) {
      counter = GetDots(str.substr(j), dots);
      if (dots > 1) {
        error = 1;
      }
    }
  }
  j += counter + 1;
  *out_counter = j;
  dots = 0;
  return error;
}

int Model::FunctionValidation(const std::string& str, size_t k,
                              size_t* out_counter, OperatorType& type) {
  int counter = 0;
  int error = 0;
  if (std::isalpha(str[k]) && str[k] != 'x') {
    counter = FunctionParser(str.substr(k), type);
    if (!(type >= OperatorType::PLUS && type <= OperatorType::SQRT)) {
      error = 1;
    }
  }
  k += counter + 1;
  *out_counter = k;
  return error;
}

}  // namespace s21
