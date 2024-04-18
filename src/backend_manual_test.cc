#include "model/backend.h"

int main() {
  // Create an instance of Calculator
  s21::Model object;

  // Define the expression
  std::string expression = "12.34+56.78-90.12*34/7.68";  // = -329.84875
  // std::string expression = "(3+5)*10-17*2";  // = 46
  // std::string expression = "1+2*(3+4/2-(1+2))*2+1";  // = 10
  // std::string expression = "1+2*atan(0.5)";  // = 1.927295218
  // std::string expression = "123456*78910111213";  // = 9.7419267e+15
  // std::string expression = "2^8.5*1+sqrt(87.554+cos(1))";  // = 371.424528471
  // std::string expression = "(1+2)*4*cos(3.141592*7-2)+sin(2*3.141592)";  // = 4.99381065317
  // std::string expression = "-sin(-1)";  // = 0.8414709848
  // std::string expression = "log(-2)";  // = nan
  // std::string expression = "sqrt(cos(2+7)+tan(2+5))";  // = nan
  // std::string expression = "-(-1)";  // = 1
  // std::string expression = "cos(10mod2.2)";  // = 0.36235775447
  // std::string expression = "sqrt(ln(10))";  // = 1.51742712939
  // std::string expression = "sqrt(30)+4^5";  // = 1029.47722558
  // std::string expression = "5.006* 97.83 +3.7^8.37/(-5.6) + ln(25.6)";  // = -9684.9725462
  // std::string expression = "(4+1-1*23*5/4/6)/((cos(1)+cos(2))/(1+2+3))/7";  // = 1.43828886112
  // std::string expression = "tan(250)-cos(45)+2^(sin(52))*5";  // = 5.35513314933
  // std::string expression = "log(25)-ln(50)";  // = -2.51408299676
  // std::string expression = "-1+1/cos(250)";  // = 3.14957895495
  // std::string expression = "7mod3+5mod2/2^(9mod2)";  // = 1.5
  // std::string expression = "(sin(45)+cos(30)+tan(45)+tan(90))*2";  // = 1.25945950551
  // std::string expression = "sin(sin(sin(sin(sin(90)))))";  // = 0.60239260455
  // std::string expression = "10*10/10+10-10+(-10)";  // = 0
  // std::string expression = "16-(7+38*(6/2))*((3*6)-(9*(4+9-99)))/(96*9)";  // = -94.9166666667
  // std::string expression = "2/1+2+3+4*5*6^7-727mod728+((1000+500*2)*201)+sin(1)";  // = 6000000.84147
  // std::string expression = "cos(0.785)+sin(0.785)+tan(0.785)+acos(0.785)+asin(0.785)+atan(0.785)+ln(0.785)+log(0.785)+sqrt(0.785)";  // = 5.1885416 ?
  // std::string expression = "sin(cos(111))+tan(sqrt(222))-acos(asin(333))*1.56854408/ln(log(555))";  // must break? nan?
  // std::string expression = "123456789+123456789+123456789+123456789+123456789+123456789+123456789+123456789+123456789+123456789+123456789+123456789+123456789+123456789+123456789+123456789+123456789+123456789+123456789+123456789+123456789+123456789+123456789+123456789+123456789+12345";  // 255 chars, = 3086432070

  // was broken on these:
  // std::string expression = "sin(1)^2+cos(1)^2";  // = 1
  // std::string expression = "506546+sin(2+8.5*1)-log(54654.6568)";  // = 506540.382677
  // std::string expression = "2^2^3";  // correct
  // std::string expression = "2^(2^(3))";  // correct, = 256
  // std::string expression = "2^1.5^1.25^1.125";  // correct
  // std::string expression = "2^(1.5^(1.25^1.125))";  // correct, = 3.2131590953
  // std::string expression = "4^sqrt(4)";  // = 16
  // std::string expression = "4^sqrt(9)";  // = 64
  // std::string expression = "3^sin(0.4)^3";  // correct
  // std::string expression = "3^(sin(0.4)^3)";  // correct, = 1.06702823486
  // std::string expression = "sin(-(-1))^3";  // correct, = 0.59582323659
  // std::string expression = "3^sin(-(-1))^3";  // correct
  // std::string expression = "3^(sin(-(-1))^3)";  // correct, = 1.92433168261
  // std::string expression = "3^sin(0.4)^3*2";  // correct
  // std::string expression = "(3^(sin(0.4)^3))*2";  // correct, = 2.13405646972
  // std::string expression = "1+2*3^sin(0.4)^3*2+1";  // correct
  // std::string expression = "1+(2*(3^(sin(0.4)^3))*2)+1";  // correct, = 6.26811293943
  // std::string expression = "4^acos(1.2/4)/tan(2*1.2)";  // not correct, must be = -6.31492384607

  std::cout << "Expression: " << expression << std::endl;

  // Validate the expression
  int validationResult = object.Validation(expression);
  // Check the result
  std::cout << "Validation: ";
  if (validationResult == 0) {
    std::cout << "valid" << std::endl;
  } else {
    std::cout << "invalid" << std::endl;
  }

  // Parse the expression
  object.ConvertToRpnAndCalculate(expression);

  return 0;
}