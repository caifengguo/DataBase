#ifndef MYSQL_T_H
#define MYSQL_T_H

#include "mysql.h"
#pragma comment(lib, "libmysql.lib")

struct stGamePerson;

extern MYSQL* mysql_t;

bool mysql_connect_db(const char *host,
				   const char *user,
				   const char *passwd,
				   const char *db,
				   unsigned int port);

void mysql_reset_user_score();

void mysql_gamer_addin(int userid);

void mysql_gamer_exit(int userid);

void mysql_gamer_query_detial(int userid, stGamePerson*);

void mysql_update_user_score(const char* szGameId, SYSTEMTIME st, int nSeatNumber, const char* pszResult, stGamePerson*);

void mysql_update_user_score(int nPlayerId, int nAccuScore);

void mysql_update_user_score(const char* szGameId, SYSTEMTIME st, int nSeatNumber,int nPlayerId, int nPlayerType, const char* pszResult, int nScore);

void mysql_query_user_byname(HELE &m_hUserList, const wchar_t* uname);

void mysql_query_user_byname1(HELE &m_hUserList, const wchar_t* uname);

void mysql_store_picture_byid(int userid);

void mysql_update_user_picture(int userid, const wchar_t* pic);

void mysql_update_user_name(int userid, const wchar_t* uname);

void mysql_new_user(int userid, const wchar_t* uname, const wchar_t* pic);

void mysql_del_user(int userid);

int mysql_get_seqno();

void mysql_query_user_list(HELE &m_hUserList, const char* bgnDate, const char* endDate);

#endif