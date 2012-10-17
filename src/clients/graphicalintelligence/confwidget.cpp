#include "confwidget.h"
//#include <QDir>

ConfWidget::ConfWidget(QWidget *)
    : VarTreeView(new VarTypes::VarTreeModel())
{
  //TODO

  model->setRootItems(root_items);
}

ConfWidget::~ConfWidget()
{
}
