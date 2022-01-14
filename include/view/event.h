#ifndef VIEW_EVENT_H_
#define VIEW_EVENT_H_

namespace view {

class TerminalResizeEvent;

// `Event` represents an input to, or a change in state of the terminal.
class Event {
  public:
    // `Visitor` facilitates prescribing how a class should react to each type of `Event`.
    class Visitor {
      public:
        virtual bool visit_terminal_resize_event(const TerminalResizeEvent* event);
    };

    virtual ~Event() = default;

    // Dispatches the correct `Visitor` method.
    virtual bool accept(Visitor* visitor) const = 0;
};

// `TerminalResizeEvent` represents the resizing of the terminal.
class TerminalResizeEvent : public Event {
  public:
    bool accept(Visitor* visitor) const override;
};

} // namespace view

#endif // VIEW_EVENT_H_
