#include "pq2DLinePropertyWidget.h"

#include "vtkLineContextItem.h"
#include "vtkPVArrayInformation.h"
#include "vtkPVDataInformation.h"
#include "vtkPVDataSetAttributesInformation.h"
#include "vtkSMNew2DWidgetRepresentationProxy.h"
#include "vtkSMPropertyGroup.h"
#include "vtkSMPropertyHelper.h"
#include "vtkSMSourceProxy.h"
#include "vtkSMUncheckedPropertyHelper.h"

#include "pqDoubleLineEdit.h"
#include "pqIntRangeWidget.h"
#include "pqLineEdit.h"
#include "pqPropertiesPanel.h"
#include "pqPropertyLinks.h"

#include <QCheckBox>
#include <QVBoxLayout>

class pq2DLinePropertyWidget::pqInternals
{
public:
  pqIntRangeWidget* posWidget;
};

pq2DLinePropertyWidget::pq2DLinePropertyWidget(
  vtkSMProxy* proxy, vtkSMPropertyGroup* smgroup, QWidget* parent)
  : Superclass("representations", "2DLineWidgetRepresentation", proxy, smgroup, parent)
  , Internals(new pqInternals())
{
  Init(proxy, smgroup);
}

pq2DLinePropertyWidget::~pq2DLinePropertyWidget()
{
  delete this->Internals;
}

void pq2DLinePropertyWidget::placeWidget()
{
  vtkSMNew2DWidgetRepresentationProxy* wdgProxy = this->widgetProxy();
  wdgProxy->UpdateVTKObjects();
}

void pq2DLinePropertyWidget::onStartInteraction()
{
  UpdatePosition();
}

void pq2DLinePropertyWidget::onInteraction()
{
  UpdatePosition();
}

void pq2DLinePropertyWidget::onEndInteraction()
{
  UpdatePosition();
}

void pq2DLinePropertyWidget::Init(vtkSMProxy* proxy, vtkSMPropertyGroup* smgroup)
{
  Q_UNUSED(proxy);

  vtkSMSourceProxy* input = vtkSMSourceProxy::SafeDownCast(
    vtkSMUncheckedPropertyHelper(this->proxy(), "Input").GetAsProxy(0));
  if (!input)
    return;

  vtkSMProxy* wdgProxy = this->widgetProxy();

  QVBoxLayout* layout = new QVBoxLayout(this);
  layout->setMargin(pqPropertiesPanel::suggestedMargin());

  QCheckBox* visibility = new QCheckBox(tr("Visibility"), this);
  layout->addWidget(visibility);

  this->WidgetLinks.addPropertyLink(
    visibility, "checked", SIGNAL(toggled(bool)), wdgProxy, wdgProxy->GetProperty("Visibility"));

  this->Internals->posWidget = new pqIntRangeWidget(this);
  // pqDoubleLineEdit* pos_widget = new pqDoubleLineEdit(this);
  vtkPVDataSetAttributesInformation* fdi = input->GetDataInformation(0)->GetRowDataInformation();
  if (!fdi)
    return;
  vtkPVArrayInformation* array_info = fdi->GetArrayInformation(0);
  if (!array_info)
    return;
  auto row_count = array_info->GetNumberOfTuples();
  this->Internals->posWidget->setMinimum(0);
//  this->Internals->posWidget->setMaximum(row_count - 1);
  this->Internals->posWidget->setMaximum(500); // FD/2,

  layout->addWidget(this->Internals->posWidget);

  if (vtkSMProperty* p1 = smgroup->GetProperty("MarkerPositionFunc"))
  {
    this->addPropertyLink(this->Internals->posWidget, "value", SIGNAL(valueEdited(int)), p1, 0);
    this->WidgetLinks.addPropertyLink(this->Internals->posWidget, "value", SIGNAL(valueEdited(int)),
      wdgProxy, wdgProxy->GetProperty("MarkerPositionFunc"));
  }

  connect(this, SIGNAL(startInteraction()), this, SLOT(onStartInteraction()));
  connect(this, SIGNAL(interaction()), this, SLOT(onInteraction()));
  connect(this, SIGNAL(endInteraction()), this, SLOT(onEndInteraction()));
}

void pq2DLinePropertyWidget::UpdatePosition()
{
  vtkSMNew2DWidgetRepresentationProxy* wdgProxy = this->widgetProxy();
  vtkSMProxy* contextProxy = wdgProxy->GetContextItemProxy();
  vtkLineContextItem* item = vtkLineContextItem::SafeDownCast(contextProxy->GetClientSideObject());
  auto pos = item->GetPosition();
  this->Internals->posWidget->setValue(pos);
}
