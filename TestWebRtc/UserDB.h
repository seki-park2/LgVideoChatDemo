#ifndef _USER_DB_H_
#define _USER_DB_H_


#include <mutex>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <openssl/sha.h>
#include <sstream>

class CUserDB
{
public:
	CUserDB();
	~CUserDB();

	int CreateTable();
	int RegisterUserId(std::string& unique_id, std::string& passwd, std::string& username, std::string& email, std::string& phone, std::string& address, uint64_t utc);
	int GetUserInfo(std::string& unique_id, std::string& username, std::string& email, std::string& phone, std::string& address);
	int DeleteUserId(std::string& unique_id);
	int CountUserId(std::string& id);
	int GetUserPasswd(std::string& id, std::string& passwd);
	std::string saltStr(const std::string str);
	std::string sha256(const std::string str);
	int ClearWrongPasswdCnt(std::string& id);
	int IncreaseWrongPasswdCnt(std::string& id);
	int GetWrongPasswdCnt(std::string& id);
	int UpdateWrongPasswdLockTime(std::string& id, uint64_t utc_time);
	uint64_t GetWrongPasswdLockTime(std::string& id);

private:
	sql::Driver* driver;
	sql::Connection* con;
	std::mutex mMutex;
};



#endif