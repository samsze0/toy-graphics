add_rules("mode.debug", "mode.release")  -- See https://xmake.io/#/manual/custom_rule?id=built-in-rules

-- add_cxflags("-include-pch ./src/pch.pch")
add_ldflags()

set_languages("c++17")

-- set_optimize()
-- add_defines()

add_requires("glfw")  -- OS-independent window, input etc library
add_requires("glad")  -- modern alternative to GLEW
-- add_requires("glew")  -- hook into system OpenGL
add_requires("glm")  -- maths
add_requires("stb")  -- stb_image.h for image loading
add_requires("imgui", { configs = { glfw_opengl3 = true, use_glad = true } })  -- UI
add_requires("spdlog")  -- logging

target("myexe")
  set_kind("binary")
  add_files("./src/**.cpp")
  
  add_rules("load.files")
  add_files("./**.vs", "./**fs")
  add_files("./**.png")
  add_files("./**.ttf")

  add_packages("glfw", "glad", "glm", "stb", "imgui", "spdlog")

-- add_rules('imgui.binding')

-- rule("imgui.binding")
--   on_install(function (target)
--     print('target.targetfile' .. target:targetfile())
--     -- os.cp(path.join(target:targetdir(), "res/bindings"), path.join(target:targetdir(), "bindings"))
--   end)

rule("load.files")
  set_extensions(".fs", ".vs", ".png", ".ttf")
  on_build_file(function (target, sourcefile, opt)
    os.cp(sourcefile, path.join(target:targetdir(), sourcefile))
  end)
  
--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
--
-- You can enter the project directory firstly before building project.
--
--   $ cd projectdir
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro defination
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "c++11")
--
--    -- set optimization: none, faster, fastest, smallest
--    set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--

