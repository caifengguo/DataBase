#include "stdafx.h"
#include "mysql_t.h"
#include "TFileOption.h"
#include "Global.h"

MYSQL* mysql_t = 0;

bool mysql_connect_db(const char *host,
					  const char *user,
					  const char *passwd,
					  const char *db,
					  unsigned int port)
{
	mysql_t = mysql_init(NULL);

	if (!(mysql_real_connect(mysql_t,
		TFile_Option->mysql_host.c_str(),
		TFile_Option->mysql_user.c_str(),
		TFile_Option->mysql_pass.c_str(),
		TFile_Option->mysql_dbname.c_str(),
		TFile_Option->mysql_port,NULL, 0)))
	{
		mysql_close(mysql_t);
		return false;
	}

	mysql_query(mysql_t, "set names 'GBK'");

	return true;
}

void mysql_reset_user_score()
{
	mysql_query(mysql_t, "delete from player_statistics_data");
}

void mysql_gamer_addin(int userid)
{
	char sql[256] = {0};
	sprintf(sql, "update player_table set online = 1 where player_id = %d", userid);
	mysql_query(mysql_t, sql);
}

void mysql_gamer_exit(int userid)
{
	char sql[256] = {0};
	sprintf(sql, "update player_table set online = 0 where player_id = %d", userid);
	mysql_query(mysql_t, sql);
}

void mysql_gamer_query_detial(int userid, stGamePerson* pGamePerson)
{
	char sql[512] = {0};
	sprintf(sql, "select * from player_table "
		"left JOIN player_statistics_data on player_table.player_id=player_statistics_data.player_id "
	    "where player_table.player_id = %d", userid);
	mysql_query(mysql_t, sql);

	MYSQL_RES *result = mysql_store_result(mysql_t);

	MYSQL_ROW row;

	int i = 0;

	if ((row= mysql_fetch_row(result)) != NULL)
	{
		pGamePerson->id = atoi(row[0]);
		MByteToWChar(row[1], 64, pGamePerson->person);
		if (row[5])
			pGamePerson->month_winner = atoi(row[5]);
		if (row[9])
			pGamePerson->accu_score = atoi(row[9]);
		if (row[10])
			pGamePerson->count_game_number = atoi(row[10]);
		if (row[11])
			pGamePerson->count_m_number = atoi(row[11]);
		if (row[12])
			pGamePerson->count_m_win_number = atoi(row[12]);
		if (row[13])
			pGamePerson->count_j_number = atoi(row[13]);
		if (row[14])
			pGamePerson->count_j_win_number = atoi(row[14]);
		if (row[15])
			pGamePerson->count_s_number = atoi(row[15]);
		if (row[16])
			pGamePerson->count_s_win_number = atoi(row[16]);
	}

	mysql_free_result(result);
}

void mysql_update_user_score(const char* szGameId, SYSTEMTIME st, int nSeatNumber, const char* pszResult, stGamePerson* pGamePerson)
{
	char sql[512] = {0};
	sprintf(sql, "replace detail_table set "
		"game_number= '%s', game_date='%.2d-%.2d-%.2d %.2d:%.2d:%.2d', seat_number=%d, player_id=%d, player_identity=%d, game_result='%s', player_score=%d",
		szGameId, 
		st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond,
		nSeatNumber, pGamePerson->id, pGamePerson->gamer_type, pszResult, pGamePerson->current_score);
	mysql_query(mysql_t, sql);

	sprintf(sql, "replace player_statistics_data set "
		"player_id=%d, count_score=%d, count_game_number=%d, count_m_number=%d, count_m_win_number=%d, count_j_number=%d, count_j_win_number=%d, count_s_number=%d, count_s_win_number=%d",
		pGamePerson->id, pGamePerson->accu_score, pGamePerson->count_game_number, 
		pGamePerson->count_m_number, pGamePerson->count_m_win_number,
		pGamePerson->count_j_number, pGamePerson->count_j_win_number,
		pGamePerson->count_s_number, pGamePerson->count_s_win_number);
	mysql_query(mysql_t, sql);
}

