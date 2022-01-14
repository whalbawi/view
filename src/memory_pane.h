#ifndef VIEW_MEMORY_PANE_H_
#define VIEW_MEMORY_PANE_H_

#include <string>
#include <vector>

#include "pane.h"

namespace view {

// TODO (whalbawi): Fill me in
class MemoryPane : public Pane {
  public:
    MemoryPane(size_t height, size_t width);

    void put_char(wchar_t ch, size_t pos_y, size_t pos_x) override;

  private:
    Pane* clone() override;

  private:
    std::vector<std::string> rows;
};

} // namespace view

#endif // VIEW_MEMORY_PANE_H_
