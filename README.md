MFC-Draw
==========
编译环境
----------
   VS2013，但是由于使用“多字节字符编码（MBCS）”，所以要加一个插件[坑逼微软](http://http://blog.csdn.net/shuaihj/article/details/17071351)

原理
----------
* 按照MFC向导创建的项目，包括单文档和多文档类型都将会看到App类、Doc类、View类、Frame类。DocTemplate类是隐藏的用来连接他们的一个类。基于对话框的结构简单些，其中的Dialog类，和View类、Frame类一样是由CWnd派生的。