void mysql_update_user_score(int nPlayerId, int nAccuScore)
{
	char sql[512] = {0};
	sprintf(sql, "replace player_table set player_id = %d, accu_score = %d",
		nPlayerId, nAccuScore);
	mysql_query(mysql_t, sql);
}

void mysql_update_user_score(const char* szGameId, SYSTEMTIME st, int nSeatNumber,int nPlayerId, int nPlayerType, const char* pszResult, int nScore)
{
	char sql[512] = {0};
	sprintf(sql, "replace detail_table set "
		    "game_number= '%s', game_date='%.2d-%.2d-%.2d %.2d:%.2d:%.2d', seat_number=%d, player_id=%d, player_identity=%d, game_result='%s', player_score=%d",
		    szGameId, 
			st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond,
			nSeatNumber, nPlayerId, nPlayerType, pszResult, nScore);
	mysql_query(mysql_t, sql);
}

void mysql_query_user_byname(HELE &m_hUserList, const wchar_t* uname)
{
	char asciiName[64] = {0};
	WCharToMByte(uname, sizeof(asciiName), asciiName);

	char sql[128] = {0};
	sprintf(sql, "select player_id, player_name from player_table where player_name like '%s%%'",asciiName);
	mysql_query(mysql_t, sql);

	MYSQL_RES *result = mysql_store_result(mysql_t);

	MYSQL_ROW row;

	int i = 0;

	while ((row= mysql_fetch_row(result)) != NULL)
	{
		wchar_t szUserId[32] = {0};
		wsprintf(szUserId, L"%d",atoi(row[0]));

		wchar_t szName[64] = {0};
		MByteToWChar(row[1], 64, szName);

		XList_AddItem(m_hUserList,L"");
		XList_SetItemText(m_hUserList,i,1,szUserId);
		XList_SetItemText(m_hUserList,i,2,szName);

		i++;
	}

	mysql_free_result(result);
}

void mysql_query_user_byname1(HELE &m_hUserList, const wchar_t* uname)
{
	char asciiName[64] = {0};
	WCharToMByte(uname, sizeof(asciiName), asciiName);

	char sql[512] = {0};
	sprintf(sql, "select player_table.player_id, player_table.player_name, player_statistics_data.count_score from player_table "
		"left JOIN player_statistics_data on player_table.player_id=player_statistics_data.player_id "
		"where player_table.player_name like '%s%%' order by player_statistics_data.count_score desc",asciiName);

	mysql_query(mysql_t, sql);

	MYSQL_RES *result = mysql_store_result(mysql_t);

	MYSQL_ROW row;

	int i = 0;

	while ((row= mysql_fetch_row(result)) != NULL)
	{
		wchar_t szUserId[32] = {0};
		wsprintf(szUserId, L"%d",atoi(row[0]));

		wchar_t szName[64] = {0};
		MByteToWChar(row[1], 64, szName);

		wchar_t szScore[32] = {0};
		if (row[2])
			wsprintf(szScore, L"%d",atoi(row[2]));

		
		XList_AddItem(m_hUserList,szUserId);
		XList_SetItemText(m_hUserList,i,1,szName);
		XList_SetItemText(m_hUserList,i,2,szScore);
		if (row[2])
			XList_SetItemText(m_hUserList,i,3,GetLevelByScore(atoi(row[2])));

		i++;
	}

	mysql_free_result(result);
}

