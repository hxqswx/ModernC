// ModernC++.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <typeinfo>
#include <string>
#include <type_traits>
#include <chrono>
#include <thread>
#include <array>
#include <algorithm>
#include <set>
#include <map>
#include <variant>
#include <any>
#include <regex>

#include "C++17Template.h"
#include "ModemC++.h"
using namespace std;

/*
* Welcome back to C++ - Modern C++
https://docs.microsoft.com/en-us/cpp/cpp/welcome-back-to-cpp-modern-cpp?view=vs-2019
*/

// Resources and smart pointers
void functionUsingWidget() {
  widget w(1000000);   // lifetime automatically tied to enclosing scope
              // constructs w, including the w.data gadget member
  // ...
  w.do_something();
  // ...
} // automatic destruc\Repos

// Standard Library algorithms

/*
Here are some important examples:

for_each, the default traversal algorithm (along with range-based for loops).

transform, for not-in-place modification of container elements

find_if, the default search algorithm.

sort, lower_bound, and the other default sorting and searching algorithms.

To write a comparator, use strict < and use named lambdas when you can.
*/

void funcrangebasedfor()
{
  std::vector<int> v{ 1,2,3 };

  // C-style
  for (unsigned int i = 0; i < v.size(); ++i)
  {
    std::cout << v[i];
  }

  // Modern C++:
  for (auto& num : v)
  {
    std::cout << num;
  }
}

void funcAlgo()
{
  auto comp = [](const widget& w1, const widget& w2)
  {return w1.weight() < w2.weight(); };

  std::vector<widget> v;
  v.emplace_back(1);
  v.emplace_back(2);
  v.emplace_back(3);

  auto it = v.begin(); // auto
  std::cout << typeid(*it).name() << std::endl;

  std::sort(v.begin(), v.end(), comp);

  auto i = lower_bound(v.begin(), v.end(), v.at(1), comp);
}

/*
constexpr expressions instead of macros
*/
#define SIZE 10 // C-style
constexpr int size = 10; // modern C++




/* Regular Expression

Special Charactor Descriptions
$ Matches the end position of the input string.
(,) Marks the start and end of a subexpression. Subexpressions can be obtained for later
use.
* Matches the previous subexpression zero or more times.
+ Matches the previous subexpression one or more times.
. Matches any single character except the newline character \n.
[ Marks the beginning of a bracket expression.
? Matches the previous subexpression zero or one time, or indicates a non-greedy qualifier.
\ Marks the next character as either a special character, or a literal character, or a
backward reference, or an octal escape character. For example, n Matches the character
n. \n matches newline characters. The sequence \\ Matches the '\' character, while \(
matches the '(' character.
^ Matches the beginning of the input string, unless it is used in a square bracket
expression, at which point it indicates that the set of characters is not accepted.
{ Marks the beginning of a qualifier expression.
\ Indicates a choice between the two.
*/

void MordenC19Regex()
{
  std::string fnames[] = { "foo.txt", "bar.txt", "test", "a0.txt", "AAA.txt" };
  // In C++, `\` will be used as an escape character in the string. In order for
  // `\.` to be passed as a regular expression, it is necessary to perform second
  // escaping of `\`, thus we have `\\.`
  std::regex txt_regex("[a-z]+\\. txt");
  for (const auto& fname : fnames)
    std::cout << fname << ": " << std::regex_match(fname, txt_regex) << std::endl;

  std::regex base_regex("([a-z]+) \\. txt");
  std::smatch base_match;
  for (const auto& fname : fnames) {
    if (std::regex_match(fname, base_match, base_regex))
    {
      // the first element of std:: smatch matches the entire string
        // the second element of std:: smatch matches the first expression with brackets
      if (base_match.size() == 2)
      {
        std::string base = base_match[1].str();
        std::cout << "sub -match [0]: " << base_match[0].str() << std::endl;
        std::cout << fname << " sub -match [1]: " << base << std::endl;
      }
    }
  }
}

