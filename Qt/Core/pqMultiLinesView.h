#ifndef pqScrolledView_h
#define pqScrolledView_h

#include "pqContextView.h"

class vtkSMSourceProxy;
class pqDataRepresentation;

/**
 * @class The pqMultiLinesView class
 */

class PQCORE_EXPORT pqMultiLinesView : public pqContextView
{
  Q_OBJECT
  typedef pqContextView Superclass;

public:
  static QString MultiLinesViewType() { return "MultiLinesView"; }

public:
  pqMultiLinesView(const QString& group, const QString& name, vtkSMContextViewProxy* viewModule,
    pqServer* server, QObject* parent = NULL);

  virtual ~pqMultiLinesView();

public slots:
  void onAddRepresentation(pqRepresentation*);
  void onScrollValueChanged(int);

protected:
  QWidget* createWidget() override;

private:
  Q_DISABLE_COPY(pqMultiLinesView)

  pqDataRepresentation* activeRepresentation() const;

  class pqInternals;
  pqInternals* Internals;
};

#endif // PQSCROLLEDVIEW_H
