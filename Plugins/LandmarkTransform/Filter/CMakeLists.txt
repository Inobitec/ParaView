set(classes
  vtkLandmarkTransformFilter)

#set(headers
#  vtkLandmarkTransformFilter.h)

#set(sources
#  vtkLandmarkTransformFilter.cxx)

vtk_module_add_module(LandmarkTransform::LandmarkTransformFilter
  CLASSES ${classes}
#  SOURCES ${sources}
#  HEADERS ${headers}
  )

#paraview_add_server_manager_xmls(
#  XMLS  LandmarkTransformFilter.xml)
