#include "view/text_view.h"

#include "gtest/gtest.h"

#include "memory_pane.h"

class TextViewTest : public ::testing::Test {
  protected:
    view::TextView view{};
    view::MemoryPane pane{25, 31};
};

TEST_F(TextViewTest, Init) {
    view::TextView text_view{};
    text_view.set_content("Test content.\n");
    text_view.render(&pane);
}
