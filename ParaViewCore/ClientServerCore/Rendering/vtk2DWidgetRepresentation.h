#ifndef vtk2DWidgetRepresentation_h
#define vtk2DWidgetRepresentation_h

#include "vtkDataRepresentation.h"
#include "vtkPVClientServerCoreRenderingModule.h"

class vtkWidgetRepresentation;

/**
 * @class   vtk2DWidgetRepresentation
 *
 * vtk2DWidgetRepresentation is a vtkDataRepresentation subclass for 2D widgets
 * and their representations. It makes it possible to add 2D widgets to
 * vtkPVContextView.
 */

class VTKPVCLIENTSERVERCORERENDERING_EXPORT vtk2DWidgetRepresentation : public vtkDataRepresentation
{
public:
  static vtk2DWidgetRepresentation* New();
  vtkTypeMacro(vtk2DWidgetRepresentation, vtkDataRepresentation);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  //@{
  /**
   * Get/Set the representation.
   */
  void SetRepresentation(vtkWidgetRepresentation*);
  vtkGetObjectMacro(Representation, vtkWidgetRepresentation);
  //@}

  //@{
  /**
   * Get/Set whether the widget is enabled.
   */
  void SetEnabled(bool);
  vtkGetMacro(Enabled, bool);
  vtkBooleanMacro(Enabled, bool);
  //@}

protected:
  vtk2DWidgetRepresentation();
  ~vtk2DWidgetRepresentation() override;

  vtkWidgetRepresentation* Representation;
  bool Enabled;

private:
  vtk2DWidgetRepresentation(const vtk2DWidgetRepresentation&) = delete;
  void operator=(const vtk2DWidgetRepresentation&) = delete;
};

#endif
