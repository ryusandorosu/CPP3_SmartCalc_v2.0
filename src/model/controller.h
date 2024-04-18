#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include "backend.h"

namespace s21 {

class Controller {
 public:
  double calculateExpression(const std::string& expression) {
    return model.ConvertToRpnAndCalculate(expression);
  };
  int validateExpression(const std::string& expression) {
    return model.Validation(expression);
  };

 private:
  s21::Model model;
};

}  // namespace s21

#endif  // SRC_CONTROLLER_CONTROLLER_H_
