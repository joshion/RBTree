#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <limits>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  RedBlackTree<int>()
{
  //设置主界面
  this->setWindowOpacity(1.0);//设置窗口透明度
  this->setMinimumSize(840,480); //设置最小大小
  this->setWindowTitle("View Of RedBlack_Tree");//设置主窗口标题
  InitWindow();                                            //要先new才能使用
  flashIntroduceBrower();                                  //刷新说明窗口
  flashTextBrower();                                       //刷新红黑树显示窗口
}

MainWindow::~MainWindow()
{
  delete m_pEditor;
  delete m_pInsert;
  delete m_pDelete;
  delete m_pTextEdit;
  delete m_pTextBrower;
  delete m_pIntroduceBrower;
}

void MainWindow::InitWindow()
{
  m_pEditor = new QLabel(this);
  m_pEditor->setText(tr("作者信息:   班级:计科13(2), 学号:3113005848, 姓名:魏永倬"));
  m_pEditor->setAlignment(Qt::AlignLeft);

  m_pInsert = new QPushButton("Insert", this);                      //设置图标;
  m_pInsert->setVisible(true);                                      //设置可见
  connect(m_pInsert, SIGNAL(clicked()), this, SLOT(insertData()));

  m_pDelete = new QPushButton("Delete", this);    //删
  m_pDelete->setVisible(true);
  connect(m_pDelete, SIGNAL(clicked()), this, SLOT(deleteData()));

  m_pSearch = new QPushButton("Search", this); ;  //查
  m_pSearch->setVisible(true);
  connect(m_pSearch, SIGNAL(clicked()), this, SLOT(searchData()));

  m_pClear = new QPushButton("Clear", this); ;   //清
  m_pClear->setVisible(true);
  connect(m_pClear, SIGNAL(clicked()), this, SLOT(clearTree()));

  m_pTextEdit = new QTextEdit("Please only enter number(" +
                              QString::number(numeric_limits<int>::min(), 10) + "~" +
                              QString::number(numeric_limits<int>::max(), 10) + ")!", this); //提示输入范围(int)
  m_pTextEdit->setVisible(true);

  m_pTextBrower = new QTextBrowser(this);
  m_pTextBrower->setVisible(true);

  m_pIntroduceBrower = new QTextBrowser(this);
  m_pIntroduceBrower->setVisible(true);
}

void MainWindow::flashTextBrower()
{
  m_pTextBrower->clear();   //清空m_pTextBrower内容
  m_cShowText.clear();      //清空m_cShowText内容

  m_cShowText.push_back("<h1><font color = black><font size = 5>EnterData:</font><h2><font size = 4>");
  for(auto a : m_vEnterData)
  {
    m_cShowText.push_back( QString::number(a, 10) );
    m_cShowText.push_back(" ");
  }
  m_cShowText.push_back("</font>");

  //显示红黑树深度
  m_cShowText.push_back("<h1><font color = blue><font size = 5>Depth:<font  color = black>");
  m_cShowText.push_back(QString::number(this->depthTree(),10));
  m_cShowText.push_back("</font>");

  //先序显示红黑树
   m_cShowText.push_back("<h1><font color = blue><font size = 5>PreOrder:</font><h2><font size = 4>");
  this->preOrder();

  //中序显示红黑树
  m_cShowText.push_back("<h1><font color = blue><font size = 5>InOrder:</font><h2><font size = 4>");
  this->inOrder();

  //后序显示红黑树
    m_cShowText.push_back("<h1><font color = blue><font size = 5>PostOrder:</font><h2><font size = 4>");
  this->postOrder();

  //层次显示红黑树
  m_cShowText.push_back("<h1><font color = blue><font size = 5>LevelOrder:</font><h2><font size = 4>");
  this->levelOrder();

  m_pTextBrower->setText(m_cShowText);
}

void MainWindow::flashIntroduceBrower()
{
  m_pIntroduceBrower->setText(
        QObject::tr("<h1><div align = center>"
                    "<font color = green><font size = 6>Introduction</font>"
                    "</div></h1>"
                    "<h2><font color = orange><font size = 4>红黑树性质:</font></h2>"
                    "<body><font color = black>1.每个结点或是红色的,或是黑色的。<body>"
                    "<body><font color = black>2.根是黑色的。<body>"
                    "<body><font color = black>3.每个叶结点是黑色的。<body>"
                    "<body><font color = black>4.如果一个结点是红色的,那么它的两个子结点都是是黑色的。<body>"
                    "<body><font color = black>5.对于每个结点,从该结点到其所有后代叶结点的简单路径上,均包含相同数目的黑色结点。<body>"));
}

