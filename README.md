# auto_test

auto_test是一个自动测试化工具，能够直接一键测试C程序，输出测试结果。

## 命令格式
+ `--help`       获取帮助
+ `[program]`    运行测试程序
+ `-s [n]`       创建n个in、out测试文件
## 使用方法：
1. 将测试工具引入到工程目录中
2. 在工程目录下创建一个sample子目录，其下存放测试输入用例，文件名格式为：`xxx_in.txt`；其下存放测试输出用例，文件名格式为：`xxx_out.txt`
3. 运行测试程序：`autotest [你的main程序]`
4. 用例输出结果保存在sample_testout（该目录可以由系统生成）中，文件名格式为：`xxx_testout.txt`
5. 用例比较文件`sample_test_diff.txt`输出在工程目录下，其格式为：
+ 1. 所有测试文件名：`Sample File`
+ 2. 测试文件数：`Sample File Num`
+ 3. 总测试时间：`Test Time`
+ 4. 如果输出与用例输出不同，那么显示相同与不同的信息

## For Example:
+ `git clone`
+ `cp autotest.c C:/Program`
+ `cd C:/Program`
+ `gcc autotest.c -o autotest`
+ `./autotest -s 5`
+ `./autotest program`
+ `cat sample_test_diff.txt`

Diff File Format:
```
Sample File: a_in.txt b_in.txt
Sample File Num: 2
Test Time: 1534 ms

Failed a_in.txt:
xxxsametxtxxx
xxxxxxxxxx
<<<==== testout =======
xxxxxxxxxxxxx
xxxxxxxx
+++++++++ out +++++++++
xxxxxxxxxxx
xxxxxxxxxxx
====================>>>

Failed b_in.txt:
xxxsametxtxxx
xxxxxxxxxx
<<<==== testout =======
xxxxxxxxxxxxx
xxxxxxxx
+++++++++ out +++++++++
xxxxxxxxxxx
xxxxxxxxxxx
====================>>>

...
```