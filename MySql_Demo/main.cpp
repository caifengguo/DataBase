#include <iostream>
#include "MySqlClass.h"

using namespace std;


int main()
{
	///��ʼ������sql���ݿ�
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
		cout << "���ݿ�����ʧ��!" <<endl;
	}
	else
	{
		cout << "���ݿ����ӳɹ�!" <<endl;
	}
#endif


	///��ѯ����
#if 0
	char str [1024] ={""};
	sprintf(str,"select * from student");
	retval = mysqlclass.MsqlQuery(mMYSQL,str);
	if (retval != 0 ) 
	{
		cout << "��ѯ���ʧ��!" <<endl;
	}
#endif


	///��������
#if 0
	char str [1024] ={""};
	sprintf(str,"insert into student values ('guo',222,'��',14)");
	retval = mysqlclass.MsqlInsert(mMYSQL,str);
	if (retval != 0 ) 
	{
		cout << "��������ʧ��!" <<endl;
	}
#endif


	///�޸�����
#if 0
	char str [1024] ={""};
	sprintf(str,"update student set name = 'feng' where id = 222");
	retval = mysqlclass.MsqlUpdate(mMYSQL,str);
	if (retval != 0 ) 
	{
		cout << "�޸�����ʧ��!" <<endl;
	}
#endif


	///ɾ������
#if 0
	char str [1024] ={""};
	sprintf(str,"delete from student where id = 111");
	retval = mysqlclass.MsqlDelete(mMYSQL,str);
	if (retval != 0 ) 
	{
		cout << "ɾ������ʧ��!" <<endl;
	}
#endif

	///�ر����ݿ�
	mysql_close(mMYSQL);
	//mysql_shutdown(mMYSQL,SHUTDOWN_DEFAULT);
	return 0;
}