#include "pqMultiLinesView.h"

#include <QGridLayout>
#include <QPushButton>
#include <QScrollBar>

#include "pqDataRepresentation.h"
#include "vtkSMChartSeriesSelectionDomain.h"
#include "vtkSMContextViewProxy.h"
#include "vtkSMProperty.h"
#include "vtkSMPropertyHelper.h"
#include "vtkXYChartRepresentationExt.h"

class pqMultiLinesView::pqInternals
{
public:
  pqInternals()
    : VerticalSB(nullptr)
  {
  }

  QScrollBar* VerticalSB;
};

pqMultiLinesView::pqMultiLinesView(const QString& group, const QString& name,
  vtkSMContextViewProxy* viewModule, pqServer* server, QObject* parent)
  : Superclass(MultiLinesViewType(), group, name, viewModule, server, parent)
  , Internals(new pqInternals())
{
  QObject::connect(this, SIGNAL(representationAdded(pqRepresentation*)), this,
    SLOT(onAddRepresentation(pqRepresentation*)));
}

pqMultiLinesView::~pqMultiLinesView()
{
  delete Internals;
}

void pqMultiLinesView::onAddRepresentation(pqRepresentation* repr)
{
  //  auto count = vtkSMPropertyHelper(repr->getProxy(), "CountOfArrays").GetAsInt();
  //  std::cout << "count of arrays = " << count << std::endl;
  vtkSMProxy* reprProxy = repr->getProxy();
  vtkSMChartSeriesSelectionDomain* domain = vtkSMChartSeriesSelectionDomain::SafeDownCast(
    reprProxy->GetProperty("SeriesVisibility")->FindDomain("vtkSMChartSeriesSelectionDomain"));
  if (domain == NULL)
  {
    return;
  }

  auto count = domain->GetNumberOfStrings();
  std::cout << "count of arrays = " << count << std::endl;
  this->Internals->VerticalSB->setRange(0, count-1);
}

QWidget* pqMultiLinesView::createWidget()
{
  QWidget* widget = new QWidget();
  QWidget* vtkwidget = Superclass::createWidget();
  QGridLayout* layout = new QGridLayout(widget);
  this->Internals->VerticalSB = new QScrollBar(Qt::Vertical, widget);
  layout->addWidget(vtkwidget, 0, 0);
  layout->addWidget(this->Internals->VerticalSB, 0, 1);

  connect(this->Internals->VerticalSB, &QScrollBar::valueChanged, this, &pqMultiLinesView::onScrollValueChanged);

  return widget;
}

pqDataRepresentation* pqMultiLinesView::activeRepresentation() const
{
  const auto reprs = this->getRepresentations();
  for (auto repr : reprs)
  {
    pqDataRepresentation* drepr = qobject_cast<pqDataRepresentation*>(repr);
    if (drepr && drepr->isVisible())
    {
      return drepr;
    }
  }
  return nullptr;
}

void pqMultiLinesView::onScrollValueChanged(int index)
{
  pqRepresentation* repr = this->activeRepresentation();
  if (!repr)
    return;

  vtkSMPropertyHelper(repr->getProxy(), "CurrentIndex").Set(index);
  repr->getProxy()->UpdateProperty("CurrentIndex");

  vtkSMViewProxy* view = this->getViewProxy();
  if (view)
    view->Update();
}
