Wishing to toy with the following
- CMake
- C++
- OpenGL
- CI (Continuous Integration), Jenkins & commit hooks

TODO
- CMake visibility options
- OpenGL texture. Loading/alignment
- C++ template specialisation & good practice
- OSX retina display resolution and density problem

Resources
- CMake official docs
- [Modern CMake](https://cliutils.gitlab.io/modern-cmake/)
- learnopengl
- Cherno's C++ & OpenGL series
- docs.gl
- [Microsoft C++ Ref](https://docs.microsoft.com/en-us/cpp/cpp/cpp-language-reference?view=msvc-170)
- Wikipedia on Computer Graphics
- Real-time Rendering 4th edition
- [Apple developer document archive on dynamic lib](https://developer.apple.com/library/archive/documentation/DeveloperTools/Conceptual/DynamicLibraries/100-Articles/OverviewOfDynamicLibraries.html)
- [Tomshardware forum - core vs thread](https://forums.tomshardware.com/threads/cores-vs-threads-explained.3460905/)
- [Stackoverflow - process vs thread](https://stackoverflow.com/questions/200469/what-is-the-difference-between-a-process-and-a-thread)
- [Wikipedia - dynamic dispatch](https://en.wikipedia.org/wiki/Dynamic_dispatch)
- [Wikipedia - virtual function table](https://en.wikipedia.org/wiki/Virtual_method_table)
- [LLDB guide](https://lldb.llvm.org/use/tutorial.html)
- [DAP](https://microsoft.github.io/debug-adapter-protocol/)
- [Sublime debugger](https://github.com/daveleroy/sublime_debugger)
- [Stackoverflow - std::async vs std::thread](https://stackoverflow.com/questions/66803430/stdasync-vs-thread)
- [Stackoverflow - ifstream vs ofstream vs fstream and the stream hierarchy](https://stackoverflow.com/questions/67631098/what-is-the-difference-between-ifstream-ofstream-and-fstream)
- [Wikipedia on Standard streams](https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin))
- [Stackoverflow - cross platform IPC](https://stackoverflow.com/questions/60649/cross-platform-ipc)

# Computer Graphics Basics

## Convention
- Left-handed / Right-handed system
- Row-major / Colume-major ordering (matrices)
- Normalised coordinates: 0 to 1 / -1 to 1
- Look at -ve z / +ve z / y

## Graphics Pipeline
1. Per-vertex operation (vertex shader). Optional tessellation & geometric shader
2. Projection + clipping
3. Rasterisation (non-programmable ; fixed) on each generated primitive. Write each pixels' color to colorbuffer (framebuffer)
4. Per-fragment (pixel + some data from other buffers e.g. z, stencil) operation (fragment shader). Optional blending
5. Double buffering: swap front buffer with back buffer and have monitor loads from the front buffer

## Geometry Pipeline
1. Load models into world: model coord -> world coord (Model transform)
2. Specify camera and view volume (or clipping window if 2D) in world coord
3. View transform: world coord -> viewing coord (with respect to camera) (View transform)
4. Viewing coord -> normalised viewing coord (view volume -> cube if 3D)
5. (3D only) Projection
6. Clipping
7. Window-viewport transformation: normalised viewing coord -> normalised device coord

## View Volume
- Perspective: frustum (paramid without tip) ; specify using fov, near plane, far plane
- Orthogonal: box/cube ; used also for 2D

# C++

## Dynamic Library
- `*dll.lib` contains function pointers to the functions in `.dll` (`.dylib` if \*nix). Eliminate need to query the functions locations at runtime (by invoking a dynamic loader)
- Place `.dll` at same directory as `.exe` to have `.dll` be loaded at launch time
- Dynamic lib lives in the same process and address space (global, heap, stack, code) hence global and heap are shared
- A dynamic loader process is started by the kernel at launch time and the loader will attempt to find all dependent libraries in the filesystem. Abort if cannot find all. The dynamic loader also loads dynamic lib at runtime at the app's request (on-request).
- Different platform implement dynamic loader differently. \*nix uses DLC (dynamic loader compatibility) functions
  - `dlopen`: "Open" the lib. Load dynamic lib into current process's address space (if not already exist). Return dynamic lib handle. Increment ref count (no. times current process has invoked `dlopen` on the dynamic lib)
  - `dlsys`: Return the address of the requested symbol exported by the dynamic lib
  - `dlcount`: Decrement ref count. If ref count reaches 0, unload lib from current process's address space
- ABI (app binary interface) all the symbols exposed to clients
- API (app programming interface) functions that a library makes available to its clients
- Must disclose the library’s major version number in its filename if intended to have future revisions
- Break the ABI/API = major version
- Compiler `-current_version` option to set the minor version
- Compiler `-compatibility_version` option to set the earliest minor version of the dynamic lib that the `.exe` is compatible with. At load time, the compatibility version is compared against the minor version of the dynamic lib situated in the file system. Abort if not compatible (< compatibility version)

### Symbol Exporting Strategies
- Prefix private symbols with `_`
1. `static`: drawback: hide private symbols from other modules in the dynamic lib
2. `export_list` file: list all the public symbols (with an `_` prefix)

```
# File: export_list
_name
_set_name
```

```bash
clang -dynamiclib Person.c -exported_symbols_list export_list -o libPerson.dylib
```

3. Combination of visibility attribute and compiler `-fvisibility` option (specifies the visibility of symbols with unspecified visibility)

```c++
/* File: Person.c */

// Symbolic name for visibility("default") attribute.
#define EXPORT __attribute__((visibility("default")))

EXPORT                        // Symbol to export
char* name(void) {
    return _person_name;
}
 
void _set_name(char* name) {
   strcpy(_person_name, name);
}
```

```bash
% clang -dynamiclib Person.c -fvisibility=hidden -o libPerson.dylib
```

## Process Management
- Platform-dependent
- For \*nix: 

## Parallelism (thread & process)
- Hardware-level multithreading: asynchronously run multiple tasks on a single core at once (minimising idle time of the CPU by efficient scheduling)
  - OS sees processor as having twice as many cores, but performance-wise, these extra hardware threads only provide around 50% more performance compared to an actual physical core in a best-case scenario
- Process: provides the resources needed to execute a program. Has the following:
  - Virtual address space
  - System objects handles
  - Security context
  - Unique process identifier
  - Environment variables
  - Priority class
  - At least one thread of execution (primary thread)
- Thread: entity within a process that can be scheduled for execution
  - All threads of a process share the same virtual address space and system resources
  - Each thread maintains its own:
    - Exception handlers
    - Scheduling priority
    - Thread local storage
    - Unique thread identifier
    - Thread context
    - Security context (optional. To impersonate clients)
- Process context switching is much less efficient than thread context switching
- Process management: platform-dependent. For \*unix: `fork()`, `std::system`, `exec()`, PID, etc
- Thread management: `std::thread` and `std::jthread`

```c++
void DoWork() {
  // ...
  // std::this_thread for giving commands to current thread

  using namespace std::literals::chrono_literals;  // providing "s" as unit

  std::cout << std::this_thread::get_id() << std::endl;
  std::this_thread::sleep_for(1s);
}

int main() {
  std::thread worker(DoWork);  // Construct (and starts) worker by passing in function pointer
  worker.join();  // block current thread until worker thread finishes
                  // and collect its return status
  return 0;
}
```

## Concurrency (async)
- Implemented using thread pool behind the scene
- `std::thread` is the traditional POSIX thread style way of asynchronous programming
- Futures (or Promises or Tasks) and async/await is a pattern many languages use nowadays that makes asynchronous program much more maintainable
- `std::async(std::Launch::async, someFunction)`. Return `std::future<void>` (assuming return type of function is `void`)
- `std::mutex myMutex`
- `std::Lock_guard<std::mutex> lock(myMutex, arg1, arg2, ...)`. Work via RAII (Resource Acquisition Is Initialization): acquisition of a resource is tied to the object lifetime

## IPC (Interprocess Communication)

## Streams
- `fstream`, `ifstream`, `ostream` for file streams
- `istream`, `ostream`, `iostream` for standard streams
- `istringstream`, `ostringstream`, `stringstream` for string streams
- file stream inherits from standard streams, string stream inherits from file streams

## Smart Pointer
- Automate the free-ing of allocated memory
- Scope (unique) pointer: `std::unique_ptr<>` and `std::make_unique<>`
- Shared & weak pointer: `std::shared_ptr<>`, `std::weak_ptr<>` and `std::make_shared<>`
  - Weak pointer: doesn't increment ref count

## Copying, Copy Constructor, Move Constructor & Move Semantics
- Copying: when an object is assigned (`=`) to another object of the same type (or when an object is constructed using another object of the same type). Or when a function is called (argument passed by value)
- Default copy constructor: shallow copy - copy all values of all class fields (basically `memcpy()` the whole object)
- Let copy constructor = `delete` to ban copying
- Prevent copying by assigning it to a ref e.g. `Entity& e2 = e1;`
- lvalues: values with locations ; rvalues: temporary values
- Move constructor: when an object is assigned to another object of the same type which is temporary (e.g. `Entity&&`) (or when an object is constructed using another object of the same type which is temporary).

```c++
void Print(const std::string& str) {  // Prevent copying and also allow rvalues to be passed into the func
  // ...
}
```

```c++
class Entity {
  Entity() {  // Default constructor
    // ...
  }

  Entity(const Entity& other) {  // Copy constructor
    // ...
  }

  Entity(Entity&& other) {  // Move constructor
    // other will need to be casted into temporary again if further functions that take rvalue ref were to be invoked
    // ...
  }
};

int main() {
  Entity e1;  // Invoke with default constructor
  Entity e2(e1);  // Invoke with copy constructor
  Entity e3((Entity&&)e1);  // Invoke with move constructor, as e is casted into rvalue
  Entity e3(std::move(e1));  // Same as above. Method using template.
  return 0;
}
```

```c++
void Print(std::string& myStr) {  // 1. lvalue ref can bound to only lvalue
  // ...
}

void Print(const std::string& myStr) {  // 2. lvalue ref can bound to both lvalue & rvalue
  // ...
}

void Print(std::string&& myStr) {  // 3. rvalue ref can bound to only rvalue
  // ...
}

/* Speciality rule: 3rd or 1st function overload precede 2nd */

int main() {
  std::string myStr = "some string";
  Print(myStr);  // lvalue as arg
  Print("some string");  // rvalue as arg
  Print(myStr + myStr);  // rvalue as arg
  return 0;
}
```

## Iterator

```c++
int main() {
  std::vector<int> values = { 1, 2, 3 };

  for (int val : values) {  // Range-based for loop. Based on iterator
    // ...
  }

  for (std::vector<int>::iterator it = values.begin() ; it != values.end() ; it++) {
    // Full-version of above
    // ++ and * are overloaded
    // ...
    // *it
  }

  for (auto [key,value] : map) {  // With structured binding
    // ...
  }

  return 0;
}
```

## Casting & Virtual Function Table
- Polymorphism: e.g. a `Pawn` is also a `ChessPiece`
- Dynamic dispatch

## Types
- Size of each type (e.g. `int`) depends on the compiler
- `size_t`: a `typedef` (alias) for some unsigned (integer) type (either `uchar`, `ushort`, `uint`, `ulong` or `ulonglong`). E.g. on 64-bit system `size_t` will likely to be 8 bytes
- All primitive (integer) data types are just numbers. `char a = 65` will print out `A` when passed to `std::cout`
- Floating point primitives: `float` and `double`. By default decimal rvalues are `double`. Suffix with `f` to make it `float`
- Long: suffix with `L`
- `bool`: usually 1 byte (same as `char`)

## Enum
- 4 bytes integer by default, can be explicitly set to `uchar` to save space
- Not a namespace in itself (unlike class/struct)

```c++
enum Level : uchar {
  Error = 0,
  Warning,
  Info
};

Level logLevel = Error;  // Add extra compiler checkings by giving it the type "Level"
                         // But it is just uchar underneath
```

## Visibility
- Specifier: `private`, `public`, `protected`
- `friend`: able to access the private members of the class by appending the function declaration inside the class and prefix it with `friend`

## Array
- Array = pointer
- `array[2]` = `*(array + 2)` = `*(int*)((char*)array + 8)` (if array is `int*`)
- Cannot reliably find size of array if allocated on heap
- `std::array`: incl. bound checking + keep track of size of array

## String
- String literal: `"some string"`. Create a `const char[]` with `\0` appended at the end ; Always stored in read-only memory
- utf8 by default (1 byte per character)
- `const char16_t[]` (`std::u16string`) using `u"some string"` and `const char32_t` (`std::u32string`) using `U"some string"`
- Raw string `R"(some string)"`

## Singleton
- Only 1 instance exists

```c++
class Singleton {
public:
  static Singleton& Get() {
    static Singleton instance;
    return instance;
  }
};

int main() {
  Singleton::Get();
  return 0;
}
```

## Function Pointers, Anonymous Functions & Lambdas

```c++
void Print(int value) {
  // ...
}

// C way of declaring function pointer
void ForEach(const std::vector<int>& values, void(*func)(int)) {
  // the function is named func and takes int as argument and return void
  for (int value : values)
    func(value);
}

// C++ way of declaring function pointer
void ForEach(const std::vector<int>& values, const std::function<void(int)>& func) {
  // ...
}

int main() {
  std::vector vec = { 1, 2, 3, 4, 5 };
  ForEach(vec, Print);
  ForEach(vec, [](int value){  // with lambda:
                               // captures (capturing outside variable by value or by ref),
                               // parameters,
                               // (optionally return type,)
                               // body
    // ...
  });
  return 0;
}
```

## Timing
- `std::chrono` for timing in c++ instead of relying on platform-specific API

```c++
int main() {
  auto start = std::chrono::high_resolution_clock::now();
  // ...
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<float> duration = end - start;
}
```

## Casting (Explicit Type Conversion) & Type Punning
- Type punning: get around type system by e.g. `*(Entity*)(&e)`
- C style cast: using e.g. `(int)value`. Basically doing type punning, with some extra compiler checks
- C++ style cast (subdividing what C style cast can do)
  - Static cast: `static_cast<int>(value)`. Basically = type punning
  - Reinterpret cast: reinterpret the memory as something else. E.g. `reinterpret_cast<Entity*>(&e)`
  - Dynamic cast: cast at runtime. Figure out what super-type the entity is. Require RTTI (runtime type information and hence extra overhead)
  - Const cast: adding/removing `const`

```c++
int main() {
  Base* e = new Super();
  Super* e2 = dynamic_cast<Super*>(e)
  if (e2) {  // If e can be dynamically cast to Super*
    // ...
  }
  return 0;
}
```

## Debugger
- Debugger adapter protocol: standardise how debug tooling of IDE communicate with debugger
- Debug adapter: adapt existing debuggers to the DAP

## Structured Binding
- C++17 feature

```c++
std::tuple<std::string, int> CreateTuple() {
  return { "Some String", 10 };
}

int main() {
  auto[myStr, myInt] = CreateTuple();
  return 0;
}
```

## Optional Type
- C++17 feature

```c++
int main() {
  std::optional<std::string> data = ReadFileAsString("data.txt");
  // if (data) {  // also work
  if (data.has_value()) {
    // data behave like a smart pointer
    // data->...
    // std::string& myStr = *data;
    // std::string& myStr = data.value();
  }
  return 0;
}
```

## Variant Type
- `std::variant<>` (c++ style) or `Union` (c style)
- `Union`'s size is the size of its biggest member
- `std::variant<>`'s size is the total size of its members (like a struct)
- `std::variant` is type safe and no undefined behaviour (the edge cases that the specification of C++ doesn't specify. Up to compiler to decide)

```c++
int main() {
  // Union
  Union {
    std::string myStr;
    int myInt;
  };

  // std::variant
  std::variant<std::string, int> data;
  // ...
  auto value = std::get_if<std::string>(&data);  // return ptr to data. nullptr if data is not of type std::string
  if (value) {
    // std::string& myStr = *value;
  }
  return 0;
}
```