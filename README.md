MFC-Draw
==========
编译环境
----------
   VS2013，但是由于使用“多字节字符编码（MBCS）”，所以要加一个插件[坑逼微软](http://blog.csdn.net/shuaihj/article/details/17071351)

原理
----------
* 按照MFC向导创建的项目，包括单文档和多文档类型都将会看到App类、Doc类、View类、Frame类。DocTemplate类是隐藏的用来连接他们的一个。基于对话框的结构简单些，其中的Dialog类，和View类、Frame类一样是由CWnd派生的。
* 怎么与Windows通信呢？说白了就是，按鼠标、点击菜单栏、按钮等产生的消息，Windows怎么处理？响应函数写在什么地方？在WindowsAPI中有WindowProc()函数，MFC封装了看不到了之后呢？实际上上面你能看到的类都能处理windows消息，类中DECLARE_MESSAGE_MAP()宏表明这个类里面有作为消息处理程序的函数成员。
 * 把消息处理程序放置在什么地方取决于消息的类别。一、标准的Windows消息，以WM_开头（不包括WM_COMMAND），包括重画WM_PAINT,释放鼠标左键WM_LBUTTONUP等，它们总是由最终派生于CWnD的类的对象处理，意思就是不能放在App类，Doc类中；二、对话框里的控件发出的消息，包括点击了按钮，这样的消息顺其自然可以由Dialog类对象处理；三、命令消息，即WM_COMMAND消息，包括点击了菜单栏和工具栏，处理这样的消息比较灵活，可能放在上面可以看到的任一类对象中，比如在此程序就放在了CDoc类中。
 
基础算法
-----------
* 如果想在窗口上绘制直线的话，我们需要捕捉两个点：线段的起点和终点。二者可以分别通过WM_LBUTTONDOWN和WM_LBUTTONUP来实现。类似于上节课讲述的添加消息函数的方法，在类视图的CDrawView右键属性，选择“消息”菜单，找到对应的消息即可。进入二者的消息函数的实现之前，需要定义一个变量表示线段的起点CPoint m_ptOrigin，同样是右键View类添加变量即可。
* 如何绘制连续线呢？其实这里的关键在于实现的想法，如果我们把曲线看作许多小线段的组合，那么每次更新起点连续绘制小线段不就可以了么？但是这里需要注意的是我们需要一个Bool m_bDraw来判断鼠标是否点下是否应当一直绘制。我们需要使用WM_MOUSEMOVE来捕捉鼠标的不断移动。
* 基础算法的代码实现在[我的仓库](http://github.com/Tast0)中给出。

运行效果
----------
![](https://github.com/Tast0/MFC-Draw/blob/master/Draw/renderings.png)  
