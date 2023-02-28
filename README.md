# QT5Book
《Qt 5.9 C++开发指南》

## 第一章 认识Qt

## 第二章 GU1 I 应用程序设计墓础

### 信号与槽

信号与槽（ Signal & Slot ）是Qt 编程的基础，也是Qt 的一大创新。因为有了信号与槽的编程机制，在Qt 中处理界面各个组件的交互操作时变得更加直观和简单。

**信号**（ Signal ）就是在特定情况下被发射的事件， 例如PushButton 最常见的信号就是鼠标单击时发射的**clicked()** 信号，一个ComboBox 最常见的信号是选择的列表项变化时发射的**CurrentlndexChanged()** 信号。GUI 程序设计的主要内容就是对界面上各组件的信号的响应， 只需要知道什么情况下发射哪些信号，合理地去响应和处理这些信号就可以了。

**槽**（ Slot ）就是对信号响应的函数。槽就是一个函数，与一般的C++函数是一样的，可以定义在类的任何部分（ public 、private 或protected ），可以具有任何参数，也可以被直接调用。槽函数与一般的函数不同的是： 槽函数可以与一个信号关联， 当信号被发射时， 关联的槽函数被自动执行。

信号与槽关联是用**QObject: : connect()** 函数实现的， 其基本格式是：

```c++
QObject::connect(sender,SIGNAL(signal()),receiver,SLOT(slot()));
```

connect()是QObject 类的一个静态函数，而QObject 是所有Qt 类的基类，在实际调用时可以忽略前面的限定符，所以可以直接写为：

```c++
connect(sender,SIGNAL(signal()),receiver,SLOT(slot()));
```

其中， sender 是发射信号的对象的名称， **signal()** 是信号名称。信号可以看做是特殊的函数，需要带括号，有参数时还需要指明参数。receiver 是接收信号的对象名称，**slot()**是槽函数的名称，需要带括号， 有参数时还需要指明参数。SIGNAL 和SLOT 是Qt 的宏，用于指明信号和槽，并将它们的参数转换为相应的字符串。

关于信号与槽的使用， 有以下一些规则需要**注意**

- 一个信号可以连接多个槽

- 多个信号可以连接同一个槽
-  一个信号可以连接另外一个信号
- 严格的情况下，信号与槽的参数个数和类型需要一致， 至少信号的参数不能少于槽的参数。如果不匹配，会出现编译错误或运行错误。
- 在使用信号与槽的类中，必须在类的定义中加入宏**Q_OBJECT** 。
-  当一个信号被发射时， 与其关联的槽函数通常被立即执行，就像正常调用一个函数一样。只有当信号关联的所有槽函数执行完毕后，才会执行发射信号处后面的代码。信号与槽机制是Qt GUI 编程的基础，使用信号与槽机制可以比较容易地将信号与响应代码关联起来。

### 为应用程序设置图标

用Qt C reator 创建的项目编译后的可执行文件具有默认的图标，如果需要为应用设置一个自己的图标， 其操作很简单， 只需两步。

- 将一个图标文件（ 必须是“ .ico”后缀的图标文件） 复制到项目源程序目录下。

- 在项目配置文件里用RC_ICONS 设置图标文件名，添加下面一行代码。

  ```
  RC_ICONS = Appicon.ico
  ```

  > 其中，“ Applcon.ico” 就是复制到项目源程序目录下的图标文件名称。这样设置后， 编译后生成的可执行文件，以及主窗口的图标就换成设置的图标了。生成图标网站:https://www.bitbug.net/

## 第三章 Qt 类库概述

### 元对象系统

组成部分

- QObject类是所有使用原对象系统的类的基类

- 在一个类的private部分声明了Q_OBJECT宏，使得类可以使用原对象的特征，如动态属性、信号与槽

- MOC（元对象编译器）为每个QObject的子类提供必要代码类实现原对象的特性

- QObject::metaObject()函数返回类关联的元对象

  ```c++
  QObject*obj=new QPushButton;
  obj->metaObject()->className();
  ```

