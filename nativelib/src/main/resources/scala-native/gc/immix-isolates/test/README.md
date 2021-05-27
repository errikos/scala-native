# GC tests

[μnit](https://nemequ.github.io/munit/) is used as a light-weight and simple to use testing framework.

To add tests, you need to add a single C source file in the `tests` directory.
Essentially, adding tests consists of adding the test functions, declaring them in an `MunitTest` array
and then wrapping them inside an `MunitSuite`.

There is a sample available in `test-sample.c` to get you started.

Finally, you need to call your tests by adding the appropriate definitions in `main.c`.