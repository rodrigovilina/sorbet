#include "main/hello-greet.h"
#include "parser/parser.h"
#include "spdlog/spdlog.h"
#include "gtest/gtest.h"
#include <cxxopts.hpp>

TEST(HelloTest, GetGreet) {
    EXPECT_EQ(get_greet("Bazel"), "Hello Bazel");
}

namespace spd = spdlog;

TEST(HelloTest, GetSpdlog) {
    auto console = spd::stdout_color_mt("console");
    console->info("Welcome to spdlog!");
}

TEST(HelloTest, SimpleParse) {
  sruby::parser::parse_ruby("def hello_world; p :hello; end");
}

TEST(HelloTest, GetCXXopts) {
    cxxopts::Options options("MyProgram", "One line description of MyProgram");
}
