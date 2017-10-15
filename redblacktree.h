#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <queue>
using namespace std;

//红黑树颜色类型
enum Color{RED, BLACK};

/*************************************************
 * 红黑树结点类
 ************************************************/
template <class RbtElement>
class RbtNode
{
public:
  RbtElement m_key;
  Color m_eColor;
  RbtNode *m_pLeft;
  RbtNode *m_pRight;
  RbtNode *m_pParent;

public:
  RbtNode(RbtElement key, Color color, RbtNode *left,RbtNode *right, RbtNode *parent)
  {
    this->m_key = key;
    this->m_eColor = color;
    this->m_pLeft = left;
    this->m_pRight = right;
    this->m_pParent = parent;
  }
  RbtNode(Color color, RbtNode *left,RbtNode *right, RbtNode *parent)
  {
    this->m_eColor = color;
    this->m_pLeft = left;
    this->m_pRight = right;
    this->m_pParent = parent;
  }
};

/*************************************************
 * 红黑树类
 ************************************************/
template <class RbtElement>
class RedBlackTree
{
private:
  RbtNode<RbtElement> *m_pRoot; //根结点
  RbtNode<RbtElement> *m_pNil;  //哨兵结点

public:
  RedBlackTree();
  ~RedBlackTree();

public:
  //红黑树的外部接口

  bool setEmpty();
  //构建一个空的红黑树
  bool destroyTree();
  //销毁红黑树
  bool empty();
  //红黑树判空。若为空返回TRUE,否则返回FALSE
  int depthTree();
  // 求红黑树的深度

  void preOrder();
  // 先序遍历红黑树
  void inOrder();
  // 中序遍历红黑树
  void postOrder();
  // 后序遍历红黑树
  void levelOrder();
  // 层次遍历红黑树


  virtual void visitNode(RbtNode<RbtElement> *root) = 0;
  //访问结点操作函数,设置为纯虚函数

  bool search(RbtElement value);
  //查找键值为value的结点,存在返回true,不存在则返回false
  RbtElement minimum();
  //查找最小键值,并返回该键值(红黑树的最左孩子)
  RbtElement maxmum();
  //查找最大键值,并返回该键值(红黑树的最右孩子)
  bool insert(RbtElement value);
  //将键值为value的结点添加进红黑树,若树中已存在与z键值相同的结点,则不再插入,并返回false;插入成功则返回true
  bool remove(RbtElement value);
  //将键值为value的结点从红黑树中移除

private:
  /*设置以下重载函数方便实现递归以及红黑树内部信息的隐藏
   *如果一个成员函数的不会修改数据成员,那么最好将其声明为const，
   *因为const成员函数中不允许对数据成员进行修改,如果修改,编译器将报错,这大大提高了程序的健壮性
  */

  void destroyTree(RbtNode<RbtElement> *&root);
  // 销毁红黑树
  int depthTree(RbtNode<RbtElement> *root);
  // 求红黑树的深度

  void preOrder(RbtNode<RbtElement>* root) ;
  // 前序遍历红黑树
  void inOrder(RbtNode<RbtElement>* root);
  // 中序遍历红黑树
  void postOrder(RbtNode<RbtElement>* root);
  // 后序遍历红黑树
  void levelOrder(RbtNode<RbtElement>* root);
  // 层次遍历红黑树

  RbtNode<RbtElement>* search(RbtNode<RbtElement> *root, RbtElement value) const;
  // 查找红黑树中键值为value的结点
  RbtNode<RbtElement>* minimum(RbtNode<RbtElement> *root);
  // 查找最小结点,返回红黑树的最小结点的指针
  RbtNode<RbtElement>* maxmum(RbtNode<RbtElement> *root);
  // 查找最大结点,返回红黑树的最大结点的指针


  void leftRotate(RbtNode<RbtElement> *&root, RbtNode<RbtElement>* x);
  //对红黑树T中的失衡子树x进行左旋调整
  void rightRotate(RbtNode<RbtElement> *&root, RbtNode<RbtElement>* y);
  //对红黑树T中的失衡子树y进行右旋调整
  void insertFixUp(RbtNode<RbtElement> *&root, RbtNode<RbtElement>* z);
  //插入结点时重新着色旋转调整
  void removeFixUp(RbtNode<RbtElement> *&root, RbtNode<RbtElement>* x);
  //移除结点时重新着色旋转调整

