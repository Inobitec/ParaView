#include "pqDistancePropertyWidget.h"
#include "ui_pqLinePropertyWidget.h"

#include "vtkSMNewWidgetRepresentationProxy.h"
#include "vtkSMPropertyHelper.h"
#include "vtkSMPropertyGroup.h"

#include <QGridLayout>
#include <QLineEdit>


class pqDistancePropertyWidget::pqInternals
{
public:
  Ui::LinePropertyWidget Ui;
  bool PickPoint1;
  pqInternals()
    : PickPoint1(true)
  {
  }
};


pqDistancePropertyWidget::pqDistancePropertyWidget(vtkSMProxy *proxy, vtkSMPropertyGroup *smgroup, QWidget *parent)
  : Superclass("representations", "DistanceWidgetRepresentation", proxy, smgroup, parent)
  , Internals(new pqInternals())
{
//  QGridLayout* grid = new QGridLayout(this);
//  QLineEdit* le = new QLineEdit(this);
//  grid->addWidget(le, 0, 0);
  Ui::LinePropertyWidget& ui = this->Internals->Ui;
  ui.setupUi(this);

    if (vtkSMProperty* p1 = smgroup->GetProperty("Point1WorldPosition"))
  {
    ui.labelPoint1->setText(tr(p1->GetXMLLabel()));
    this->addPropertyLink(ui.point1X, "text2", SIGNAL(textChangedAndEditingFinished()), p1, 0);
    this->addPropertyLink(ui.point1Y, "text2", SIGNAL(textChangedAndEditingFinished()), p1, 1);
    this->addPropertyLink(ui.point1Z, "text2", SIGNAL(textChangedAndEditingFinished()), p1, 2);
    ui.labelPoint1->setText(p1->GetXMLLabel());
  }
  else
  {
    qCritical("Missing required property for function 'Point1WorldPosition'.");
  }

  if (vtkSMProperty* p2 = smgroup->GetProperty("Point2WorldPosition"))
  {
    ui.labelPoint2->setText(tr(p2->GetXMLLabel()));
    this->addPropertyLink(ui.point2X, "text2", SIGNAL(textChangedAndEditingFinished()), p2, 0);
    this->addPropertyLink(ui.point2Y, "text2", SIGNAL(textChangedAndEditingFinished()), p2, 1);
    this->addPropertyLink(ui.point2Z, "text2", SIGNAL(textChangedAndEditingFinished()), p2, 2);
    ui.labelPoint2->setText(p2->GetXMLLabel());
  }
  else
  {
    qCritical("Missing required property for function 'Point2WorldPosition'.");
  }

  if (smgroup->GetProperty("Input"))
  {
    this->connect(ui.centerOnBounds, SIGNAL(clicked()), SLOT(centerOnBounds()));
  }
  else
  {
    ui.centerOnBounds->hide();
  }

  // link show3DWidget checkbox
  this->connect(ui.show3DWidget, SIGNAL(toggled(bool)), SLOT(setWidgetVisible(bool)));
  ui.show3DWidget->connect(this, SIGNAL(widgetVisibilityToggled(bool)), SLOT(setChecked(bool)));
  this->setWidgetVisible(ui.show3DWidget->isChecked());

}

pqDistancePropertyWidget::~pqDistancePropertyWidget()
{
  delete  this->Internals;
}

void pqDistancePropertyWidget::centerOnBounds()
{
  vtkBoundingBox bbox = this->dataBounds();
  if (!bbox.IsValid())
  {
    return;
  }

  vtkSMNewWidgetRepresentationProxy* wdgProxy = this->widgetProxy();
  vtkSMPropertyHelper(wdgProxy, "Point1WorldPosition").Set(bbox.GetMinPoint(), 3);
  vtkSMPropertyHelper(wdgProxy, "Point2WorldPosition").Set(bbox.GetMaxPoint(), 3);
  wdgProxy->UpdateVTKObjects();
  emit this->changeAvailable();
  this->render();
}

void pqDistancePropertyWidget::placeWidget()
{
  vtkBoundingBox bbox = this->dataBounds();
  if (!bbox.IsValid())
  {
    bbox = vtkBoundingBox(0, 1, 0, 1, 0, 1);
  }

  vtkSMNewWidgetRepresentationProxy* wdgProxy = this->widgetProxy();

  double bds[6];
  bbox.GetBounds(bds);
  vtkSMPropertyHelper(wdgProxy, "PlaceWidget").Set(bds, 6);
  wdgProxy->UpdateVTKObjects();

  // This is incorrect. We should never be changing properties on the proxy like
  // this. The way we are letting users set the box without explicitly setting
  // the bounds is wrong. We'll have revisit that. For now, I am letting this
  // be. Please don't follow this pattern in your code.
  vtkSMPropertyHelper(this->proxy(), "Bounds", /*quiet*/ true).Set(bds, 6);
  this->proxy()->UpdateVTKObjects();
}
