#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <optional>

///////////////////////////////////////////////////////////////////////
// C++11 Language Features
///////////////////////////////////////////////////////////////////////
/*
Move semantics
Move semantics is mostly about performance optimization: the ability to move an object without the expensive overhead of copying. The difference between a copy and a move is that a copy leaves the source unchanged, and a move will leave the source either unchanged or radically different -- depending on what the source is. For plain old data, a move is the same as a copy.

To move an object means to transfer ownership of some resource it manages to another object. You could think of this as changing pointers held by the source object to be moved, or now held, by the destination object; the resource remains in its location in memory. Such an inexpensive transfer of resources is extremely useful when the source is an rvalue, where the potentially dangerous side-effect of changing the source after the move is redundant since the source is a temporary object that won't be accessible later.

Moves also make it possible to transfer objects such as std::unique_ptrs, smart pointers that are designed to hold a pointer to a unique object, from one scope to another.

See the sections on: rvalue references, defining move special member functions, std::move, std::forward.
*/

/*
Rvalue references
C++11 introduces a new reference termed the rvalue reference. An rvalue reference to A is created with the syntax A&&. This enables two major features: move semantics; and perfect forwarding, the ability to pass arguments while maintaining information about them as lvalues/rvalues in a generic way.

auto type deduction with lvalues and rvalues:
*/

/*
Variadic templates
The ... syntax creates a parameter pack or expands one. A template parameter pack is a template parameter that accepts zero or more template arguments (non-types, types, or templates). A template with at least one parameter pack is called a variadic template.
*/

template<typename T> struct TD;

template <typename... T>
struct arity 
{
	constexpr static int value = sizeof...(T);
};

/*
Initializer lists
A lightweight array-like container of elements created using a "braced list" syntax. For example, { 1, 2, 3 } creates a sequences of integers, that has type std::initializer_list<int>. Useful as a replacement to passing a vector of objects to a function.
*/
int sum(const std::initializer_list<int>& list) 
{
	int total = 0;
	for (auto& e : list) {
		total += e;
	}

	return total;
}

/*
auto
auto-typed variables are deduced by the compiler according to the type of their initializer.
*/

/*
Functions can also deduce the return type using auto. In C++11, a return type must be specified either explicitly, or using decltype like so:
*/
template <typename X, typename Y>
auto add(X x, Y y) -> decltype(x + y) 
{
	return x + y;
}

/*
Static assertions
Assertions that are evaluated at compile-time.
*/

/*
Lambda expressions
A lambda is an unnamed function object capable of capturing variables in scope. It features: a capture list; an optional set of parameters with an optional trailing return type; and a body. Examples of capture lists:

[] - captures nothing.
[=] - capture local objects (local variables, parameters) in scope by value.
[&] - capture local objects (local variables, parameters) in scope by reference.
[this] - capture this pointer by value.
[a, &b] - capture objects a by value, b by reference.
*/

/*
By default, value-captures cannot be modified inside the lambda because the compiler-generated method is marked as const. The mutable keyword allows modifying captured variables. The keyword is placed after the parameter-list (which must be present even if it is empty).
*/

/*
decltype
decltype is an operator which returns the declared type of an expression passed to it. Examples of decltype:
*/

/*
Template aliases
Semantically similar to using a typedef however, template aliases with using are easier to read and are compatible with templates.
*/
template <typename T>
using Vec = std::vector<T>;

/*
nullptr
C++11 introduces a new null pointer type designed to replace C's NULL macro. nullptr itself is of type std::nullptr_t and can be implicitly converted into pointer types, and unlike NULL, not convertible to integral types except bool.
*/
void foo(int) { ; }
void foo(char*) { ; }

/*
Strongly-typed enums
Type-safe enums that solve a variety of problems with C-style enums including: implicit conversions, inability to specify the underlying type, scope pollution.
*/

/*
Attributes
Attributes provide a universal syntax over __attribute__(...), __declspec, etc.
*/

/*
noreturn
*/
// `noreturn` attribute indicates `f` doesn't return.
[[noreturn]] void f()
{
	throw "error";
}

