#ifndef VIEW_MEMORY_PANE_H_
#define VIEW_MEMORY_PANE_H_

#include <string>
#include <vector>

#include "pane.h"

namespace view {

// `MemoryPane` emulates a fixed-size terminal, where every character is initially null ('\0').
class MemoryPane : public Pane {
  public:
    MemoryPane(size_t height, size_t width);

    void put_char(wchar_t ch, size_t pos_y, size_t pos_x) override;

    std::vector<std::wstring> rows; // Exposed for testing

  private:
    Pane* clone() override;
};

} // namespace view

#endif // VIEW_MEMORY_PANE_H_
