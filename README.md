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

其中， sender 是发射信号的对象的名称， **signal()** 是信号名称。信号可以看做是特殊的函数，需要带括号，有参数时还需要指明参数。receiver 是接收信号的对象名称，**slot()**是槽函数的名称，需要带括号， 有参数时还需要指明参数。

SIGNAL 和SLOT 是Qt 的宏，用于指明信号和槽，并将它们的参数转换为相应的字符串。



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

### 信号与槽补充

- connect（） 函数的不同参数形式

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

-  使用sender（）获得信号发射者

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