/*
constexpr
Constant expressions are expressions evaluated by the compiler at compile-time. Only non-complex computations can be carried out in a constant expression. Use the constexpr specifier to indicate the variable, function, etc. is a constant expression.
*/
constexpr int square(int x)
{
	return x * x;
}

int square2(int x)
{
	return x * x;
}

/*
Delegating constructors
Constructors can now call other constructors in the same class using an initializer list.
*/
struct Foo_DC 
{
	int foo;
	Foo_DC(int foo) : foo(foo) {}
	Foo_DC() : Foo_DC(0) {}
};

/*
User-defined literals
User-defined literals allow you to extend the language and add your own syntax. To create a literal, define a T operator "" X(...) { ... } function that returns a type T, with a name X. Note that the name of this function defines the name of the literal. Any literal names not starting with an underscore are reserved and won't be invoked. There are rules on what parameters a user-defined literal function should accept, according to what type the literal is called on.

Converting Celsius to Fahrenheit:
*/

/*
Explicit virtual overrides
Specifies that a virtual function overrides another virtual function. If the virtual function does not override a parent's virtual function, throws a compiler error.
*/
struct A1 
{
	virtual void foo();
	void bar();
};

struct B1 : A1 
{
	void foo() override; // correct -- B::foo overrides A::foo
	// void bar() override; // error -- A::bar is not virtual
	// void baz() override; // error -- B::baz does not override A::baz
};

/*
Final specifier
Specifies that a virtual function cannot be overridden in a derived class or that a class cannot be inherited from.
*/
struct A2 
{
	virtual void foo();
};

struct B2 : A2 
{
	virtual void foo() final;
};

struct C : B2 
{
	// virtual void foo(); // error -- declaration of 'foo' overrides a 'final' function
};

/*
Deleted functions
A more elegant, efficient way to provide a deleted implementation of a function. Useful for preventing copies on objects.
*/
class A3 
{
	int x;

public:
	A3(int x) : x(x) {};
	A3(const A3&) = delete;
	A3& operator=(const A3&) = delete;
};

/*
Range-based for loops
Syntactic sugar for iterating over a container's elements.
*/

/*
Special member functions for move semantics
The copy constructor and copy assignment operator are called when copies are made, and with C++11's introduction of move semantics, there is now a move constructor and move assignment operator for moves.
*/

struct A4 
{
	std::string s;
	A4() : s("test") {}
	A4(const A4& o) : s(o.s) {}
	A4(A4&& o) : s(std::move(o.s)) {}
	A4& operator=(A4&& o) 
	{
		s = std::move(o.s);
		return *this;
	}
};

A4 f(A4 a) 
{
	return a;
}


/*
Converting constructors
Converting constructors will convert values of braced list syntax into constructor arguments.
*/

/*
Explicit conversion functions
Conversion functions can now be made explicit using the explicit specifier.
*/
struct A5
{
	operator bool() const { return true; }
};

struct B5 
{
	explicit operator bool() const { return true; }
};

/*
Inline namespaces
All members of an inline namespace are treated as if they were part of its parent namespace, allowing specialization of functions and easing the process of versioning. This is a transitive property, if A contains B, which in turn contains C and both B and C are inline namespaces, C's members can be used as if they were on A.
*/
namespace Program 
{
	namespace Version1 
	{
		int getVersion() { return 1; }
		bool isFirstVersion() { return true; }
	}
	inline namespace Version2 
	{
		int getVersion() { return 2; }
	}
}

/*
Non-static data member initializers
Allows non-static data members to be initialized where they are declared, potentially cleaning up constructors of default initializations.
*/
// Default initialization prior to C++11
class Human
{
	Human() : age(0) {}
private:
	unsigned age;
};

// Default initialization on C++11
class Human_11 
{
private:
	unsigned age{ 0 };
};

/*
Right angle Brackets
C++11 is now able to infer when a series of right angle brackets is used as an operator or as a closing statement of typedef, without having to add whitespace.
*/

///////////////////////////////////////////////////////////////////////
// C++11 Library Features
///////////////////////////////////////////////////////////////////////

