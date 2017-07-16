
#include <iostream>
#include <fstream>
#include<vector>
using namespace std;

#include "libpq-fe.h"

#include "ace/ACE.h"
#include "ace//OS.h"
#include "ace/Log_Msg.h"
#include "ace/High_Res_Timer.h"
#include "ace/Throughput_Stats.h"
#include "ace/Date_Time.h"

#include <occi.h>
using namespace oracle::occi;

struct item
{
	int job_id;
	int src_feature_id;
	int candidate_id;
	int score;
};

#define  SQL_LENGTH    1024
#define  MAX_LENGTH    90000000  

int ACE_TMAIN(int argv, ACE_TCHAR * args[])
{
	//连接数据库  PQconnectdb
	PGconn * pgconn = NULL;
#if 0
	pgconn = PQsetdbLogin("10.1.28.3",
		"5432",
		NULL,
		NULL,
		"gabsfz",
		"gab_rx_hx",
		"gab_rx_hx");
#else
	pgconn = PQsetdbLogin("192.168.186.129",
		"5432",
		NULL,
		NULL,
		"postgres",
		"gpmon",
		"pivotal");
#endif
#if 1

	if(PQstatus(pgconn) == CONNECTION_BAD)
	{
		cout<<"Connection db "<<"gabsfz"<<" failed!"<<endl;
		cout<<PQerrorMessage(pgconn)<<endl;
	}
	else
	{
		cout<<"Connection db "<<"gabsfz"<<" success!"<<endl;
	}


	//设置数据库字符集
	int ret = PQsetClientEncoding(pgconn,"GBK");
	if (ret == 0)
	{
		cout<<"set charset success!"<<endl;
	}
	else
		cout<<"set charset failed!"<<endl;
#endif



	//外部表插入操作
#if 0
	char id[SQL_LENGTH]={0};
	char seq[SQL_LENGTH]={0};
	char order[SQL_LENGTH]={0};
	char path[SQL_LENGTH]="";
	std::ofstream aim_file;
	for(int j = 0; j < 1; j++)
	{
		itoa(j,order,10);
		sprintf(path,
			ACE_TEXT("e:\\date_%s.txt"),
			order);

		ACE_UINT32 gsf = ACE_High_Res_Timer::global_scale_factor ();
		//开始时间
		ACE_hrtime_t test_start = ACE_OS::gethrtime();
		ACE_DEBUG((LM_DEBUG,ACE_TEXT("(%t|%T)开始打开文件!\n")));
		aim_file.open(path, std::ios::out|std::ios::binary|std::ios::app);
		for (int i = 0 ; i < 2000000; i ++)
		{
			itoa(i,id,10);
			itoa(i+1,seq,10);
			itoa(i+2,order,10);
			char buffer[SQL_LENGTH]={0};
			sprintf(buffer,
				ACE_TEXT("%s|123|12|457|%s|345|256|567|99.1|2016/08/30 15:40:11\n"),
				id,
				seq);
			aim_file.write(buffer,strlen(buffer));
		}
		aim_file.close();
		ACE_DEBUG((LM_DEBUG,ACE_TEXT("(%t|%T)关闭文件!\n")));


		//将外部表数据插入gp数据库
		int ret_val = 0;
		PGresult* res = PQexec(pgconn,"INSERT INTO t_hxjgb SELECT * FROM t_test_data_external1");
		if(PQresultStatus(res) != PGRES_COMMAND_OK)
		{
			ACE_DEBUG((LM_DEBUG,
				ACE_TEXT("INSERT EXTERNAL_TABLE FAILED,ERROR CODE %s"),
				PQresultErrorField(res,PG_DIAG_SQLSTATE)));
			ret_val = -1;
		}
		while (0 != ret_val)
		{
			res = PQexec(pgconn,"INSERT INTO t_hxjgb SELECT * FROM t_test_data_external1");
			if(PQresultStatus(res) != PGRES_COMMAND_OK)
			{
				ACE_DEBUG((LM_DEBUG,
					ACE_TEXT("INSERT EXTERNAL_TABLE FAILED,ERROR CODE %s"),
					PQresultErrorField(res,PG_DIAG_SQLSTATE)));
				ret_val = -1;
			}
			else
				ret_val = 0;
		}

		ACE_hrtime_t test_end = ACE_OS::gethrtime ();
		ACE_hrtime_t elaps_time = (test_end - test_start)* (1024000u / ACE_High_Res_Timer::global_scale_factor ());
		elaps_time = elaps_time >> 10;
		//总时间
		ACE_DEBUG ((LM_DEBUG,ACE_TEXT ("(%t|%T) 总时间==》%fs!\n"),
			elaps_time * 1e-9));
		system("pause");
	}

#endif


//设置超时连接
#if 0
	while(1)
	{
		char *conninfo = "hostaddr=192.168.111.130 port=5432 dbname=testDB\
						 user=gpmon password=pivotal connect_timeout=2";
		pgconn = PQconnectdb(conninfo);
		if(PQstatus(pgconn) != CONNECTION_OK)
		{
			cout<<"Connection db testDB failed!"<<endl;
			cout<<PQerrorMessage(pgconn)<<endl;
			PQreset(pgconn);
		}
		else
		{
			cout<<"Connection db testDB success!"<<endl;
		}
	}
#endif

	//重连数据库
#if 0
	PQreset(pgconn);
#endif

	//查看共享库是否为线程安全
#if 0
	int ret_val = PQisthreadsafe();
	if (ret_val == 1)
	{
		cout<<"共享库是线程安全的!\n"<<endl;
	}
	else
		cout<<"共享库不是线程安全的!\n"<<endl;
#endif
	//insert插入
#if 0
	//开始事务
	res = PQexec(pgconn,"begin");
	ACE_hrtime_t test_start1 = ACE_OS::gethrtime ();
	for (int i = 0 ; i < 1000 ; i++)
	{
		res = PQexec(pgconn,"insert into weather values('南京',20,30,'2016-06-07')");
		if(PQresultStatus(res) != PGRES_COMMAND_OK)
		{
			cout << "command faild! PQresultStatus=" << PQresultStatus(res) << endl;
			cout << PQresultErrorMessage(res) << endl;
			cout << PQresultErrorField(res,PG_DIAG_SQLSTATE) << endl;
		}
	}

	ACE_hrtime_t test_end1 = ACE_OS::gethrtime ();
	ACE_hrtime_t elaps_time1 = (test_end1 - test_start1)* (1024000u / gsf);
	elaps_time1 = elaps_time1 >> 10;

	ACE_DEBUG ((LM_DEBUG,
		ACE_TEXT ("(%t|%T) insert插入总时间_____%fs____!\n"),
		elaps_time1 * 1e-9));
	//结束事务
	res = PQexec(pgconn,"end"); 
	PQclear(res);
#endif


	//调用存储过程
#if 0
	ACE_hrtime_t test_start = ACE_OS::gethrtime ();
	for (int i = 0 ; i < 1000; i++)
	{
		res = PQexec(pgconn,"select * from insert_fun()");
		if(PQresultStatus(res) != PGRES_TUPLES_OK)
		{
			cout << "command faild! PQresultStatus=" << PQresultStatus(res) << endl;
			cout << PQresultErrorMessage(res) << endl;
			cout << PQresultErrorField(res,PG_DIAG_SQLSTATE) << endl;
		}
	}

	ACE_hrtime_t test_end = ACE_OS::gethrtime ();
	ACE_hrtime_t elaps_time = (test_end - test_start)* (1024000u / gsf);
	elaps_time = elaps_time >> 10;
	ACE_DEBUG ((LM_DEBUG,
		ACE_TEXT ("(%t|%T) 调用存储过程总时间_____%fs____!\n"),
		elaps_time * 1e-9));
	PQclear(res);
#endif

//批量插入
#if 0
	char buf[8192];
	vector<struct item>::iterator it;
	int lastLong = 0;
	for(it=fealist.begin();it!=fealist.end();it++)
	{
		char string[25];
		sprintf(buf+lastLong,"%d,'%s',%d,%d\n",it->job_id,(it->candidate_id).c_str(),it->score,it->src_feature_id);
		itoa(it->job_id,string,10);
		lastLong += strlen(string);
		//itoa(it->candidate_id,string,10);
		lastLong += strlen((it->candidate_id).c_str());
		itoa(it->score,string,10);
		lastLong += strlen(string);
		itoa(it->src_feature_id,string,10);
		lastLong += strlen(string);
		lastLong += strlen(",")*5 +1 ;
	}
	PGresult *res;

	res=PQexec(pgconn,"COPY test_table FROM STDIN DELIMITER ',';");
	if(PQresultStatus(res)!=PGRES_COPY_IN)
	{
		cout<<"copy in not ok";
	}
	else
	{
		if(PQputCopyData(pgconn,buf,lastLong)<=0)
		{
			cout<<"transmit error"<<endl;
		}
		else
		{
			if(PQputCopyEnd(pgconn,NULL)==1)
			{
				res = PQgetResult(pgconn);
				if(PQresultStatus(res)==PGRES_COMMAND_OK)
				{
					cout<<"done";
				}
				else
				{
					cout<<PQerrorMessage(pgconn);
				}
			}
		}
#endif


//存储过程
#if 0
	PGresult* res =  NULL;
	ACE_UINT32 gsf = ACE_High_Res_Timer::global_scale_factor ();
	//开始时间
	ACE_hrtime_t test_start = ACE_OS::gethrtime();
	char buffer[SQL_LENGTH] = {""};
	//事物开始
	for(int j = 1; j< 2; j++)
	{
		res = PQexec(pgconn, "BEGIN");
		for (int i = 1; i < 10; i ++)
		{
			ACE_DEBUG((LM_DEBUG,ACE_TEXT("(%t|%T) PQexec start!\n")));
			sprintf(buffer,"select * from addtest3(%d,%d,%d)",
				i,
				(i+j)*2,
				(i+j)*3
				);
			res = PQexec(pgconn,buffer);
			if(PQresultStatus(res) != PGRES_TUPLES_OK)
			{
				ACE_DEBUG((LM_ERROR,ACE_TEXT("(%t|%T) %s ERROR CODE %s,%d! \n"),
					buffer,
					PQresultErrorField(res,PG_DIAG_SQLSTATE),
					PQresultStatus(res)));

				res = PQexec(pgconn,"rollback");
				ACE_DEBUG((LM_ERROR,ACE_TEXT("(%t|%T) %s ERROR CODE %s,%d! \n"),
					buffer,
					PQresultErrorField(res,PG_DIAG_SQLSTATE),
					PQresultStatus(res)));
			}
			else
				ACE_DEBUG((LM_DEBUG,ACE_TEXT("(%t|%T)INSERT SUCCESS!\n")));
		}
		//事物结束
		res = PQexec(pgconn, "END");

	}

	ACE_hrtime_t test_end = ACE_OS::gethrtime ();
	ACE_hrtime_t elaps_time = (test_end - test_start)* (1024000u / ACE_High_Res_Timer::global_scale_factor ());
	elaps_time = elaps_time >> 10;
	//总时间
	ACE_DEBUG ((LM_DEBUG,ACE_TEXT ("(%t|%T) 总时间==》%fs!\n"),
		elaps_time * 1e-9));
		ACE_Throughput_Stats::dump_throughput (ACE_TEXT("Total"), gsf,
		test_end - test_start,
		MAX_LENGTH); 
     system("pause");
#endif


	//插入操作
#if 0
	ACE_UINT32 gsf = ACE_High_Res_Timer::global_scale_factor ();
	//开始时间
	ACE_hrtime_t test_start = ACE_OS::gethrtime();
	char buffer[SQL_LENGTH] = {""};
	for (int i = 8000; i < MAX_LENGTH; i ++)
	{
		ACE_DEBUG((LM_DEBUG,ACE_TEXT("(%t|%T) PQexec start!\n")));
		sprintf(buffer,"INSERT INTO T_HXJGB_TEST(RWID, RWTJID,\
					   YZPID, YKB,\
					   MBZPID, MBKB,\
					   PW, XSD)\
					   VALUES(%d,%d,%d,%d,%d,%d,%d,%2.2f)",
					   i,
					   1,
					   i,
					   1,
					   i,
					   1,
					   i+1,
					   0.50
					   );
		res = PQexec(pgconn,buffer);
		ACE_DEBUG((LM_DEBUG,ACE_TEXT("(%t|%T) PQexec finished!\n")));
		if(PQresultStatus(res) != PGRES_COMMAND_OK)
		{
			ACE_DEBUG((LM_ERROR,ACE_TEXT("(%t|%T) %s ERROR CODE %s! \n"),
				buffer,
				PQresultErrorField(res,PG_DIAG_SQLSTATE)));
		}
		else
			ACE_DEBUG((LM_DEBUG,ACE_TEXT("(%t|%T)INSERT SUCCESS!\n")));
		ACE_DEBUG((LM_DEBUG,ACE_TEXT("(%t|%T) INSERT finished!\n")));
	}

	ACE_hrtime_t test_end = ACE_OS::gethrtime ();
	ACE_hrtime_t elaps_time = (test_end - test_start)* (1024000u / ACE_High_Res_Timer::global_scale_factor ());
	elaps_time = elaps_time >> 10;
	//总时间
	ACE_DEBUG ((LM_DEBUG,ACE_TEXT ("(%t|%T) 总时间==》%fs!\n"),
		elaps_time * 1e-9));
	ACE_Throughput_Stats::dump_throughput (ACE_TEXT("Total"), gsf,
		test_end - test_start,
		MAX_LENGTH); 
#endif


	//查询操作
#if 0
	ACE_UINT32 gsf = ACE_High_Res_Timer::global_scale_factor ();
	//开始时间
	ACE_hrtime_t test_start = ACE_OS::gethrtime();
	ACE_TCHAR select_sql[SQL_LENGTH] = {'\0'};
	for(int j = 1; j < MAX_LENGTH; j ++)
	{
		ACE_OS::sprintf(select_sql,
			ACE_TEXT("SELECT * FROM T_HXJGB WHERE RWID=%d AND \
					 YZPID = %d AND MBKB = %d"),
					 j,
					 j,
					 1);
		res = PQexec(pgconn,select_sql);
		if(PQresultStatus(res) == PGRES_EMPTY_QUERY)
		{
			ACE_DEBUG((LM_ERROR,
				ACE_TEXT("(%t|%T)%s,错误返回值为%s\n"),
				select_sql,
				PQresultErrorField(res,PG_DIAG_SQLSTATE)));
		}
		else
		{
			int tuple_num=PQntuples(res);
			int field_num=PQnfields(res);
			for(int i = 0; i < tuple_num; ++i)
			{
				for(int j = 0; j < field_num; ++j)
				{
					ACE_DEBUG((LM_DEBUG,ACE_TEXT("%s  "),
						PQgetvalue(res,i,j)));
				}
				ACE_DEBUG((LM_DEBUG,ACE_TEXT("\n")));
			} 
		}
	}	
	ACE_hrtime_t test_end = ACE_OS::gethrtime ();
	ACE_hrtime_t elaps_time = (test_end - test_start)* (1024000u / ACE_High_Res_Timer::global_scale_factor ());
	elaps_time = elaps_time >> 10;

	//总时间
	ACE_DEBUG ((LM_DEBUG,ACE_TEXT ("(%t|%T) 总时间==》%fs!\n"),
		elaps_time * 1e-9));
	ACE_Throughput_Stats::dump_throughput (ACE_TEXT("Total"), gsf,
		test_end - test_start,
		MAX_LENGTH); 
#endif


	//删除操作
#if 0
	ACE_UINT32 gsf = ACE_High_Res_Timer::global_scale_factor ();
	//开始时间
	ACE_hrtime_t test_start = ACE_OS::gethrtime();
	ACE_TCHAR dele_sql[SQL_LENGTH] = {'\0'};
	for(int j = 0; j < MAX_LENGTH; j ++)
	{
		ACE_OS::sprintf(dele_sql,
			ACE_TEXT("DELETE FROM T_HXJGB WHERE RWID=%d AND \
					 YZPID = %d AND MBKB = %d"),
					 j,
					 j,
					 1);
		res = PQexec(pgconn,dele_sql);
		if(PQresultStatus(res) != PGRES_COMMAND_OK)
		{
			ACE_DEBUG((LM_ERROR,
				ACE_TEXT("(%t|%T)%s,错误返回值为%s\n"),
				dele_sql,
				PQresultErrorField(res,PG_DIAG_SQLSTATE)));
		}
		else
			ACE_DEBUG((LM_DEBUG,ACE_TEXT("DELETE SUCCESS!\n")));
	}

	ACE_hrtime_t test_end = ACE_OS::gethrtime ();
	ACE_hrtime_t elaps_time = (test_end - test_start)* (1024000u / ACE_High_Res_Timer::global_scale_factor ());
	elaps_time = elaps_time >> 10;
	//总时间
	ACE_DEBUG ((LM_DEBUG,ACE_TEXT ("(%t|%T) 总时间==》%fs!\n"),
		elaps_time * 1e-9));
	ACE_Throughput_Stats::dump_throughput (ACE_TEXT("Total"), gsf,
		test_end - test_start,
		MAX_LENGTH); 
#endif


	//修改操作
#if 0
	ACE_UINT32 gsf = ACE_High_Res_Timer::global_scale_factor ();
	//开始时间
	ACE_hrtime_t test_start = ACE_OS::gethrtime();
	ACE_TCHAR update_sql[SQL_LENGTH] = {'\0'};
	for(int j = 1; j < MAX_LENGTH; j ++)
	{
		ACE_OS::sprintf(update_sql,
			ACE_TEXT("UPDATE T_HXJGB SET XSD =%2.2f WHERE RWID=%d AND \
					 YZPID = %d AND MBKB = %d"),
					 j,
					 j,
					 j,
					 1);
		res = PQexec(pgconn,update_sql);
		if(PQresultStatus(res) != PGRES_COMMAND_OK)
		{
			ACE_DEBUG((LM_ERROR,
				ACE_TEXT("(%t|%T)%s,错误返回值为%s\n"),
				update_sql,
				PQresultErrorField(res,PG_DIAG_SQLSTATE)));
		}
		else
			ACE_DEBUG((LM_DEBUG,ACE_TEXT("UPDATE SUCCESS!\n")));
	}

	ACE_hrtime_t test_end = ACE_OS::gethrtime ();
	ACE_hrtime_t elaps_time = (test_end - test_start)* (1024000u / ACE_High_Res_Timer::global_scale_factor ());
	elaps_time = elaps_time >> 10;
	//总时间
	ACE_DEBUG ((LM_DEBUG,ACE_TEXT ("(%t|%T) 总时间==》%fs!\n"),
		elaps_time * 1e-9));
	ACE_Throughput_Stats::dump_throughput (ACE_TEXT("Total"), gsf,
		test_end - test_start,
		MAX_LENGTH); 

	//ACE_TCHAR* StrTime = new ACE_TCHAR[SQL_LENGTH];
	//ACE_Date_Time CurTime(ACE_OS::gettimeofday());
	//memset(StrTime,'\0',100);
	//sprintf(StrTime,ACE_TEXT("%d-%02d-%02d  %02d:%02d:%02d:%d\t"),
	//		CurTime.year(),CurTime.month(),CurTime.day(),  
	//		CurTime.hour(),CurTime.minute(),CurTime.second(),
	//		CurTime.microsec());
#endif	

	//关闭数据库连接
#if 0
	PQfinish(pgconn);
#endif


//插入字符串
#include <fstream>
#if 1
	//获取特征文件

	std::fstream src_file;
	src_file.open("d:/2.jpg", std::ios::in|std::ios::binary);
	if (0 == src_file) // file not exist
	{
		return 1;
	}
	src_file.seekg(0, std::ios::end);
	int buffer_size = static_cast<unsigned long>(src_file.tellg());
	src_file.seekg(0);
	
	char* fea = new char[buffer_size + 1];
	memset(fea, 0, buffer_size + 1);
	src_file.read(fea, buffer_size);
	src_file.close();


	ofstream os1;
	os1.open("d:\\101.jpg",std::ios::out|std::ios::binary);
	os1.write((char *)fea,buffer_size);
	os1.close();


	const char* stmtName = "Insert";
	PGresult* stmt = PQprepare(
		pgconn,
		stmtName,
		"INSERT INTO TEST.FEATURE(\
		FEATURE_ID,\
		FEA) VALUES\
		($1::integer,$2::bytea)",
		2,
		NULL
		);
	if(PQresultStatus(stmt) != PGRES_COMMAND_OK)
	{
		ACE_DEBUG((LM_ERROR,
			ACE_TEXT("(%t|%T)调用PQprepare时出错,返回值为%s\n"),
			PQresultErrorField(stmt,PG_DIAG_SQLSTATE)));
		return false;
	}
	PQclear(stmt);

	//参数格式(参数类型1：二进制  0：非二进制)
	int paramFormats[2] = { 0, 1};
	char* paramValues[2]={'\0'};
	char feature_id[1024]={'\0'};
	unsigned char *byteaStr;// = new unsigned char[buffer_size * 2]; 
	ltoa(100,feature_id,10);
	paramValues[0]= feature_id;
	paramValues[1]= fea;

	int paramLengths[2];
	paramLengths[0] = strlen(paramValues[0]);
	paramLengths[1] = buffer_size;

	PGresult* test = PQexecPrepared(pgconn,
		stmtName,
		2,
		(const char *const *)paramValues,
		paramLengths, 
		paramFormats,
		0);
	if(PQresultStatus(test) != PGRES_COMMAND_OK)
	{
		ACE_DEBUG((LM_ERROR,
			ACE_TEXT("(%t|%T)调用PQexecPrepared时出错,返回值为%s\n"),
			PQresultErrorField(test,PG_DIAG_SQLSTATE)));
		return false;
	}

#if 1

	char select_sql[1024]={0};
	ACE_OS::sprintf(select_sql,
		ACE_TEXT("SELECT fea FROM test.feature WHERE feature_id=100"));
	test = PQexec(pgconn,select_sql);
	if(PQresultStatus(test) == PGRES_EMPTY_QUERY)
	{
		ACE_DEBUG((LM_ERROR,
			ACE_TEXT("(%t|%T)%s,错误返回值为%s\n"),
			select_sql,
			PQresultErrorField(test,PG_DIAG_SQLSTATE)));
	}
	else
	{
		int tuple_num=PQntuples(test);
		int field_num=PQnfields(test);
		for(int i = 0; i < tuple_num; ++i)
		{
			for(int j = 0; j < field_num; ++j)
			{
				int len = PQgetlength(test,i,j);
				char * buffer = new char [len];
				memset(buffer,0,len);
				buffer = PQgetvalue(test,i,j);

 				int len2 = 0;
				unsigned char * buffer1 = PQunescapeBytea((const unsigned char *)buffer,
					(size_t *)&len2);
 				
				ofstream os;
				os.open("d:\\100.jpg",std::ios::out|std::ios::binary);
				os.write((char *)buffer1,len2);
				os.close();
			}
			ACE_DEBUG((LM_DEBUG,ACE_TEXT("\n")));
		} 
	}
	PQclear(test);
#endif


#endif

	return 0;
}