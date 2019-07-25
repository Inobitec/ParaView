#include "vtk2DWidgetRepresentation.h"

#include "vtkObjectFactory.h"

vtkStandardNewMacro(vtk2DWidgetRepresentation);

vtk2DWidgetRepresentation::vtk2DWidgetRepresentation()
  : vtkDataRepresentation()
  , Representation(nullptr)
  , Enabled(false)
{

}

vtk2DWidgetRepresentation::~vtk2DWidgetRepresentation() {}

void vtk2DWidgetRepresentation::PrintSelf(std::ostream& os, vtkIndent indent)
{
  vtkDataRepresentation::PrintSelf(os, indent);
}

void vtk2DWidgetRepresentation::SetRepresentation(vtkWidgetRepresentation *repr)
{
  if (this->Representation == repr)
  {
    return;
  }
}

void vtk2DWidgetRepresentation::SetEnabled(bool enabled)
{
  this->Enabled = enabled;
}
