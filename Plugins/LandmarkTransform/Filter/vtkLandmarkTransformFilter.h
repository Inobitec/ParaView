#ifndef __vtkLandmarkTransformFilter_h
#define __vtkLandmarkTransformFilter_h

#include "vtkSmartPointer.h" // compiler errors if this is forward declared

#include "vtkExecutive.h"
#include "vtkPolyDataAlgorithm.h" //superclass
#include "vtkMath.h"
#include "vtkLandmarkTransformFilterModule.h"

class vtkPolyData;
class vtkTransform;
class vtkInformation;
class vtkInformationVector;
class vtkLandmarkTransform;


class VTKLANDMARKTRANSFORMFILTER_EXPORT vtkLandmarkTransformFilter : public vtkPolyDataAlgorithm
{
public:
  static vtkLandmarkTransformFilter* New();
  vtkTypeMacro(vtkLandmarkTransformFilter, vtkPolyDataAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent) override;

protected:
  vtkLandmarkTransformFilter();
  ~vtkLandmarkTransformFilter();

  // Make sure the pipeline knows what type we expect as input
  int FillInputPortInformation(int port, vtkInformation* info) override;

  // Generate output
  int RequestData(vtkInformation*, vtkInformationVector**,
    vtkInformationVector*) override; // the function that makes this class work with the vtk pipeline

private:
  // BTX
  // BTX-ETX comment is to hide these variable declarations from
  // bin/vtkWrapClientServer. If omitted, we'd get a
  // *** SYNTAX ERROR found in parsing the header file vtkICPFilter.h before line 34 ***

  vtkSmartPointer<vtkLandmarkTransform> LandmarkTransform;
  // ETX
};
#endif
