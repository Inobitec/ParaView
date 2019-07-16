#ifndef vtkXYChartRepresentationExt_h
#define vtkXYChartRepresentationExt_h

#include "vtkXYChartRepresentation.h"


/**
 * @class The vtkXYChartRepresentationExt class
 */

class VTKPVCLIENTSERVERCORERENDERING_EXPORT vtkXYChartRepresentationExt : public vtkXYChartRepresentation
{
public:
  static vtkXYChartRepresentationExt* New();
  vtkTypeMacro(vtkXYChartRepresentationExt, vtkXYChartRepresentation);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  vtkSetMacro(CurrentIndex, int);
  vtkGetMacro(CurrentIndex, int);

  vtkSetMacro(CountOfArrays, int);
  // vtkGetMacro(CountOfArrays, int);
  int GetCountOfArrays() const;

  void SetSeriesVisibility(const char* seriesname, bool visible);

protected:
  vtkXYChartRepresentationExt();
  ~vtkXYChartRepresentationExt() override;

  void PrepareForRendering() override;

private:
  vtkXYChartRepresentationExt(const vtkXYChartRepresentationExt&) = delete;
  void operator=(const vtkXYChartRepresentationExt&) = delete;

  int CurrentIndex;
  int CountOfArrays;

  class vtkInternals;
  vtkInternals* Internals;
};

#endif