  bool insert(RbtNode<RbtElement> *&root, RbtNode<RbtElement>* z);
  //将结点z添加进红黑树T,若树中已存在与z键值相同的结点,则不再插入,并返回false;插入成功则返回true
  void remove(RbtNode<RbtElement> *&root, RbtNode<RbtElement>* z);
  //将结点z从红黑树T中移除,(前提z结点在红黑树中,在与否的判断在public重载函数中)
  //delete为关键字,不可用
  void transPlant(RbtNode<RbtElement> *&root, RbtNode<RbtElement>* u, RbtNode<RbtElement>* v);
  //移除结点辅助函数

};



template <class RbtElement>
RedBlackTree<RbtElement>::RedBlackTree()
{
  m_pNil =  new RbtNode<RbtElement>(BLACK, NULL, NULL, NULL);
  this->m_pRoot = m_pNil;
}

template <class RbtElement>
RedBlackTree<RbtElement>::~RedBlackTree()
{
  this->destroyTree();
  delete m_pNil;
}


/************************************************
 * 红黑树类外部接口
 * *********************************************/
template <class RbtElement>
bool RedBlackTree<RbtElement>::setEmpty()
//构建一个空的红黑树
{
  return this->RedBlackTree();
}

template <class RbtElement>
bool RedBlackTree<RbtElement>::destroyTree()
//销毁红黑树,销毁成功，返回true
{
  destroyTree(m_pRoot);
  if(m_pRoot) //如果根结点非空,则没有销毁成功
    return false;
  else
    return true;
}

template <class RbtElement>
bool RedBlackTree<RbtElement>::empty()
//红黑树判空。若为空返回TRUE,否则返回FALSE
{
  if(m_pRoot)
    return false;
  else
    return true;
}

template <class RbtElement>
int RedBlackTree<RbtElement>::depthTree()
//求红黑树深度
{
  return depthTree(m_pRoot);
}

template <class RbtElement>
void RedBlackTree<RbtElement>::preOrder()
// 先序遍历红黑树
{
  preOrder(m_pRoot);
}

template <class RbtElement>
void RedBlackTree<RbtElement>::inOrder()
// 中序遍历红黑树
{
  inOrder(m_pRoot);
}

template <class RbtElement>
void RedBlackTree<RbtElement>::postOrder()
// 后序遍历红黑树
{
  postOrder(m_pRoot);
}

template <class RbtElement>
void RedBlackTree<RbtElement>::levelOrder()
// 层次遍历红黑树
{
  levelOrder(m_pRoot);
}


template <class RbtElement>
bool RedBlackTree<RbtElement>::search(RbtElement value)
//查找键值为value的结点,存在返回true,不存在则返回false
{
  if(search(m_pRoot, value) != m_pNil)
    return true;
  else
    return false;
}

template <class RbtElement>
RbtElement RedBlackTree<RbtElement>::minimum()
//查找最小键值,并返回该键值
{
  if(minimum(m_pRoot) != m_pNil)//若最小结点为哨兵结点,则树为空
    return minimum(m_pRoot)->m_key;
}

template <class RbtElement>
RbtElement RedBlackTree<RbtElement>::maxmum()
//查找最大键值,并返回该键值
{
  if(maxmum(m_pRoot) != m_pNil)//若最大结点为哨兵结点,则树为空
    return maxmum(m_pRoot)->m_key;
}

template <class RbtElement>
bool RedBlackTree<RbtElement>::insert(RbtElement value)
//将结点z添加进红黑树T,若树中已存在与z键值相同的结点,则不再插入,并返回false;插入成功则返回true
{
  RbtNode<RbtElement> *z = NULL;
  if (!(z = new RbtNode<RbtElement>(value, RED, NULL, NULL, NULL)))
    return false;    //创建结点失败返回false
  return insert(m_pRoot, z);
}

