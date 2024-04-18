#include "tests.h"

TEST(Validation, 01) {
  std::string str = "(-1)";
  EXPECT_TRUE(object.Validation(str) == 0);
}

TEST(Validation, 02) {
  std::string str = "(*1)";
  EXPECT_FALSE(object.Validation(str) == 0);
}

TEST(Validation, 03) {
  std::string str = "(1)1";
  EXPECT_FALSE(object.Validation(str) == 0);
}

TEST(Validation, 04) {
  std::string str = "(1)x";
  EXPECT_FALSE(object.Validation(str) == 0);
}

TEST(Validation, 05) {
  std::string str = "1..2";
  EXPECT_FALSE(object.Validation(str) == 0);
}

TEST(Validation, 06) {
  std::string str = "1+-2";
  EXPECT_FALSE(object.Validation(str) == 0);
}

TEST(Validation, 07) {
  std::string str = "1.x";
  EXPECT_FALSE(object.Validation(str) == 0);
}

TEST(Validation, 08) {
  std::string str = "x.x";
  EXPECT_FALSE(object.Validation(str) == 0);
}

TEST(Validation, 09) {
  std::string str = "+";
  EXPECT_FALSE(object.Validation(str) == 0);
}

TEST(Validation, 10) {
  std::string str = "*1";
  EXPECT_FALSE(object.Validation(str) == 0);
}

TEST(Validation, 11) {
  std::string str = "xsin(1)";
  EXPECT_FALSE(object.Validation(str) == 0);
}

TEST(Validation, 12) {
  std::string str = "10mod/2";
  EXPECT_FALSE(object.Validation(str) == 0);
}

TEST(Validation, 13) {
  std::string str = "1.2.3";
  EXPECT_FALSE(object.Validation(str) == 0);
}

TEST(Validation, 14) {
  std::string str = "()";
  EXPECT_FALSE(object.Validation(str) == 0);
}

TEST(Validation, 15) {
  std::string str = ")";
  EXPECT_FALSE(object.Validation(str) == 0);
}

TEST(Validation, 16) {
  std::string str = ")(";
  EXPECT_FALSE(object.Validation(str) == 0);
}

TEST(Validation, 17) {
  std::string str = "(-(-1)))";
  EXPECT_FALSE(object.Validation(str) == 0);
}

TEST(Validation, 18) {
  std::string str = "son(x)";
  EXPECT_FALSE(object.Validation(str) == 0);
}

TEST(Validation, 19) {
  std::string str = "3sin(x)";
  EXPECT_FALSE(object.Validation(str) == 0);
}

TEST(Validation, 20) {
  std::string str = "sin3(x)";
  EXPECT_FALSE(object.Validation(str) == 0);
}

TEST(Validation, 21) {
  std::string str = "-sin(cos(-x*3^2)";
  EXPECT_FALSE(object.Validation(str) == 0);
}

TEST(Validation, 22) {
  std::string str = "x";
  EXPECT_TRUE(object.Validation(str) == 0);
}

TEST(Validation, 23) {
  std::string str = "3.1415-21/42+12tan(5)";
  EXPECT_FALSE(object.Validation(str) == 0);
}

TEST(Validation, 24) {
  std::string str = "5mod2";
  EXPECT_TRUE(object.Validation(str) == 0);
}

TEST(Validation, 25) {
  std::string str =
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1";
  EXPECT_FALSE(object.Validation(str) == 0);
}

TEST(Validation, 26) {
  std::string str = "a";
  EXPECT_FALSE(object.Validation(str) == 0);
}

TEST(Validation, 27) {
  std::string str = "(+1)";
  EXPECT_TRUE(object.Validation(str) == 0);
}
