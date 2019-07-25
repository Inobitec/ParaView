#include "vtk2DWidgetRepresentation.h"

#include "vtkObjectFactory.h"
#include "vtkPVContextView.h"

vtkStandardNewMacro(vtk2DWidgetRepresentation);

vtk2DWidgetRepresentation::vtk2DWidgetRepresentation()
  : vtkDataRepresentation()
  , Representation(nullptr)
  , Enabled(false)
{
  this->SetNumberOfInputPorts(0);
}

vtk2DWidgetRepresentation::~vtk2DWidgetRepresentation() {}

bool vtk2DWidgetRepresentation::AddToView(vtkView *view)
{
  vtkPVContextView* pvview = vtkPVContextView::SafeDownCast(view);
  if(pvview)
  {
    this->View = pvview;
    return true;
  }

  return false;
}

bool vtk2DWidgetRepresentation::RemoveFromView(vtkView *view)
{
  vtkPVContextView* pvview = vtkPVContextView::SafeDownCast(view);
  if(pvview)
  {
    this->View = nullptr;
    return true;
  }

  return false;
}

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