- QMetaObject::newInstance()函数创建类的一个新的实例
- QObject::inherits() 函数判断一个类是都是名称className的类或者QObject的子类的实例
- QObject::tr()和QObject::trUtf8()函数可翻译字符串
- QObject::setProperty()和QObject::Property()函数用于通过属性名称动态设置和获取属性
- 对于QObject及其子类，可使用qobject_cast()进行动态投射
  
### 属性系统
```
Q_PROPERTY(type name
   READ getFunction
   [WRITE setFunction]
   [RESET resetFunction]
   [NOTIFY notifySignal]
   [DESIGNABLE bool]
   [SCRIPTABLE bool]
   [STORED bool]
   [USER bool]
   [CONSTANT]
   [FINAL])
```

- READ：用于读取属性值，如果未指定成员变量（通过MEMBER ），则需要读取访问器函数。

- WRITE：写访问器函数是可选的。用于设置属性值。它必须返回void，并且必须只接受一个参数，要么是属性的类型，要么是指向该类型的指针或引用。

- MEMBER：如果未指定读取访问器函数，则需要成员变量关联。这使得给定的成员变量可读写，而无需创建读写访问器函数。如果需要控制变量访问，除了成员变量关联（但不是两者）之外，还可以使用读或写访问器函数。

- RESET：复位功能是可选的。它用于将属性设置回其特定于上下文的默认值。

- NOTIFY：通知信号是可选的。如果已定义，它应该指定该类中的一个现有信号，该信号在属性值更改时发出。成员变量的通知信号必须采用零个或一个参数，这些参数必须与属性的类型相同。参数将采用属性的新值。仅当属性确实发生更改时才应发出NOTIFY信号，以避免绑定在QML中被不必要地重新计算。

- REVISION：修订号是可选的。如果包含，它将定义属性及其通知程序信号，以便在特定版本的API中使用（通常用于暴露于QML）。如果不包含，则默认为0。

- DESIGNABLE：表示属性是否应该在GUI设计工具（例如Qt Designer）的属性编辑器中可见。大多数属性是可设计的（默认为true）。可以指定布尔成员函数，而不是true或false。

- SCRIPTABLE：表示脚本引擎是否应该访问此属性（默认为true）。可以指定布尔成员函数，而不是true或false。

- STORED：表示属性是应该被认为是独立存在还是依赖于其他值。它还指示在存储对象状态时是否必须保存属性值。

- USER：表示是将属性指定为类的面向用户属性还是用户可编辑属性。通常，每个类只有一个用户属性（默认值为false）。

- CONSTANT：表示属性值是常量。对于给定的对象实例，常量属性的READ方法每次调用时必须返回相同的值。对于对象的不同实例，此常量值可能不同。常量属性不能有写入方法或通知信号。

- FINAL：表示派生类不会重写该属性。在某些情况下，这可以用于性能优化，但不是由moc强制执行的
### 信号与槽补充

- connect() 函数的不同参数形式

**QObject::connect()** 函数有多重参数形式， 一种参数形式的函数原型是：

```c++
QMetaObject::Connection QObject::connect(const QObject *sender,canst char* signal,const QObject *receiver,const char *method,Qt ::ConnectionType type = Qt::AutoConnection)
```

使用这种参数形式的**connect()**进行信号与槽函数的连接时， 一般句法如下：

```
QObject::connect(sender,SIGNAL(signal()),receiver,SLOT(slot()));
```

这里使用了宏**SIGNAL()** 和**SLOT()**指定信号和槽函数， 而且如果信号和槽函数带有参数， 还需注明参数类型。

另外一种参数形式的**connect()** 函数的原型是：

```c++
QMetaObject::Connection QObject::connect(const QObject * sender , canst QMetaMethod &signal, const QObject *receiver, canst QMetaMethod &method,Qt:ConnectionType type = Qt::AutoConnection)
```

对于具有默认参数的信号与槽（即信号名称是唯一的， 没有参数不同而同名的两个信号） ，可
以使用这种函数指针形式进行关联

-  使用**sender()**获得信号发射者

在槽函数里， 使用**QObject: : sender()**可以获取信号发射者的指针。如果知道信号发射者的类型，可以将指针投射为确定的类型， 然后使用这个确定类的接口函数。
```c++
QSpinBox *sp 工nBox = qobject cast<QSpinBox *>(sender()) ;
```
- 自定义信号及其使用

