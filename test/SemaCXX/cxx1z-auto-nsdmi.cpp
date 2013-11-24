// RUN: %clang_cc1 -std=c++1y -verify -fsyntax-only -fblocks -emit-llvm-only %s

namespace ansdmi1 {
struct X {
  auto sz = sizeof(X);
  const auto sz_const = sizeof(*this);
  auto L = [](auto a) { return a; };
  auto L2 = [this](auto a) { return a + this->sz + f(); };
  int f() const { return 0; }
  // FIXME: this error should say something along the lines of 'sz' not being deduced yet
  auto f2() const -> decltype(this->sz) { return sizeof(sz); } //expected-error{{cannot initialize return object}}
};

auto x1 = X{};
auto x11 = X{}.sz_const;
auto x12 = X{}.L;
auto x123 = x12(5);

//auto x2 = X{}.L(5);
//auto x3 = X{}.L2(5);
//auto x4 = X{}.L2;
//auto x5 = x4(7);


}

namespace size_calc {

struct X {
  auto sz1 = sizeof(X);
  auto d = 3.5;
  auto sz2 = d + sz1;
}; 

static_assert(sizeof(X) == sizeof(double) * 3, "sizeof class should be 3 times a double");

}