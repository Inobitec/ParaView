#include "vtkPVXYChartViewInteractive.h"

#include "vtkObjectFactory.h"

vtkStandardNewMacro(vtkPVXYChartViewInteractive);

vtkPVXYChartViewInteractive::vtkPVXYChartViewInteractive()
  : vtkPVXYChartView()
{

}

vtkPVXYChartViewInteractive::~vtkPVXYChartViewInteractive()
{

}

void vtkPVXYChartViewInteractive::PrintSelf(std::ostream &os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}