/*
std::move
std::move indicates that the object passed to it may be moved, or in other words, moved from one object to another without a copy.The object passed in should not be used after the move in certain situations.

A definition of std::move(performing a move is nothing more than casting to an rvalue) :

template <typename T>
typename remove_reference<T>::type&& move(T&& arg) {
return static_cast<typename remove_reference<T>::type&&>(arg);
}
*/

/*
std::forward
Returns the arguments passed to it as-is, either as an lvalue or rvalue references, and includes cv-qualification. Useful for generic code that need a reference (either lvalue or rvalue) when appropriate, e.g factories. Forwarding gets its power from template argument deduction:

T& & becomes T&
T& && becomes T&
T&& & becomes T&
T&& && becomes T&&
A definition of std::forward:

template <typename T>
T&& forward(typename remove_reference<T>::type& arg) {
return static_cast<T&&>(arg);
}
*/

/*
std::to_string
Converts a numeric argument to a std::string.
*/

/*
Type traits
Type traits defines a compile - time template - based interface to query or modify the properties of types.
*/

struct A 
{
	A() = default;
	A(const A& o) { std::cout << "copied" << std::endl; }
	A(A&& o) { std::cout << "moved" << std::endl; }
};

template <typename T>
A wrapper(T&& arg) 
{
	return A{ std::forward<T>(arg) };
}

/*
Smart pointers
C++11 introduces new smart(er) pointers: std::unique_ptr, std::shared_ptr, std::weak_ptr. std::auto_ptr now becomes deprecated and then eventually removed in C++17.

std::unique_ptr is a non-copyable, movable smart pointer that properly manages arrays and STL containers. Note: Prefer using the std::make_X helper functions as opposed to using constructors. See the sections for std::make_unique and std::make_shared.
*/

class Foo
{
public:
	void bar() const { std::cout << "bar..." << std::endl; }
};

/*
A std::shared_ptr is a smart pointer that manages a resource that is shared across multiple owners.A shared pointer holds a control block which has a few components such as the managed object and a reference counter.All control block access is thread - safe, however, manipulating the managed object itself is not thread - safe.
*/

void foo(std::shared_ptr<Foo> t)
{
	// Do something with `t`...
}

void bar(std::shared_ptr<Foo> t)
{
	// Do something with `t`...
}

void baz(std::shared_ptr<Foo> t)
{
	// Do something with `t`...
}


/*
std::chrono
The chrono library contains a set of utility functions and types that deal with durations, clocks, and time points. One use case of this library is benchmarking code:
*/

/*
Tuples
Tuples are a fixed - size collection of heterogeneous values.Access the elements of a std::tuple by unpacking using std::tie, or using std::get.
*/

/*
std::tie
Creates a tuple of lvalue references. Useful for unpacking std::pair and std::tuple objects. Use std::ignore as a placeholder for ignored values. In C++17, structured bindings should be used instead.
*/

/*
std::array
std::array is a container built on top of a C-style array. Supports common container operations such as sorting.
*/

/*
Unordered containers
These containers maintain average constant-time complexity for search, insert, and remove operations. In order to achieve constant-time complexity, sacrifices order for speed by hashing elements into buckets. There are four unordered containers:

unordered_set
unordered_multiset
unordered_map
unordered_multimap
*/

/*
std::make_shared
std::make_shared is the recommended way to create instances of std::shared_ptrs due to the following reasons:

Avoid having to use the new operator.
Prevents code repetition when specifying the underlying type the pointer shall hold.
It provides exception-safety. Suppose we were calling a function foo like so:
foo(std::shared_ptr<T>{ new T{} }, function_that_throws(), std::shared_ptr<T>{ new T{} });
The compiler is free to call new T{}, then function_that_throws(), and so on... Since we have allocated data on the heap in the first construction of a T, we have introduced a leak here. With std::make_shared, we are given exception-safety:

foo(std::make_shared<T>(), function_that_throws(), std::make_shared<T>());
Prevents having to do two allocations. When calling std::shared_ptr{ new T{} }, we have to allocate memory for T, then in the shared pointer we have to allocate memory for the control block within the pointer.
See the section on smart pointers for more information on std::unique_ptr and std::shared_ptr.
*/

