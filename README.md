MFC-Draw
==========
编译环境
----------
   VS2013，但是由于使用“多字节字符编码（MBCS）”，所以要加一个插件[坑逼微软](http://http://blog.csdn.net/shuaihj/article/details/17071351)

原理
----------
* 按照MFC向导创建的项目，包括单文档和多文档类型都将会看到App类、Doc类、View类、Frame类。DocTemplate类是隐藏的用来连接他们的一个。基于对话框的结构简单些，其中的Dialog类，和View类、Frame类一样是由CWnd派生的。
* 怎么与Windows通信呢？说白了就是，按鼠标、点击菜单栏、按钮等产生的消息，Windows怎么处理？响应函数写在什么地方？在WindowsAPI中有WindowProc()函数，MFC封装了看不到了之后呢？实际上上面你能看到的类都能处理windows消息，类中DECLARE_MESSAGE_MAP()宏表明这个类里面有作为消息处理程序的函数成员。
* 把消息处理程序放置在什么地方取决于消息的类别。一、标准的Windows消息，以WM_开头（不包括WM_COMMAND），包括重画WM_PAINT,释放鼠标左键WM_LBUTTONUP等，它们总是由最终派生于CWnD的类的对象处理，意思就是不能放在App类，Doc类中；二、对话框里的控件发出的消息，包括点击了按钮，这样的消息顺其自然可以由Dialog类对象处理；三、命令消息，即WM_COMMAND消息，包括点击了菜单栏和工具栏，处理这样的消息比较灵活，可能放在上面可以看到的任一类对象中，比如在此程序就放在了CDoc类中。
