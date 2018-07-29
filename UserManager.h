#pragma once
#include "public_header.h"
class UserManager {
	std::unordered_map<std::string, class User> pool;
	FILE *user_info, *buffer;
	void readFromString(std::string &temp);
public:
	UserManager();

	User *getUser(std::string username);
	bool addUser(std::string username, std::string password, bool isAdmin);
	bool deleteUser(std::string username);
	
	void fullUpdate();//�������´洢�ļ�������洢��
	void readBuffer();//�ӻ����й��ϻָ�
	void writeBuffer(User a);//д�뻺��

	~UserManager();
};