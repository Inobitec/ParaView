#include "pqEqualizerPropertyWidget.h"

#include "vtkEqualizerContextItem.h"
#include "vtkPVArrayInformation.h"
#include "vtkPVDataInformation.h"
#include "vtkPVDataSetAttributesInformation.h"
#include "vtkSMNew2DWidgetRepresentationProxy.h"
#include "vtkSMProperty.h"
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
#include <QPushButton>
#include <QVBoxLayout>

class pqEqualizerPropertyWidget::pqInternals
{
public:
  pqLineEdit* pointsLE;
  QPushButton* savePB;
  QPushButton* loadPB;
  vtkEqualizerContextItem* EqualizerItem;
};


pqEqualizerPropertyWidget::pqEqualizerPropertyWidget(vtkSMProxy *proxy, vtkSMPropertyGroup *smgroup, QWidget *parent)
  : Superclass("representations", "EqualizerWidgetRepresentation", proxy, smgroup, parent)
  , Internals(new pqInternals())
{
  Init(proxy, smgroup);
}

pqEqualizerPropertyWidget::~pqEqualizerPropertyWidget()
{
  delete this->Internals;
}

void pqEqualizerPropertyWidget::placeWidget()
{
  vtkSMNew2DWidgetRepresentationProxy* wdgProxy = this->widgetProxy();
  wdgProxy->UpdateVTKObjects();
}

void pqEqualizerPropertyWidget::onStartInteraction()
{
  UpdatePosition();
}

void pqEqualizerPropertyWidget::onInteraction()
{
  UpdatePosition();
}

void pqEqualizerPropertyWidget::onEndInteraction()
{
  UpdatePosition();
}

void pqEqualizerPropertyWidget::Init(vtkSMProxy *proxy, vtkSMPropertyGroup *smgroup)
{
  Q_UNUSED(proxy);
  std::cout << "pqEqualizerPropertyWidget::Init" << std::endl;
  vtkSMSourceProxy* input = vtkSMSourceProxy::SafeDownCast(
    vtkSMUncheckedPropertyHelper(this->proxy(), "Input").GetAsProxy(0));
  if (!input)
    return;

  vtkSMNew2DWidgetRepresentationProxy* wdgProxy = this->widgetProxy();

  QVBoxLayout* layout = new QVBoxLayout(this);
  layout->setMargin(pqPropertiesPanel::suggestedMargin());

  QCheckBox* visibility = new QCheckBox(tr("Visibility"), this);
  layout->addWidget(visibility);

  this->WidgetLinks.addPropertyLink(
    visibility, "checked", SIGNAL(toggled(bool)), wdgProxy, wdgProxy->GetProperty("Visibility"));

  this->Internals->savePB = new QPushButton(tr("Save"), this);
  this->Internals->loadPB = new QPushButton(tr("Load"), this);
  layout->addWidget(this->Internals->savePB);
  layout->addWidget(this->Internals->loadPB);
  // TODO: add an implementation

  this->Internals->pointsLE = new pqLineEdit(this);
  this->Internals->pointsLE->setEnabled(false);
  layout->addWidget(this->Internals->pointsLE);

  vtkPVDataSetAttributesInformation* fdi = input->GetDataInformation(0)->GetRowDataInformation();
  if (!fdi)
    return;
  vtkPVArrayInformation* array_info = fdi->GetArrayInformation(0);
  if (!array_info)
    return;

  if (vtkSMProperty* p1 = smgroup->GetProperty("EqualizerPointsFunc"))
  {
    this->addPropertyLink(this->Internals->pointsLE, "text2", SIGNAL(textChangedAndEditingFinished()), p1, 0);
    this->WidgetLinks.addPropertyLink(this->Internals->pointsLE, "text2", SIGNAL(textChangedAndEditingFinished()),
      wdgProxy, wdgProxy->GetProperty("EqualizerPointsFunc"));
  }

  connect(this, SIGNAL(startInteraction()), this, SLOT(onStartInteraction()));
  connect(this, SIGNAL(interaction()), this, SLOT(onInteraction()));
  connect(this, SIGNAL(endInteraction()), this, SLOT(onEndInteraction()));


  // TODO: add real frequency
  constexpr auto frequency = 1000;
  // auto row_count = array_info->GetNumberOfTuples();
  QString init_points(QString("0,0; %1,0;").arg(frequency/2));
  this->Internals->pointsLE->setText(init_points);

  vtkSMProxy* contextProxy = wdgProxy->GetContextItemProxy();
  this->Internals->EqualizerItem = vtkEqualizerContextItem::SafeDownCast(contextProxy->GetClientSideObject());
  this->Internals->EqualizerItem->SetPoints(init_points.toStdString());

  smgroup->GetProperty("EqualizerPointsFunc")->Modified();

  connect(visibility, &QCheckBox::toggled, [this](bool visible) {
    if(visible)
      this->Internals->EqualizerItem->SetPoints(this->Internals->pointsLE->text().toStdString());
  });

  this->reset();
}

void pqEqualizerPropertyWidget::UpdatePosition()
{
  if(!this->Internals->EqualizerItem)
    return;
  auto points = this->Internals->EqualizerItem->GetPoints();
  this->Internals->pointsLE->setText(QString::fromStdString(points));
}
