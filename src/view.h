#ifndef VIEW_VIEW_H_
#define VIEW_VIEW_H_

#include <string>

namespace view {

class View {
  public:
    static std::string get_version();

    void add(int a, int b);
    int get_result() const;

  private:
    int result;
};

} // namespace view

#endif // VIEW_VIEW_H_
