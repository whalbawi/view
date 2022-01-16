#include "view/engine.h"

#include <clocale>
#include <memory>

#include "ncurses.h"

#include "ncurses_pane.h"
#include "view/view.h"

namespace view {

WINDOW* root_window;

Engine::Engine(std::shared_ptr<View> main_view) : main_view(std::move(main_view)) {
    setlocale(LC_ALL, ""); // Needed for proper rendering of border characters
    root_window = initscr();
    keypad(root_window, true);
    curs_set(0); // Hide the cursor
    noecho();    // Do not echo input characters
}

Engine::~Engine() = default;

void Engine::run() {
    refresh();

    int ch;
    while ((ch = wgetch(root_window)) != -1) {
        std::unique_ptr<Event> event{};
        switch (ch) {
        case KEY_SLEFT:
            event = std::make_unique<ComboKeyEvent>(ComboKeyEvent::FunctionKey::SHIFT,
                                                    ComboKeyEvent::Key::LEFT);
            break;
        case KEY_SRIGHT:
            event = std::make_unique<ComboKeyEvent>(ComboKeyEvent::FunctionKey::SHIFT,
                                                    ComboKeyEvent::Key::RIGHT);
            break;
        case KEY_RESIZE:
            refresh();
            break;
        default:
            break;
        }
        if (!event) continue;

        main_view->on_event(event.get());
        refresh();
    }
}

void Engine::refresh() {
    werase(root_window);
    auto root_pane = NCursesPane{root_window};
    main_view->render(&root_pane);
    wrefresh(root_window);
}

} // namespace view
