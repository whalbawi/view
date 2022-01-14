#ifndef VIEW_PANE_H_
#define VIEW_PANE_H_

#include <string>

namespace view {

// `Pane` is a represents a portion of the terminal on which a `View` can be rendered.
// It is specified at an offset relative to the top left corner of the backing terminal,
// and has fixed dimensions.
class Pane {
  public:
    virtual ~Pane();

    // Renders a single character at the relative offset (`pos_y`, `pos_x`).
    // The caller must ensure that values `pos_y` and `pos_x` are valid with respect to the `Pane`'s
    // dimensions.
    virtual void put_char(wchar_t ch, size_t pos_y, size_t pos_x) = 0;

    // Renders a row of characters starting at the relative offset (`pos_y`, `pos_x`).
    // The caller must ensure that the row fits on the `Pane`. Otherwise, implementations are free
    // to ignore the request and render nothing.
    // The default implementation calls `put_char` for each character in `row`, but implementations
    // are free to provide optimized implementations when possible.
    virtual void put_row(const std::string& row, size_t pos_y, size_t pos_x);

    // Renders a `len`-long repetition of the provided character, starting at the relative offset
    // (`pos_y`, `pos_x`).
    // The caller must ensure that the repetition fits on the `Pane`. Otherwise, implementations
    // are free to ignore the request and render nothing.
    // The default implementation calls `put_char` in a loop, but implementations are free
    // to provide optimized implementations when possible.
    virtual void h_line(wchar_t ch, size_t len, size_t pos_y, size_t pos_x);

    // Creates a new `Pane` at the offset (`pos_y`, `pos_x`) relative to this `Pane`'s top left
    // corner. The backend supporting this instance remains the same.
    Pane* limit(size_t pos_y, size_t pos_x, size_t height, size_t width);

    size_t get_height() const;
    size_t get_width() const;

  protected:
    Pane(size_t start_y, size_t start_x, size_t height, size_t width);

    inline size_t off_y(size_t pos_y) const {
        return start_y + pos_y;
    }

    inline size_t off_x(size_t pos_x) const {
        return start_x + pos_x;
    };

  private:
    virtual Pane* clone() = 0;

    size_t start_y;
    size_t start_x;
    size_t height;
    size_t width;
};

} // namespace view

#endif // VIEW_PANE_H_
