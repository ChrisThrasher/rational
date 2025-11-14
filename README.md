# Rational

[![CI](https://github.com/ChrisThrasher/rational/actions/workflows/ci.yml/badge.svg)](https://github.com/ChrisThrasher/rational/actions/workflows/ci.yml)

`Rational` is a header-only C++20 library that provides a `constexpr` implementation of a rational number.
This class template provides a type-safe interface for creating and manipulating rational numbers which supports all arithmetic operations.
The class template maintains the invariant that the fraction is always in a reduced representation.

## Usage

```cpp
#include <rational/rational.hpp>

...

Rational value(10, 3); // 10 / 3
value += Rational(1, 2); // Add one half, new value is 23 / 6
```

By default `Rational` uses `int` for the underlying integer type.
You may supply any signed integer type as a template parameter:

```cpp
Rational<std::int64_t> big_value(389'674'130'590'529, 30'943'876'602'937);
Rational<char> small_value(17, 13);
```
