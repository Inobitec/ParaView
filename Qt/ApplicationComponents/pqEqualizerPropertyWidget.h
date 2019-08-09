#ifndef pqEqualizerPropertyWidget_h
#define pqEqualizerPropertyWidget_h

#include "pqInteractiveProperty2DWidget.h"

/**
 * @class pqEqualizerPropertyWidget
 * @brief The pqEqualizerPropertyWidget class
 *
 * To use this widget for a property group (vtkSMPropertyGroup),
 * use "EqualizerPropertyWidget" as the "panel_widget" in the XML configuration for the proxy.
 */

class PQAPPLICATIONCOMPONENTS_EXPORT pqEqualizerPropertyWidget : public pqInteractiveProperty2DWidget
{
  Q_OBJECT
  typedef pqInteractiveProperty2DWidget Superclass;

public:
  explicit pqEqualizerPropertyWidget(vtkSMProxy* proxy, vtkSMPropertyGroup* smgroup, QWidget* parent = 0);
  ~pqEqualizerPropertyWidget() override;

protected slots:
  /**
   * Places the interactive widget using current data source information.
   */
  void placeWidget() override;
  void onStartInteraction();
  void onInteraction();
  void onEndInteraction();

private:
  void Init(vtkSMProxy* proxy, vtkSMPropertyGroup* smgroup);
  void UpdatePosition();

  Q_DISABLE_COPY(pqEqualizerPropertyWidget)
  pqPropertyLinks WidgetLinks;

  class pqInternals;
  pqInternals* Internals;
};

#endif
