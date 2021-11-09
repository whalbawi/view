#include "view.h"

#include "gtest/gtest.h"

class ViewTest : public ::testing::Test {
  protected:
    view::View view{};
};

TEST_F(ViewTest, Adder) {
    view.add(1, 2);
    ASSERT_EQ(view.get_result(), 3);
}

TEST_F(ViewTest, Version) {
    ASSERT_NE(view::View::get_version(), "");
}
