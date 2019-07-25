#include "vtkSMNew2DWidgetRepresentationProxy.h"

#include "vtkObjectFactory.h"

vtkStandardNewMacro(vtkSMNew2DWidgetRepresentationProxy);

vtkSMNew2DWidgetRepresentationProxy::vtkSMNew2DWidgetRepresentationProxy()
  : vtkSMProxy()
{

}

vtkSMNew2DWidgetRepresentationProxy::~vtkSMNew2DWidgetRepresentationProxy()
{

}

void vtkSMNew2DWidgetRepresentationProxy::CreateVTKObjects()
{

}

void vtkSMNew2DWidgetRepresentationProxy::PrintSelf(std::ostream &os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

bool vtkSMNew2DWidgetRepresentationProxy::LinkProperties(vtkSMProxy *controlledProxy, vtkSMPropertyGroup *controlledPropertyGroup)
{
  return true;
}

bool vtkSMNew2DWidgetRepresentationProxy::UnlinkProperties(vtkSMProxy *controlledProxy)
{
  return true;
}