template <class RbtElement>
bool RedBlackTree<RbtElement>::remove(RbtElement value)
//将键值为value的结点从红黑树中移除
{
  RbtNode<RbtElement> *z = NULL;
  if((z = search(m_pRoot, value)) != m_pNil)
  // 查找键值value对应的节点z,找到的话就删除该节点
  {
    remove(m_pRoot, z);
    return true;
  }
  else
    return false;
}

/************************************************
 * 红黑树类内部接口
 * *********************************************/

template <class RbtElement>
void RedBlackTree<RbtElement>::destroyTree(RbtNode<RbtElement> *&root)
//销毁红黑树,销毁成功，返回true
//递归删除
//root形参用指针的引用,root的值可以改变，而非只有root指向的值可以改变
{
  if(root != m_pNil)
  {
    //递归删除左右子树,再删除根节点
    destroyTree(root->m_pLeft);
    destroyTree(root->m_pRight);
    delete root;
    root = m_pNil;
  }
}

template <class RbtElement>
int RedBlackTree<RbtElement>:: depthTree(RbtNode<RbtElement> *root)
// 求红黑树的深度
{
   int depthLeft, depthRight;
   if(root == m_pNil)
     return 0;  //空红黑树深度为0
   else
   {
     // 分别求左右子树深度,将深度大的加一则为当前树的深度
     depthLeft = depthTree(root->m_pLeft);
     depthRight = depthTree(root->m_pRight);
     return 1 + (depthLeft > depthRight ? depthLeft : depthRight);
   }
}

template <class RbtElement>
void RedBlackTree<RbtElement>::preOrder(RbtNode<RbtElement> *root)
// 前序遍历红黑树
{
  if(root != m_pNil)
  {
    this->visitNode(root);
    preOrder(root->m_pLeft);
    preOrder(root->m_pRight);
  }
}

template <class RbtElement>
void RedBlackTree<RbtElement>::inOrder(RbtNode<RbtElement>* root)
// 中序遍历红黑树
{
  if(root != m_pNil)
  {
    inOrder(root->m_pLeft);
    this->visitNode(root);
    inOrder(root->m_pRight);
  }
}

template <class RbtElement>
void RedBlackTree<RbtElement>::postOrder(RbtNode<RbtElement>* root)
// 后序遍历红黑树
{
  if(root != m_pNil)
  {
    postOrder(root->m_pLeft);
    postOrder(root->m_pRight);
    this->visitNode(root);
  }
}

template <class RbtElement>
void RedBlackTree<RbtElement>::levelOrder(RbtNode<RbtElement>* root)
// 层次遍历红黑树
{
  if(root != m_pNil)
  {
    queue< RbtNode<RbtElement>* > Q;
    RbtNode<RbtElement>* p = root;
    this->visitNode(root);  //对根结点访问操作
    Q.push(root);           //根结点入队
    while(!Q.empty())       //Q非空时重复执行操作
    {
      p = Q.front();  Q.pop(); //将队头结点赋给p,并将Q进行出队操作
      if(p->m_pLeft != m_pNil)   //访问左孩子,并将之入队
      {
        this->visitNode(p->m_pLeft);
        Q.push(p->m_pLeft);
      }
      if(p->m_pRight != m_pNil)  //访问右孩子,并将之入队
      {
        this->visitNode(p->m_pRight);
        Q.push(p->m_pRight);
      }
    }
  }
}

template <class RbtElement>
RbtNode<RbtElement>* RedBlackTree<RbtElement>::search(RbtNode<RbtElement> *root, RbtElement value) const
// 查找红黑树中键值为value的结点,不存在此值返回m_pNil
{
  if(root != m_pNil)
  {
    if(root->m_key == value)
      return root;
    else if(value < root->m_key) //当value比根结点键值小时,在左子树查找
      return search(root->m_pLeft, value);
    else                         //当value比根结点键值大时,在左子树查找
      return search(root->m_pRight, value);
  }
  else  //找不到,则返回m_pNil
    return m_pNil;
}