void mysql_update_user_picture(int userid, const wchar_t* pic)
{
	return;

	FILE* fp = _wfopen(pic, _T("rb"));
	if (fp)
	{
		fseek(fp, 0, SEEK_END);
		int flen = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		char* icon = new char[flen+1];
		int size = fread(icon, 1, flen, fp);
		fclose(fp);

		char* chunk = new char[2*size+1];
		mysql_real_escape_string(mysql_t, chunk, icon, size);

		char* sql = new char[512+2*size+1];
		int len = sprintf(sql, "update player_table set image = '%s' where player_id = %d;",
			(char*)chunk, userid);
		int err = mysql_real_query(mysql_t, sql, len);

		int crr = mysql_errno(mysql_t);

		const char*errr = mysql_error(mysql_t);

		delete[] icon;
		delete[] chunk;
		delete[] sql;
	}
}

void mysql_store_picture_byid(int userid)
{
	char sql[128] = {0};
	sprintf(sql, "select image from player_table where player_id=%d",userid);
	mysql_query(mysql_t, sql);

	MYSQL_RES *result = mysql_store_result(mysql_t);
	if (mysql_num_rows(result) > 0)
	{
		MYSQL_ROW row = mysql_fetch_row(result);
		unsigned long *lengths = mysql_fetch_lengths(result);

		if (lengths[0] > 0)
		{
			wchar_t szFile[1024] = {0};
			wsprintf(szFile, _T("%s\\skin\\user\\%d.png"), g_szAppPath, userid);

			FILE* fp = _wfopen(szFile, _T("wb"));
			fwrite(row[0],1,lengths[0],fp);
			fclose(fp);
		}
		else
		{
			wchar_t srcFile[1024] = {0};
			wchar_t dstFile[1024] = {0};
			wsprintf(srcFile, _T("%s\\skin\\main\\gamer.png"), g_szAppPath);
			wsprintf(dstFile, _T("%s\\skin\\user\\%d.png"), g_szAppPath, userid);

			CopyFile(srcFile, dstFile, FALSE);
		}
	}
	else
	{
		wchar_t srcFile[1024] = {0};
		wchar_t dstFile[1024] = {0};
		wsprintf(srcFile, _T("%s\\skin\\main\\gamer.png"), g_szAppPath);
		wsprintf(dstFile, _T("%s\\skin\\user\\%d.png"), g_szAppPath, userid);

		CopyFile(srcFile, dstFile, FALSE);
	}
	mysql_free_result(result);
}

void mysql_update_user_name(int userid, const wchar_t* uname)
{
	char asciiName[64] = {0};
	WCharToMByte(uname, sizeof(asciiName), asciiName);

	char sql[128] = {0};
	sprintf(sql, "update player_table set player_name = '%s' where player_id=%d",asciiName, userid);
	mysql_query(mysql_t, sql);
}

