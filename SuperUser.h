#pragma once
#include"public_header.h"
//su����:1234567890
class SuperUser {
public:
	//���õ��ռ۸�,�޷��޸���ʷ�۸�
	bool setStockPrice(std::string id, float p);
	//ע��
	class User *addUser(std::string username, std::string password, bool isAdmin);
	//�����û����
	bool setBalance(std::string username, float b);
	//ɾ���û�
	bool deleteUser(std::string username);
};