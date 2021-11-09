#include "view.h"

#include "version.h"

namespace view {

std::string View::get_version() {
    return "Version: " + version() + " - Commit: " + git_commit_hash();
}

void View::add(int a, int b) {
    result = a + b;
}

int View::get_result() const {
    return result;
}

} // namespace view