void mysql_new_user(int userid, const wchar_t* uname, const wchar_t* pic)
{
	char asciiName[64] = {0};
	WCharToMByte(uname, sizeof(asciiName), asciiName);

	SYSTEMTIME st;
	GetLocalTime(&st);

	FILE* fp = _wfopen(pic, _T("rb"));
	if (fp)
	{
		fseek(fp, 0, SEEK_END);
		int flen = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		char* icon = new char[flen+1];
		int size = fread(icon, 1, flen, fp);
		fclose(fp);

		char* chunk = new char[2*size+1];
		mysql_real_escape_string(mysql_t, chunk, icon, size);

		char* sql = new char[512+2*size+1];
		int len = sprintf(sql, "insert into player_table(player_id, player_name, createtime, image, online, month_winner) "
			"values(%d, '%s', '%.2d-%.2d-%.2d %.2d:%.2d:%.2d', '%s', 0, 0)",
			userid, asciiName, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, 0, chunk);
		int err = mysql_real_query(mysql_t, sql, len);

		delete[] icon;
		delete[] chunk;
		delete[] sql;

		/*wchar_t dstFile[1024] = {0};
		wsprintf(dstFile, _T("%s\\skin\\user\\%d.png"), g_szAppPath, userid);
		CopyFile(pic, dstFile, FALSE);*/
	}
	else
	{
		char sql[512] = {0};
		int len = sprintf(sql, "insert into player_table(player_id, player_name, createtime, online, month_winner) "
			"values(%d, '%s', '%.2d-%.2d-%.2d %.2d:%.2d:%.2d', 0, 0)",
			userid, asciiName, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
		int err = mysql_real_query(mysql_t, sql, len);

		/*wchar_t srcFile[1024] = {0};
		wchar_t dstFile[1024] = {0};
		wsprintf(srcFile, _T("%s\\skin\\main\\gamer.png"), g_szAppPath);
		wsprintf(dstFile, _T("%s\\skin\\user\\%d.png"), g_szAppPath, userid);

		CopyFile(srcFile, dstFile, FALSE);*/
	}

	char pssql[512] = {0};
	int len = sprintf(pssql, "insert into player_statistics_data values(%d,0,0,0,0,0,0,0,0)",userid);
	int err = mysql_real_query(mysql_t, pssql, len);
}

void mysql_del_user(int userid)
{
	char sql[128] = {0};

	sprintf(sql, "delete from player_table where player_id=%d",userid);
	mysql_query(mysql_t, sql);

	sprintf(sql, "delete from player_statistics_data where player_id=%d",userid);
	mysql_query(mysql_t, sql);
}

int mysql_get_seqno()
{
	int nSeqNo = -1;

	mysql_query(mysql_t, "UPDATE sequence SET SEQ_NO=LAST_INSERT_ID(SEQ_NO+1)");
	mysql_query(mysql_t, "select LAST_INSERT_ID()");

	MYSQL_RES *result = mysql_store_result(mysql_t);

	MYSQL_ROW row;

	if ((row= mysql_fetch_row(result)) != NULL)
	{
		nSeqNo = atoi(row[0]);
	}

	mysql_free_result(result);

	return nSeqNo;
}

void mysql_query_user_list(HELE &m_hUserList, const char* bgnDate, const char* endDate)
{
	char sql[1024] = {0};
	sprintf(sql, "select p.player_id, p.player_name, s.count_score " \
		"from player_table p, player_statistics_data s, detail_table d "\
		"where p.player_id = s.player_id and s.player_id = d.player_id "\
		"and d.game_date >= '%s' and d.game_date <= '%s' order by s.count_score desc", bgnDate, endDate);

	mysql_query(mysql_t, sql);

	MYSQL_RES *result = mysql_store_result(mysql_t);

	MYSQL_ROW row;

	int i = -1;

	while ((row= mysql_fetch_row(result)) != NULL)
	{
		wchar_t szUserId[32] = {0};
		wsprintf(szUserId, L"%d",atoi(row[0]));

		wchar_t szName[64] = {0};
		MByteToWChar(row[1], 64, szName);

		wchar_t szScore[32] = {0};
		if (row[2])
			wsprintf(szScore, L"%d",atoi(row[2]));

		int j = 0;
		bool bFound = false;

		for (j = 0; j < XList_GetItemCount(m_hUserList); j++)
		{
			if (wcscmp(szUserId, XList_GetItemText(m_hUserList,j,4)) == 0)
			{
				bFound = true;
				break;
			}
		}

		if (!bFound)
		{
			i++;
			wchar_t szIndex[32] = {0};
			wsprintf(szIndex, L"%d",i);
			XList_AddItem(m_hUserList,szIndex);
			XList_SetItemText(m_hUserList,i,1,szName);
			XList_SetItemText(m_hUserList,i,2,szScore);
			XList_SetItemText(m_hUserList,i,3,_T("1"));
			XList_SetItemText(m_hUserList,i,4,szUserId);
		}
		else
		{
			wchar_t szGameCount[32] = {0};
			wsprintf(szGameCount, _T("%d"), _wtoi(XList_GetItemText(m_hUserList,j,4))+1);
			XList_SetItemText(m_hUserList,i,3,szGameCount);
		}
	}

	mysql_free_result(result);
}