#include "tests.h"

TEST(BinaryOperations, 01) {
  std::string str = "12.34+56.78-90.12*34/7.68";
  EXPECT_TRUE(object.ConvertToRpnAndCalculate(str) == -329.84875);
}

TEST(BinaryOperations, 02) {
  std::string str = "-5.0mod(-3.0)";
  EXPECT_TRUE(object.ConvertToRpnAndCalculate(str) == -2);
}

TEST(BinaryOperations, 03) {
  std::string str = "10*10/10+10-10+(-10)";
  EXPECT_TRUE(object.ConvertToRpnAndCalculate(str) == 0);
}

TEST(BinaryOperations, 04) {
  std::string str = "(3+5)*10-17*2";
  EXPECT_TRUE(object.ConvertToRpnAndCalculate(str) == 46);
}

TEST(BinaryOperations, 05) {
  std::string str = "1+2*(3+4/2-(1+2))*2+1";
  EXPECT_TRUE(object.ConvertToRpnAndCalculate(str) == 10);
}

TEST(BinaryOperations, 06_1) {
  std::string str = "2^2^3";
  EXPECT_TRUE(object.ConvertToRpnAndCalculate(str) == 256);
}

TEST(BinaryOperations, 06_2) {
  std::string str = "2^(2^(3))";
  EXPECT_TRUE(object.ConvertToRpnAndCalculate(str) == 256);
}

TEST(BinaryOperations, 06_3) {
  std::string str = "2^3^2";
  EXPECT_TRUE(object.ConvertToRpnAndCalculate(str) == 512);
}

TEST(BinaryOperations, 06_4) {
  std::string str = "2^(3^2)";
  EXPECT_TRUE(object.ConvertToRpnAndCalculate(str) == 512);
}

TEST(BinaryOperations, 06_5) {
  std::string str = "(2^3)^2";
  EXPECT_TRUE(object.ConvertToRpnAndCalculate(str) == 512);
}

TEST(BinaryOperations, 07_1) {
  std::string str = "2^1.5^1.25^1.125";
  EXPECT_NEAR(object.ConvertToRpnAndCalculate(str), 3.2131590953, accuracy);
}

TEST(BinaryOperations, 07_2) {
  std::string str = "2^(1.5^(1.25^1.125))";
  EXPECT_NEAR(object.ConvertToRpnAndCalculate(str), 3.2131590953, accuracy);
}

TEST(BinaryOperations, 08) {
  std::string str = "(5+5)*(-2)";
  EXPECT_TRUE(object.ConvertToRpnAndCalculate(str) == -20);
}

TEST(BinaryOperations, 09) {
  std::string str = "100*4+23-50/ 0.5+(123-112)";
  EXPECT_TRUE(object.ConvertToRpnAndCalculate(str) == 334);
}

TEST(BinaryOperations, 10) {
  std::string str = "124.5mod21.2*25/137";
  EXPECT_NEAR(object.ConvertToRpnAndCalculate(str), 3.37591240876, accuracy);
}

// TEST(BinaryOperations, 11) {
//   std::string str = "5^5^2/5^5-4/2^2";
//   EXPECT_TRUE(object.ConvertToRpnAndCalculate(str) == 95367431640624);
//   // 9.5367432e+13
// }

TEST(BinaryOperations, 12) {
  std::string str = "10-20*(-10)";
  EXPECT_TRUE(object.ConvertToRpnAndCalculate(str) == 210);
}

TEST(BinaryOperations, 13) {
  std::string str = "2-(-2+2.343434)";
  EXPECT_NEAR(object.ConvertToRpnAndCalculate(str), 1.656566, accuracy);
}

TEST(BinaryOperations, 14) {
  std::string str = "(2^3+8)/1.5";
  EXPECT_NEAR(object.ConvertToRpnAndCalculate(str), 10.6666666667, accuracy);
}

// TEST(BinaryOperations, 15) {
//   std::string str = "123456*78910111213";
//   EXPECT_TRUE(object.ConvertToRpnAndCalculate(str) == 9.7419267e+15);
// }

TEST(BinaryOperations, 16) {
  std::string str = "512/2/2/2/2/2/2/2/2/2";
  EXPECT_TRUE(object.ConvertToRpnAndCalculate(str) == 1);
}

TEST(BinaryOperations, 17) {
  std::string str = "17/4+(14/2*(3-1^4))";
  EXPECT_TRUE(object.ConvertToRpnAndCalculate(str) == 18.25);
}

TEST(BinaryOperations, 18) {
  std::string str = "5mod2*3";
  EXPECT_TRUE(object.ConvertToRpnAndCalculate(str) == 3);
}

TEST(BinaryOperations, 19) {  // 255 chars expression
  std::string str =
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1";
  EXPECT_TRUE(object.ConvertToRpnAndCalculate(str) == 128);
}

TEST(BinaryOperations, 20) {  // 255 chars expression
  std::string str =
      "123456789+123456789+123456789+123456789+123456789+123456789+123456789+"
      "123456789+123456789+123456789+123456789+123456789+123456789+123456789+"
      "123456789+123456789+123456789+123456789+123456789+123456789+123456789+"
      "123456789+123456789+123456789+123456789+12345";
  EXPECT_TRUE(object.ConvertToRpnAndCalculate(str) == 3086432070);
}
