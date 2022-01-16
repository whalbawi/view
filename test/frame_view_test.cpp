#include "view/frame_view.h"

#include "gtest/gtest.h"

#include "memory_pane.h"
#include "view/text_view.h"

class FrameViewTest : public ::testing::Test {
  protected:
    view::FrameView view{std::make_shared<view::TextView>()};
    view::MemoryPane pane{50, 80};
};

TEST_F(FrameViewTest, Render) {
    std::string content{};
    view.render(&pane);

    for (int i = 0; i < pane.rows.size(); ++i) {
        std::wstring& row = pane.rows[i];
        for (int j = 0; j < row.size(); ++j) {
            // `FrameView` should only touch the `Pane`'s border
            if (i == 0 || i == pane.rows.size() - 1 || j == 0 || j == row.size() - 1) {
                ASSERT_NE(row[j], L'\0');
            } else {
                ASSERT_EQ(row[j], L'\0');
            }
        }
    }
}