template <class RbtElement>
RbtNode<RbtElement>* RedBlackTree<RbtElement>::minimum(RbtNode<RbtElement>* root)
// 查找最小结点,返回红黑树的最小结点的指针
{

  while(root->m_pLeft != m_pNil)  //迭代左孩子, 直到为m_pNil
    root = root->m_pLeft;
  return root;                    //返回最左孩子
}

template <class RbtElement>
RbtNode<RbtElement>* RedBlackTree<RbtElement>::maxmum(RbtNode<RbtElement> *root)
// 查找最大结点,返回红黑树的最大结点的指针
{

  while(root->m_pRight != m_pNil)  //迭代右孩子, 直到为m_pNil
    root = root->m_pRight;
  return root;                     //返回最右孩子
}

template <class RbtElement>
void RedBlackTree<RbtElement>::leftRotate(RbtNode<RbtElement>* &root, RbtNode<RbtElement>* x)
{
  //算法参考《算法导论-第三版》Page177
  //root形参用指针的引用,root的值可以改变，而非只有root指向的值可以改变

  RbtNode<RbtElement>* y = x->m_pRight;  //设置y为x的右子树
  x->m_pRight = y->m_pLeft;              //将y的左子树移为x的右子树
  if(y->m_pLeft != m_pNil)               //若y的左子树为m_pNil时,则无须设置其双亲结点,否则设置为x
    y->m_pLeft->m_pParent = x;
  y->m_pParent = x->m_pParent;           //将x的双亲结点链接给y

  //依据x的双亲结点以及x为其双亲结点的左或右孩子设置y
  if(x->m_pParent == m_pNil)             //x的双亲为空,即x为根结点,故将y设为根结点
    root = y;
  else if(x == x->m_pParent->m_pLeft)    //x为其双亲结点的左孩子时
    x->m_pParent->m_pLeft = y;
  else if(x == x->m_pParent->m_pRight)   //x为其双亲结点的右孩子时
    x->m_pParent->m_pRight = y;

  //关联x,y
  y->m_pLeft = x;
  x->m_pParent = y;
}

template <class RbtElement>
void RedBlackTree<RbtElement>::rightRotate(RbtNode<RbtElement>* &root, RbtNode<RbtElement>* y)
{
  //操作与左旋对称

  RbtNode<RbtElement>*  x = y->m_pLeft;
  y->m_pLeft = x->m_pRight;
  if(x->m_pRight != m_pNil)
    x->m_pRight->m_pParent = y;
  x->m_pParent = y->m_pParent;

  //依据y的双亲结点属性以及y为其双亲结点的左或右孩子设置x
  if(y->m_pParent == m_pNil)
    root = x;
  else if(y == y->m_pParent->m_pLeft)
    y->m_pParent->m_pLeft = x;
  else if(y == y->m_pParent->m_pRight)
    y->m_pParent->m_pRight = x ;

  x->m_pRight = y;
  y->m_pParent = x;
}

