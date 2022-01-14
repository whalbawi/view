#ifndef VIEW_ENGINE_H_
#define VIEW_ENGINE_H_

#include <memory>

#include "event.h"

namespace view {

class View;

// `Engine` is the main driver of the library. It intercepts terminal events and then passes them
// down a `View` tree for processing, doing so in a loop until the application is terminated.
// Every application using `view` must instantiate an instance with the root of a `View` tree and
// then proceed with invoking `Engine::run()`. Here's an example of usage:
//
// int main(int argc, char** argv) {
//     auto frame = std::make_shared<view::FrameView>();
//     view::Engine engine{frame};
//     engine.run();
//
//     return 0;
// }
//
// `Engine` is backed by the ncurses library both for retrieving terminal events and for output
// rendering.
//
class Engine {
  public:
    explicit Engine(std::shared_ptr<View> main_view);
    ~Engine();

    // Processes keyboard events in an infinite loop.
    void run();

  private:
    std::shared_ptr<View> main_view;

    void refresh();
};

} // namespace view

#endif // VIEW_ENGINE_H_
