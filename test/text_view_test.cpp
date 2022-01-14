#include "view/text_view.h"

#include "gtest/gtest.h"

#include "memory_pane.h"

class TextViewTest : public ::testing::Test {
  protected:
    view::TextView view{};
    view::MemoryPane pane{25, 31};
};

TEST_F(TextViewTest, RenderEmpty) {
    std::string content{};
    view.set_content(content);
    view.render(&pane);

    for (auto& row : pane.rows) {
        std::for_each(row.begin(), row.end(), [](auto&& ch) { ASSERT_EQ(ch, '\0'); });
    }
}

TEST_F(TextViewTest, Render) {
    std::string content{"Test content"};
    view.set_content(content);
    view.render(&pane);

    ASSERT_EQ(pane.rows[0].substr(0, content.size()),
              (std::wstring{content.begin(), content.end()}));

    for (int i = 1; i < pane.rows.size(); ++i) {
        ASSERT_EQ(pane.rows[i], std::wstring(pane.get_width(), L'\0'));
    }
}
