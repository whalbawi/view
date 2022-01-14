#include "pane.h"

namespace view {

Pane::Pane(size_t start_y, size_t start_x, size_t height, size_t width)
    : start_y(start_y), start_x(start_x), height(height), width(width) {}

Pane::~Pane() = default;

void Pane::put_row(const std::string& row, size_t pos_y, size_t pos_x) {
    for (size_t i = 0; i < row.length(); ++i) {
        put_char(row[i], pos_y, pos_x + i);
    }
}

void Pane::h_line(wchar_t ch, size_t pos_y, size_t pos_x, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        put_char(ch, pos_y, pos_x + i);
    }
}

Pane* Pane::limit(size_t off_y, size_t off_x, size_t height_new, size_t width_new) {
    Pane* child = clone();
    child->start_y += off_y;
    child->start_x += off_x;
    child->height = height_new;
    child->width = width_new;

    return child;
}

size_t Pane::get_height() const {
    return height;
}

size_t Pane::get_width() const {
    return width;
}

} // namespace view
