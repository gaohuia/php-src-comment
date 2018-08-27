PHP源码阅读笔记. 
--------------------
阅读过程中的一些笔记，便于将来写扩展时使用. 
基于php源码7.2.9

## 重要文件

* Zend/zend_types.h 		定义了所有的变量及值相关的数据结构, 定义了变量快捷取值的宏
* Zend/zend_string.h 		定义了zend_string相关操作. 
* Zend/zend_API.h 		定义了扩展相关的宏和函数.
* Zend/zend_alloc.h 		定义了内存分配相关的方法.
* Zend/zend_hash.h 		定义了hash表相关的方法和宏. 

## 数据类型及常用操作

### Long类型

	暂无


### 字符串类型

#### 创建一个zend_string结构. 并设置引用数为1
	zend_string *zend_string_alloc(size_t len, int persistent)

#### 创建一个zend_string结构, 并为期赋值. 设置引用数为1. str指向的缓冲区将会被copy到zend_str结构内. 
	zend_string *zend_string_init(const char *str, size_t len, int persistent)	

#### 此方法只是简单增加了引用计数, 并返回传入的zend_string
	zend_string *zend_string_copy(zend_string *s)

#### 释放zend_string, 只是减少一次引用, 如果引用减为0自动释放
	void zend_string_release(zend_string *s)

#### 增加引用
	uint32_t zend_string_addref(zend_string *s)
	
#### 减少引用
	uint32_t zend_string_delref(zend_string *s)
