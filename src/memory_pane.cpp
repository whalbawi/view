#include "memory_pane.h"

namespace view {

MemoryPane::MemoryPane(size_t height, size_t width) : Pane(0, 0, height, width) {}

void MemoryPane::put_char(wchar_t ch, size_t pos_y, size_t pos_x) {}

Pane* MemoryPane::clone() {
    return nullptr;
}

} // namespace view
