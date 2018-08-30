PHP源码阅读笔记.
--------------------
阅读过程中的一些笔记，便于将来写扩展时使用.
基于php源码7.2.9

## 重要文件

* Zend/zend_types.h         定义了所有的变量及值相关的数据结构, 定义了变量快捷取值的宏
* Zend/zend_string.h         定义了zend_string相关操作.
* Zend/zend_API.h         定义了扩展相关的宏和函数.
* Zend/zend_alloc.h         定义了内存分配相关的方法.
* Zend/zend_hash.h         定义了hash表相关的方法和宏.

## zval

#### 取得变量类型, 如: IS_NULL, IS_LONG, IS_STRING 等
```C
    zend_uchar zval_get_type(const zval* pz);
    zend_uchar Z_TYPE(zval);
    zend_uchar Z_TYPE_P(zval*);
```

#### 取得变量类型, TYPE_INFO. 如IS_STRING_EX, IS_ARRAY_EX 等.
```C
    uint32_t Z_TYPE_INFO(zval);
    uint32_t Z_TYPE_INFO_P(zval*);
```

#### 取得变量的counted, zend_refcounted_h结构指针. 此值同时是str,arr等指向的内存的开始.
```C
    zend_refcounted_h* Z_COUNTED(zval);
    zend_refcounted_h* Z_COUNTED_P(zval*);
```

#### 返回引用计数, 数字.
```C
    uint32_t GC_REFCOUNT(zend_refcounted_h*);
```

#### zval取值

```C
    zend_long Z_LVAL(zval);         // 取long值
    zend_long Z_LVAL_P(zval*);      // 取long值
    double Z_DVAL(zval);            // 取double值
    double Z_DVAL(zval*);           // 取double值
    zend_string Z_STR(zval);        // 返回字符串zend_string
    zend_string Z_STR(zval*);       // 返回字符串zend_string
    char* Z_STRVAL(zval);           // 取字符串缓冲区
    char* Z_STRVAL_P(zval*);        // 取字符串缓冲区
    size_t Z_STRLEN(zval);          // 取字符串变量的长度
    size_t Z_STRLEN(zval*);         // 取字符串变量的长度
    zend_ulong Z_STRHASH(zval);     // 计算字符串hash值
    zend_ulong Z_STRHASH_P(zval*);  // 计算字符串hash值
    zend_array* Z_ARR(zval);        // 取zend_array 别名: Z_ARRVAL
    zend_array* Z_ARR_P(zval*);     // 取zend_array 别名: Z_ARRVAL_P
    zend_object *Z_OBJ(zval);       // 取zend_object值
    zend_object *Z_OBJCE(zval);     // 取zend_object值
    zend_object *Z_OBJ_P(zval*);    // 取zend_object值
    zend_object *Z_OBJCE_P(zval*);  // 取zend_object值
    zend_resource *Z_RES(zval);
    zend_resource *Z_RES_P(zval*);
    zend_reference *Z_REF(zval);
    zend_reference *Z_REF_P(zval);
    zend_function *Z_FUNC(zval);
    zend_function *Z_FUNC_P(zval*);
    zend_class_entry *Z_CE(zval);
    zend_class_entry *Z_CE_P(zval*);
    void *Z_PTR(zval);
    void *Z_PTR_P(zval*);
```

#### zval赋值

以下方法会变更变量的类型. 没有特殊声明不影响引用计数.

```C
    ZVAL_UNDEF(zval*);                  // 将变量设置为undefined
    ZVAL_NULL(zval*);                   // 设置变量为null
    ZVAL_FALSE(zval*);                  // 设置为false
    ZVAL_TRUE(zval*);                   // 设置为true
    ZVAL_BOOL(zval*, bool);             // 同上两个
    ZVAL_LONG(zval*, long);             // 设置为long值
    ZVAL_DOUBLE(zval*, double);         // 设置为double值
    ZVAL_STR(zval*, zend_string*);      // 设置为zend_string值, 会考虑zend_string为internal的情况
    ZVAL_NEW_STR(zval*, zend_string*);  // 设置为zend_string值, 没有上述考虑
    ZVAL_STR_COPY(zval*, zend_string*); // 设置zval*变量的值为zend_string, 会增加zend_string引用数
    ZVAL_ARR(zval*, zend_array*);       // 设置zval*变量的值为zend_array
    ZVAL_NEW_ARR(zval*);                // 分配一个新的zend_array结构, 并设置到zval作为其值, 引用计数为1.
    ZVAL_NEW_PERSISTENT_ARR(zval*);     // 分配一个新的zend_array结构, 并设置到zval作为其值. 引用计数为1. 在系统内存中分配, 而不是zend内存
    ZVAL_OBJ(zval*, zend_object*);      // 设置zend_object值
    ZVAL_RES(zval*, zend_resource*);    // zend_resource
    ZVAL_NEW_RES(zval* p_zval, int handler, int type, void *p); // 用handler, type, p初始化一个zend_resource结构, 并设置其值.
    ZVAL_REF(zval*, zend_reference*);   // 设置zend_reference
    ZVAL_NEW_EMPTY_REF(zval*);          // 分配一个新的zend_reference结构, 并设置到zval作为其值. 引用计数为1.
    ZVAL_NEW_REF(zval* p_val, zval* r); // 分配一个新的zend_reference结构, 将引用r变量.
    ZVAL_NEW_PERSISTENT_REF(zval* p_zval, zend_reference* r);             // 同上, 只是在系统内存中分配.
    ZVAL_CE(zval* p, zend_function* v);
    ZVAL_PTR(zval* p, void* v);
    ZVAL_FUNC(zval* p, zend_function* v);
```

