#include "munit.h"

extern const MunitSuite sampleSuite;
extern const MunitSuite settingsSuite;
extern const MunitSuite btreeSuite;

int main(int argc, char *argv[]) {
    munit_suite_main(&sampleSuite, NULL, argc, argv);
    munit_suite_main(&settingsSuite, NULL, argc, argv);
    munit_suite_main(&btreeSuite, NULL, argc, argv);
}
