#include <iostream>
#include "MySqlClass.h"

using namespace std;


int main()
{
	///初始化连接sql数据库
#if 1
	MySqlClass mysqlclass;
	MYSQL* mMYSQL = NULL;
	mMYSQL = mysql_init(NULL);
	int retval = mysqlclass.InitMsql(mMYSQL,
		"192.168.30.123",
		"root",
		"root",
		"test",
		3306,
		NULL, 
		0);
	if (retval != 0)
	{
		cout << "数据库连接失败!" <<endl;
	}
	else
	{
		cout << "数据库连接成功!" <<endl;
	}
#endif


	///查询数据
#if 0
	char str [1024] ={""};
	sprintf(str,"select * from student");
	retval = mysqlclass.MsqlQuery(mMYSQL,str);
	if (retval != 0 ) 
	{
		cout << "查询结果失败!" <<endl;
	}
#endif


	///插入数据
#if 0
	char str [1024] ={""};
	sprintf(str,"insert into student values ('guo',222,'男',14)");
	retval = mysqlclass.MsqlInsert(mMYSQL,str);
	if (retval != 0 ) 
	{
		cout << "插入数据失败!" <<endl;
	}
#endif


	///修改数据
#if 0
	char str [1024] ={""};
	sprintf(str,"update student set name = 'feng' where id = 222");
	retval = mysqlclass.MsqlUpdate(mMYSQL,str);
	if (retval != 0 ) 
	{
		cout << "修改数据失败!" <<endl;
	}
#endif


	///删除数据
#if 0
	char str [1024] ={""};
	sprintf(str,"delete from student where id = 111");
	retval = mysqlclass.MsqlDelete(mMYSQL,str);
	if (retval != 0 ) 
	{
		cout << "删除数据失败!" <<endl;
	}
#endif

	///关闭数据库
	mysql_close(mMYSQL);
	//mysql_shutdown(mMYSQL,SHUTDOWN_DEFAULT);
	return 0;
}