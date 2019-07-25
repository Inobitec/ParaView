#ifndef pq2DLinePropertyWidget_h
#define pq2DLinePropertyWidget_h

/**
 * @class The pq2DLinePropertyWidget class
 *
 * To use this widget for a property group (vtkSMPropertyGroup),
 * use "2DLinePropertyWidget" as the "panel_widget" in the XML configuration for the proxy.
 */

#include "pqInteractiveProperty2DWidget.h"

class PQAPPLICATIONCOMPONENTS_EXPORT pq2DLinePropertyWidget : public pqInteractiveProperty2DWidget
{
  Q_OBJECT
  typedef pqInteractiveProperty2DWidget Superclass;
public:
  pq2DLinePropertyWidget(vtkSMProxy* proxy, vtkSMPropertyGroup* smgroup, QWidget* parent = 0);
  ~pq2DLinePropertyWidget() override;

protected slots:
  /**
  * Places the interactive widget using current data source information.
  */
  void placeWidget() override;

private:
  Q_DISABLE_COPY(pq2DLinePropertyWidget)
  pqPropertyLinks WidgetLinks;
};

#endif
