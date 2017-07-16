#include<iostream>
using namespace  std;

#include "MyOci.h"
#include <assert.h>


int main(void)
{
	MyOci myoci;

	//<< ����OCCI�����Ļ���
	myoci.Env = Environment::createEnvironment();
	//<< ����ָ���Ƿ�Ϊ��
	assert(myoci.Env != NULL);
	//<< �������ݿ�����
	myoci.conn = myoci.Env->createConnection(myoci.username,myoci.password,myoci.m_connection);

	if (myoci.conn != NULL)
	{
		cout<<"���ݿ����ӳɹ���"<<endl;
		system("pause");
	}
	else
	{
		cout<<"���ݿ�����ʧ�ܣ�"<<endl;
		return 0;
	}
	
	//<< ����SQL�����ƾ��
	myoci.stmt = myoci.conn ->createStatement();

/**************************************/
/***** ִ�в�ѯ���(select) ***********/
/**************************************/ 
#if 0
    myoci.ExecuteSelect();
#endif 

/**************************************/
/***** �ǲ�ѯ��䣨��select)***********/
/**************************************/ 
#if 0
   myoci.ExecuteNoSelect();
#endif

/**************************************/
/***** ������䣨��select)***********/
/**************************************/ 
#if 0
   myoci.update_sql();
#endif


/**************************************/
/***** ִ��������ѯ���(select) ***********/
/**************************************/ 
#if 0
   myoci.Batch_ExecuteSelect();
#endif

/**************************************/
/***** �����ǲ�ѯ��䣨��select)***********/
/**************************************/ 
#if 1
  myoci.Batch_ExecuteNoSelect();
#endif

/***********************/
/****�������ز���*****/
/***********************/
#if 0
  myoci.Transaction();

#endif

//Date�����ز���
#if 0
  //��ȡϵͳʱ��
  myoci.Execute_Date();

#endif


#if 0
  //��ȡblob�ֶ�
  myoci.get_blob();

#endif

#if 0
   //��ȡ�����������ݵ���ͬ����
    myoci.get_same_data();

#endif

#if 0
//����executeArrayUpdate����
    
    myoci.test();
#endif


	//�ͷ�SQL�����
	myoci.conn->terminateStatement(myoci.stmt);
	//<< �ر�����
	myoci.Env -> terminateConnection(myoci.conn);
	//<< �ͷŻ�������
	Environment::terminateEnvironment(myoci.Env);

	return 0;
}