void MainWindow::insertData()
{
  QString inText;                        //由m_pTextEdit输入,等待处理的文本
  inText = m_pTextEdit->toPlainText();   //读取m_pTextEdit内容,存在m_text中

  if(inText.contains(" ") || (0 == inText.toInt() && !inText.contains("0")) ) //如果输入含有空格或其他字符
     QMessageBox::information(NULL,"Enter Again","Only enter number!"); //警示窗口
  else
  {
    if(!this->search(inText.toInt()))   //将字符串转换为整型,且红黑树不存在该值
    {
      m_vEnterData.push_back(inText.toInt());
      this->insert(inText.toInt());
      flashTextBrower();
    }
    else
       QMessageBox::information(NULL,"Warning","There is a same key in the tree!");//警示窗口
  }
  m_pTextEdit->clear();                    //清空m_pTextEdit内容
}

void MainWindow::deleteData()
{
  QString inText;                        //由m_pTextEdit输入,等待处理的文本
  inText = m_pTextEdit->toPlainText();   //读取m_pTextEdit内容,存在m_text中

  if(inText.contains(" ") || (0 == inText.toInt() && !inText.contains("0")) ) //如果输入含有空格或其他字符
     QMessageBox::information(NULL, "Enter Again", "Only enter number!"); //警示窗口
  else
  {
    if(this->search(inText.toInt()))    //将字符串转换为整型,且红黑树存在该值
    {
      this->remove(inText.toInt());
      flashTextBrower();
    }
    else
       QMessageBox::information(NULL,"Warning","There is no this key in the tree!");//警示窗口
  }
   m_pTextEdit->clear();  //清空m_pTextEdit内容
}

void MainWindow::searchData()
{
  QString inText;                        //由m_pTextEdit输入,等待处理的文本
  inText = m_pTextEdit->toPlainText();   //读取m_pTextEdit内容,存在m_text中

  if(inText.contains(" ") || (0 == inText.toInt() && !inText.contains("0")) ) //如果输入含有空格或其他字符
     QMessageBox::information(NULL,"Enter Again","Only enter number!"); //警示窗口
  else
  {
    if(this->search(inText.toInt()))   //将字符串转换为整型,且红黑树存在该值
      QMessageBox::information(NULL, "Tips", "The key is in the tree!");//警示窗口
    else
      QMessageBox::information(NULL, "Tips", "There is no this key in the tree!");//警示窗口
  }
  m_pTextEdit->clear();                    //清空m_pTextEdit内容
}

void MainWindow::clearTree()
{
  this->destroyTree();
  flashTextBrower();
}

void MainWindow::paintEvent(QPaintEvent *)
{
  m_pEditor->setGeometry(QRect(10,10,this->width()-20,30));

  m_pInsert->setGeometry(this->width() * 1/8 - 90, 90, 80, 30);                           //设置位置
  m_pDelete->setGeometry(this->width() * 1/8 + 10, 90, 80, 30);
  m_pSearch->setGeometry(this->width() * 1/8 - 90, 120, 80, 30);
  m_pClear->setGeometry(this->width() * 1/8 + 10, 120, 80, 30);

  m_pTextEdit->setGeometry(this->width() * 1/8 -90, 40, 180, 40);
  m_pTextBrower->setGeometry(this->width() * 1/4, 40, this->width() * 3/4 - 10, this->height()- 50);
  m_pIntroduceBrower->setGeometry(10, 160, this->width() * 1/4- 20 , this->height()-170);
}


/******************************************************************
 *重载RedBlackTree中的函数
 * ***************************************************************/

void MainWindow::visitNode(RbtNode<int> *root)
//访问结点操作函数
{
  if(root->m_eColor == RED)
    m_cShowText.push_back("<font color = red>");
  else
    m_cShowText.push_back("<font color = black>");

  m_cShowText.push_back( QString::number(root->m_key, 10) );
  m_cShowText.push_back("</font>");
  m_cShowText.push_back(" ");
}

