
#======================================================================
# Bare-bones Bazel BUILD file for HW-2
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

java_test(
    name = "token-test",
    srcs = ["tests/TokenTest.java"], 
    test_class = "TokenTest",
    deps = ["lib/junit-4.13.2.jar", "lib/hamcrest-core-1.3.jar", ":mypl-lib"],
)

java_test(
    name = "lexer-test",
    srcs = ["tests/LexerTest.java"],
    test_class = "LexerTest",
    deps = ["lib/junit-4.13.2.jar", "lib/hamcrest-core-1.3.jar","//:mypl-lib"],
)

java_test(
    name = "incremental-test",
    srcs = ["tests/IncrementalTest.java"],
    test_class = "IncrementalTest",
    deps = ["lib/junit-4.13.2.jar", "lib/hamcrest-core-1.3.jar","//:mypl-lib"],
)


