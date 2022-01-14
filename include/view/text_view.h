#ifndef VIEW_TEXT_VIEW_H_
#define VIEW_TEXT_VIEW_H_

#include <string>

#include "view.h"

namespace view {

// `TextView` is a read-only `View` that holds a string of text, and renders it on the provided
// `Pane`. It does not process any events.
class TextView : public View {
  public:
    bool on_event(const Event* event) override;
    void render(Pane* pane) override;

    // Replace the existing content, if any.
    void set_content(const std::string& content);

  private:
    std::string content;
};

}

#endif // VIEW_TEXT_VIEW_H_
