#ifndef VIEW_SPLIT_VIEW_H_
#define VIEW_SPLIT_VIEW_H_

#include <memory>

#include "event.h"
#include "view.h"

namespace view {

// `SplitView` presents two `View`s next to one another, either vertically or horizontally.
// It delivers `Event`s to one and only one of the two `View`s: the one that is in focus.
// Initially, the left (top) `View` of a vertical (horizontal) `SplitView`.
// The `View` in focus can be changed once a "shift-left" or "shift-right" key combination
// is received by `SplitView`.
class SplitView : public View {
  public:
    // Constructs a `SplitView` with the specified geometry.
    // `vertical`: The child `View`s are side-by-side if only and if this value is true.
    // The child `Views` are scaled so that the width (height) ratio is `scale_first`:`scale_second`
    // for a vertical (horizontal) `SplitView`.
    //
    // Note: In general, child `View`s must not process focus-changing keys unless they themselves
    //       are instances of `SplitView`. This allows `SplitView`s to compose naturally where
    //       the change in focus transfers from the children to the parent.
    SplitView(std::shared_ptr<View> first,
              std::shared_ptr<View> second,
              bool vertical = true,
              size_t scale_first = 1,
              size_t scale_second = 1);

    bool on_event(const Event* event) override;

    bool visit_combo_key_event(const ComboKeyEvent* event) override;

  protected:
    void render(Pane* pane) override;

  private:
    const bool vertical;
    const size_t scale_first;
    const size_t scale_second;
    const std::shared_ptr<View> first;
    const std::shared_ptr<View> second;

    bool first_in_focus;
};

} // namespace view

#endif // VIEW_SPLIT_VIEW_H_
