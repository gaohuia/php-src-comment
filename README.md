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

## zval

#### 取得变量类型, 如: IS_NULL, IS_LONG, IS_STRING 等
	zend_uchar zval_get_type(const zval* pz)
	zend_uchar Z_TYPE(zval)
	zend_uchar Z_TYPE_P(zval*)

#### 取得变量类型, TYPE_INFO. 如IS_STRING_EX, IS_ARRAY_EX 等. 
	uint32_t Z_TYPE_INFO(zval)
	uint32_t Z_TYPE_INFO_P(zval*)

#### 取得变量的counted, zend_refcounted_h结构指针. 此值同时是str,arr等指向的内存的开始. 
	zend_refcounted_h* Z_COUNTED(zval)
	zend_refcounted_h* Z_COUNTED_P(zval*)

#### 返回引用计数, 数字. 	
	uint32_t GC_REFCOUNT(zend_refcounted_h*) 

#### zval取值
	zend_long Z_LVAL(zval) 			取long值
	zend_long Z_LVAL_P(zval*) 		取long值
	double Z_DVAL(zval) 			取double值
	double Z_DVAL(zval*) 			取double值         	
	zend_string Z_STR(zval) 		返回字符串zend_string
	zend_string Z_STR(zval*)        返回字符串zend_string
	char* Z_STRVAL(zval)    		取字符串缓冲区
	char* Z_STRVAL_P(zval*) 		取字符串缓冲区
	size_t Z_STRLEN(zval)   		取字符串变量的长度
	size_t Z_STRLEN(zval*)  		取字符串变量的长度
	zend_ulong Z_STRHASH(zval) 		计算字符串hash值
	zend_ulong Z_STRHASH_P(zval*) 	计算字符串hash值
	zend_array* Z_ARR(zval) 		取zend_array 别名: Z_ARRVAL
	zend_array* Z_ARR_P(zval*) 		取zend_array 别名: Z_ARRVAL_P
	zend_object *Z_OBJ(zval) 		取zend_object值	
	zend_object *Z_OBJCE(zval) 		取zend_object值	
	zend_object *Z_OBJ_P(zval*) 	取zend_object值
	zend_object *Z_OBJCE_P(zval*) 	取zend_object值
	zend_resource *Z_RES(zval) 
	zend_resource *Z_RES_P(zval*) 
	zend_reference *Z_REF(zval)
	zend_reference *Z_REF_P(zval)
	zend_function *Z_FUNC(zval)
	zend_function *Z_FUNC_P(zval*)
	zend_class_entry *Z_CE(zval)
	zend_class_entry *Z_CE_P(zval*)
	void *Z_PTR(zval)
	void *Z_PTR_P(zval*)

#### zval赋值
	ZVAL_UNDEF(zval*)
	ZVAL_NULL(zval*)
	ZVAL_FALSE(zval*)
	ZVAL_TRUE(zval*)
	ZVAL_BOOL(zval*, bool)
	ZVAL_LONG(zval*, long)
	ZVAL_DOUBLE(zval*, double)
	ZVAL_STR(zval*, zend_string*)

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
