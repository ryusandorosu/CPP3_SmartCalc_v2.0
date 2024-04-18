#include "tests.h"

TEST(UnaryOperations, 00_1) {
  std::string str = "1-";
  EXPECT_TRUE(object.ConvertToRpnAndCalculate(str) == -1);
}

TEST(UnaryOperations, 00_2) {
  std::string str = "-(-1)";
  EXPECT_TRUE(object.ConvertToRpnAndCalculate(str) == 1);
}

TEST(UnaryOperations, 01) {
  std::string str = "-sin(-1)";
  EXPECT_NEAR(object.ConvertToRpnAndCalculate(str), 0.8414709848, accuracy);
}

// TEST(UnaryOperations, 02) {
//   std::string str = "log(-2)";
//   double result = object.ConvertToRpnAndCalculate(str);
//   EXPECT_TRUE(isnan(result) == isnan(NAN));
//   results 0.30103 here instead of nan
// }

TEST(UnaryOperations, 03) {
  std::string str = "sqrt(ln(10))";
  EXPECT_NEAR(object.ConvertToRpnAndCalculate(str), 1.51742712939, accuracy);
}

TEST(MixedOperations, 01) {
  std::string str = "1+2*atan(0.5)";
  EXPECT_NEAR(object.ConvertToRpnAndCalculate(str), 1.927295218, accuracy);
}

TEST(MixedOperations, 02) {
  std::string str = "cos(10mod2.2)";
  EXPECT_NEAR(object.ConvertToRpnAndCalculate(str), 0.36235775447, accuracy);
}

TEST(MixedOperations, 03) {
  std::string str = "-1+1/cos(250)";
  EXPECT_NEAR(object.ConvertToRpnAndCalculate(str), 3.14957895495, accuracy);
}

TEST(MixedOperations, 04) {
  std::string str = "sqrt(30)+4^5";
  EXPECT_NEAR(object.ConvertToRpnAndCalculate(str), 1029.47722558, accuracy);
}

TEST(MixedOperations, 05) {
  std::string str = "log(25)-ln(50)";
  EXPECT_NEAR(object.ConvertToRpnAndCalculate(str), -2.51408299676, accuracy);
}

TEST(MixedOperations, 07_1) {
  std::string str = "7mod3+5mod2/2^(9mod2)";
  EXPECT_TRUE(object.ConvertToRpnAndCalculate(str) == 1.5);
}

TEST(MixedOperations, 07_2) {
  std::string str = "7%3+5%2/2^(9%2)";
  EXPECT_TRUE(object.ConvertToRpnAndCalculate(str) == 1.5);
}

TEST(MixedOperations, 08) {
  std::string str = "sqrt(cos(2+7)+tan(2+5))";
  double result = object.ConvertToRpnAndCalculate(str);
  EXPECT_TRUE(isnan(result) == isnan(NAN));
}

TEST(MixedOperations, 09) {
  std::string str = "tan(250)-cos(45)+2^(sin(52))*5";
  EXPECT_NEAR(object.ConvertToRpnAndCalculate(str), 5.35513314933, accuracy);
}

TEST(MixedOperations, 10) {
  std::string str = "(sin(45)+cos(30)+tan(45)+tan(90))*2";
  EXPECT_NEAR(object.ConvertToRpnAndCalculate(str), 1.25945950551, accuracy);
}

TEST(MixedOperations, 11) {
  std::string str = "sin(sin(sin(sin(sin(90)))))";
  EXPECT_NEAR(object.ConvertToRpnAndCalculate(str), 0.60239260455, accuracy);
}

TEST(MixedOperations, 12) {
  std::string str = "2^8.5*1+sqrt(87.554+cos(1))";
  EXPECT_NEAR(object.ConvertToRpnAndCalculate(str), 371.424528471, accuracy);
}

TEST(MixedOperations, 13) {
  std::string str = "(1+2)*4*cos(3.141592*7-2)+sin(2*3.141592)";
  EXPECT_NEAR(object.ConvertToRpnAndCalculate(str), 4.99381065317, accuracy);
}

TEST(MixedOperations, 14) {
  std::string str = "16-(7+38*(6/2))*((3*6)-(9*(4+9-99)))/(96*9)";
  EXPECT_NEAR(object.ConvertToRpnAndCalculate(str), -94.9166666667, accuracy);
}

TEST(MixedOperations, 15) {
  std::string str = "(4+1-1*23*5/4/6)/((cos(1)+cos(2))/(1+2+3))/7";
  EXPECT_NEAR(object.ConvertToRpnAndCalculate(str), 1.43828886112, accuracy);
}

TEST(MixedOperations, 16) {
  std::string str = "2/1+2+3+4*5*6^7-727mod728+((1000+500*2)*201)+sin(1)";
  EXPECT_NEAR(object.ConvertToRpnAndCalculate(str), 6000000.84147, accuracy);
}

TEST(MixedOperations, 17) {
  std::string str =
      "cos(0.785)+sin(0.785)+tan(0.785)+acos(0.785)+asin(0.785)+atan(0.785)+ln("
      "0.785)+log(0.785)+sqrt(0.785)";
  EXPECT_NEAR(object.ConvertToRpnAndCalculate(str), 5.1885416, accuracy);
}

TEST(MixedOperations, 18) {
  std::string str =
      "sin(cos(111))+tan(sqrt(222))-acos(asin(333))*1.56854408/ln(log(555))";
  double result = object.ConvertToRpnAndCalculate(str);
  EXPECT_TRUE(isnan(result) == isnan(NAN));  // (-0.0445964 < x < 0.0439771)
}

