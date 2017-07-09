#pragma once

#include  "mysql.h"
#include <iostream>

using namespace std;

class MySqlClass
{
public:
	MySqlClass(void);
	~MySqlClass(void);

	/**
	*\ InitMsql  初始化连接数据库
	*\ param[in]  mysql  输入sql对象
	*\ param[in]  user   用户名
	*\ param[in]  passwd 密码
	*\ param[in]  db     数据库名称
	*\ param[in]  port   端口号
	*\ param[in]  默认为NULL
	*\ param[in]  默认为0
	*\ param[out]  return  0:成功 1:失败
	*/
	int InitMsql(MYSQL *mysql, const char *host,
		const char *user,
		const char *passwd,
		const char *db,
		unsigned int port,
		const char *unix_socket,
		unsigned long clientflag);


	/** 
	*\ MsqlQuery 查询sql语句
	*\ param[in] MYSQL对象
	*\ param[in] str sql语句
	*\ param[out] 返回值 
	**/
	int MsqlQuery(MYSQL *mysql, const char *str);
	

	/** 
	*\ MsqlQuery 插入sql语句
	*\ param[in] MYSQL对象
	*\ param[in] str sql语句
	*\ param[out] 返回值 
	**/
	int MsqlInsert(MYSQL *mysql, const char *str);


	/** 
	*\ MsqlQuery 修改sql语句
	*\ param[in] MYSQL对象
	*\ param[in] str sql语句
	*\ param[out] 返回值 
	**/
	int MsqlUpdate(MYSQL *mysql, const char *str);


	/** 
	*\ MsqlQuery 删除sql语句
	*\ param[in] MYSQL对象
	*\ param[in] str sql语句
	*\ param[out] 返回值 
	**/
	int MsqlDelete(MYSQL *mysql, const char *str);


};
