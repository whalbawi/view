#ifndef VIEW_EVENT_H_
#define VIEW_EVENT_H_

namespace view {

class ComboKeyEvent;
class TerminalResizeEvent;

// `Event` represents an input to, or a change in state of the terminal.
class Event {
  public:
    // `Visitor` facilitates prescribing how a class should react to each type of `Event`.
    class Visitor {
      public:
        virtual bool visit_combo_key_event(const ComboKeyEvent* event);
        virtual bool visit_terminal_resize_event(const TerminalResizeEvent* event);
    };

    virtual ~Event() = default;

    // Dispatches the correct `Visitor` method.
    virtual bool accept(Visitor* visitor) const = 0;
};

// `ComboKeyEvent` represents the pressing of a combination of two keys in which one is a function
// key: control, shift, alt, etc. The combination is described by the pair `function_key` and `key`,
class ComboKeyEvent : public Event {
  public:
    enum class FunctionKey {
        SHIFT,
    };

    enum class Key { LEFT, RIGHT };

    ComboKeyEvent(FunctionKey function_key, Key key);

    bool accept(Visitor* visitor) const override;

    const FunctionKey function_key;
    const Key key;
};

// `TerminalResizeEvent` represents the resizing of the terminal.
class TerminalResizeEvent : public Event {
  public:
    bool accept(Visitor* visitor) const override;
};

} // namespace view

#endif // VIEW_EVENT_H_
