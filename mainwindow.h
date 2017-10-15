#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QTextBrowser>
#include <QLabel>
#include <QString>
#include <vector>
#include "redblacktree.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, private RedBlackTree<int>
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:

  QLabel *m_pEditor;
  QPushButton *m_pInsert;  //增
  QPushButton *m_pDelete;  //删
  QPushButton *m_pSearch;  //查
  QPushButton *m_pClear;   //清
  QTextEdit *m_pTextEdit;
  QTextBrowser *m_pTextBrower;
  QTextBrowser *m_pIntroduceBrower;
  QString m_cShowText;

public:
  vector< int > m_vEnterData;            //输入数据

private:
  void InitWindow();         //创建各子窗口

public:
  void flashTextBrower();
  void flashIntroduceBrower();

private slots:
  void insertData();
  void deleteData();
  void searchData();
  void clearTree();

protected:
  void paintEvent(QPaintEvent *);



public:
  void visitNode(RbtNode<int> *root);
  //访问结点操作函数

};

#endif // MAINWINDOW_H
