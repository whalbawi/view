#ifndef VIEW_VIEW_H_
#define VIEW_VIEW_H_

#include "event.h"

namespace view {

class Pane;

// `View` is main the building block of a TUI created using `view`. It reacts to `Event`s and then
// renders its state on a `Pane`.
class View : public Event::Visitor {
  public:
    virtual ~View() = default;

    // Processes an `Event`. Subclasses must implement `Event::Visitor` to perform the appropriate
    // action depending on type of `Event` being passed.
    // Returns true if and only if the event is consumed.
    virtual bool on_event(const Event* event) = 0;

    // Displays the state of the `View` on the provided `Pane`.
    virtual void render(Pane* pane) = 0;
};

} // namespace view

#endif // VIEW_VIEW_H_
