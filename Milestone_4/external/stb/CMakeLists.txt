add_library(stb INTERFACE
  include/stb_image.h
)

set_target_properties(stb PROPERTIES
  LINKER_LANGUAGE CXX
)