template <class RbtElement>
void RedBlackTree<RbtElement>::insertFixUp(RbtNode<RbtElement>* &root, RbtNode<RbtElement>* z)
{
  //算法参考《算法导论-第三版》Page178~182
  while(z->m_pParent->m_eColor == RED)
  //若插入结点的双亲结点颜色为黑色,则红黑树性质得以保持,无须调整
  //调整到z的双亲结点颜色为黑色时,则红黑树性质得以保持,无须继续调整
  //该函数的旋转操作不超过2次,只要执行了case3, while循环即结束
  {
    if(z->m_pParent == z->m_pParent->m_pParent->m_pLeft)
    //case z的双亲结点为左孩子
    {
      RbtNode<RbtElement>* y = z->m_pParent->m_pParent->m_pRight;

      if(y->m_eColor == RED)   //叔结点颜色为红色
      //case 1
      {
        z->m_pParent->m_eColor = BLACK;
        y->m_eColor = BLACK;
        z->m_pParent->m_pParent->m_eColor = RED;
        z = z->m_pParent->m_pParent;
      }
      else //叔结点颜色为黑色(空也为黑色)
      {
        if(z == z->m_pParent->m_pRight)
        //case 2
        {
          z = z->m_pParent;
          leftRotate(root, z);
        }

        //case 3  此情况可由case 2变换可得
        z->m_pParent->m_eColor = BLACK;
        z->m_pParent->m_pParent->m_eColor = RED;
        rightRotate(root, z->m_pParent->m_pParent);
     }
    }

    else if(z->m_pParent == z->m_pParent->m_pParent->m_pRight)
    //case z的双亲结点为右孩子,与case z的双亲结点为左孩子 操作对称
    {
      RbtNode<RbtElement>* y = z->m_pParent->m_pParent->m_pLeft;

      if(y->m_eColor == RED) //叔结点颜色为红色
      //case 1
      {
        z->m_pParent->m_eColor = BLACK;
        y->m_eColor = BLACK;
        z->m_pParent->m_pParent->m_eColor = RED;
        z = z->m_pParent->m_pParent;
      }
      else  //叔结点颜色为黑色(空也为黑色)
      {
        if(z == z->m_pParent->m_pLeft)
        //case 2
        {
          z = z->m_pParent;
          rightRotate(root, z);
        }

        //case 3 此情况可由case 2变换可得
        z->m_pParent->m_eColor = BLACK;
        z->m_pParent->m_pParent->m_eColor = RED;
        leftRotate(root, z->m_pParent->m_pParent);
      }
    }
  }
  root->m_eColor = BLACK;
}

template <class RbtElement>
bool RedBlackTree<RbtElement>::insert(RbtNode<RbtElement>* &root, RbtNode<RbtElement>* z)
//将结点z添加进红黑树T,若树中已存在与z键值相同的结点,则不再插入,并返回false;插入成功则返回true
//root形参用指针的引用,root的值可以改变，而非只有root指向的值可以改变
//算法参考《算法导论-第三版》Page178
{
  RbtNode<RbtElement>* y = m_pNil;
  RbtNode<RbtElement>* x = root;
  while(x != m_pNil)
  //当x非空, 迭代, 找到插入点
  {
    y = x;
    if(z->m_key < x->m_key)
      x = x->m_pLeft;
    else if(z->m_key > x->m_key)
      x = x->m_pRight;
    else if(z->m_key == x->m_key) //红黑树中有与z结点键值相等的结点,则不再插入
      return false;
  }
  z->m_pParent = y;
  if(y == m_pNil)  //z的双亲结点为空时, 树的根结点为z
    root = z;
  else
  // 依据z与其双亲结点的大小比较设置为左或右孩子
  {
    if(z->m_key < y->m_key)
      y->m_pLeft = z;
    else
      y->m_pRight = z;
  }
  //设置z的属性, 保持红黑树性质
  z->m_pLeft = m_pNil;
  z->m_pRight = m_pNil;
  z->m_eColor = RED;
  insertFixUp(root, z); //调用插入调整函数, 保持红黑树性质
  return true;
}

