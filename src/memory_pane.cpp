#include "memory_pane.h"

namespace view {

MemoryPane::MemoryPane(size_t height, size_t width) : Pane(0, 0, height, width), rows(height) {
    for (auto& row : rows) {
        row.resize(width);
    }
}

void MemoryPane::put_char(wchar_t ch, size_t pos_y, size_t pos_x) {
    if (pos_y >= get_height() || pos_x >= get_width()) return;
    rows[pos_y].at(pos_x) = ch;
}

Pane* MemoryPane::clone() {
    return new MemoryPane(*this);
}

} // namespace view
