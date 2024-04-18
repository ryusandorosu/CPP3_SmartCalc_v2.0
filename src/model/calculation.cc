#include "backend.h"

namespace s21 {

double Model::UnaryOperation(double number, OperatorType op) {
  double result = 0;
  if (op == OperatorType::UNMIN) {
    result = number * (-1);
  } else if (op == OperatorType::SIN) {
    result = sin(number);
  } else if (op == OperatorType::COS) {
    result = cos(number);
  } else if (op == OperatorType::TAN) {
    result = tan(number);
  } else if (op == OperatorType::ASIN) {
    result = asin(number);
  } else if (op == OperatorType::ACOS) {
    result = acos(number);
  } else if (op == OperatorType::ATAN) {
    result = atan(number);
  } else if (op == OperatorType::LN) {
    result = log(number);
  } else if (op == OperatorType::LOG) {
    result = log10(number);
  } else if (op == OperatorType::SQRT) {
    result = sqrt(number);
  }
  return result;
}

double Model::BinaryOperation(double right, double left, OperatorType op) {
  double result = 0;
  if (op == OperatorType::PLUS) {
    result = left + right;
  } else if (op == OperatorType::MINUS) {
    result = left - right;
  } else if (op == OperatorType::MULT) {
    result = left * right;
  } else if (op == OperatorType::DIV) {
    result = left / right;
  } else if (op == OperatorType::MOD) {
    result = fmod(left, right);
    if (left < 0 || right < 0) {
      result += right;
    }
  } else if (op == OperatorType::POW) {
    result = pow(left, right);
  }
  return result;
}

double Model::Calculation(
    const std::vector<std::pair<double, OperatorType> >& output_stack) {
  std::vector<double> numbers;
  std::vector<OperatorType> queue;

  OperatorType current_type = OperatorType::DEFAULT,
               next_type = OperatorType::DEFAULT;
  size_t size = output_stack.size();
  int flag_to_not_pop_queue = 0;  // ultracostyl
  double current_value = 0, result = 0, right = 0, left = 0, temp_result = 0;

  for (size_t i = 0; i < size; i++) {
    current_type = output_stack[i].second;
    if (current_type == OperatorType::VALUE) {
      current_value = output_stack[i].first;
      numbers.push_back(current_value);
      // < costyl
    } else if ((queue.size() != 0) && (numbers.size() > 1) &&
               (GetPriority(current_type) != Priority::HIGHEST) &&
               ((((current_type != OperatorType::VALUE)) &&
                 (GetPriority(current_type) == GetPriority(queue.back()))) ||
                (current_type == OperatorType::VALUE))) {
      // < ultracostyl
      if ((output_stack.size() >= 1 + i + 2) &&
          (GetPriority(current_type) == Priority::HIGH &&
           GetPriority(output_stack[i + 2].second) == Priority::HIGH)) {
        flag_to_not_pop_queue = 1;
        queue.push_back(current_type);
        // ultracostyl >
      } else if (current_type != OperatorType::SQRT) {
        right = numbers.back();
        numbers.pop_back();
        left = numbers.back();
        numbers.pop_back();
        temp_result = BinaryOperation(right, left, current_type);
        numbers.push_back(temp_result);
      } else {
        right = numbers.back();
        numbers.pop_back();
        temp_result = UnaryOperation(right, current_type);
        numbers.push_back(temp_result);
      }
      // < ultracostyl
      if (flag_to_not_pop_queue == 0) {
        next_type = queue.back();
        queue.pop_back();
        right = numbers.back();
        numbers.pop_back();
        if (numbers.size() == 0) {
          left = current_value;
        } else {
          left = numbers.back();
          numbers.pop_back();
        }
        temp_result = BinaryOperation(right, left, next_type);
        numbers.push_back(temp_result);
      } else {
        flag_to_not_pop_queue = 0;
      }
      // ultracostyl >
      // costyl >
    } else {
      // < costyl
      if ((output_stack.size() >= 1 + i + 1) &&
          (current_type >= OperatorType::PLUS &&
           current_type <= OperatorType::MINUS) &&
          numbers.back() < 0 &&
          GetPriority(output_stack[i + 1].second) == Priority::HIGHEST) {
        right = numbers.back();
        numbers.pop_back();
        if (numbers.size() > 0) {
          left = 0;
        } else if (numbers.size() == 0) {
          left = 0;
        } else {
          left = numbers.back();
          numbers.pop_back();
        }
        temp_result = BinaryOperation(right, left, current_type);
        numbers.push_back(temp_result);
        // costyl >
      } else if (current_type >= OperatorType::PLUS &&
                 current_type <= OperatorType::MINUS) {
        right = numbers.back();
        numbers.pop_back();
        if (numbers.size() == 0) {
          left = 0;
        } else {
          left = numbers.back();
          numbers.pop_back();
        }
        temp_result = BinaryOperation(right, left, current_type);
        numbers.push_back(temp_result);
        // < costyl
      } else if (current_type >= OperatorType::MULT &&
                 current_type <= OperatorType::MOD) {
        if (numbers.size() == 1) {
          queue.push_back(current_type);
        } else if ((output_stack.size() >= 1 + i + 5) &&
                   ((output_stack[i - 1].second != OperatorType::VALUE) &&
                    (output_stack[i - 2].second != OperatorType::VALUE)) &&
                   (GetPriority(output_stack[i + 2].second) >
                    GetPriority(current_type)) &&
                   (GetPriority(output_stack[i + 5].second) >
                    GetPriority(current_type))) {
          queue.push_back(current_type);
        } else if ((output_stack.size() >= 1 + i + 5) &&
                   !(GetPriority(output_stack[i - 2].second) >
                     GetPriority(current_type)) &&
                   (GetPriority(output_stack[i + 2].second) >
                    GetPriority(current_type)) &&
                   (GetPriority(output_stack[i + 5].second) !=
                        Priority::DEFAULT &&
                    GetPriority(output_stack[i + 5].second) <
                        GetPriority(current_type))) {
          queue.push_back(current_type);
        } else if ((output_stack.size() >= 1 + i + 2) &&
                   GetPriority(current_type) == Priority::HIGH &&
                   GetPriority(output_stack[i + 2].second) == Priority::HIGH) {
          queue.push_back(current_type);
        } else {  // < normal
          right = numbers.back();
          numbers.pop_back();
          left = numbers.back();
          numbers.pop_back();
          temp_result = BinaryOperation(right, left, current_type);
          numbers.push_back(temp_result);  // normal >
        }
      } else if ((output_stack.size() >= 1 + i + 2) &&
                 current_type == OperatorType::UNMIN &&
                 output_stack[i + 2].second == OperatorType::UNMIN) {
        right = numbers.back();
        numbers.pop_back();
        temp_result = (-1) * UnaryOperation(right, current_type);
        numbers.push_back(temp_result);
        // costyl >
      } else {
        right = numbers.back();
        numbers.pop_back();
        temp_result = UnaryOperation(right, current_type);
        numbers.push_back(temp_result);
      }
    }
  }
  // < ultracostyl
  if (queue.size() != 0 && numbers.size() > 1) {
    next_type = queue.back();
    queue.pop_back();
    right = numbers.back();
    numbers.pop_back();
    left = numbers.back();
    numbers.pop_back();
    temp_result = BinaryOperation(right, left, next_type);
    numbers.push_back(temp_result);
  }
  // ultracostyl >
  result = numbers.back();
  numbers.pop_back();
  return result;
}

}  // namespace s21