在自己设计的类里也可以自定义信号，信号就是在类定义里声明的一个函数，但是这个函数无需实现， 只需发射(emit) 。信号函数必须是无运回值的函数，但是可以有输入参数。信号函数无需实现， 只需在某些条件下发射信号。

``` c++
// 在下面的自定义类QPerson 的signals 部分定义一个信号ageChanged(int)
class QPerson : publiC QObject
{
    Q OBJECT
private:
	int m_age=lO ;
public:
	void incAge();
signals:
	void ageChanged( int value);
}

void QPerson ::incAge ()
{ 
    m_age++;
	emit ageChanged (m_age); // 发射信号
}
```

### 顺序容器
- QList<T>
```c++
QList<Qstring> list;
list<<"one"<<"two"<<three";
QString str1=list[0];
Qstring str0=list.at(0);
```
- QLinkList<T>
-  QVector<T>
- QStack<T>
- QQueue<T>

### 关联容器
- QSet<T>
- QMap<Key,T>
```c++
QMap<String,int> map;
map["one"]=1;
map["two"]=2;
map["three"]=3;

map.insert("four")=4;

map.remove("four")=4;
```

- QMultimap<Key,T>
- QHash<Key,T>
- QQMultiHash<Key,T>

## 第四章 常用界面设计组件

### 字符串与输入输出

字符串转换数值

```c++
int toInt(bool *ok = nullptr, int base = 10) const
long toLong(bool *ok = nullptr, int base = 10) const
float toFloat(bool *ok = nullptr) const
double toDouble(bool *ok = nullptr) const
    
QString number(int, int base=10);
QString &setNum(short, int base=10);
```

其他操作

- append()、prepend() 

```c++
QString &append(const QString &str)// append()后加字符串
QString &prepend(const QString &str) // prepend()前加字符串
```

- toUpper()、toLower() 

```c++
QString toUpper() const // toUpper()全部转换为大写
QString toLower() const // toLower()全部转换为小写
```

- count()、size()、length()

```c++
// 返回字符串中字符个数
int count(const QString &str, Qt::CaseSensitivity cs = Qt::CaseSensitive) const 
int size() const
int length() const
```

- trimmed()、simplified()

```c++
QString trimmed() const 		// trimmed()去除字符串首尾空格
QString simplified() const   	// simplified()不仅去除字符串首尾空格，中间连续空格也用一个空格代替
```

- indexOf()、lastIndexOf()

```c++
int indexOf(const QString &str, int from = 0, Qt::CaseSensitivity cs = Qt::CaseSensitive) const 	//indexOf()查找子串首次首先的位置
int lastIndexOf(const QString &str, int from = -1, Qt::CaseSensitivity cs = Qt::CaseSensitive) const // lastIndexO()f查找子串末次首先的位置
```

- isNull()、isEmpty()

```c++
// 判空 常用isEmpty()
bool isNull() const
bool isEmpty() const
```

- contains()

```c++
bool contains(const QString &str, Qt::CaseSensitivity cs = ...) const // 判断字符串内是否包含子串
```

- endsWith()、startsWith()

```c++
bool endsWith(const QString &s, Qt::CaseSensitivity cs = Qt::CaseSensitive) const // endWith()是否以某个字符串结尾
bool startsWith(const QString &s, Qt::CaseSensitivity cs = Qt::CaseSensitive) const //startsWith()是否以某个字符串开头
```

- left()、right()

```c++
QString left(int n) const // left()从字符串中左取n个字符
QString right(int n) const // right()从字符串中右取n个字符
```

- section()

```c++
QString section(QChar sep, int start, int end = ..., QString::SectionFlags flags = SectionDefault) const //从字符串中以sep为分隔符，从start到end端的字符串
```

### QSpinBox的使用

| 属性               | 描述               |
| ------------------ | ------------------ |
| prefix             | 前缀               |
| suffix             | 后缀               |
| diaplayIntegerBase | 显示整数使用的进制 |
| decimals           | 显示数值的小数位数 |

### 时间日期相关