int main()
{
  ///////////////////////////////////////////////////////////////////////
  // C++11 Language Features
  ///////////////////////////////////////////////////////////////////////

  // Rvalue references
  {
    int x = 0; // `x` is an lvalue of type `int`
    int& xl = x; // `xl` is an lvalue of type `int&`
    // int&& xr = x; // compiler error -- `x` is an lvalue
    int&& xr2 = 0; // `xr2` is an lvalue of type `int&&`
    auto& al = x; // `al` is an lvalue of type `int&`
    auto&& al2 = x; // `al2` is an lvalue of type `int&`
    auto&& ar = 0; // `ar` is an lvalue of type `int&&`
    auto a = 0; // int

    // print type
    //std::cout << typeid(decltype(x)).name() << std::endl;
    //std::cout << typeid(decltype(xl)).name() << std::endl;
    //std::cout << typeid(decltype(xr2)).name() << std::endl;
    //std::cout << typeid(decltype(al)).name() << std::endl;
    //std::cout << typeid(decltype(al2)).name() << std::endl;
    //std::cout << typeid(decltype(ar)).name() << std::endl;
    //std::cout << typeid(decltype(a)).name() << std::endl;
  }

  // Variadic templates

  {
    static_assert(arity<>::value == 0);
    static_assert(arity<char, short, int>::value == 3);
  }

  // Initializer lists
  {
    auto list = { 1, 2, 3 };
    sum(list); // == 6
    sum({ 1, 2, 3 }); // == 6
    sum({}); // == 0
  }

  // static assertion
  {
    constexpr int x = 1;
    constexpr int y = 1;
    static_assert(x == y, "x != y");
  }

  // auto
  {
    auto a = 3.14; // double
    auto b = 1; // int
    auto& c = b; // int&
    auto d = { 0 }; // std::initializer_list<int>
    auto&& e = 1; // int&&
    auto&& f = b; // int&
    auto g = new auto(123); // int*
    const auto h = 1; // const int
    auto i = 1, j = 2, k = 3; // int, int, int
    // auto l = 1, m = true, n = 1.61; // error -- `l` deduced to be int, `m` is bool
    // auto o; // error -- `o` requires initializer

  }

  {
    add(1, 2); // == 3
    add(1, 2.0); // == 3.0
    add(1.5, 1.5); // == 3.0
  }

  // Lambda
  {
    int x = 1;

    auto getX = [=] { return x; };
    getX(); // == 1

    auto addX = [=](int y) { return x + y; };
    addX(1); // == 2

    auto getXRef = [&]() -> int& { return x; };
    getXRef(); // int& to `x`
  }

  // lambda mutable
  {
    int x = 1;

    auto f1 = [&x] { x = 2; }; // OK: x is a reference and modifies the original

    // auto f2 = [x] { x = 2; }; // ERROR: the lambda can only perform const-operations on the captured value
                  // vs.
    auto f3 = [x]() mutable { x = 2; }; // OK: the lambda can perform any operations on the captured value
  }

  // decltype
  {
    int a = 1; // `a` is declared as type `int`
    decltype(a) b = a; // `decltype(a)` is `int`
    const int& c = a; // `c` is declared as type `const int&`
    decltype(c) d = a; // `decltype(c)` is `const int&`
    decltype(123) e = 123; // `decltype(123)` is `int`
    int&& f = 1; // `f` is declared as type `int&&`
    decltype(f) g = 1; // `decltype(f) is `int&&`
    decltype((a)) h = g; // `decltype((a))` is int&
  }

  // template alias
  {

    Vec<int> v{}; // std::vector<int>

    using String = std::string;
    String s{ "foo" };
  }

  // nullptr
  {
    // foo(NULL); // error -- ambiguous
    foo(nullptr); // calls foo(char*)
  }

  // Strongly-typed enums
  {
    // Specifying underlying type as `unsigned int`
    enum class Color : unsigned int { Red = 0xff0000, Green = 0xff00, Blue = 0xff };
    // `Red`/`Green` in `Alert` don't conflict with `Color`
    enum class Alert : bool { Red, Green };
    Color c = Color::Red;
  }

  // Attributes
  {

  }

  // constexpr
  {
    int a = square(2);  // mov DWORD PTR [rbp-4], 4

    int b = square2(2); // mov edi, 2
              // call square2(int)
              // mov DWORD PTR [rbp-8], eax

    // constexpr values are those that the compiler can evaluate at compile-time:
    const int x = 123;
    constexpr const int& y = x; // error -- constexpr variable `y` must be initialized by a constant expression

    std::cout << y << std::endl;
  }

  // Delegating constructors
  {
    Foo_DC foo{};
    foo.foo; // == 0
  }

  // 

  ///////////////////////////////////////////////////////////////////////
  // C++11 Library Features
  ///////////////////////////////////////////////////////////////////////

  // std::move
  {
    std::unique_ptr<int> p1{ new int };
    // std::unique_ptr<int> p2 = p1; // error -- cannot copy unique pointers
    std::unique_ptr<int> p3 = std::move(p1); // move `p1` into `p2` // now unsafe to dereference object held by `p1`
  }


  // std::forward
  {
    wrapper(A{}); // moved
    A a{};
    wrapper(a); // copied
    wrapper(std::move(a)); // moved
  }


  // std::to_string
  {
    std::string str1 = std::to_string(1.2); // == "1.2"
    std::string str2 = std::to_string(123); // == "123"
  }

  // Type traits
  {
    static_assert(std::is_integral<int>::value);
    static_assert(std::is_same<int, int>::value);
    static_assert(std::is_same<std::conditional<true, int, double>::type, int>::value);
  }


  // Smart pointers - unique_ptr
  {
    std::unique_ptr<Foo> p1{ new Foo{} };  // `p1` owns `Foo`
    if (p1) p1->bar();
    std::unique_ptr<Foo> pm = std::make_unique<Foo>();
    if (pm) pm->bar();

    {
      std::unique_ptr<Foo> p2{ std::move(p1) };  // Now `p2` owns `Foo`
      if (p2) p2->bar();;

      //p1 = std::move(p2);  // Ownership returns to `p1` -- `p2` gets destroyed
    }

    if (p1) p1->bar();
    // `Foo` instance is destroyed when `p1` goes out of scope
  }

  // Smart pointer - shared_ptr
  {

    std::shared_ptr<Foo> p1{ new Foo{} };
    std::shared_ptr<Foo> pm = std::make_shared<Foo>();
    // Perhaps these take place in another threads?
    foo(p1);
    bar(p1);
    baz(p1);
  }

  // std::chrono
  {
    std::chrono::time_point<std::chrono::steady_clock> start, end;
    start = std::chrono::steady_clock::now();
    // Some computations...
    std::this_thread::sleep_for(std::chrono::milliseconds(123));
    end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << elapsed_seconds.count() << std::endl; // t number of seconds, represented as a `double`
  }

  // std::tuple
  {
    // 'playerProfile' has type 'std::tuple<int, std::string, std::string>'.
    auto playerProfile = std::make_tuple(51, "Frans Nielsen", "NYI");
    auto p0 = std::get<0>(playerProfile); // 51
    auto p1 = std::get<1>(playerProfile); // "Frans Nielsen"
    auto p2 = std::get<2>(playerProfile); // "NYI"
  }

  // std::tie
  {
    // With tuples...
    std::string playerName;
    auto playerProfile = std::make_tuple(91, "John Tavares", "NYI");
    std::tie(std::ignore, playerName, std::ignore) = playerProfile;

    std::cout << playerName << " player no. " << std::get<0>(playerProfile) << std::endl;

    // With pairs...
    std::string yes, no;
    std::tie(yes, no) = std::make_pair("yes", "no");
  }

  // std::array
  {
    std::array<int, 3> a = { 2, 1, 3 };
    std::sort(a.begin(), a.end()); // a == { 1, 2, 3 }
    for (int& x : a) x *= 2; // a == { 2, 4, 6 }
  }


  // Deleted functions 
  {
    A3 x{ 123 };
    // A3 y = x; // error -- call to deleted copy constructor
    // y = x; // error -- operator= deleted
  }


  // rage based loop
  {
    std::array<int, 5> a{ 1, 2, 3, 4, 5 };
    for (int& x : a) x *= 2;
    // a == { 2, 4, 6, 8, 10 }
  }

  // special member functions
  {
    A4 a1 = f(A4{}); // move-constructed from rvalue temporary
    A4 a2 = std::move(a1); // move-constructed using std::move
    A4 a3 = A4{};
    a2 = std::move(a3); // move-assignment using std::move
    a1 = f(A4{}); // move-assignment from rvalue temporary
  }

  // Explicit conversion functions
  {
    A5 a{};
    if (a) {}; // OK calls A::operator bool()
    bool ba = a; // OK copy-initialization selects A::operator bool()

    B5 b{};
    if (b) {}// OK calls B::operator bool()
    //bool bb = b; // error copy-initialization does not consider B::operator bool()
  }

  // Inline namespaces
  {
    int version{ Program::getVersion() };              // Uses getVersion() from Version2
    int oldVersion{ Program::Version1::getVersion() }; // Uses getVersion() from Version1
    bool firstVersion{ Program::Version1::isFirstVersion() };    // Does not compile when Version2 is added
    int version2{ Program::Version2::getVersion() };              // Uses getVersion() from Version2
  }

  // Right angle Brackets
  {
    typedef std::map<int, std::map <int, std::map <int, int> > > cpp98LongTypedef;
    typedef std::map<int, std::map <int, std::map <int, int>>>   cpp11LongTypedef;
  }

  ///////////////////////////////////////////////////////////////////////
  // C++14 Language Features
  ///////////////////////////////////////////////////////////////////////
  /*
  Binary literals
  Binary literals provide a convenient way to represent a base-2 number. It is possible to separate digits with '.
  */
  {
    0b110; // == 6
    0b1111'1111; // == 255
  }

  /*
  Generic lambda expressions
  C++14 now allows the auto type-specifier in the parameter list, enabling polymorphic lambdas.
  */
  {
    auto identity = [](auto x) { return x; };
    int three = identity(3); // == 3
    std::string foo = identity("foo"); // == "foo"
  }

  /*
  Lambda capture initializers
  This allows creating lambda captures initialized with arbitrary expressions. The name given to the captured value does not need to be related to any variables in the enclosing scopes and introduces a new name inside the lambda body. The initializing expression is evaluated when the lambda is created (not when it is invoked).
  */
  {
    auto f = [x = factory(2)]{ return x; }; // returns 20

    auto generator = [x = 0]() mutable {
      // this would not compile without 'mutable' as we are modifying x on each call
      return x++;
    };
    auto a = generator(); // == 0
    auto b = generator(); // == 1
    auto c = generator(); // == 2
  }

  /*
  Because it is now possible to move (or forward) values into a lambda that could previously be only captured by copy or reference we can now capture move-only types in a lambda by value. Note that in the below example the p in the capture-list of task2 on the left-hand-side of = is a new variable private to the lambda body and does not refer to the original p.
  */
  {
    auto p = std::make_unique<int>(1);

    // auto task1 = [=] { *p = 5; }; // ERROR: std::unique_ptr cannot be copied
                    // vs.
    auto task2 = [p = std::move(p)]{ *p = 5; }; // OK: p is move-constructed into the closure object
                          // the original p is empty after task2 is created
  }

  /*
  Using this reference-captures can have different names than the referenced variable.
  */
  {
    auto x = 1;
    auto f = [&r = x, x = x * 10]
    {
      ++r;
      return r + x;
    };
    f(); // sets x to 2 and returns 12
  }

  /*
  Return type deduction
  Using an auto return type in C++14, the compiler will attempt to deduce the type for you. With lambdas, you can now deduce its return type using auto, which makes returning a deduced reference or rvalue reference possible.
  */
  // Deduce return type as `int`.
  {
    // Returns a reference to a deduced type.
    auto g = [](auto& x) -> auto& { return ft(x); };
    int y = 123;
    int& z = g(y); // reference to `y`
  }

  /*
  decltype(auto)
  The decltype(auto) type-specifier also deduces a type like auto does. However, it deduces return types while keeping their references or "const-ness", while auto will not.
  */
  {
    const int x = 0;
    auto x1 = x; // int
    decltype(auto) x2 = x; // const int
    int y = 0;
    int& y1 = y;
    auto y2 = y1; // int
    decltype(auto) y3 = y1; // int&
    int&& z = 0;
    auto z1 = std::move(z); // int
    decltype(auto) z2 = std::move(z); // int&&

  }

  // Note: Especially useful for generic code!
  {
    int x = 123;
    static_assert(std::is_same<const int&, decltype(f2(x))>::value == 0);
    static_assert(std::is_same<int, decltype(f2(x))>::value == 1);
    static_assert(std::is_same<const int&, decltype(g2(x))>::value == 1);
  }

  /*
  Relaxing constraints on constexpr functions
  In C++11, constexpr function bodies could only contain a very limited set of syntaxes, including (but not limited to): typedefs, usings, and a single return statement. In C++14, the set of allowable syntaxes expands greatly to include the most common syntax such as if statements, multiple returns, loops, etc.
  */
  {
    // factorial
    std::cout << "factorial" << factorial(5) << std::endl; // == 120
  }

  /*
  Variable Templates
  C++14 allows variables to be templated:
  */
  {
    std::cout << "pi = " << pi<int> << std::endl;
  }

  ///////////////////////////////////////////////////////////////////////
  // C++14 Library Features
  ///////////////////////////////////////////////////////////////////////
  /*
  User-defined literals for standard library types
  New user-defined literals for standard library types, including new built-in literals for chrono and basic_string. These can be constexpr meaning they can be used at compile-time. Some uses for these literals include compile-time integer parsing, binary literals, and imaginary number literals.
  */
  {
    using namespace std::chrono_literals;
    auto day = 24h;
    auto c = day.count(); // == 24
    auto c1 = std::chrono::duration_cast<std::chrono::minutes>(day).count(); // == 1440
  }

  /*
  Compile-time integer sequences
  The class template std::integer_sequence represents a compile-time sequence of integers. There are a few helpers built on top:

  std::make_integer_sequence<T, N...> - creates a sequence of 0, ..., N - 1 with type T.
  std::index_sequence_for<T...> - converts a template parameter pack into an integer sequence.
  Convert an array into a tuple:
  */

  /*
  std::make_unique
  std::make_unique is the recommended way to create instances of std::unique_ptrs due to the following reasons:

  Avoid having to use the new operator.
  Prevents code repetition when specifying the underlying type the pointer shall hold.
  Most importantly, it provides exception-safety. Suppose we were calling a function foo like so:
  foo(std::unique_ptr<T>{ new T{} }, function_that_throws(), std::unique_ptr<T>{ new T{} });
  The compiler is free to call new T{}, then function_that_throws(), and so on... Since we have allocated data on the heap in the first construction of a T, we have introduced a leak here. With std::make_unique, we are given exception-safety:

  foo(std::make_unique<T>(), function_that_throws(), std::make_unique<T>());
  See the section on smart pointers for more information on std::unique_ptr and std::shared_ptr.
  */

  ///////////////////////////////////////////////////////////////////////
  // C++17 Language Features
  ///////////////////////////////////////////////////////////////////////

  {
    MyContainer<int> c1{ 1 }; // OK MyContainer<int>
    MyContainer<float> c2; // OK MyContainer<float>
  }


  {
    // Explicitly pass type `int` as template argument.
    //auto seq = std::integer_sequence<int, 0, 1, 2>();
    //// Type is deduced to be `int`.
    //auto seq2 = my_integer_sequence<0, 1, 2>();
  }

  /*
  Folding expressions
  A fold expression performs a fold of a template parameter pack over a binary operator.

  An expression of the form (... op e) or (e op ...), where op is a fold-operator and e is an unexpanded parameter pack, are called unary folds.
  An expression of the form (e1 op ... op e2), where op are fold-operators, is called a binary fold. Either e1 or e2 are unexpanded parameter packs, but not both.
  */

  {
    //bool b = true;
    //bool& b2 = b;
    //logicalAnd(b, b2, true); // == true

    sum(1.0, 2.0f, 3);     // == 6.0
  }

  /*
  New rules for auto deduction from braced-init-list
  Changes to auto deduction when used with the uniform initialization syntax. Previously, auto x{ 3 }; deduces a std::initializer_list<int>, which now deduces to int.
  */
  {
    // auto x1{ 1, 2, 3 }; // error: not a single element
    auto x2 = { 1, 2, 3 }; // decltype(x2) is std::initializer_list<int>
    auto x3{ 3 }; // decltype(x3) is int
    auto x4{ 3.0 }; // decltype(x4) is double
  }

  /*
  constexpr lambda
  Compile-time lambdas using constexpr.
  */
  {
    auto identity = [](int n) constexpr { return n; };
    static_assert(identity(123) == 123);
  }

  {
    constexpr auto add = [](int x, int y)
    {
      auto L = [=] { return x; };
      auto R = [=] { return y; };
      return [=] { return L() + R(); };
    };

    static_assert(add(1, 2)() == 3);
  }

  {
    static_assert(addOne(1) == 2);
  }

  /*
  Lambda capture this by value
  Capturing this in a lambda's environment was previously reference-only. An example of where this is problematic is asynchronous code using callbacks that require an object to be available, potentially past its lifetime. *this (C++17) will now make a copy of the current object, while this (C++11) continues to capture by reference.
  */
  {
    MyObj mo;
    auto valueCopy = mo.getValueCopy();
    auto valueRef = mo.getValueRef();
    mo.value = 321;
    // valueCopy; // 123
    // valueRef; // 321
    std::cout << valueCopy() << " vs " << valueRef() << std::endl;
  }

  /*
  Inline variables
  The inline specifier can be applied to variables as well as to functions. A variable declared inline has the same semantics as a function declared inline.
  */
  {
    // Disassembly example using compiler explorer.
    struct S { int x; };
    //  inline S x1 = S{ 321 }; // mov esi, dword ptr [x1]
                  // x1: .long 321

    S x2 = S{ 123 };        // mov eax, dword ptr [.L_ZZ4mainE2x2]
                // mov dword ptr [rbp - 8], eax
                // .L_ZZ4mainE2x2: .long 123
  }

  /*
  Structured bindings
  A proposal for de-structuring initialization, that would allow writing auto [ x, y, z ] = expr; where the type of expr was a tuple-like object, whose elements would be bound to the variables x, y, and z (which this construct declares). Tuple-like objects include std::tuple, std::pair, std::array, and aggregate structures.
  */
  {
    using Coordinate = std::pair<int, int>;
    //Coordinate origin() 
    //{
    //  return Coordinate{ 0, 0 };
    //}

    using my_tuple = std::tuple<int, double, std::string>;

    const auto [a, b, c] = my_tuple{ 1, 1.1, "2" };

    std::cout << a << b << c << std::endl;

    const auto [x, y] = Coordinate{ 0, 0 };
    x; // == 0
    y; // == 0

  }

  /*
  Selection statements with initializer
  New versions of the if and switch statements which simplify common code patterns and help users keep scopes tight.
  */
  {
    //{
    //  std::lock_guard<std::mutex> lk(mx);
    //  if (v.empty())
    //  {
    //    v.push_back(val);
    //  }
    //}
    //// vs.
    //{
    //  if (std::lock_guard<std::mutex> lk(mx); v.empty())
    //  {
    //    v.push_back(val);
    //  }
    //}
  }

  {
    //Foo gadget(args);
    //switch (auto s = gadget.status()) 
    //{
    //case OK: gadget.zip(); break;
    //case Bad: throw BadFoo(s.message());
    //}
    //// vs.
    //switch (Foo gadget(args); auto s = gadget.status()) 
    //{
    //case OK: gadget.zip(); break;
    //case Bad: throw BadFoo(s.message());
    //}
  }

  /*
  constexpr if
  Write code that is instantiated depending on a compile-time condition.
  */
  {
    static_assert(isIntegral<int>() == true);
    static_assert(isIntegral<char>() == true);
    static_assert(isIntegral<double>() == false);
    struct S {};
    static_assert(isIntegral<S>() == false);
  }

  /*
  UTF-8 Character Literals
  A character literal that begins with u8 is a character literal of type char. The value of a UTF-8 character literal is equal to its ISO 10646 code point value.
  */
  {
    char x = u8'x';
  }

  /*
  Direct List Initialization of Enums
  Enums can now be initialized using braced syntax.
  */
  {
    enum byte : unsigned char {};
    byte b{ 0 }; // OK
    // byte c{ -1 }; // ERROR
    byte d = byte{ 1 }; // OK
    // byte e = byte{ 256 }; // ERROR
  }

  ///////////////////////////////////////////////////////////////////////
  // C++17 Library Features
  ///////////////////////////////////////////////////////////////////////

  /*
  std::variant
  The class template std::variant represents a type-safe union. An instance of std::variant at any given time holds a value of one of its alternative types (it's also possible for it to be valueless).
  */
  {
    std::variant<int, double> v{ 12 };
    auto vi = std::get<int>(v); // == 12
    auto v0 = std::get<0>(v); // == 12
    v = 12.0;
    auto vd = std::get<double>(v); // == 12.0
    auto v1 = std::get<1>(v); // == 12.0
  }

  /*
  std::optional
  The class template std::optional manages an optional contained value, i.e. a value that may or may not be present. A common use case for optional is the return value of a function that may fail.
  */
  {
    auto e = create(false).value_or("empty"); // == "empty"
    auto v = create(true).value(); // == "Godzilla", // optional-returning factory functions are usable as conditions of while and if
    if (auto str = create(true))
    {
      // ...
    }
  }

  /*
  std::any
  A type-safe container for single values of any type.
  */
  {
    std::any x{ 5 };
    auto v = x.has_value(); // == true
    auto vi = std::any_cast<int>(x); // == 5
    std::any_cast<int&>(x) = 10;
    auto vc = std::any_cast<int>(x); // == 10
  }

  /*
  std::string_view
  A non-owning reference to a string. Useful for providing an abstraction on top of strings (e.g. for parsing).
  */
  {
    std::string_view strv{ "Peach" };

    std::cout << strv << '\n';

    // Ignore the first characters.
    strv.remove_prefix(1);

    std::cout << strv << '\n';

    // Ignore the last 2 characters.
    strv.remove_suffix(2);

    std::cout << strv << '\n';

  }

  /*
  std::invoke
  Invoke a Callable object with parameters. Examples of Callable objects are std::function or std::bind where an object can be called similarly to a regular function.
  */
  {
    auto add = [](int x, int y)
    {
      return x + y;
    };
    Proxy<decltype(add)> p{ add };
    p(1, 2); // == 3
  }

  /*
  std::apply
  Invoke a Callable object with a tuple of arguments.
  */
  {
    auto add = [](int x, int y)
    {
      return x + y;
    };
    std::apply(add, std::make_tuple(1, 2)); // == 3
  }

  /*
  //  extract
  Splicing for maps and sets
  Moving nodes and merging containers without the overhead of expensive copies, moves, or heap allocations/deallocations.

  Moving elements from one map to another:
  */
  {
    std::map<int, string> src{ { 1, "one" },{ 2, "two" },{ 3, "buckle my shoe" } };
    std::map<int, string> dst{ { 3, "three" } };
    dst.insert(src.extract(src.find(1))); // Cheap remove and insert of { 1, "one" } from `src` to `dst`.
    dst.insert(src.extract(2)); // Cheap remove and insert of { 2, "two" } from `src` to `dst`.
    // dst == { { 1, "one" }, { 2, "two" }, { 3, "three" } };
  }

  // Inserting an entire set:
  {
    std::set<int> src{ 1, 3, 5 };
    std::set<int> dst{ 2, 4, 5 };
    dst.merge(src);
    // src == { 5 }
    // dst == { 1, 2, 3, 4, 5 }
  }

  // Inserting elements which outlive the container:
  {
    //auto elementFactory() 
    //{
    //  std::set<...> s;
    //  s.emplace(...);
    //  return s.extract(s.begin());
    //}
    //s2.insert(elementFactory());
  }

  // Changing the key of a map element:
  std::map<int, string> m{ { 1, "one" },{ 2, "two" },{ 3, "three" } };
  auto e = m.extract(2);
  e.key() = 4;
  m.insert(std::move(e));
  // m == { { 1, "one" }, { 3, "three" }, { 4, "two" } }

  return 0;
}

