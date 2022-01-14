#ifndef VIEW_NCURSES_PANE_H_
#define VIEW_NCURSES_PANE_H_

#include <string>

#include "pane.h"

// Cannot forward declare `WINDOW` as it is a typedef in the ncurses library.
typedef struct _win_st WINDOW;

namespace view {

// `NCursesPane` represents an entire ncurses window.
class NCursesPane : public Pane {
  public:
    explicit NCursesPane(WINDOW* root_window);

    void put_char(wchar_t ch, size_t pos_y, size_t pos_x) override;

    void put_row(const std::string& row, size_t pos_y, size_t pos_x) override;
    void h_line(wchar_t ch, size_t pos_y, size_t pos_x, size_t len) override;

  private:
    NCursesPane* clone() override;

    WINDOW* root_window;
};

} // namespace view

#endif // VIEW_NCURSES_PANE_H_
