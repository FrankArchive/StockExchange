#pragma once
#include "public_header.h"

//format: "id,name,float,...;"
struct Stock {
	std::string id, name; int remaining;
	bool stopped;//�Ƿ�ֹͣ����
	std::vector<float>price_log;//���飬��¼����ʷ�۸�
	Stock() { stopped = 0; }
	Stock(std::string id, std::string n, int a, std::vector<float> p) :id(id), name(n), remaining(a), price_log(p) { stopped = 0; }
	float getCurrentPrice();                                                                                                           //��ǰ�۸�
	float getHistoryPrice(int days_cnt);                                                                                         //����days_cnt��ǰ�۸�
	float getRise();
	void changeIdName(std::string i, std::string n);
	std::string toString();
};