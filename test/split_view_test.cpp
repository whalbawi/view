#include "view/split_view.h"

#include <memory>

#include "gtest/gtest.h"

#include "memory_pane.h"
#include "view/view.h"

class TestEvent : public view::Event {
    bool accept(Visitor* visitor) const override {
        return true;
    }
};

class ReactiveView : public view::View {
  public:
    // Explicitly reject combo key events. This way, we know that any event delivered to the `View`
    // must have been a `TestEvent`.
    bool visit_combo_key_event(const view::ComboKeyEvent* event) override {
        return false;
    }

    bool on_event(const view::Event* event) override {
        return touched = event->accept(this);
    }

    void render(view::Pane* pane) override {}

    bool touched{};
};

class SplitViewTest : public ::testing::Test {
  protected:
    SplitViewTest()
        : view1(std::make_shared<ReactiveView>()),
          view2(std::make_shared<ReactiveView>()),
          view(view1, view2) {}
    std::shared_ptr<ReactiveView> view1;
    std::shared_ptr<ReactiveView> view2;

    view::SplitView view;
    view::MemoryPane pane{50, 80};
};

TEST_F(SplitViewTest, HandlesEventFirstInFocus) {
    TestEvent test_event{};
    view.on_event(&test_event);

    ASSERT_TRUE(view1->touched);
    ASSERT_FALSE(view2->touched);
}

TEST_F(SplitViewTest, HandlesEventSecondInFocus) {
    // First shift focus to the second view,
    view::ComboKeyEvent shift_focus_event{view::ComboKeyEvent::FunctionKey::SHIFT,
                                          view::ComboKeyEvent::Key::RIGHT};
    view.on_event(&shift_focus_event);
    // now send a test event,
    TestEvent test_event{};
    view.on_event(&test_event);
    // and make sure it's delivered to the correct view.
    ASSERT_FALSE(view1->touched);
    ASSERT_TRUE(view2->touched);
}
