#include "MyOci.h"
#include<iostream>
using namespace std;

#include<stdlib.h>
#include<conio.h>


//<< 构造函数
MyOci::MyOci(void)
{
	//<< 初始化用户名
	username ="xzl";
	//<< 初始化密码
	password ="123456";
	//<< 初始化ip
	ip ="192.168.30.30";
	//<< 初始化port
	port ="1521";
	
	//<< 初始化连接字符串
	m_connection = ip + ":";
	m_connection += port;
	m_connection += "/ORCL";
}

MyOci::~MyOci(void)
{
}


void MyOci::ExecuteSelect()
{

	//<<SQL语句
	string sql_1 = "select * from person t where t.logic_db_id = 1";
	//<< 准备SQL语句
	stmt ->setSQL(sql_1);
	int m_id;
	string  name;
	try
	{
		//执行SQL语句,获取结果集
		rs = stmt->executeQuery();        // executeQuery()函数有返回值    
		                                  // executeUpdate()函数没有返回值
		while (rs->next()) //取数据
		{
			//获取第一列的数据
			m_id  = rs->getInt(1);   //获取查询结果值
			//获取第三列的数据
			name  = rs->getString(3);
			//输出结果
			cout<< m_id << "  AND  " << name << endl;
		}
		//<< 关闭结果集
		stmt ->closeResultSet(rs);

		cout <<"SELECT  SUCCESS" << endl;
	}
	catch(SQLException ex)     //异常处理
	{
		cout << " Error Number "<< ex.getErrorCode() << endl;  //取出异常代码
		cout << ex.getMessage() << endl;             //取出异常信息
	}
}



void MyOci::ExecuteNoSelect()
{
#if 0
	//SQL语句
	//string sql = "create table student (sno int,sname varchar(20),sage int)";

	//复制表的结构，同时复制表的数据
	//string sql = "create table image_1 as select * from image";
	//只复制表结构，不复制表数据
	 string sql = "create table image_1 as select * from image where 1=2";
	//准备SQL语句(即设置SQL语句到statement对象中)
	stmt->setSQL(sql);

	try
	{
		//<< 创建student表
		stmt->executeUpdate();
		cout<<"CREATE---SUCCESS----"<<endl;
	}
	catch(SQLException ex)     //异常处理
	{
		cout << " Error Number "<< ex.getErrorCode() << endl;  //取出异常代码
		cout << ex.getMessage() << endl;             //取出异常信息
	}
#endif

#if 0
    //SQL语句
      string strsql = "insert into student(sno,sname) values(:x,:y)";
	  stmt->setSQL(strsql);

	  try
	  {
		  stmt->setInt(1,1003);
		  stmt->setString(2,"zhangsan");

	    //<< 向student表中插入数据
	     stmt->executeUpdate();
		 cout<<"INSERT-------SUCCESS-----"<<endl;
	 }
	  catch(SQLException ex)     //异常处理
	  {
		  cout << " Error Number "<< ex.getErrorCode() << endl;  //取出异常代码
		  cout << ex.getMessage() << endl;             //取出异常信息
	  }
#endif
}



void MyOci::update_sql()
{
#if 1
    //SQL语句
    string strsql = "update student set sno = '123' where sname = '张三'";
    stmt->setSQL(strsql);

    try
    {
        //<< 更新数据
        stmt->executeUpdate();
        cout<<"update-------SUCCESS-----"<<endl;
    }
    catch(SQLException ex)     //异常处理
    {
        cout << " Error Number "<< ex.getErrorCode() << endl;  //取出异常代码
        cout << ex.getMessage() << endl;             //取出异常信息
    }

#endif
}


void MyOci::Batch_ExecuteNoSelect()
{
#if 0
	int i_sno[2]={10,11};
	int i_age[2]={20,21};
	string str_name[2]={"zhangsan","lisi"};
	//SQL语句
	string sql = "insert  into student(sno,sname,sage) values(:x,:y,:z)";
	stmt->setSQL(sql);

	stmt->setAutoCommit(false);   //设置事务为手动提交

	try
	{
		//设置最大的批处理数
		stmt->setMaxIterations(2);
		//设置对应参数的大小
		stmt->setMaxParamSize(1,sizeof(int));
		stmt->setMaxParamSize(2,sizeof(string));
		stmt->setMaxParamSize(3,sizeof(int));

		for (int i = 0; i< 2; i++)
		{
			//绑定输入参数
			stmt->setInt(1,i_sno[i]);
			stmt->setString(2,str_name[i]);
			stmt->setInt(3,i_age[i]);
			cout<<i_sno[i]<<str_name[i]<<i_age[i]<<endl;

			if (i!=1)
			{
				//添加一行记录（类似与ADO中的ADDNEW）
				stmt->addIteration();  //该方法使得循环进入下一次 
			}
		}
		stmt->executeUpdate();
		conn->commit();          //事务提交
	}
	catch (SQLException ex) 
	{
		int n = stmt->getUpdateCount();   //获取更新条数
		cout << n << " FAIL !" << endl;
		cout << " INSERT Error Number: "<< ex.getErrorCode() << endl;
		cout << ex.getMessage() <<endl;

		conn->rollback();     //事务回滚
	}
#endif
	try{
		char strsql[1024*4] ={'\0'};
		sprintf_s(strsql,1024*4,"INSERT INTO JCRLBD VALUES(:1, :2, :3, :4, :5, :6, :7, :8, :9)");
		//		string strSQL = "INSERT INTO JCRLBD VALUES(:1, :2, :3, :4, :5, :6, :7, :8, :9)";
		stmt->setSQL(strsql);
		stmt->setInt(1,1);
		stmt->setString(2,"111111111111111111111111111111");
		stmt->setString(3,"123");
		stmt->setString(4,"2345");
		stmt->setNumber(5,11.23);
		stmt->setString(6,"1");

		Date dt;
		Date dt1 = dt.getSystemDate(Env);
		string strval = dt1.toText("YYYY-MM-DD");
		stmt->setDate(7,dt1);
		stmt->setDate(8,dt1);
		stmt->setDate(9,dt1);
		stmt->execute();
		conn->commit();

	}
	catch(SQLException &e)
	{
		cout<<"SQLException:"<<e.getMessage()<<endl;
	}
	catch(exception &e)
	{
		cout<<"exception"<<endl;
	}
	catch(...)
	{
		cout<<"Insert TranceAction Exception"<<endl;
	}
}