#### zval引用
```C
    zval* Z_REFVAL(zval);           // 返回所引用的zval
    zval* Z_REFVAL_P(zval*);        // 返回所引用的zval
    ZVAL_DEREF(zval* p_zval);       // 解引用, 如果p_zval是一个引用的变量, p_zval将会被设置为它所引用的zval地址
    ZVAL_MAKE_REF(zval* p_zval);    // 做引用, 与上面的方法相反. 如果p_zval并非一个引用变量. 将会创建一个新的zval变量引用p_zval, 并将p_zval设置为新的变量地址
    ZVAL_UNREF(zval* p_zval);       // 强制取消引用. 原来的引用变量被强行转换成非引用变量
```

#### ZVAL COPY

```C
    ZVAL_COPY_VALUE(zval* p_zval, zval* v); // 简单COPY value和type_info字段. 不增加引用计数.
    ZVAL_COPY(zval* p_zval, zval* v);       // 同上, 但如果是引用计数的类型, copy值后, 增加引用计数.
    ZVAL_DUP(zval* p_zval, zval* v);        // 先简单COPY, 如果值是COPYABLE的, copy之, 如果是引用计数的, 增加引用. 其它情况不管.
```

#### 引用计数

```C
    Z_TRY_ADDREF(zval* p);  // 如果是可以引用计数的, 那么增加它.
    Z_TRY_DELREF(zval* p);  // 尝试, 减少引用.
    add_index_long
```

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

### 数组类型

#### 分配一个HashTable结构zend_array
    ALLOC_HASHTABLE(HashTable *ht)

#### 释放一个HashTable指针的内存.
    FREE_HASHTABLE(HashTable *ht)

#### 判断两个zend_string是否相等. 
    zend_bool zend_string_equals(zend_string* s1, zend_string* s2)

### 数组(HashTable)

    PHP中有一个Packed数组. 用于存储类似于数组的数据. 

```C

    zend_bool HT_IS_PACKED(HashTable *);            // 判断一个数组是不是Packed的. 
    zend_bool HT_IS_WITHOUT_HOLES(HashTable *);     // 返回数组是否有空洞, 因为unset可以删除数组中的元素, 留下空洞. 
    zend_bool HT_HAS_STATIC_KEYS_ONLY(HashTable*);  // 是否只有静态KEY


    void zend_hash_real_init(HashTable*, zend_bool packed);     // 初始化一个HashTable
    int zend_hash_del(HashTable*, zend_string*);                // 删除一个key
    void zend_hash_packed_to_hash(HashTable*);                  // 把packed数组转为hash
    void zend_hash_to_packed(HashTable*);                       // hash转为packed数组
    uint32_t zend_array_count(HashTable *);                     // 返回数组长度.

    // zend_hash_str_* 系统的方法, 它的参数都是原始的C字符串
    // _ind方法. 如果zval变量为IS_INDIRECT类型, 需要解析出他的真实值存入. 
    zval *zend_hash_str_update(HashTable *, char *, size_t len, zval *pData); // 更新一个Hash类型的Key.  返回一个新的zval指针
    zval *zend_hash_str_update_ind(HashTable *, char *, size_t len, zval *pData); // pData是一个间接的变量...(还不明白这里的用意)
    zval *zzend_hash_str_add(HashTable *, char*, size_t len, zval *pData);
    zval *zzend_hash_str_add_new(HashTable *, char*, size_t len, zval *pData);

    // 
    zval *zend_hash_update(HashTable *, zend_string *, zval);       // 其实就是设置key => value. 没有值时, 应该也会添加值. 
    zval *zend_hash_update_ind(HashTable *, zend_string *, zval);       // 其实就是设置key => value. 没有值时, 应该也会添加值. 
    zval *zend_hash_add(HashTable *, zend_string *, zval);       // 其实就是设置key => value. 没有值时, 应该也会添加值. 
    zval *zend_hash_add_new(HashTable *, zend_string *, zval);       // 跳过查询原来的key阶段, 直接添加新值. 有些情况下, 可以断言key不存在于HashTable中, 就可以直接调用此函数提高效率. 




    // 遍历
    ZEND_HASH_FOREACH_STR_KEY_VAL(HashTable *, zend_string *key, zval *value);
    // 可以使用 key && value
    // 如果key不存在, 将会是null
    ZEND_HASH_FOREACH_END();
```

### 参考文档

* [Blog by nikic](http://nikic.github.io/)
* [PHP Internals Book](http://www.phpinternalsbook.com/index.html)
* [PHP at the Core: A Hacker's Guide](http://php.net/manual/en/internals2.php)
