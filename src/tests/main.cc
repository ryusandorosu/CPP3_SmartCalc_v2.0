#include "tests.h"

s21::Model object;
double accuracy = 0.00001;

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
