#include "view/frame_view.h"

#include "pane.h"

#define NWC 4194412 // ┌
#define SWC 4194413 // └
#define NEC 4194411 // ┐
#define SEC 4194410 // ┘
#define NH 4194417  // ─
#define SH 4194417  // ─
#define WV 4194424  // │
#define EV 4194424  // │

namespace view {

FrameView::FrameView(std::shared_ptr<View> wrapped_view) : wrapped_view(std::move(wrapped_view)) {}

bool FrameView::on_event(const Event* event) {
    return wrapped_view->on_event(event);
}

void FrameView::render(Pane* pane) {
    pane->put_char(NWC, 0, 0);
    pane->h_line(NH, 0, 1, pane->get_width() - 2);
    pane->put_char(NEC, 0, pane->get_width() - 1);

    for (size_t i = 1; i < pane->get_height() - 1; ++i) {
        pane->put_char(WV, i, 0);
        pane->put_char(EV, i, pane->get_width() - 1);
    }

    pane->put_char(SWC, pane->get_height() - 1, 0);
    pane->h_line(SH, pane->get_height() - 1, 1, pane->get_width() - 2);
    pane->put_char(SEC, pane->get_height() - 1, pane->get_width() - 1);

    Pane* child = pane->limit(1, 1, pane->get_height() - 2, pane->get_width() - 2);
    wrapped_view->render(child);
}

} // namespace view
