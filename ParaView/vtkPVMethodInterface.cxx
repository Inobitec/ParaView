/*=========================================================================

  Program:   ParaView
  Module:    vtkPVMethodInterface.cxx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

Copyright (c) 2000-2001 Kitware Inc. 469 Clifton Corporate Parkway,
Clifton Park, NY, 12065, USA.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

 * Neither the name of Kitware nor the names of any contributors may be used
   to endorse or promote products derived from this software without specific 
   prior written permission.

 * Modified source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=========================================================================*/
#include "vtkPVMethodInterface.h"
#include "vtkStringList.h"
#include "vtkObjectFactory.h"


//----------------------------------------------------------------------------
vtkPVMethodInterface::vtkPVMethodInterface()
{
  this->VariableName = NULL;
  this->SetCommand = NULL;
  this->GetCommand = NULL;
  this->ArgumentTypes = vtkIdList::New();
  this->WidgetType = VTK_PV_METHOD_WIDGET_ENTRY;
  this->SelectionEntries = NULL;
  this->FileExtension = NULL;
  this->BalloonHelp = NULL;
}

//----------------------------------------------------------------------------
vtkPVMethodInterface::~vtkPVMethodInterface()
{
  this->SetVariableName(NULL);
  this->SetSetCommand(NULL);
  this->SetGetCommand(NULL);
  this->ArgumentTypes->Delete();
  this->ArgumentTypes = NULL;
  if (this->SelectionEntries)
    {
    this->SelectionEntries->Delete();
    this->SelectionEntries = NULL;
    }
  this->SetFileExtension(NULL);
  if (this->BalloonHelp)
    {
    delete [] this->BalloonHelp;
    this->BalloonHelp = NULL;
    }
}

//----------------------------------------------------------------------------
vtkPVMethodInterface* vtkPVMethodInterface::New()
{
  // First try to create the object from the vtkObjectFactory
  vtkObject* ret = vtkObjectFactory::CreateInstance("vtkPVMethodInterface");
  if(ret)
    {
    return (vtkPVMethodInterface*)ret;
    }
  // If the factory was unable to create the object, then create it here.
  return new vtkPVMethodInterface;
}

//----------------------------------------------------------------------------
void vtkPVMethodInterface::AddArgumentType(int type)
{
  this->ArgumentTypes->InsertNextId(type);
}

//----------------------------------------------------------------------------
void vtkPVMethodInterface::AddSelectionEntry(int idx, const char *string)
{
  if (this->SelectionEntries == NULL)
    {
    this->SelectionEntries = vtkStringList::New();
    }
  this->SelectionEntries->SetString(idx, string);
}

//----------------------------------------------------------------------------
void vtkPVMethodInterface::SetWidgetType(int type)
{
  if (this->WidgetType == type)
    {
    return;
    }
  this->Modified();
  this->WidgetType = type;
  
  if (this->WidgetType == VTK_PV_METHOD_WIDGET_TOGGLE)
    {
    this->ArgumentTypes->Reset();
    this->AddIntegerArgument();
    }
  if (this->WidgetType == VTK_PV_METHOD_WIDGET_SELECTION)
    {
    this->ArgumentTypes->Reset();
    this->AddIntegerArgument();
    }
  if (this->WidgetType == VTK_PV_METHOD_WIDGET_FILE)
    {
    this->ArgumentTypes->Reset();
    this->AddStringArgument();
    }
}

