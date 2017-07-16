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
	//<< ������������
	Environment * Env;
	//<< �����������ݿ���ַ���ָ��
	Connection* conn;
    //<<����SQL�����ƾ��
	Statement* stmt;
	//<< ���ؽ��
	ResultSet* rs;

	//<< ���ݿ��û���
	string username;
	//<< ���ݿ�����
	string password;
	//<< ���ݿ�ip
	string ip;
	//<< ���ݿ�port;
	string port;

	//�����ַ���
	string m_connection;
};




/* Environment��
   (1)Environment���ṩ�˹���OCCI������ڴ漰������Դ��һ������

   (2)Connection���ṩ��C++������ָ�����ݿ������
   (3)ConnectionPoll���ṩ��C++������ָ�����ݿ������ӳ�
   (4)Statement������Ҫ������ִ��SQL��䣬����������һ����ѯ��䷵��һ�������Ҳ��������UPDATE��DELETE��SQL��䡣
   (5)ResultSet���ǲ�ѯ���ݱ�Ľ����
   (6)SQLException���ṩ������뼰�������Ϣ���������·�����
		1�� getErrorCode();�������ݿ��еĴ�����롣
		2�� getMessage();���ش�����Ϣ��û����Ϊ�ա�
*/



//����Ĳ�������
/*
�����ݿ�����();
try
{
��������();
���ݿ����1();
���ݿ����2();
......;
���ݿ����n();
�ύ����();
}
catch (Exception err)
{
�ع�����();
throw err; // �����׳��쳣�������쳣�Ķ�ջ��Ϣ�����仯���޷�֪��ԭʼ�쳣����λ�ã������ڵ��ԣ�
}
finally
{
�ر����ݿ�����();
}

��ʹ���о�����Ϊ SQL ����ĳ��δ֪�Ĵ������쳣������ʧ�ܣ����� catch �������� trhow err �������׳����쳣�Ķ�ջ��Ϣ�����仯���޷�֪��ԭʼ�쳣����λ�á���
*/