/*
Memory model
C++11 introduces a memory model for C++, which means library support for threading and atomic operations. Some of these operations include (but aren't limited to) atomic loads/stores, compare-and-swap, atomic flags, promises, futures, locks, and condition variables.
*/


///////////////////////////////////////////////////////////////////////
// C++14 Language Features
///////////////////////////////////////////////////////////////////////

/*
Binary literals
Binary literals provide a convenient way to represent a base-2 number. It is possible to separate digits with '.
*/

/*
Generic lambda expressions
C++14 now allows the auto type-specifier in the parameter list, enabling polymorphic lambdas.
*/

/*
Lambda capture initializers
This allows creating lambda captures initialized with arbitrary expressions. The name given to the captured value does not need to be related to any variables in the enclosing scopes and introduces a new name inside the lambda body. The initializing expression is evaluated when the lambda is created (not when it is invoked).
*/
int factory(int i) { return i * 10; }

/*
return type deduction
*/
auto f(int i)
{
	return i;
}

template <typename T>
auto& ft(T& t)
{
	return t;
}

/*
decltype(auto)
*/
// Return type is `int`.
auto f2(const int& i)
{
	return i;
}

// Return type is `const int&`.
decltype(auto) g2(const int& i) 
{
	return i;
}

// constexpr
constexpr int factorial(int n)
{
	if (n <= 1)
	{
		return 1;
	}
	else
	{
		return n * factorial(n - 1);
	}
}

// variable template
template<class T>
constexpr T pi = T(3.1415926535897932385);
template<class T>
constexpr T e = T(2.7182818284590452353);

// Compile-time integer sequences
template<typename Array, std::size_t... I>
decltype(auto) a2t_impl(const Array& a, std::integer_sequence<std::size_t, I...>) 
{
	return std::make_tuple(a[I]...);
}

template<typename T, std::size_t N, typename Indices = std::make_index_sequence<N>>
decltype(auto) a2t(const std::array<T, N>& a) 
{
	return a2t_impl(a, Indices());
}

///////////////////////////////////////////////////////////////////////
// C++14 Library Features
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
// C++17 Language Features
///////////////////////////////////////////////////////////////////////
/*
Template argument deduction for class templates

Automatic template argument deduction much like how it's done for functions, but now including class constructors.
*/
template <typename T = float>
struct MyContainer
{
	T val;
	MyContainer() : val() {}
	MyContainer(T val) : val(val) {}
};

/*
Declaring non - type template parameters with auto
Following the deduction rules of auto, while respecting the non - type template parameter list of allowable types[*], template arguments can be deduced from the types of its arguments :
*/
//template <auto ... seq>
//struct my_integer_sequence 
//{
//	// Implementation here ...
//};


//template<typename... Args>
//bool logicalAnd(Args... args) 
//{
//	// Binary folding.
//	return (true && ... && args);
//}

template<typename... Args>
auto sum(Args... args) 
{
	// Unary folding.
	return (... + args);
}

// constexpr lambda
constexpr int addOne(int n)
{
	return [n] { return n + 1; }();
}

// lambda capture this
struct MyObj 
{
	int value{ 123 };
	auto getValueCopy() {
		return[*this]{ return value; };
	}
	auto getValueRef() {
		return [this] { return value; };
	}
};

/*
Nested namespaces
Using the namespace resolution operator to create nested namespace definitions.
*/
namespace A8::B8::C8
{
	int i;
}

// constexpr if
template <typename T>
constexpr bool isIntegral() 
{
	if constexpr (std::is_integral<T>::value) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}

///////////////////////////////////////////////////////////////////////
// C++17 Library Features
///////////////////////////////////////////////////////////////////////

std::optional<std::string> create(bool b) 
{
	if (b) 
	{
		return "Godzilla";
	}
	else 
	{
		return {};
	}
}

// std::invoke
template <typename Callable>
class Proxy 
{
	Callable c;
public:
	Proxy(Callable c) : c(c) {}
	template <class... Args>
	decltype(auto) operator()(Args&&... args) 
	{
		// ...
		return std::invoke(c, std::forward<Args>(args)...);
	}
};