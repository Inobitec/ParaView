#ifndef vtkPVXYChartViewInteractive_h
#define vtkPVXYChartViewInteractive_h

#include "vtkPVXYChartView.h"

/**
 * @class vtkPVXYChartViewInteractive
 * @brief The vtkPVXYChartViewInteractive class
 *
 *
 */

class VTKPVCLIENTSERVERCORERENDERING_EXPORT vtkPVXYChartViewInteractive : public vtkPVXYChartView
{
public:
  static vtkPVXYChartViewInteractive* New();
  vtkTypeMacro(vtkPVXYChartViewInteractive, vtkPVXYChartView);
  void PrintSelf(ostream& os, vtkIndent indent) override;

protected:
  vtkPVXYChartViewInteractive();
  ~vtkPVXYChartViewInteractive() override;

private:
  vtkPVXYChartViewInteractive(const vtkPVXYChartViewInteractive&) = delete;
  void operator=(const vtkPVXYChartViewInteractive&) = delete;
};

#endif
