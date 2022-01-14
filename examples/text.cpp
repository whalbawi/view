#include "view/engine.h"
#include "view/frame_view.h"
#include "view/text_view.h"

int main(int argc, char** argv) {
    auto text_view = std::make_shared<view::TextView>();
    auto frame = std::make_shared<view::FrameView>(text_view);

    text_view->set_content("Hello, World!\nThis is a sample view.");

    view::Engine engine{frame};
    engine.run();

    return 0;
}