void MyOci::Batch_ExecuteSelect()
{
 //  char sname[5][20];
 //  int  i_sno[5];
 //  ub2 snamelen[5];    //ub2 == usigned short
 //  int numrow = 5;
 //  int num;

	////SQL语句
	//string sql = "select sno,sname from student";
	//stmt->setSQL(sql);

	//rs = stmt->executeQuery();

	//rs->setDataBuffer(1,OCCIINT,sizeof(int));  
	//rs->setDataBuffer(2,OCCI_SQLT_STR,sizeof(sname[0]),snamelen);
 //   
	//rs->getNumArrayRows();


	//to do ............
}



void MyOci::Transaction()
{

	string sql = "create table student (sno int,sname varchar(20),sage int)";
	stmt->setSQL(sql);

	stmt->setAutoCommit(FALSE);  //设置事务手动提交
	//stmt->setAutoCommit(TRUE);  //设置事务自动提交

	try
	{
		stmt->executeUpdate();
		conn->commit();
		cout<<"CREATE---SUCCESS----"<<endl;
		//getch();
		system("pause");
	}
	catch(SQLException ex)     //异常处理   
	{
		conn->rollback();
		cout << " Error Number "<< ex.getErrorCode() << endl;  //取出异常代码
		cout << ex.getMessage() << endl;             //取出异常信息
	}
}


//执行date类的相关操作
void MyOci::Execute_Date()
{
    //获取当前系统时间
    Date dt;
    Date dt1 = dt.getSystemDate(Env);
    string strval = dt1.toText("YYYY-MM-DD");

    //获取添加n天后的日期
    Date dt2 = dt1.addDays(2);
    string str = dt2.toText("YYYY-MM-DD");

    //获取添加n个月后的日期
    Date dt3 = dt1.addMonths(2);
    string str1 = dt3.toText("YYYY-MM-DD");

    //返回当月的最后一天日期
    Date dt4 = dt1.lastDay();
    string str2 = dt4.toText("YYYY-MM-DD");

    //设置日期
    dt1.setDate(2015,1,1,0,0,0);
    string str3 = dt1.toText("YYYY-MM-DD");
}



//针对blob类型的处理
void MyOci::get_blob()
{
    string sql = "select fea from feature";
    ResultSet* rs = stmt->executeQuery(sql);

    while (rs->next())
    {
        //读取blob字段
        Blob blob = rs->getBlob(1);
        oracle::occi::Stream*  m_stream = blob.getStream(1,0);
        int len = blob.length();

#if 1
        char* buffer = new char[len + 1];
        memset(buffer,'\0',len+1);
        m_stream->readBuffer(buffer,len);
#else
        char* buffer1 = new char[len + 1];
        memset(buffer1,'\0',len+1);
        m_stream->writeBuffer(buffer1,len);
#endif
        blob.closeStream(m_stream);
    }
}


//获取两个队列相同的数据
void MyOci::get_same_data()
{
    bool is_exit;
    for (int i = 1; i < 20; i ++)
    {
        for (int j = 5; j < 10; j ++)
        {
            if (i == j)
            {
                is_exit = TRUE;
                break;
            }
            else
            {
                is_exit = FALSE;
            }
        }

        if (is_exit)
        {
            cout<< i <<endl;
        }
    }
}


