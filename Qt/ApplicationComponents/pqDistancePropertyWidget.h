#ifndef pqDistancePropertyWidget_h
#define pqDistancePropertyWidget_h

#include "pqInteractivePropertyWidget.h"

class PQAPPLICATIONCOMPONENTS_EXPORT pqDistancePropertyWidget : public pqInteractivePropertyWidget
{
  Q_OBJECT
  typedef pqInteractivePropertyWidget Superclass;
public:
  pqDistancePropertyWidget(vtkSMProxy* proxy, vtkSMPropertyGroup* smgroup, QWidget* parent = 0);
  ~pqDistancePropertyWidget() override;

public slots:
  void centerOnBounds();

protected slots:
  /**
  * Places the interactive widget using current data source information.
  */
  void placeWidget() override;

private:
  Q_DISABLE_COPY(pqDistancePropertyWidget)
  pqPropertyLinks WidgetLinks;

  class pqInternals;
  pqInternals* Internals;
};

#endif
