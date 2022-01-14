#ifndef VIEW_FRAME_VIEW_H_
#define VIEW_FRAME_VIEW_H_

#include <memory>

#include "view.h"

namespace view {

// `FrameView` renders a frame around the wrapped `View`. Each dimension of the wrapped `View`
// is reduced by two units to account for the border characters on each side.
class FrameView : public View {
  public:
    explicit FrameView(std::shared_ptr<View> wrapped_view);

    // Always delegates the call to the wrapped `View`.
    bool on_event(const Event* event) override;
    // First renders a frame along the outer edge of the `Pane`, and then extracts a sub-pane from
    // the provided one on which the wrapped `View` is rendered.
    void render(Pane* pane) override;

  private:
    const std::shared_ptr<View> wrapped_view;
};

} // namespace view

#endif // VIEW_FRAME_VIEW_H_
