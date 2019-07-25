#include "pq2DLinePropertyWidget.h"

#include "vtkSMNew2DWidgetRepresentationProxy.h"
#include "vtkSMPropertyHelper.h"
#include "vtkSMPropertyGroup.h"

pq2DLinePropertyWidget::pq2DLinePropertyWidget(vtkSMProxy *proxy, vtkSMPropertyGroup *smgroup, QWidget *parent)
  :  Superclass("representations", "2DLineWidgetRepresentation", proxy, smgroup, parent)
{

}

pq2DLinePropertyWidget::~pq2DLinePropertyWidget()
{

}

void pq2DLinePropertyWidget::placeWidget()
{
  vtkSMNew2DWidgetRepresentationProxy* wdgProxy = this->widgetProxy();
}
