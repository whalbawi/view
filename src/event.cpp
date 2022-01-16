#include "view/event.h"

namespace view {

// Default implementations
bool Event::Visitor::visit_combo_key_event(const ComboKeyEvent* event) {
    return false;
}

bool Event::Visitor::visit_terminal_resize_event(const TerminalResizeEvent* event) {
    return false;
}

ComboKeyEvent::ComboKeyEvent(FunctionKey function_key, Key key)
    : function_key(function_key), key(key) {}

bool ComboKeyEvent::accept(Visitor* visitor) const {
    return visitor->visit_combo_key_event(this);
}

bool TerminalResizeEvent::accept(Visitor* visitor) const {
    return visitor->visit_terminal_resize_event(this);
}

} // namespace view
