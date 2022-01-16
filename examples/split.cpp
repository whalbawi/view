#include "view/engine.h"
#include "view/frame_view.h"
#include "view/split_view.h"
#include "view/text_view.h"

int main(int argc, char** argv) {
    // Left View
    auto left_text = std::make_shared<view::TextView>();
    auto left_frame = std::make_shared<view::FrameView>(left_text);
    // Right View
    auto right_text = std::make_shared<view::TextView>();
    auto right_frame = std::make_shared<view::FrameView>(right_text);
    // Present both views using a `SplitView`
    auto main_view = std::make_shared<view::SplitView>(left_frame, right_frame, true, 1, 2);

    left_text->set_content("Left View");
    right_text->set_content("Right View");

    view::Engine engine{main_view};

    engine.run();

    return 0;
}
