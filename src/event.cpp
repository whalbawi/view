#include "view/event.h"

namespace view {

// Default implementation
bool Event::Visitor::visit_terminal_resize_event(const TerminalResizeEvent* event) {
    return false;
}

bool TerminalResizeEvent::accept(Visitor* visitor) const {
    return visitor->visit_terminal_resize_event(this);
}

} // namespace view
