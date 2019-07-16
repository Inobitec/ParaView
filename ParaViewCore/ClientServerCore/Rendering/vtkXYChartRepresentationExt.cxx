#include "vtkXYChartRepresentationExt.h"

#include "vtkChartXY.h"
#include "vtkNew.h"
#include "vtkObjectFactory.h"
#include "vtkPlot.h"
#include "vtkTable.h"

#include <vector>

class vtkXYChartRepresentationExt::vtkInternals
{
public:
  vtkInternals()
    : Plot(nullptr)
  {
  }
  ~vtkInternals() {}

  vtkPlot* Plot;
};

//
vtkStandardNewMacro(vtkXYChartRepresentationExt);

vtkXYChartRepresentationExt::vtkXYChartRepresentationExt()
  : vtkXYChartRepresentation()
  , CurrentIndex(0)
  , CountOfArrays(100)
  , Internals(new vtkInternals)
{
  //  this->Modified();
}

vtkXYChartRepresentationExt::~vtkXYChartRepresentationExt()
{
  delete this->Internals;
}

void vtkXYChartRepresentationExt::PrepareForRendering()
{
  // this->Superclass::PrepareForRendering();

  vtkChartXY* chartXY = this->GetChart();
  //  assert(chartXY != NULL); // we are assured this is always so.
  if (this->Internals->Plot != nullptr)
  {
    this->Internals->Plot->SetVisible(false);
    chartXY->RemovePlotInstance(this->Internals->Plot);
  }

  vtkChartRepresentation::MapOfTables tables;
  if (!this->GetLocalOutput(tables))
  {
    //    this->Internals->HideAllPlots();
    return;
  }
  std::vector<std::string> all_column_names;
  for (auto it = tables.begin(); it != tables.end(); ++it)
  {
    const std::string& tableName = it->first;
    vtkTable* table = it->second.GetPointer();
    vtkIdType numCols = table->GetNumberOfColumns();
    for (vtkIdType cc = 0; cc < numCols; ++cc)
    {
      std::string columnName = table->GetColumnName(cc);
      all_column_names.push_back(columnName);
    }
  }

  vtkPlot* plot = chartXY->AddPlot(this->GetChartType());

  auto first = tables.begin();
  auto table = first->second;
  plot->SetInputData(table);
  plot->SetUseIndexForXSeries(this->GetUseIndexForXAxis());
  plot->SetInputArray(0, this->GetXAxisSeriesName());

  std::string columnName = table->GetColumnName(this->CurrentIndex);
  plot->SetInputArray(1, columnName);

  this->Internals->Plot = plot;
}

void vtkXYChartRepresentationExt::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

int vtkXYChartRepresentationExt::GetCountOfArrays() const
{
  std::cout << "vtkXYChartRepresentationExt::GetCountOfArrays(): " << CountOfArrays << std::endl;
  return CountOfArrays;
}

void vtkXYChartRepresentationExt::SetSeriesVisibility(const char* seriesname, bool visible)
{
  assert(seriesname != NULL);
//  std::cout << "vtkXYChartRepresentationExt::SetSeriesVisibility: " << seriesname << " - " << visible << std::endl;
  this->Modified();
}
