#include "backend.h"

namespace s21 {

double Model::ConvertToRpnAndCalculate(const std::string& expr) {
  std::vector<std::pair<double, OperatorType> > output_stack;
  std::vector<std::pair<double, OperatorType> > operators;

  double result = 0, value = 0;
  OperatorType type = OperatorType::DEFAULT;
  bool flag_unary_minus = false, flag_unary_plus = false;

  for (size_t i = 0; i < expr.size();) {
    // unary minus check
    if (expr[i] == '-' && (i == 0 || expr[i - 1] == '(') &&
        (std::isdigit(expr[i + 1]) || expr[i + 1] == '(')) {
      flag_unary_minus = true;
    }
    // unary plus check
    if (expr[i] == '+' && (i == 0 || expr[i - 1] == '(') &&
        std::isdigit(expr[i + 1])) {
      flag_unary_plus = true;
    }
    // operator check
    if (flag_unary_minus) {
      type = OperatorType::UNMIN;
      flag_unary_minus = false;
    } else if (CheckOnOperatorOrBracket(expr[i]) && !flag_unary_minus &&
               !flag_unary_plus) {
      type = GetOperatorType(expr[i]);
    }
    // closing bracket check
    if (expr[i] == ')') {
      while (!operators.empty() &&
             operators.back().second != OperatorType::BRACKET_LEFT) {
        output_stack.push_back(operators.back());
        operators.pop_back();
      }
      operators.pop_back();
    }
    // function check
    if (std::isalpha(expr[i])) {
      size_t temp = FunctionParser(expr.substr(i), type);
      i += temp - 1;
    }

    // starts pushing from here
    if (std::isdigit(expr[i])) {
      int num_len = GetNumber(expr.substr(i), value);
      if (flag_unary_plus) {
        flag_unary_plus = false;
      }
      output_stack.push_back(std::make_pair(value, OperatorType::VALUE));
      i += num_len - 1;
    }
    // opening bracket check
    if (expr[i] == '(') {
      operators.push_back(std::make_pair(0, OperatorType::BRACKET_LEFT));
    }
    // functions check
    if (type != OperatorType::DEFAULT && type != OperatorType::VALUE &&
        type != OperatorType::BRACKET_LEFT &&
        type != OperatorType::BRACKET_RIGHT) {
      if (operators.empty()) {
        operators.push_back(std::make_pair(0, type));
      } else if (GetPriority(type) == Priority::HIGHEST) {
        if (GetPriority(operators.back().second) == Priority::HIGH) {
          output_stack.push_back(operators.back());
          operators.pop_back();
        }
        operators.push_back(std::make_pair(0, type));
      } else {
        if (GetPriority(operators.back().second) < GetPriority(type)) {
          operators.push_back(std::make_pair(0, type));
        } else {
          while (!operators.empty() &&
                 GetPriority(operators.back().second) >= GetPriority(type) &&
                 GetPriority(type) != Priority::HIGHEST) {
            output_stack.push_back(operators.back());
            operators.pop_back();
          }
          operators.push_back(std::make_pair(0, type));
        }
      }
    }
    type = OperatorType::DEFAULT;
    i++;
  }
  while (!operators.empty()) {
    output_stack.push_back(operators.back());
    operators.pop_back();
  }

  // Debugging:
  // std::cout << "Output Stack: ";
  // for (const auto& pair : output_stack) {
  //   if (static_cast<int>(pair.second) == 1) {
  //     std::cout << pair.first << " ";
  //   } else {
  //     std::cout << "[" << static_cast<int>(pair.second) << "] ";
  //   }
  // }
  // std::cout << std::endl;

  result = Calculation(output_stack);

  // Debugging:
  // std::cout << "RESULT: " << result << std::endl;

  return result;
}

}  // namespace s21
