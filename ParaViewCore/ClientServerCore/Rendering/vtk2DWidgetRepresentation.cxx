#include "vtk2DWidgetRepresentation.h"

#include "vtkCommand.h"
#include "vtkContextScene.h"
#include "vtkContextView.h"
#include "vtkLineContextItem.h"
#include "vtkObjectFactory.h"
#include "vtkPlotLine.h"
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
  this->ContextItem = vtkLineContextItem::New();
  this->ContextItem->SetVisible(true);
  this->ContextItem->SetInteractive(true);

  this->ObserverTag = this->ContextItem->AddObserver(
    vtkCommand::ModifiedEvent, this, &vtk2DWidgetRepresentation::OnContextItemModified);
}

vtk2DWidgetRepresentation::~vtk2DWidgetRepresentation() {}

bool vtk2DWidgetRepresentation::AddToView(vtkView *view)
{
  vtkPVContextView* pvview = vtkPVContextView::SafeDownCast(view);
  if(pvview)
  {
    this->View = pvview;
    vtkContextScene* scene = this->View->GetContextView()->GetScene();
    auto items_count = scene->GetNumberOfItems();
    scene->AddItem(this->ContextItem);
    items_count = scene->GetNumberOfItems();
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
