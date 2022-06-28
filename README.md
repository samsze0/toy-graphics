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
4. Viewing coord -> normalised viewing coord
5. Perspective transformation (3D only): projection
6. Clipping
7. Window-viewport transformation: normalised viewing coord -> normalised device coord

## View Volume
- Perspective: frustum (paramid without tip) ; specify using fov, near plane, far plane
- Orthogonal: box/cube ; used also for 2D