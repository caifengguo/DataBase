#pragma once

#include <occi.h>
using namespace oracle::occi;

#include<string>
using namespace std;

class MyOci
{
public:
	MyOci(void);
	~MyOci(void);


	void ExecuteSelect();
	void ExecuteNoSelect();
	void Batch_ExecuteSelect();
	void Batch_ExecuteNoSelect();
	void Transaction();

    void update_sql();

    void Execute_Date();
    void get_blob();

    void get_same_data();

    void  test();

public:
	//<< 声明环境变量
	Environment * Env;
	//<< 声明连接数据库的字符集指针
	Connection* conn;
    //<<创建SQL语句控制句柄
	Statement* stmt;
	//<< 返回结果
	ResultSet* rs;

	//<< 数据库用户名
	string username;
	//<< 数据库密码
	string password;
	//<< 数据库ip
	string ip;
	//<< 数据库port;
	string port;

	//连接字符串
	string m_connection;
};




/* Environment类
   (1)Environment类提供了管理OCCI对象的内存及其它资源的一个环境

   (2)Connection类提供了C++程序与指定数据库的连接
   (3)ConnectionPoll类提供了C++程序与指定数据库间的连接池
   (4)Statement对象主要被用来执行SQL语句，它可以运行一个查询语句返回一个结果集也可以运行UPDATE、DELETE等SQL语句。
   (5)ResultSet类是查询数据表的结果集
   (6)SQLException类提供错误代码及其错误信息，包含以下方法：
		1． getErrorCode();返回数据库中的错误编码。
		2． getMessage();返回错误信息，没有则为空。
*/



//事务的操作流程
/*
打开数据库连接();
try
{
开启事务();
数据库操作1();
数据库操作2();
......;
数据库操作n();
提交事务();
}
catch (Exception err)
{
回滚事务();
throw err; // 重新抛出异常（导致异常的堆栈信息发生变化，无法知道原始异常所在位置，不利于调试）
}
finally
{
关闭数据库连接();
}

在使用中经常因为 SQL 语句或某个未知的错误导致异常和事务失败，但在 catch 块中由于 trhow err 被重新抛出，异常的堆栈信息发生变化，无法知道原始异常所在位置。所
*/