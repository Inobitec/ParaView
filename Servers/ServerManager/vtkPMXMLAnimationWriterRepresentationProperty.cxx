/*=========================================================================

  Program:   ParaView
  Module:    $RCSfile$

  Copyright (c) Kitware, Inc.
  All rights reserved.
  See Copyright.txt or http://www.paraview.org/HTML/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkPMXMLAnimationWriterRepresentationProperty.h"

#include "vtkObjectFactory.h"
#include "vtkPMProxy.h"
#include "vtkSMMessage.h"

#include <vtksys/ios/sstream>

vtkStandardNewMacro(vtkPMXMLAnimationWriterRepresentationProperty);
//----------------------------------------------------------------------------
vtkPMXMLAnimationWriterRepresentationProperty::vtkPMXMLAnimationWriterRepresentationProperty()
{
}

//----------------------------------------------------------------------------
vtkPMXMLAnimationWriterRepresentationProperty::~vtkPMXMLAnimationWriterRepresentationProperty()
{
}

//----------------------------------------------------------------------------
bool vtkPMXMLAnimationWriterRepresentationProperty::Push(
  vtkSMMessage* message, int offset)
{
  assert(message->ExtensionSize(ProxyState::property) > offset);

  const ProxyState_Property prop =
    message->GetExtension(ProxyState::property, offset);
  assert(strcmp(prop.name().c_str(), this->GetXMLName()) == 0);

  const Variant variant = prop.value();
  vtkstd::vector<vtkTypeUInt32> proxy_ids;
  proxy_ids.resize(variant.proxy_global_id_size());
  for (int cc=0; cc < variant.proxy_global_id_size(); cc++)
    {
    proxy_ids[cc] = variant.proxy_global_id(cc);
    }

  vtkObjectBase* object = this->GetVTKObject();
  vtkClientServerStream stream;
  if (this->CleanCommand)
    {
    stream << vtkClientServerStream::Invoke << object
           << this->CleanCommand << vtkClientServerStream::End;
    }
  for (size_t cc=0; cc < proxy_ids.size(); cc++)
    {
    vtkPMProxy* pmproxy = vtkPMProxy::SafeDownCast(
      this->GetPMObject(proxy_ids[cc]));

    // Assign unique group name for each source.
    vtksys_ios::ostringstream groupname_str;
    groupname_str << "source" << proxy_ids[cc];
    stream << vtkClientServerStream::Invoke
      << object
      << this->GetCommand()
      << pmproxy->GetVTKObject()
      << groupname_str.str().c_str()
      << vtkClientServerStream::End;
    }
  return this->ProcessMessage(stream);
}

//----------------------------------------------------------------------------
void vtkPMXMLAnimationWriterRepresentationProperty::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}