```c++
// QDate
QDate curDate = QDate::currentDate(); //获取当前时间
// QTime
QTime curTime = QTime::currentTime(); //获取当前时间
// QDateTime
DateTime curDateTime = QDateTime::currentDateTime(); //读取当前日期时间
```

### QComboBox和QPlainTextEdit

```c++
 //添加列表项 
comboBox->addItem(icon, QString::asprintf("Item %d", i)); //带图标
comboBox->addItem(QString::asprintf("Item %d",i)); //不带图标
```

```c++
// 逐行读取plainTextEdit的内容
QTextDocument*  doc = ui->plainTextEdit->document(); //QPlainTextEdit 的内容保存在一个 QTextDocument 里
int cnt = doc->blockCount(); //QTextDocument分块保存内容，文本文件就是硬回车符是一个block,

QIcon   icon(":/images/icons/aim.ico");

ui->comboBox->clear();  //清除条目
for (int i = 0; i < cnt; i++) //扫描所有 blobk
{
	QTextBlock textLine = doc->findBlockByNumber(i); //用blobk编号获取block，就是获取一行
	QString str = textLine.text(); //转换为文本
	ui->comboBox->addItem(icon, str); //添加一个条目到comboBox
}
```

### QListWidget

```c++
//添加
QListWidgetItem* aItem=new QListWidgetItem;
aItem->setText(str); //设置文字标签
aItem->setIcon(aIcon);//设置图标
aItem->setCheckState(Qt::Checked); //设置为选中状态
listWidget->addItem(aItem); //增加一个项

//清空
listWidget->clear();

//删除
int row = listWidget->currentRow(); //当前行
QListWidgetItem* aItem =listWidget->takeItem(row); //移除指定行的项，但不delete
delete aItem; //需要手工删除对象

//插入
listWidget->insertItem(listWidget->currentRow(), aItem); //在当前行的上方插入一个项

//改变状态
aItem->setCheckState();
Qt::Checked	//设置为选中
Qt::Unchecked	//不选
```

### QToolButton

```c++
// QToolButton按钮设置Action
ui->tBtnListIni->setDefaultAction(ui->actListIni);

// 创建下拉菜单
QMenu* menuSelection = new QMenu(this); //创建选择弹出式菜单
menuSelection->addAction(ui->actSelALL);
menuSelection->addAction(ui->actSelNone);
menuSelection->addAction(ui->actSelInvs);
ui->tBtnSelectItem->setPopupMode(QToolButton::MenuButtonPopup);//菜单弹出模式，执行按钮的Action
ui->tBtnSelectItem->setToolButtonStyle(Qt::ToolButtonTextBesideIcon); //按钮样式
ui->tBtnSelectItem->setDefaultAction(ui->actSelPopMenu);//关联Action
ui->tBtnSelectItem->setMenu(menuSelection); //设置下拉菜单

//鼠标光标位置显示右键快捷菜单
QMenu* menuList = new QMenu(this); //创建菜单
menuList->addAction(ui->actSelNone);
menuList->addAction(ui->actSelInvs);
menuList->exec(QCursor::pos()); //在鼠标光标位置显示右键快捷菜单
```

### QTreeWidget和QDockWidget

#### QTreeWidget

```c++
QTreeWidget* treeFiles; // 窗体 
enum    treeColNum {colItem = 0, colItemType = 1}; //目录树列的编号定义

QTreeWidgetItem*  item = new QTreeWidgetItem(MainWindow::itTopItem); //新建节点时设定类型为 itTopItem 1001 也是数字 没有实际意义

item->setIcon(MainWindow::colItem, icon); //设置第1列的图标
item->setText(MainWindow::colItem, "图片文件"); //设置第1列的文字
item->setText(MainWindow::colItemType, "type=itTopItem"); //设置第2列的文字

item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
item->setCheckState(colItem, Qt::Checked); //设置为选中

item->setData(MainWindow::colItem, Qt::UserRole, QVariant(dataStr)); //设置节点第1列的Qt::UserRole的Data

ui->treeFiles->addTopLevelItem(item);//添加顶层节点
```

#### QDockWidget

```c++
dockWidget->setVisible(arg1) // 停靠区的可见性
```

### QPixmap

```c++
curPixmap.load(filename); //从文件载入图片
```

