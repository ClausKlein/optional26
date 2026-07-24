// examples/optional_ref.cpp                                          -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <beman/optional/optional.hpp>

#include <string>

struct Cat {
    int catalog_index{0};
};

namespace std17 {

// Prior to C++26, the code would look like this.
// Using raw pointers to represent optional references.
// Note: Using smart pointers would also be a choice, but it involves ownership semantics.

static Cat* find_cat(const std::string& /*unused*/) { return nullptr; }

static Cat* do_it(Cat& cat) { return &cat; }

static Cat* api() {
    Cat* cat = find_cat("Fido");
    if (cat != nullptr) {
        return do_it(*cat);
    }
    return nullptr;
}

} // namespace std17

namespace std26 {
// After C++26 with P2988R5, the code would look like this.
// Using directly optional to represent optional references.

static beman::optional::optional<Cat&> find_cat(const std::string& /*unused*/) { return {}; }

static beman::optional::optional<Cat&> do_it(Cat& cat) { return {cat}; }

static beman::optional::optional<Cat&> api() {
    const beman::optional::optional<Cat&> cat = find_cat("Fido");
    return cat.and_then(do_it);
}

} // namespace std26

static int example() {
    // Example from P2988R5: optional reference.
    [[maybe_unused]] const Cat*                            old_cat = std17::api();
    [[maybe_unused]] const beman::optional::optional<Cat&> new_cat = std26::api();

    return 0;
}

int main() { example(); }
// # build example:
// $ cmake --workflow --preset gcc-14
//
// # run example:
// $ .build/gcc-14/examples/RelWithDebInfo/optional_ref
