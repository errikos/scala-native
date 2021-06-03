#include "munit.h"

extern const MunitSuite sampleSuite;

int main(int argc, char *argv[]) {
    munit_suite_main(&sampleSuite, NULL, argc, argv);
}
