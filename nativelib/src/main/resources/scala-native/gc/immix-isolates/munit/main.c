#include "munit.h"

extern const MunitSuite sampleSuite;
extern const MunitSuite settingsSuite;

int main(int argc, char *argv[]) {
  munit_suite_main(&sampleSuite, NULL, argc, argv);
  munit_suite_main(&settingsSuite, NULL, argc, argv);
}
