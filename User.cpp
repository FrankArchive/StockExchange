#include"User.h"
#include"Stock.h"
#include"sockets.h"
using namespace std;
bool User::checkPwd(string p) { return p == password; }
bool User::editPwd(string p) { if (!examPwd(p))return false; password = p; return true; }
bool User::buy(std::string id, int amount) {
	if (stock_pool.pool.find(id) == stock_pool.pool.end())return false;//�޴˹�Ʊ
	Stock *target = &stock_pool.pool[id];//������Ѱַ
	if (target->stopped)return false;//��Ʊֹͣ����
	if (target->remaining < amount)return false;//�г��еĹ�Ʊ�����û����
	if (target->getCurrentPrice()*amount > balance)return false;//�˻�����
	target->remaining -= amount;
	owned_stocks[target->id] += amount;
	balance -= target->getCurrentPrice()*amount;

	stock_pool.writeBuffer(stock_pool.pool[id]);
	user_manager.writeBuffer(*this);
	return true;//����ɹ�
}
bool User::sell(std::string id, int amount) {
	if (stock_pool.pool.find(id) == stock_pool.pool.end())return false;//�޴˹�Ʊ
	Stock *target = &stock_pool.pool[id];
	if (target->stopped)return false;
	if (owned_stocks[id] < amount)return false;//�˻���û����ô���Ʊ����
	balance += target->getCurrentPrice()*amount;
	owned_stocks[id] -= amount;
	target->remaining += amount;
	if (owned_stocks[id] == 0)owned_stocks.erase(id);//�˻������޴����Ʊ

	stock_pool.writeBuffer(stock_pool.pool[id]);
	user_manager.writeBuffer(*this);//Ӧ˵��Ҫ��д����
	return true;//�����ɹ�
}
bool User::addStock(string id, string name, float init_price, int amount) {
	if (!is_admin)return false;
	vector<float>temp; temp.push_back(init_price);
	stock_pool.pool[id] = Stock(id, name, amount, temp);
	return true;
}
bool User::editStock(string id, string new_name, string new_id) {//�޸Ĺ�Ʊ������Ʊ����
	if (!is_admin)return false;
	if (stock_pool.pool.find(id) == stock_pool.pool.end())return false;//û�д���Ϊid�Ĺ�Ʊ
	stock_pool.pool[new_id] = stock_pool.pool[id];
	/*stock_pool.pool[new_id].id = new_id;
	stock_pool.pool[new_id].name = new_name;*/
	stock_pool.pool[new_id].changeIdName(new_id, new_name);
	return true;
}
bool User::toggleStock(std::string id) {
	if (!is_admin)return false;
	stock_pool.pool[id].stopped ^= 1;
	return true;
}
string User::toString() {
	string ret = username + ',' + password + ',' + char(is_admin + '0');
	for (unordered_map<string, int>::iterator i = owned_stocks.begin();
		i != owned_stocks.end(); i++)
		ret += ',' + i->first + ',' + to_string(i->second);
	ret += ';';
	return ret;
}