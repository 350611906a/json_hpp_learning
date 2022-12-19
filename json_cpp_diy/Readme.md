# 说明  

## 1、源代码路径  

- 位置：jsoncpp文件夹

- github地址：

  ​	`https://github.com/open-source-parsers/jsoncpp`



## 2、编译json的c++库文件

- 编译工程位置：

  ​	jsoncpp_build_lib

- 库文件及头文件归拢位置：

  ​	dll_header_generated

### 2.1、报错

- 报错1：

  ​	![1671429320815](C:\Users\wangwj\AppData\Roaming\Typora\typora-user-images\1671429320815.png)

  ​	解决方法：将cmake升级到3.25.1即可，原先保存版本为3.8.1.

### 2.2、生成的sln工程文件编译库文件  

- 打开sln文件；

- 选择其中的jsoncpp_lib子工程，设置为启动项；

- 设置Debug，x64模式

- 右键生成解决方案，如下：

  ```tx
  正在创建库 E:/work_dilusense/WUQI/sent_img_tools/json_dabing_new/jsoncpp_build_lib/lib/Debug/jsoncpp.lib 和对象 E:/work_dilusense/WUQI/sent_img_tools/json_dabing_new/jsoncpp_build_lib/lib/Debug/jsoncpp.exp
  2>  jsoncpp_lib.vcxproj -> E:\work_dilusense\WUQI\sent_img_tools\json_dabing_new\jsoncpp_build_lib\bin\Debug\jsoncpp.dll
  ```

  - 生成的动态库及动态库引导文件位置如下：

    E:\work_dilusense\WUQI\sent_img_tools\json_dabing_new\jsoncpp_build_lib\bin\Debug\jsoncpp.dll

    E:/work_dilusense/WUQI/sent_img_tools/json_dabing_new/jsoncpp_build_lib/lib/Debug/jsoncpp.lib

### 2.3、归拢库文件及头文件  

​	将生成的保存到统一的dll_header_generateed路径下：

​		![1671433164360](C:\Users\wangwj\AppData\Roaming\Typora\typora-user-images\1671433164360.png)

## 3、使用Demo

- 位置：

  ​	jsoncpp_demo

- 创建工程并设置参数：

  ​	创一个vs工程，设置模式为Debug，X64（与对应的库文件一致）。

- 将json相关库及头文件加载进来：

  ​	在工程上右键 --> 属性，设置如下三个参数：

  - 包含目录：

    ​	VC++目录 -> 包含目录 -> 添加头文件所在的路径，为当前路径;

  - 库目录：

    ​	VC++目录 -> 库目录 -> 添加动态库引导文件（即lib）的路径，为当前路径;

  - 附加依赖项：

    ​	链接器 -> 输入 -> 附加依赖项 -> 输入动态库引导文件的名字jsoncpp.lib，即可。

- 编译并运行：

  ​	报错如下：

  ![1671433732021](C:\Users\wangwj\AppData\Roaming\Typora\typora-user-images\1671433732021.png)

  ​	报错原因：

  ​		需要将动态库拷贝到可执行文件的统计目录下，与exe同一目录下，或者.vcxproj文件的同级目录。



## 4、json的语法格式  

​	参考链接：https://subingwen.cn/cpp/jsoncpp/ 

