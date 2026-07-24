// examples/base_derived_cast.cpp                                     -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <beman/optional/optional.hpp>

namespace {

struct derived;
extern derived d;

// NOLINTNEXTLINE(hicpp-special-member-functions)
struct base {
    virtual ~base() = default;
    operator derived&() { return d; } // NOLINT(hicpp-explicit-conversions)
};

struct derived : base {};

derived d;

int example() {
    base                                b;
    derived&                            dref(b); // ok NOLINT(misc-const-correctness)
    beman::optional::optional<derived&> dopt(b); // ok NOLINT(misc-const-correctness)
    (void)dref;
    return 0;
}

} // namespace

int main() { example(); }
