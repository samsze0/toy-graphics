Wishing to toy with the following
- CMake
- C++
- OpenGL

TODO
- CMake visibility options
- OpenGL texture. Loading/alignment
- C++ template specialisation & good practice
- C++ filestream, stringstream
- C++ smart pointer
- C++ copy constructor, move semantics

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
- `*dll.lib` contains function pointers to the functions in `.dll`. Eliminate need to query the functions locations at runtime (by invoking a dynamic loader)
- Place `.dll` at same directory as `.exe` to have `.dll` be loaded at launch time
- Dynamic lib lives in the same process and address space (global, heap, stack, code) hence global and heap are shared
- A dynamic loader process is started by the kernel at launch time and the loader will attempt to find all dependent libraries in the filesystem. Abort if cannot find all. The dynamic loader also loads dynamic lib at runtime at the app's request (on-request).
- Different platform implement dynamic loader differently. *nix uses DLC (dynamic loader compatibility) functions
  - `dlopen`: "Open" the lib. Load dynamic lib into current process's address space (if not already exist). Return dynamic lib handle. Increment ref count (no. times current process has invoked `dlopen` on the dynamic lib)
  - `dlsys`: Return the address of the requested symbol exported by the dynamic lib
  - `dlcount`: Decrement ref count. If ref count reaches 0, unload lib from current process's address space