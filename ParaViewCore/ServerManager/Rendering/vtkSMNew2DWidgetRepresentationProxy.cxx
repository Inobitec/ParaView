#include "vtkSMNew2DWidgetRepresentationProxy.h"

#include "vtk2DWidgetRepresentation.h"
#include "vtkObjectFactory.h"
#include "vtkSMProperty.h"
#include "vtkSMPropertyIterator.h"
#include "vtkSMPropertyLink.h"

#include <list>

struct vtkSMNew2DWidgetRepresentationProxy::Internals
{
  typedef std::list<vtkSmartPointer<vtkSMLink> > LinksType;
  LinksType Links;
};


vtkStandardNewMacro(vtkSMNew2DWidgetRepresentationProxy);

vtkSMNew2DWidgetRepresentationProxy::vtkSMNew2DWidgetRepresentationProxy()
  : vtkSMProxy()
  , Internal(new Internals())
{

}

vtkSMNew2DWidgetRepresentationProxy::~vtkSMNew2DWidgetRepresentationProxy()
{
  if (this->Internal)
  {
    delete this->Internal;
  }
}

void vtkSMNew2DWidgetRepresentationProxy::CreateVTKObjects()
{
  if (this->ObjectsCreated)
  {
    return;
  }

  this->Superclass::CreateVTKObjects();
  vtk2DWidgetRepresentation* clientObject =
    vtk2DWidgetRepresentation::SafeDownCast(this->GetClientSideObject());

    // Since links copy values from input to output,
  // we need to make sure that input properties i.e. the info
  // properties are not empty.
  this->UpdatePropertyInformation();

  vtkSMPropertyIterator* piter = this->NewPropertyIterator();
  for (piter->Begin(); !piter->IsAtEnd(); piter->Next())
  {
    vtkSMProperty* prop = piter->GetProperty();
    vtkSMProperty* info = prop->GetInformationProperty();
    if (info)
    {
      // This ensures that the property value from the loaded state is
      // preserved, and not overwritten by the default value from
      // the property information
      info->Copy(prop);

      vtkSMPropertyLink* link = vtkSMPropertyLink::New();

      // NOTE: vtkSMPropertyLink no longer affect proxy reference. We're now
      // only using vtkWeakPointer in vtkSMPropertyLink.
      link->AddLinkedProperty(this, piter->GetKey(), vtkSMLink::OUTPUT);
      link->AddLinkedProperty(this, this->GetPropertyName(info), vtkSMLink::INPUT);

      this->Internal->Links.push_back(link);
      link->Delete();
    }
  }
  piter->Delete();

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
