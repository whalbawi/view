#include "view/split_view.h"

#include "pane.h"

namespace view {

SplitView::SplitView(std::shared_ptr<View> first,
                     std::shared_ptr<View> second,
                     bool vertical,
                     size_t scale_first,
                     size_t scale_second)
    : first(std::move(first)),
      second(std::move(second)),
      vertical(vertical),
      first_in_focus(true),
      scale_first(scale_first),
      scale_second(scale_second) {}

bool SplitView::on_event(const Event* event) {
    if (first_in_focus ? first->on_event(event) : second->on_event(event)) return true;

    return event->accept(this);
}

bool SplitView::visit_combo_key_event(const ComboKeyEvent* event) {
    if (event->function_key != ComboKeyEvent::FunctionKey::SHIFT) return false;

    switch (event->key) {
    case ComboKeyEvent::Key::LEFT:
        if (first_in_focus) return false;
        break;
    case ComboKeyEvent::Key::RIGHT:
        if (!first_in_focus) return false;
        break;
    default:
        return false;
    }

    first_in_focus = !first_in_focus;

    return true;
}

void SplitView::render(Pane* pane) {
    size_t height_first;
    size_t height_second;
    size_t width_first;
    size_t width_second;
    size_t off_y_second;
    size_t off_x_second;
    size_t scale = scale_first + scale_second;
    if (vertical) {
        height_first = pane->get_height();
        width_first = pane->get_width() * scale_first / scale;
        height_second = pane->get_height();
        width_second = pane->get_width() - width_first;
        off_y_second = 0;
        off_x_second = width_first;
    } else {
        height_first = pane->get_height() * scale_first / scale;
        width_first = pane->get_width();
        height_second = pane->get_height() - height_first;
        width_second = pane->get_width();
        off_y_second = height_first;
        off_x_second = 0;
    }

    Pane* pane_first = pane->limit(0, 0, height_first, width_first);
    Pane* pane_second = pane->limit(off_y_second, off_x_second, height_second, width_second);

    first->render(pane_first);
    second->render(pane_second);
}

} // namespace view
