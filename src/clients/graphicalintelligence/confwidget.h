#ifndef CONFWIDGET_H
#define CONFWIDGET_H

#include <vector>
#include <QString>
#include <vartypes/VarTreeView.h>
#include <vartypes/VarTreeModel.h>

class ConfWidget : public VarTypes::VarTreeView
{
 Q_OBJECT
 public:
  ConfWidget(QWidget *);
  virtual ~ConfWidget();

 protected:
  VarTypes::VarTreeModel *tree_model;
  vector<VarTypes::VarPtr> root_items;
};

#endif
