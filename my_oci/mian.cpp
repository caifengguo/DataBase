#include<iostream>
using namespace  std;

#include "MyOci.h"
#include <assert.h>


int main(void)
{
	MyOci myoci;

	//<< 创建OCCI上下文环境
	myoci.Env = Environment::createEnvironment();
	//<< 断言指针是否为空
	assert(myoci.Env != NULL);
	//<< 创建数据库连接
	myoci.conn = myoci.Env->createConnection(myoci.username,myoci.password,myoci.m_connection);

	if (myoci.conn != NULL)
	{
		cout<<"数据库连接成功！"<<endl;
		system("pause");
	}
	else
	{
		cout<<"数据库连接失败！"<<endl;
		return 0;
	}
	
	//<< 创建SQL语句控制句柄
	myoci.stmt = myoci.conn ->createStatement();

/**************************************/
/***** 执行查询语句(select) ***********/
/**************************************/ 
#if 0
    myoci.ExecuteSelect();
#endif 

/**************************************/
/***** 非查询语句（非select)***********/
/**************************************/ 
#if 0
   myoci.ExecuteNoSelect();
#endif

/**************************************/
/***** 更新语句（非select)***********/
/**************************************/ 
#if 0
   myoci.update_sql();
#endif


/**************************************/
/***** 执行批量查询语句(select) ***********/
/**************************************/ 
#if 0
   myoci.Batch_ExecuteSelect();
#endif

/**************************************/
/***** 批量非查询语句（非select)***********/
/**************************************/ 
#if 1
  myoci.Batch_ExecuteNoSelect();
#endif

/***********************/
/****事务的相关操作*****/
/***********************/
#if 0
  myoci.Transaction();

#endif

//Date类的相关操作
#if 0
  //获取系统时间
  myoci.Execute_Date();

#endif


#if 0
  //获取blob字段
  myoci.get_blob();

#endif

#if 0
   //获取两个队列数据的相同数据
    myoci.get_same_data();

#endif

#if 0
//测试executeArrayUpdate方法
    
    myoci.test();
#endif


	//释放SQL语句句柄
	myoci.conn->terminateStatement(myoci.stmt);
	//<< 关闭连接
	myoci.Env -> terminateConnection(myoci.conn);
	//<< 释放环境变量
	Environment::terminateEnvironment(myoci.Env);

	return 0;
}