template <class RbtElement>
void RedBlackTree<RbtElement>::removeFixUp(RbtNode<RbtElement> *&root, RbtNode<RbtElement>* x)
//移除结点时重新着色旋转调整
//算法参考《算法导论-第三版》Page185~187
{
  while(x != root && x->m_eColor == BLACK) //x有可能为m_pNil(颜色亦为BLACK)
  {
    if(x == x->m_pParent->m_pLeft)
    //case  x为左孩子
    {
      RbtNode<RbtElement>* w = x->m_pParent->m_pRight;
      if(w->m_eColor == RED)
      //case1 x的兄弟结点w颜色为红色
      {
        w->m_eColor = BLACK;
        x->m_pParent->m_eColor = RED;
        leftRotate(root, x->m_pParent);
        w = x->m_pParent->m_pRight;
      }

      if(w->m_pLeft->m_eColor == BLACK && w->m_pRight->m_eColor == BLACK)
      //case2 x的兄弟结点w颜色为黑色,且二个侄子结点颜色也为黑色
      {
        w->m_eColor = RED;
        x = x->m_pParent;
      }

      else
      {
        if(w->m_pRight->m_eColor == BLACK)
        //case3 x的兄弟结点w颜色为黑色,且w的左孩子结点颜色为红色,w的右孩子颜色为黑色
        {
          w->m_pLeft->m_eColor = BLACK;
          w->m_eColor = RED;
          rightRotate(root, w);
          w = x->m_pParent->m_pRight;
        }
        //case4 x的兄弟结点w颜色为黑色,且w的右孩子颜色为红色
        w->m_eColor = x->m_pParent->m_eColor;
        x->m_pParent->m_eColor = BLACK;
        w->m_pRight->m_eColor = BLACK;
        leftRotate(root, x->m_pParent);
        x = root;
      }
    }

    else if(x == x->m_pParent->m_pRight)
    //case  x为右孩子,操作与case x为左孩子 对称
    {
      RbtNode<RbtElement>* w = x->m_pParent->m_pLeft;
      if(w->m_eColor == RED)
      {
        w->m_eColor = BLACK;
        x->m_pParent->m_eColor = RED;
        rightRotate(root, x->m_pParent);
        w = x->m_pParent->m_pLeft;
      }
      if(w->m_pLeft->m_eColor == BLACK && w->m_pRight->m_eColor == BLACK)
      {
        w->m_eColor = RED;
        x = x->m_pParent;
      }
      else
      {
        if(w->m_pLeft->m_eColor == BLACK)
        {
          w->m_pRight->m_eColor = BLACK;
          w->m_eColor = RED;
          leftRotate(root, w);
          w = x->m_pParent->m_pLeft;
        }

        w->m_eColor = x->m_pParent->m_eColor;
        x->m_pParent->m_eColor = BLACK;
        w->m_pLeft->m_eColor = BLACK;
        rightRotate(root, x->m_pParent);
        x = root;
      }
    }
  }
  x->m_eColor = BLACK;
}

template <class RbtElement>
void RedBlackTree<RbtElement>::transPlant(RbtNode<RbtElement> *&root, RbtNode<RbtElement>* u, RbtNode<RbtElement>* v)
//移除结点辅助函数, 用v代替u
{
  if(u->m_pParent == m_pNil)
    root = v;
  else if(u == u->m_pParent->m_pLeft)
    u->m_pParent->m_pLeft = v;
  else if(u == u->m_pParent->m_pRight)
    u->m_pParent->m_pRight = v;
  v->m_pParent = u->m_pParent;
}

template <class RbtElement>
void RedBlackTree<RbtElement>::remove(RbtNode<RbtElement> *&root, RbtNode<RbtElement>* z)
//将结点z从红黑树T中移除(前提z结点在红黑树中,在与否的判断在public重载函数中)
//算法参考《算法导论-第三版》Page183~184
{
  RbtNode<RbtElement>* x = m_pNil;
  RbtNode<RbtElement>* y = z;
  Color yOriginalColor = y->m_eColor;  //存储y发生改变前的颜色

  if(z->m_pLeft == m_pNil)
  //左结点为空,右结点可空可有,用z的右子树代替z
  {
    x = z->m_pRight;
    transPlant(root, z, z->m_pRight);
  }

  else if(z->m_pRight == m_pNil)
  //左结点右结点为空,用z的左子树代替z
  {
    x = z->m_pLeft;
    transPlant(root, z, z->m_pLeft);
  }

  else
  //左右结点非空
  {
    y = minimum(z->m_pRight);     //y指向z的后继
    yOriginalColor = y->m_eColor; //存储y发生改变前的颜色

    x = y->m_pRight;

    if(y->m_pParent == z)    //这步至今没有弄懂
      x->m_pParent = y;

    else
    {
      transPlant(root, y, y->m_pRight);
      y->m_pRight = z->m_pRight;
      y->m_pRight->m_pParent = y;
    }

    transPlant(root, z, y); //将z的后继移至z的位置上
    y->m_pLeft = z->m_pLeft;
    y->m_pLeft->m_pParent = y;
    y->m_eColor = z->m_eColor;
  }

  if(yOriginalColor == BLACK)
    removeFixUp(root, x);
  delete z;//将z结点交换出来后,释放该结点内存
}
#endif // REDBLACKTREE_H

