#include "MySqlClass.h"

MySqlClass::MySqlClass(void)
{
}

MySqlClass::~MySqlClass(void)
{
}

int MySqlClass::InitMsql( MYSQL *mysql, 
						 const char *host, 
						 const char *user, 
						 const char *passwd, 
						 const char *db,
						 unsigned int port, 
						 const char *unix_socket,
						 unsigned long clientflag )
{
	try
	{
		if (!(mysql_real_connect(mysql,
			host,
			user,
			passwd,
			db,
			port,
			unix_socket, 
			clientflag)))
		{
			mysql_close(mysql);
			return -1;
		}
		mysql_query(mysql, "set names 'GBK'");
	}
	catch (...)
	{
		if (mysql)
			mysql_close(mysql);
		return -1;
	}
	return 0;
}


int MySqlClass::MsqlQuery( MYSQL *mysql, const char *str )
{
	if (mysql_query(mysql, str) != 0)
		return -1;

	/*mysql_store_result()将查询的全部结果读取到客户端，分配1个MYSQL_RES结构，并将结果置于该结构中
	如果查询未返回结果集，mysql_store_result()将返回Null指针*/
	MYSQL_RES *result = mysql_store_result(mysql);
	//mysql_fetch_row()来获取结果集中的行
	MYSQL_ROW row = mysql_fetch_row(result);

	if (row == NULL)
	{
		mysql_free_result(result);
		return -1;
	}

	while (row)
	{
		cout << "name:" << row[0] << "   id:" << row[1] << "   sex:" << row[2] << "   age:" << row[3] <<endl;
		row = mysql_fetch_row(result);
	}

	//一旦完成了对结果集的操作，必须调用mysql_free_result()。
	mysql_free_result(result);

	return 0;
}

int MySqlClass::MsqlDelete( MYSQL *mysql, const char *str )
{
	if (mysql_query(mysql, str) != 0)
		return -1;

	return 0;
}

int MySqlClass::MsqlUpdate( MYSQL *mysql, const char *str )
{
	if (mysql_query(mysql, str) != 0)
		return -1;

	return 0;
}

int MySqlClass::MsqlInsert( MYSQL *mysql, const char *str )
{
	if (mysql_query(mysql, str) != 0)
		return -1;

	return 0;
}