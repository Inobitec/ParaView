#include "vtk2DWidgetRepresentation.h"

#include "vtkChartXY.h"
#include "vtkCommand.h"
#include "vtkContextScene.h"
#include "vtkContextView.h"
#include "vtkObjectFactory.h"
#include "vtkPVContextView.h"
#include "vtkPVXYChartView.h"

vtkStandardNewMacro(vtk2DWidgetRepresentation);

vtk2DWidgetRepresentation::vtk2DWidgetRepresentation()
  : vtkDataRepresentation()
  , ContextItem(nullptr)
  , Enabled(false)
  , ObserverTag(0)
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
    vtkContextScene* scene = this->View->GetContextView()->GetScene();
    auto itemsCount = scene->GetNumberOfItems();
    for(unsigned int i=0; i<itemsCount; ++i)
    {
      vtkAbstractContextItem* item = scene->GetItem(i);
      vtkChartXY* chart = vtkChartXY::SafeDownCast(item);
      if(chart)
      {
        auto transforms = chart->GetTransforms();
        this->ContextItem->SetTransform(transforms.at(0));
        break;
      }
    }
    scene->AddItem(this->ContextItem);
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

void vtk2DWidgetRepresentation::OnContextItemModified()
{
  if(this->View != nullptr)
    this->View->Update();
}

void vtk2DWidgetRepresentation::PrintSelf(std::ostream& os, vtkIndent indent)
{
  vtkDataRepresentation::PrintSelf(os, indent);
}

void vtk2DWidgetRepresentation::SetContextItem(vtkContextItem *item)
{
  if (this->ContextItem == item)
  {
    return;
  }

  if (this->ContextItem)
  {
    this->ContextItem->RemoveObserver(this->ObserverTag);
    this->ObserverTag = 0;
  }

  this->ContextItem = item;

  if (this->ContextItem)
  {
    this->ObserverTag = this->ContextItem->AddObserver(
      vtkCommand::ModifiedEvent, this, &vtk2DWidgetRepresentation::OnContextItemModified);
  }
}

void vtk2DWidgetRepresentation::SetEnabled(bool enabled)
{
  this->Enabled = enabled;
}
