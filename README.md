# auto_test

## 工具介绍：auto_test是一个自动测试化工具，能够直接一键测试C程序，输出测试结果。
## 命令
+ `autotest --help`获取帮助
+ `autotest [program]`运行测试程序
+ `autotest -s [n]`创建n个in、out测试文件
## 使用方法：
+ 1. 将测试工具引入到工程目录中
+ 2. 在工程目录下创建一个sample子目录，其下存放测试输入用例，文件名格式为：`xxx_in.txt`；其下存放测试输出用例，文件名格式为：`xxx_out.txt`
+ 4. 运行测试程序：`./autotest <你的main程序>`
+ 5. 用例输出结果保存在sample_testout（该目录可以由系统生成）中，文件名格式为：`xxx_testout.txt`
+ 6. 用例比较文件`sample_test_diff.txt`输出在工程目录下，其格式为：
+ + 1. 列举所有测试文件名：`Sample File: a_in.txt b_in.txt ...`
+ + 2. 输出测试文件数：`Sample File Num: 5`
+ + 3. 输出总测试时间：`Test Time: 1534 ms`
+ + 3. 如果输出与用例输出不同，那么显示相同不同的信息：
```
Failed a_in.txt:
xxxsametxtxxx
xxxxxxxxxx
<<<=====out======
xxxxxxxxxxxxx
xxxxxxxx
+++++++++++++++++
xxxxxxxxxxx
xxxxxxxxxxx
====testout===>>>

Failed b_in.txt:
xxxsametxtxxx
xxxxxxxxxx
<<<=====out======
xxxxxxxxxxxxx
xxxxxxxx
+++++testout+++++
xxxxxxxxxxx
xxxxxxxxxxx
==============>>>

...
```