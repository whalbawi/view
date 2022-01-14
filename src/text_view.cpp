#include "view/text_view.h"

#include <vector>

#include "pane.h"

namespace view {

bool TextView::on_event(const Event* event) {
    return false;
}

void TextView::render(Pane* pane) {

    std::vector<std::string> lines;
    size_t idx = 0;
    size_t end;
    size_t pos_y = 0;
    do {
        end = content.find_first_of('\n', idx);
        std::string line = content.substr(idx, end - idx);
        lines.emplace_back(line);
        pane->put_row(line, pos_y++, 0);
        idx = end + 1;
    } while (end != std::string::npos);
}

void TextView::set_content(const std::string& content) {
    this->content = content;
}

} // namespace view