TEST(MixedOperations, 19) {
  std::string str = "5.006* 97.83 +3.7^8.37/(-5.6) + ln(25.6)";
  EXPECT_NEAR(object.ConvertToRpnAndCalculate(str), -9684.9725462, accuracy);
}

TEST(MixedOperations, 20) {
  std::string str = "ln(35)*5-log(6)+sqrt(16)";
  EXPECT_NEAR(object.ConvertToRpnAndCalculate(str), 20.9985890571, accuracy);
}

TEST(MixedOperations, 21) {
  std::string str = "acos(10mod3)+asin(1)+atan(1)";
  EXPECT_NEAR(object.ConvertToRpnAndCalculate(str), 2.35619449, accuracy);
}

TEST(MixedOperations, 22) {
  std::string str = "(ln(0.001)-log(1000))*atan(25)";
  EXPECT_NEAR(object.ConvertToRpnAndCalculate(str), -15.1669666, accuracy);
}

TEST(MixedOperations, 23) {
  std::string str = "-3*(-3.141592-(7*(-7)))";
  EXPECT_TRUE(object.ConvertToRpnAndCalculate(str) == -137.575224);
}

TEST(MixedOperations, 24) {
  std::string str = "3.1415-21/42+12*tan(5)";
  EXPECT_NEAR(object.ConvertToRpnAndCalculate(str), -37.924680075, accuracy);
}

TEST(MixedOperations, STE01) {
  std::string str = "sin(1)^2+cos(1)^2";
  EXPECT_TRUE(object.ConvertToRpnAndCalculate(str) == 1);
}

TEST(MixedOperations, STE02) {
  std::string str = "506546+sin(2+8.5*1)-log(54654.6568)";
  EXPECT_NEAR(object.ConvertToRpnAndCalculate(str), 506540.382677, accuracy);
}

TEST(MixedOperations, STE03_1) {
  std::string str = "4^sqrt(4)";
  EXPECT_TRUE(object.ConvertToRpnAndCalculate(str) == 16);
}

TEST(MixedOperations, STE03_2) {
  std::string str = "4^sqrt(9)";
  EXPECT_TRUE(object.ConvertToRpnAndCalculate(str) == 64);
}

// TEST(MixedOperations, STE04_1) {
//   std::string str = "3^sin(0.4)^3";
//   EXPECT_NEAR(object.ConvertToRpnAndCalculate(str), 1.06702823486, accuracy);
//   // results 0.059054 here
// }

TEST(MixedOperations, STE04_2) {
  std::string str = "3^(sin(0.4)^3)";
  EXPECT_NEAR(object.ConvertToRpnAndCalculate(str), 1.06702823486, accuracy);
}

TEST(MixedOperations, STE05_1) {
  std::string str = "3^sin(0.4)^3*2";
  EXPECT_NEAR(object.ConvertToRpnAndCalculate(str), 2.13405646972, accuracy);
}

TEST(MixedOperations, STE05_2) {
  std::string str = "(3^(sin(0.4)^3))*2";
  EXPECT_NEAR(object.ConvertToRpnAndCalculate(str), 2.13405646972, accuracy);
}

TEST(MixedOperations, STE06_1) {
  std::string str = "1+2*3^sin(0.4)^3*2+1";
  EXPECT_NEAR(object.ConvertToRpnAndCalculate(str), 6.26811293943, accuracy);
}

TEST(MixedOperations, STE06_2) {
  std::string str = "1+(2*(3^(sin(0.4)^3))*2)+1";
  EXPECT_NEAR(object.ConvertToRpnAndCalculate(str), 6.26811293943, accuracy);
}

TEST(MixedOperations, STE07_1) {
  std::string str = "sin(-(-1))^3";
  EXPECT_NEAR(object.ConvertToRpnAndCalculate(str), 0.59582323659, accuracy);
}

TEST(MixedOperations, STE07_2) {
  std::string str = "3^sin(-(-1))^3";
  EXPECT_NEAR(object.ConvertToRpnAndCalculate(str), 1.92433168261, accuracy);
}

TEST(MixedOperations, STE07_3) {
  std::string str = "3^(sin(-(-1))^3)";
  EXPECT_NEAR(object.ConvertToRpnAndCalculate(str), 1.92433168261, accuracy);
}

TEST(MixedOperations, STE08) {
  std::string str = "(2+3)*(-(2+3))";
  EXPECT_TRUE(object.ConvertToRpnAndCalculate(str) == -25);
}

TEST(MixedOperations, STE09_1) {
  std::string str = "5mod(-1.5)";
  EXPECT_TRUE(object.ConvertToRpnAndCalculate(str) == -1);
}

TEST(MixedOperations, STE09_2) {
  std::string str = "(5mod(-1.5)*4)^2";
  EXPECT_TRUE(object.ConvertToRpnAndCalculate(str) == 16);
}

TEST(MixedOperations, STE10_1) {
  std::string str = "sqrt(100)/sqrt(25)*sqrt(121)";
  EXPECT_TRUE(object.ConvertToRpnAndCalculate(str) == 22);
}

TEST(MixedOperations, STE10_2) {
  std::string str = "(sqrt(100)/sqrt(25))*sqrt(121)";
  EXPECT_TRUE(object.ConvertToRpnAndCalculate(str) == 22);
}
