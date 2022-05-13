
#======================================================================
# Bare-bones Bazel BUILD file for Final Project
# CPSC 326
# Spring, 2022
#======================================================================

load("@rules_java//java:defs.bzl", "java_test")

java_binary(
  name = "mypl",
  srcs = glob(["src/*.java"]),
  main_class = "MyPL",
)

java_library(
  name = "mypl-lib",
  srcs = glob(["src/*.java"]),
)

#----------------------------------------------------------------------
# TEST SUITES:
#----------------------------------------------------------------------


# TODO: Add your test targets here. See prior homework build files for
#       examples of creating test targets.

java_test(
    name = "error-handling-lexer-test",
    srcs = ["tests/ErrorHandlingLexerTest.java"], 
    test_class = "ErrorHandlingLexerTest",
    deps = ["lib/junit-4.13.2.jar", "lib/hamcrest-core-1.3.jar", ":mypl-lib"],
)

java_test(
    name = "error-handling-parser-test",
    srcs = ["tests/ErrorHandlingParserTest.java"], 
    test_class = "ErrorHandlingParserTest",
    deps = ["lib/junit-4.13.2.jar", "lib/hamcrest-core-1.3.jar", ":mypl-lib"],
)

java_test(
    name = "error-handling-static-checker-test",
    srcs = ["tests/ErrorHandlingStaticCheckerTest.java"], 
    test_class = "ErrorHandlingStaticCheckerTest",
    deps = ["lib/junit-4.13.2.jar", "lib/hamcrest-core-1.3.jar", ":mypl-lib"],
)

java_test(
    name = "error-handling-code-generator-test",
    srcs = ["tests/ErrorHandlingCodeGeneratorTest.java"], 
    test_class = "ErrorHandlingCodeGeneratorTest",
    deps = ["lib/junit-4.13.2.jar", "lib/hamcrest-core-1.3.jar", ":mypl-lib"],
)
