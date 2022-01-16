#include "ncurses_pane.h"

#include "ncurses.h"

namespace view {
NCursesPane::NCursesPane(WINDOW* root_window)
    : root_window(root_window), Pane(0, 0, getmaxy(root_window), getmaxx(root_window)) {}

void NCursesPane::put_char(wchar_t ch, size_t pos_y, size_t pos_x) {
    if (pos_y >= get_height() || pos_x >= get_width()) return;
    mvwaddch(root_window, off_y(pos_y), off_x(pos_x), ch);
}

// Override the default implementation to make use of a built-in ncurses function
void NCursesPane::put_row(const std::string& row, size_t pos_y, size_t pos_x) {
    if (pos_y >= get_height() || pos_x >= get_width()) return;

    size_t print_len = std::min(row.length(), get_width() - pos_x);
    mvwaddstr(root_window, off_y(pos_y), off_x(pos_x), row.substr(0, print_len).c_str());
}

// Override the default implementation to make use of a built-in ncurses function
void NCursesPane::h_line(wchar_t ch, size_t pos_y, size_t pos_x, size_t len) {
    if (pos_y >= get_height() || pos_x >= get_width()) return;
    mvwhline(root_window, off_y(pos_y), off_x(pos_x), ch, len);
}

NCursesPane* NCursesPane::clone() {
    return new NCursesPane(*this);
}

} // namespace view
