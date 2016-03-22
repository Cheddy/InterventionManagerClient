#ifndef VIEWDIALOG_H
#define VIEWDIALOG_H

#include <QDialog>
#include "Model/datastructure.h"

namespace Ui {
class ViewDialog;
}

class ViewDialog : public QDialog
{
    Q_OBJECT
    
public:
    ViewDialog(DataStructure* structure);
    ~ViewDialog();
    
protected:
    Ui::ViewDialog *ui;
};

#endif // VIEWDIALOG_H