//获取数据库表的相关字段信息
void get_field_attribute()
{
/*    string sql = "select * from feature";
    Environment* env = Environment::createEnvironment();
    oracle::occi::Connection* conn = env->createConnection("用户名","密码","连接字符串");
    Statement* stmt = conn->createStatement();
    ResultSet rst = stmt->executeQuery(sql);

    vector<MetaData> vm = rst->getColumnListMetaData();
    map<std::string,int> field_info_map;
    for (int i =0; i < vm.size(); i ++)
    {
        //获取字段名称
        std::string name = vm[i].getString(MetaData::ATTR_NAME);
        field_info_map[name] = i + 1;

        //获取字段长度
        int len = vm[i].getInt(MetaData::ATTR_DATA_SIZE);

        //获取字段类型
        int type = vm[i].getInt(MetaData::ATTR_DATA_TYPE);
        switch (type)
        {
        case SQLT_DAT:
            cout<<":is date\n"; 
            break;
        case SQLT_NUM:
            cout<<":is number\n"; 
            break;
        case SQLT_CHR:
            cout<<":is varchar2\n";
            break;
        case SQLT_STR:
            cout<<":is SQLT_STR\n";
            break;
        case SQLT_LNG:
            cout<<":is SQLT_LNG\n";
            break;
        case SQLT_BLOB:
            cout<<":is SQLT_BLOB\n";
            break;
        case SQLT_INT:
            cout<<":is SQLT_INT\n";
            break;
        default:
            break;
        }

        //获取字段精度
        int precision = vm[i].getInt(MetaData::ATTR_PRECISION);

        //获取字段取值范围
        int scale = vm[i].getInt(MetaData::ATTR_SCALE);

        if(vm[i].getBoolean(MetaData::ATTR_IS_NULL))
        {
                //允许为空
        }
        else
        {
               //不允许为空
        }
    }

*/
}





void  MyOci::test()
{
 /*   int length = 10;
    int* a1 = new int[sizeof(int)*length];
    memset(a1,0,sizeof(int)*length);

    int* a2 = new int[sizeof(int)*length];
    memset(a1,0,sizeof(int)*length);

    int* a3 = new int[sizeof(int)*length];
    memset(a1,0,sizeof(int)*length);

    int* a4 = new int[sizeof(int)*length];
    memset(a1,0,sizeof(int)*length);

    ub2  *fld1Len = new ub2[length];
    memset(fld1Len,0,sizeof(ub2)*length);

    ub2  *fld2Len = new ub2[length];
    memset(fld2Len,0,sizeof(ub2)*length);

    ub2  *fld3Len = new ub2[length];
    memset(fld3Len,0,sizeof(ub2)*length);

    ub2  *fld4Len = new ub2[length];
    memset(fld4Len,0,sizeof(ub2)*length);


    char sql_str[1024] = {0};
    sprintf(sql_str,"INSERT INTO student \
                    (A, B, C, D) \
                    VALUES \
                    (:a,:b, :c, :d)");


    for (int i =0; i < 10; i++)
    {
        a1[i] = i;
        fld1Len[i] = sizeof(int);

        a2[i] = i;
        fld2Len[i] = sizeof(int);

        a3[i] = i;
        fld3Len[i] = sizeof(int);

        a4[i] = i;
        fld4Len[i] = sizeof(int);
    }

    for(int i =0; i < 10; i ++)
    {
        cout<<a1[i]<<" ";
        cout<<a2[i]<<" ";
        cout<<a3[i]<<" ";
        cout<<a4[i]<<" ";
        cout<<endl;
    }


    try
    {
        stmt->setAutoCommit(false);
        stmt = conn->createStatement(sql_str);

        //添加
        stmt->setMaxIterations(10);

        stmt->setDataBuffer(1,(dvoid*)a1,OCCIINT,sizeof(a1[0]),fld1Len);
        stmt->setDataBuffer(2,(dvoid*)a2,OCCIINT,sizeof(a2[0]),fld2Len);
        stmt->setDataBuffer(3,(dvoid*)a3,OCCIINT,sizeof(a3[0]),fld3Len);
        stmt->setDataBuffer(4,(dvoid*)a4,OCCIINT,sizeof(a4[0]),fld4Len);

        stmt->setBatchErrorMode (true);
        stmt->executeArrayUpdate(10);
        conn->commit();

        cout<<"插入成功!"<<endl;
    }
    catch(BatchSQLException & sqlExcp)
    {
        cout<<"插入失败！"<<endl;
    }
    catch(SQLException &sqlExcp)
    {
        cout<<"插入失败！"<<endl;
    }
    catch(exception &e)
    {
        cout<<"插入失败！"<<endl;
    }
    catch(...)
    {
        cout<<"插入失败！"<<endl;
    }
*/


    stmt->setSQL("INSERT INTO student(A,B) VALUES(:1, :2)"); 
    char fruit[][10] = { "Apples","Oranges","Bananas","Grapes" };   
    int int_arr[]={ 3,4,1,5 };
    ub2 fruitlen[4]; 
    ub2 intsize[4];   
    for(int i=0 ; i<4 ; i++)   
    {   
        intsize[i] = sizeof(int);   
        fruitlen[i] = strlen( fruit[i] ) + 1 ;
    }

    stmt->setDataBuffer(1, (dvoid*)int_arr, OCCIINT, sizeof(int), intsize);     
    stmt->setDataBuffer(2, (dvoid*)fruit, OCCI_SQLT_STR, 10,fruitlen);   

    stmt->executeArrayUpdate(4);   
    conn->commit();  
}
