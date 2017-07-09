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

	/*mysql_store_result()����ѯ��ȫ�������ȡ���ͻ��ˣ�����1��MYSQL_RES�ṹ������������ڸýṹ��
	�����ѯδ���ؽ������mysql_store_result()������Nullָ��*/
	MYSQL_RES *result = mysql_store_result(mysql);
	//mysql_fetch_row()����ȡ������е���
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

	//һ������˶Խ�����Ĳ������������mysql_free_result()��
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