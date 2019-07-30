#include "pq2DLinePropertyWidget.h"

#include "vtkSMNew2DWidgetRepresentationProxy.h"
#include "vtkSMPropertyGroup.h"
#include "vtkSMPropertyHelper.h"
#include "vtkSMSourceProxy.h"
#include "vtkSMUncheckedPropertyHelper.h"

#include "pqIntRangeWidget.h"
#include "pqLineEdit.h"
#include "pqPropertiesPanel.h"

#include <QCheckBox>
#include <QVBoxLayout>

pq2DLinePropertyWidget::pq2DLinePropertyWidget(
  vtkSMProxy* proxy, vtkSMPropertyGroup* smgroup, QWidget* parent)
  : Superclass("representations", "2DLineWidgetRepresentation", proxy, smgroup, parent)
{
  Init(proxy, smgroup);
}

pq2DLinePropertyWidget::~pq2DLinePropertyWidget() {}

void pq2DLinePropertyWidget::placeWidget()
{
  vtkSMNew2DWidgetRepresentationProxy* wdgProxy = this->widgetProxy();
  wdgProxy->UpdateVTKObjects();
}

void pq2DLinePropertyWidget::Init(vtkSMProxy *proxy, vtkSMPropertyGroup *smgroup)
{
  vtkSMSourceProxy* input = vtkSMSourceProxy::SafeDownCast(
    vtkSMUncheckedPropertyHelper(this->proxy(), "Input").GetAsProxy(0));
  if (!input)
  {
    return;
  }

  vtkSMProxy* wdgProxy = this->widgetProxy();

  QVBoxLayout* layout = new QVBoxLayout(this);
  layout->setMargin(pqPropertiesPanel::suggestedMargin());

  QCheckBox* visibility = new QCheckBox(tr("Visibility"), this);
  layout->addWidget(visibility);

  this->WidgetLinks.addPropertyLink(visibility, "checked", SIGNAL(toggled(bool)),
    wdgProxy, wdgProxy->GetProperty("Visibility"));
}
