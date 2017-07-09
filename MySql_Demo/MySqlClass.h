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
	*\ InitMsql  ��ʼ���������ݿ�
	*\ param[in]  mysql  ����sql����
	*\ param[in]  user   �û���
	*\ param[in]  passwd ����
	*\ param[in]  db     ���ݿ�����
	*\ param[in]  port   �˿ں�
	*\ param[in]  Ĭ��ΪNULL
	*\ param[in]  Ĭ��Ϊ0
	*\ param[out]  return  0:�ɹ� 1:ʧ��
	*/
	int InitMsql(MYSQL *mysql, const char *host,
		const char *user,
		const char *passwd,
		const char *db,
		unsigned int port,
		const char *unix_socket,
		unsigned long clientflag);


	/** 
	*\ MsqlQuery ��ѯsql���
	*\ param[in] MYSQL����
	*\ param[in] str sql���
	*\ param[out] ����ֵ 
	**/
	int MsqlQuery(MYSQL *mysql, const char *str);
	

	/** 
	*\ MsqlQuery ����sql���
	*\ param[in] MYSQL����
	*\ param[in] str sql���
	*\ param[out] ����ֵ 
	**/
	int MsqlInsert(MYSQL *mysql, const char *str);


	/** 
	*\ MsqlQuery �޸�sql���
	*\ param[in] MYSQL����
	*\ param[in] str sql���
	*\ param[out] ����ֵ 
	**/
	int MsqlUpdate(MYSQL *mysql, const char *str);


	/** 
	*\ MsqlQuery ɾ��sql���
	*\ param[in] MYSQL����
	*\ param[in] str sql���
	*\ param[out] ����ֵ 
	**/
	int MsqlDelete(MYSQL *mysql, const char *str);


};
