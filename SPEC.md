# Introduction

- [Introduction](#introduction)
  - [Features](#features)
    - [Safety first](#safety-first)
    - [Beautiful mess](#beautiful-mess)
    - [Not a C killer](#not-a-c-killer)
    - [Order independent top level declarations](#order-independent-top-level-declarations)
    - [No null](#no-null)
    - [Generics](#generics)
    - [Compile time reflection](#compile-time-reflection)
    - [Calling C functions through the C FFI](#calling-c-functions-through-the-c-ffi)
    - [Non archaeic build system](#non-archaeic-build-system)
    - [Asynchronous programming](#asynchronous-programming)
  - [Syntax](#syntax)
    - [Hello world](#hello-world)
    - [Comments](#comments)
      - [Comment Macros](#comment-macros)
    - [Variables and Constants](#variables-and-constants)
    - [Primitive types](#primitive-types)
    - [String and Char literals](#string-and-char-literals)
      - [Interpolation](#interpolation)
    - [Integers](#integers)
      - [Integer literals](#integer-literals)
    - [Floats](#floats)
      - [Float literals](#float-literals)
      - [Infinty and NaN](#infinty-and-nan)
    - [Number casting](#number-casting)
    - [Operators](#operators)
    - [Arrays](#arrays)
    - [Structs](#structs)
      - [Packed structs](#packed-structs)
    - [Interfaces](#interfaces)
    - [Enums](#enums)
    - [Unions](#unions)
    - [Shadowing](#shadowing)
    - [Maps](#maps)
    - [Regular Expressions](#regular-expressions)
    - [Pattern matching](#pattern-matching)
      - [Matching literals](#matching-literals)
      - [Matching enums](#matching-enums)
      - [Matching multiple patterns](#matching-multiple-patterns)
      - [Matching ranges](#matching-ranges)
      - [Matching Maps](#matching-maps)
      - [Matching types](#matching-types)
      - [Matching regular expressions](#matching-regular-expressions)
    - [if/else statements](#ifelse-statements)
    - [Functions](#functions)
      - [Anonymous functions](#anonymous-functions)
      - [Functions as arguments](#functions-as-arguments)
    - [Loops](#loops)
      - [For loops](#for-loops)
      - [While loops](#while-loops)
      - [Do-while loops](#do-while-loops)
    - [Decorators](#decorators)
    - [Unsafe](#unsafe)

## Features

Programming languages should be both friendly and fast, but ideally not have to sacrifice one for the other. Unfortunately for the vast majority of languages this isn't the case. They tend to be either really friendly and easy to use, but super slow; or extremely fast and powerful, but with a syntax that leaves a lot to be desired.

The goal of Hex is to be extremely user friendly with a large standard library and a vibrant, helpful community, but also fast. It is also relatively simple with no hidden control flow. If a function, class, variable or otherwise isn't explicitly defined or imported into the current scope it doesn't exist in the current scope.

### Safety first

If Rust has taught us anything it's that developers want memory safety. Since then several languages have come out that promise safety and performance, and many have delivered. Unfortunately this safety usually also comes at a cost to productivity and developer happiness.

Hex uses [reference counting](https://en.wikipedia.org/wiki/Reference_counting) to manage memory rather than a traditional garbage collector. This allows you to easily track how memory is being managed in your application. It also provides some more traditional [memory management techniques](#manual-memory-management), including pointers, but we'll get to that.

TODO: Memory flow chart

### Beautiful mess

Who likes error messages? No one. Why? They mean you did something wrong, and in most cases they are not all that helpful. Rust taught us that you don't have to fear the compiler, but rather that you should embrace it, and they did that by providing some of the [best error messages](https://doc.rust-lang.org/error-index.html) that have ever been seen in modern development. Since then several languages have jumped on the band wagon with varying degrees of success. Elm also has [amazingly helpful errors](https://elm-lang.org/news/compiler-errors-for-humans).

Hex continues this trend by providing error messages that could almost be called beautiful, as well as stack traces and the ability to [generate a memory access graph](#memory-access-graphs). In short, it does everything it can to help you understand exactly what you did wrong and how to fix it.

TODO: Add error message example

### Not a C killer

The goal of Hex is not to be a C killer. This is not another Rust, another C, another Java, or another _insert name of any language here_. Hex is Hex and that's all it's going to be. This provides a certain level of freedom to the language. Hex has no goal beyond the ones mentioned in the first section of this document. Developer happiness and safety come first, performance second. Period.

That being said, this is a statically typed, compiled, non-garbage-collected language. It's going to be fast.

### Order independent top level declarations

Top level declarations such as constants and functions are order-independent and lazily evaluated. Constant values are known at compile time and are completely constant.

TODO:

### No null

Null is the devil, and has been since it was created by Tony Hoare in 1964. He even coined it his "billion dollar mistake". Null is the source of so many runtime exceptions and they're really not necessary, so we're not going to have them.

**Enter: the Option type**. Like in Rust, Hex has an Option type that can either contain a value, or an error. This combined with type matching forces you to handle all potential exceptions before your program will compile.

TODO: Option type example

### Generics

Generics are a powerful language concept, allowing the creation of containers that could potentially hold anything. One example of generic use in Hex is the `Array`, which can contain any type of element (provided all elements in the array are of the same type).

TODO: Generic example

### Compile time reflection

TODO

### Calling C functions through the C FFI

Unfortunately, there is no way to make it in the systems programming world without interfacing with C. This is a reality that even Rust has had to accept. And with C comes inherant unsafety. Hex does all it can to mitigate this, but ultimately it is up to the developer to give an accurate representation of the C functions to be called, so that the Hex compiler can do its job.

TODO: C FFI example

### Non archaeic build system

Gone are the days of writing complicated make files, shell scripts, and the like to create easily reproducable builds. Hex has its own built in build system that works with you, and doesn't require you to learn a new language or file format. That's because Hex build scripts are written in a variation of Hex known as [HexScript](#hexscript) which is syntactically the same as Hex, but interpreted rather than compiled.

TODO: Build file example

### Asynchronous programming

Hex makes concurrency easy with the use of the async/await pattern. JavaScript developer should feel right at home here.

TODO: Example

## Syntax

Hex's syntax is meant to be friendly, familiar, and adaptable. For this reason a variation on the C style syntax has been chosen, since it eases adoption by many who are use to other C style languages such as Java, JavaScript, C++, C#, etc. Let's take a look at some syntax examples.

### Hello world

```hex
from debug import log

log("Hello world")
```

That's it. As you can see, `log` isn't a built in function that can be called out of nowhere. Rather it's an actual function, imported from the [debug module](todo://), that writes to [stdout](https://en.wikipedia.org/wiki/Standard_streams#Standard_output_(stdout)). You can even check out the source for it [here](todo://).

### Comments

Comments in Hex are special, in that they're actually fist class citizens of the language. Most languages discard comments, but in Hex we embrace them. Take this example:

```hex
from debug import log

/// Takes an input integer `n`. If `n` is divisible by
/// 3 it returns "Foo", if divisible by 5 it returns
/// "Bar", otherwise it returns `n`.
fun foobar(n: int) {
    for i in 1..n {
        match n {
            (. % 3 == 0) { log("Foo") }
            (. % 5 == 0) { log("Bar") }
            _            { log(n)     }
        }
    }
}
```

Ignore the function for the moment, we'll get to functions, for loops, and pattern matching soon enough. For now we'll focus on the comment. The syntax is similar to what you'd see in Rust for documentation comments, and that's the idea. In Hex, any comment that begins with three forward slashes (`///`) is a doc comment, and can be used to describe the module, function, or data structure that directly follows it. They can be formatted using markdown syntax.

At compile time these doc comments are inserted directly into the AST node that they're assigned to, and can be accessed by functions via reflection. Not only can the comment itself be accessed, but all comment metadata is available. Let's look at another example:

```hex
from reflect.ast.modules import self
from debug import log

/// Adds two numbers and returns the result.
///
/// @example
///   add(2, 2) // 4
/// @param a
///   @desc The first number
/// @param b
///   @desc The second number
fun add(a: int, b: int) int {
    return a + b
}

/// Describes the `add` function.
fun describeAdd() {
    // Evaluated at compile time
    for f in self.functions[:add] {
        const doc = f.documentation
        log(f.doc.desc)

        log("Examples:")
        for e in f.doc.examples {
            log(e.indent(2))
        }

        log("Params:")
        for p in f.doc.params {
            const fp = f.params[p.id]
            log("  {fp.name} ({fp.type}): {p.desc}")
        }
    }
}
```

If you were to run the above `describe_add` function, you would get the following written to the console:

```txt
Adds two numbers and returns the result.
Examples:
  add(2, 2) // 4
Params:
  a (int): The first number
  b (int): The second number
```

#### Comment Macros

Using comment macros, you can add metadata to the document itself. This is extremely useful for documentation generation. Take this example using the built in `section` macro.

```hex
//+ @section: Operators

fun add(a: int, b: int) int {
    return a + b
}

fun sub(a: int, b: int) int {
    return a - b
}

//+ @endsection: Operators
```

This adds a `sections` attribute to the current document's AST, allowing you to retrieve all of the functions, structs, etc. defined within that section. For now comment macros can't be created, but you will be able to create custom comment macros eventually.

### Variables and Constants

Constants are defined with the `const` keyword and can be defined globally or locally within a function. Constants are immutable, and when defined globally they are evaluated at compile time. Variables are mutable and can change as much as needed, but they cannot change type.

```hex
// Because why not
const PI = 3.14

/// Calculate the circumference of a circle.
fun circumference(radius float) float {
    return radius * PI
}
```

Variables are defined using the `let` keyword. They cannot be defined globally, but are completely mutable.

```hex
def changeMe(let n: i32) i32 {
    n = 5
    return n
}
```

Data passed in to functions is usually immutable, as you can see this functionality can also be changed by prefixing the parameter name with `let`.

### Primitive types

| Name     | Description                                            |
| :------- | :----------------------------------------------------- |
| `int`    | Pointer sized signed integer (`i32` or `i64`)          |
| `uint`   | Pointer sized unsigned integer (`u32` or `u64`)        |
| `i8`     | Signed 8-bit integer                                   |
| `u8`     | Unsigned 8-bit integer                                 |
| `i16`    | Signed 16-bit integer                                  |
| `u16`    | Unsigned 8-bit integer                                 |
| `i32`    | Signed 32-bit integer                                  |
| `u32`    | Unsigned 32-bit integer                                |
| `i64`    | Signed 64-bit integer                                  |
| `u64`    | Unsigned 64-bit integer                                |
| `i128`   | Signed 128-bit integer                                 |
| `u128`   | Unsigned 128-bit integer                               |
| `float`  | Pointer sized double precision float (`f64` or `f128`) |
| `number` | Any float, int, or uint                                |
| `f32`    | 32-bit floating point integer                          |
| `f64`    | 64-bit floating point integer                          |
| `f128`   | 128-bit floating point integer                         |
| `bool`   | Boolean value (`true` or `false`)                      |
| `void`   | 0 bit type                                             |
| `byte`   | Alias for `u8`                                         |

### String and Char literals

String literals are immutable byte arrays. They are always wrapped with double quotes, are fully UTF-8 compatible, and can contain escape sequences.

Char literals are immutable byte sequences as well, but they make up a single UTF-8 character. They are created with single quotes.

```hex
from debug import log

fun test_strings() {
    const str = "Hello world"

    log(str.size)     // 11
    log(str.chars.size) // 11
    log(str.chars)    // ['H', 'e', 'l', ...]

    // You can iterate over a strings bytes, like an array
    for b in str {
        log(b)
    }

    // You can obtain a slice of a string
    log(str[5..]) // "world"

    // Chars and bytes can be compared
    log(str[0] == 'H') // true

    // Chars also have a byte size
    log('😃'.bytesize) // 4

    // An array of chars can become a string
    log(String.new(['H', 'i'])) // "Hi"
}
```

#### Interpolation

String interpolation, or inserting a value into a string, can be accomplished by wrapping the value in curly braces.

```hex
from debug import log

fun interpolationTest() {
    const message = "Hello, world!"
    log("Message: {message}") // "Message: Hello, world!"
}
```

### Integers

#### Integer literals

Integer literals can be defined in binary, octal, decimal, and hex formats.

```hex
const binary  = 0b10011010010
const octal   = 0o2322
const decimal = 1234
const hex     = 0x04d2 // or 0x04D2
```

### Floats

Hex has the following floating point types:

- f16 - IEEE-754-2008 binary16
- f32 - IEEE-754-2008 binary32
- f64 - IEEE-754-2008 binary64
- f128 - IEEE-754-2008 binary128

#### Float literals

Float literals contain a decimal point or scientific notation.

```hex
const floatOne   = 1230.0
const floatTwo   = 123e+1
const floatThree = 123E+1

const hexFloat   = 0x4ce.0
const hexFloat   = 0x7b.0p+1
const hexFloat   = 0x7b.0P+1
```

#### Infinty and NaN

Infinity and NaN exist as their own literals.

```hex
const a = 0/0 // NaN

const c = 1/0 // Infinity
```

This is similar to the behavior you'd see in Ruby.

### Number casting

All integer types can be used as casting functions to easily cast one type to another. For example:

```hex
from debug import log
from reflect import typeof

const testOne = i64(1234)
log(typeof(testOne)) // i64

// Same can be done with floats
const testTwo = f64(3.14)
log(typeof(testTwo)) // f64

// And for type coersion from int to float
const testThree = f64(1234)
log(typeof(testThree)) // f64

// But not from float to int. This will not compile.
const testFour = i32(3.14)
```

All number literals can also include underscores. These are ignored by the compiler, but can help separate large numbers into sections.

```hex
const largeNumber = 123_456_789
```

This is similar to what you'd see in Ruby and Python.

### Operators

TODO: Operator table

### Arrays

In Hex, arrays are ordered lists of a particular type. They can only contain one type, but that type can be a [union](todo://).

```hex
from debug import log

// Create an array of i8
const nums = [1, 2, 3, 4, 5]

// Get the size of the array
log(nums.size) // 5

// Type cast the array values
const bytes = [_]byte[97, 98, 99, 100, 101]

// A byte array is the same as a string
log(bytes) // "abcde"

// Arrays have a constant length
let another = [5]i8

// Push a value on to the end of the array
another.push(2)

// Also
another << 3

// Add a value on to the beginning of the array
another.unshift(1)

// Also
another >> 0
```

### Structs

Hex has structs instead of classes.

```hex
// Hex gives no guarantees about the order of fields
// and the size of the struct, but the fields are
// guaranteed to be ABI aligned
struct Point {
    pub const x: f32
    pub const y: f32
}

// If you want to be particular about how the bytes
// are arranged
packed struct Point2 {
    pub const x: f32
    pub const y: f32
}

// To declare an instance of a struct
let p2 = Point{
    x: 2.2,
    y: 2.5,
}

// And to access its properties
p2.x // 2.2
p2.y // 2.5

// Struct fields can have default values
struct Line {
    pub let a: Point = Point{0, 0}
    pub let b: Point = Point{0, 0}
}

let molly = Person{ "Molly" }
molly.age = 24

// Struct fields are private by default
struct Rect {
    const a: Point
    const b: Point
    const x: Point
    const y: Point
}

// Structs can have methods as well
struct Animal {
    const latin_name: String
    let age: i32

    pub fun new(latin_name: String, age: i32) Animal {
        return Animal{latin_name, age}
    }

    pub fun genus(self: Animal) String {
        return self.latin_name.split(' ')[0]
    }
}

const dog = Animal.new("Canis lupus familiaris", 6)
dog.genus() // "Canis"
```

#### Packed structs

Unlike normal structs, **packed** structs have a guaranteed in-memory layout. Definition taken from Zig.

- Fields remain in the order declared.
- There is no padding between fields.
- Hex supports arbitrary width Integers and although normally,integers with fewer than 8 bits will still use 1 byte of memory, inpacked structs, they use exactly their bit width.
bool fields use exactly 1 bit.
- A [packed enum](todo://) field uses exactly the bit width of its integer tagtype.
- Non-ABI-aligned fields are packed into the smallest possibleABI-aligned integers in accordance with the target endianness.

### Interfaces

Interfaces in Hex are very much like the interfaces in Typescript and Rust. By themselves they are functionally useless, but their real power comes into play when combined with structs.

```hex
interface CanSpeak {
    fun speak(String) void
}
```

### Enums

Enums in Hex work very similarly to those in Rust, in that they're actually [algebraic data types](https://en.wikipedia.org/wiki/Algebraic_data_type) and can include embedded data.

```hex
// Declare a basic enum
enum Result {
    Ok,
    Error
}

// Declare a specific instance of an enum variant.
const o = Result.Ok

// A generic enum with embedded data
enum Option<T> {
    Some(T),
    None
}

const res = Option.Some(123)
```

Enums also have a packed variant that follow the same rules as the [packed struct](#packed-structs).

### Unions

Unions in Hex will be familiar to anyone coming from Crystal. They are defined by using type literals separated by the pipe (`|`) character.

```hex
type HeaderValue = String | []String
type Header = Map<String, HeaderValue>
```

If a function accepts a union type, it is the developer's responsibility to match on that type to make sure they're operating on the correct value. For instance:

```hex
fun getSetCookies(h: Header) []String {
    return match h["Set-Cookies"] {
        Some([]String) { . }
        Some(String)   { [ . ] }
        None           { []String }
    }
}
```

### Shadowing

Shadowing is disallowed completely for now. Variables cannot be reassigned, but not redefined.

### Maps

Maps in Hex are typed key value pairs, also called hashes and dictionaries in other languages. You can create a Map one of three ways.

```hex
// Empty map of a specific type
let emptyMap = new Map<String, String>

// Explicitly typed map with values
let secondMap: Map<String, String> = {
    "a": "Hello",
    "b": "World",
}

// Auto-typed Map
let thirdMap = {
    "a": "Hello",
    "b": "World",
}
```

In the first case we create a Map with no values. This Map can be modified later, provided it's not a constant.

The second Map is explicitly given a type, but also initialized with values. This is especially helpful when creating a map that may be able to accept multiple types as values, but doesn't start off with each of those types.

The third one is the most common. It will be automatically typed as a `Map<String, String>`. Empty Maps cannot be created with the shorthand syntax, since the compiler won't know how to type it.

### Regular Expressions

Hex uses the [hyperscan](https://github.com/intel/hyperscan) regular expression algorithm, making regex in Hex [extremely fast](https://rust-leipzig.github.io/regex/2017/03/28/comparison-of-regex-engines/). Regular expressions in Hex can be created two different ways.

```hex
// Create a Regex from a String
const matcher = new Regex("[a-b]")

// Use a Regex literal
const matcher2 = /[a-b]/
```

Regex literals work just like they do in JavaScript. So to ignore case just add an `i` to the end.

### Pattern matching

Hex, like Go, Rust, and several other languages, includes pattern matching. With pattern matching you can match an expression by type, value, or sub-expression.

#### Matching literals

```hex
from debug import log

fun matchLiterals(num i32) {
    match num {
        1 { log("one") }
        2 { log("two") }
        3 { log("three") }
        _ { log("something else")  }
    }
}
```

Think of the `_` character as an `else` or "anything that doesn't fit the other matches". Matches have to be exhaustive, so if you don't exhaust all of the possible matches it's necessary to use the underscore operator.

#### Matching enums

Most Rust matching patterns will work in Hex, including enum matching. Just like in Rust, enums also create their own scope. For example:

```hex
from debug import log

fun enumMatching() {
    let x = Some(5)
    let y = 10

    match x {
        Some(50) { log("It was 50!") }
        Some(y)  { log("It was {y}!") }
        _        { log("Default matched. Got {x}") }
    }
}
```

`Some(y)` creates the variable `y` in its own scope and doesn't shadow the outer scope's `y`. If you want to use the outer scope's `y` definition you can use the `&` prefix.

```hex
...
Some(&y) { log("It was 10!") }
...
```

#### Matching multiple patterns

Sometimes you need to match several patterns and have them do the same thing, this can be accomplished by separating your patterns with a comma.

```hex
from debug import log

fun multiMatch() {
    let x = 1

    match x {
        1, 2 { log("one or two) }
        3    { log("three") }
        _    { log("something else") }
    }
}
```

#### Matching ranges

You can use Hex's [range literal](#range-literals) to match on a range of values.

```hex
from debug import log

fun matchRange() {
    let x = 10

    match x {
        0..5   { log("zero to five") }
        6..10  { log("six to ten") }
        _      { log("something else") }
    }
}
```

#### Matching Maps

You can also match on values inside of a Map.

```hex
from debug import log

fun matchMaps() {
    let m = {
        a: "Hello",
        b: "World"
    }

    match m {
        { b: "Hello" } { log("Backwards") }
        { a: "hello", b: "world" } { log("Lowercase") }
        { a: "Hello", b: "World" } { log("Correct") }
        _ { log("Nope") }
    }
}
```

Just like with enums, Map matches create their own scope, and just like with enums you can use the `&` character to use the outer scope's variables. This works for keys and values.

#### Matching types

Sometimes you accept a union as an argument, or get one back from a function and need to do something specific dependent on the type of the value.

```hex
from debug import log

fun matchUnion(map: Map<String, String | []String>) {
    for k, v in map {
        match v {
            String { log("String: {v}") }
            Array  { log("Array: {v}") }
        }
    }
}
```

#### Matching regular expressions

Of course you can also match Strings based on regular expression.

```hex
from debug import log

fun regexMatch() {
    const str = "Hello world"

    match str {
        /Goodbye/ { log("Bye") }
        /Hello/   { log("Hi!") }
        _         { /* Ignore this */ }
    }
}
```

### if/else statements

Hard to have a language without the control flow you get from if/else statements. In Hex we use `if`, `else if`, and `else`. Conditions don't have to be wrapped in parentheses, but for longer conditions it isn't discouraged.

```hex
const a = 2

if a < 1 {
    // Doesn't match
} else if (a > 2) {
    // Also doesn't match
} else {
    // This one will match
}
```

### Functions

Functions in Hex are defined with the `fun` keyword, and are also fully [tail call optimized](https://en.wikipedia.org/wiki/Tail_call). This means that recursive functions in Hex are more performant than you'd find in languages without TCO.

We've already seen several functions so far, but here's some more examples:

```hex
// Function names should be camel-cased
fun someFunction() { ... }

// Function arguments have to be typed. No duck typing.
fun anotherOne(n: int, n2: int) { ... }

// Variadic arguments are supported, but also have to be typed.
fun someVarArgs(...a: int) { ... }

// Functions support default arguments
fun defaultArgs(a: int = 1) { ... }

// Functions can also be overloaded. Overloading is highly dependent
// on the types of arguments. This is the same behavior as seen
// in Crystal
fun defaultArgs(a: String) { ... }

// Function arguments can also by position or name
defaultArgs("Hello world")
defaultArgs(a: "Hello world")
```

#### Anonymous functions

Functions in Hex are first class citizens, and as such can be assigned to variables and passed around. Functions can take other functions as arguments, and return functions.

To create an anonymous function just create a function without a name. This is especially handy inside of methods that accept a function as an argument. Take `Array.map` for instance.

```hex
let arr = [1, 2, 3, 4, 5]
let arr2 = arr.map(fun (x) x + 1)
// [2, 3, 4, 5, 6]
```

With short functions you can even leave out the curly braces. The result will be automatically returned.

#### Functions as arguments

To accept a function as an argument:

```hex
fun scan(cb: (String) void) {
    for x in 1..10 {
        cb(x.str())
    }
}
```

### Loops

Hex has three loop styles. For loops, while loops, and do-while loops.

#### For loops

For loops can be used to loop over iterables.

```hex
from debug import log

fun forLoopTest() {
    const arr = [1, 2, 3, 4, 5]
    for i in arr {
        log(i)
    }
}
```

This function could've also been done as:

```hex
from debug import log

fun forLoopTest() {
    for i in 1..5 {
        log(i)
    }
}
```

#### While loops

While loops allow you to continue looping until a condition is met, or potentially forever.

```hex
from debug import log

fun whileLoopTest() {
    let x = 0
    while (x != 10) {
        log(x)
        x++
    }
}
```

#### Do-while loops

Unlike while loops, do-while loops check the condition after the loop executes.

```hex
from debug import log

fun doWhileLoopTest() {
    let x = 0
    do {
        log(x)
        x++
    } while (x != 10)
}
```

This will print the value of `x` one more time than the while loop example.

### Decorators

Sometimes it's helpful to be able to add metadata to a function. Whether it's marking a function as deprecated, adding additional functionality to it, or otherwise. This can be done with an annotation.

An annotation is a function that takes a function, and returns a function. This is very similar to the Python/TypeScript model. Here's an example decorator:

```hex
from debug import log

fun deprecated(func: Function) {
    const wrapper = (message: String) {
        log("Function {func.name} is deprecated: {message}")
        func()
    }
}

@deprecated("please use nonDeprecatedMethod instead")
fun deprecatedMethod() {
    // Do something
}
```

### Unsafe

Hex tries to be as memory safe as possible, but sometimes you just have to do unsafe things. For those cases we have `unsafe` blocks, just like in Rust, as well as the `@unsafe` decorator to mark a whole function as unsafe.
