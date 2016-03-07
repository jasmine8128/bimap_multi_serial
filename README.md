# bimap_multi_serial
Serial-based multi-attribute retrieval
1、bitmap.py和data.py处理原始数据属性，输出bitmap
2、index_bitmapm_f.c是对多属性数据进行属性检索，bitmap为01串
3、index_D也是对多属性数据进行属性检索，但bitmap为十进制数值，相较于前者，index_D更为简单，便于操作
4、outputs.txt 是原始01串数据位图
5、outputm.txt 是十进制数据位图
6、对index_D运行时，只需输入相应的属性，得到具有输入属性的位图和最终的位置。
7、O(∩_∩)O
