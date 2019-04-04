vtk_module_scan(
  MODULE_FILES      "${CMAKE_CURRENT_SOURCE_DIR}/Filter/vtk.module"
  REQUEST_MODULES   LandmarkTransform::LandmarkTransformFilter
  PROVIDES_MODULES  landmark_transform_modules
  REQUIRES_MODULES  required_modules
  HIDE_MODULES_FROM_CACHE ON)

if (required_modules)
  foreach (required_module IN LISTS required_modules)
    # message("module: ${required_module}")
    if (NOT TARGET "${required_module}")
      message(FATAL_ERROR
        "Failed to find the required module ${required_module}.")
    endif ()
  endforeach ()
endif ()

vtk_module_build(
  MODULES             ${landmark_transform_modules}
  PACKAGE             LandmarkTransform
  INSTALL_HEADERS     OFF
  LIBRARY_NAME_SUFFIX "pv${PARAVIEW_VERSION_MAJOR}.${PARAVIEW_VERSION_MINOR}"
  VERSION             "${PARAVIEW_VERSION}"
  SOVERSION           "1")

paraview_add_plugin(LandmarkTransform
  REQUIRED_ON_SERVER
  VERSION "1.0"
  SERVER_MANAGER_XML LandmarkTransformFilter.xml
  MODULES LandmarkTransform::LandmarkTransformFilter)
