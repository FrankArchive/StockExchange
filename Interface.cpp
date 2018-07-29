#include "Interface.h"
#include"SuperUser.h"
#include"User.h"
#include"Stock.h"
#include"sockets.h"
using namespace std;

void Interface::suLogin() {
	system("cls");
	printf("����su����:");
	string pwd; pwd = readPassword();
	if (pwd != "1234567890") {
		printf("���벻��ȷ������������");
		return;
	}
	char f = 0;
	SuperUser instance;
	
	while(1){
		system("cls");
		printf("�ѵ�¼su\n");
		f = 0;
		printf("1.������Ʊ�۸�\n2.ɾ���û�\n3.�޸��û����\n4.����\n");
		printf("����������:");
		while (!isalnum(f))f = getchar();
		while (f<'1' || f>'4') { printf("��������ȷ����:"); getchar(); f = getchar(); }
		string buffer1; float buffer3;
		switch (f) {
		case '1'://������Ʊ�۸�
			printf("�������Ʊ����:"); getchar();
			cin >> buffer1;
			printf("�������޸ĺ�۸�:"); 
			cin >> buffer3;
			if (instance.setStockPrice(buffer1, buffer3))printf("�ɹ�\n");
			else printf("ʧ��\n");
			break;
		case '2'://ɾ���û�
			printf("������Ҫɾ�����û���:");
			cin >> buffer1;
			if(instance.deleteUser(buffer1))printf("�ɹ�\n");
			else printf("ʧ�ܣ�����û�д��û�\n");
			break;
		case '3':
			printf("�����û���:"); cin >> buffer1;
			printf("�������:"); cin >> buffer3;
			if (instance.setBalance(buffer1, buffer3))printf("�ɹ�\n");
			else printf("���޴��û�\n");
			break;
		case '4':
			return;
		}
		system("pause");
	}
}

void Interface::userLogin() {
	string username, password; char f = 0;
	printf("�������û���:"); cin >> username;
	User *target = user_manager.getUser(username);
	printf("����������:"); password = readPassword();
	if (target->checkPwd(password) == false) {
		printf("���������������");
		return;
	}
	while (1) {
		system("cls");
		f = 0;
		printf("�ѵ�¼%s\n", username.c_str());
		printf("1.�޸�����\n2.��ѯ��Ʊ\n3.�����Ʊ\n4.������Ʊ\n5.����\n");
		printf("����Ա��Ϊ��\n6.��ӹ�Ʊ\n7.�޸Ĺ�Ʊ���롢����\n8.�л���Ʊͣ�ۡ�����״̬\n");
		printf("������һ��ָ��:");
		while (!isalnum(f))f = getchar();
		while (f<'1' || f>'8') { printf("��������ȷ����:"); getchar(); f = getchar(); }
		string buffer1, buffer2, buffer5; float buffer3; int buffer4;
		switch (f) {
		case '1'://�޸�����
			printf("������������:"); cin >> password;
			if (target->editPwd(password))printf("�ɹ�\n");
			else printf("ʧ�ܣ����벻����Ҫ��\n");
			break;
		case '2'://��ѯ��Ʊ
			query();
			break;

		case '3'://�����Ʊ
			printf("�����Ʊ����:"); cin >> buffer1;
			printf("���빺������:"); cin >> buffer4;
			if (target->buy(buffer1, buffer4))printf("����ɹ�\n");
			else printf("����ʧ�ܣ������¼��ֿ��ܣ�\n��Ʊ��������\n��Ʊ�رս���\n����\n�г��й�Ʊ����\n");
			break;
		case '4'://���۹�Ʊ
			printf("�����Ʊ����"); cin >> buffer1;
			printf("�����������:"); cin >> buffer4;
			if (target->sell(buffer1, buffer4))printf("���۳ɹ�\n");
			else printf("����ʧ�ܣ������¼��ֿ��ܣ�\n��Ʊ��������\n��Ʊ�رս���\nӵ�й�Ʊ����\n");
			break;

		case '5':return;//����

		case '6'://������Ʊ
			printf("�¹�Ʊ����:"); cin >> buffer1;
			printf("�¹�Ʊ����:"); cin >> buffer2;
			printf("�׷��۸�:"); cin >> buffer3;
			printf("��������:"); cin >> buffer4;
			if (target->addStock(buffer1, buffer2, buffer3, buffer4))
				printf("�ɹ�\n");
			else printf("�û����ǹ���Ա������ʧ��\n");
			break;

		case '7'://�޸Ĺ�Ʊ
			printf("��Ʊ����:"); cin >> buffer1;
			printf("��Ʊ�´���(������Ϊ���޸�):"); cin >> buffer2;
			printf("��Ʊ������(�����޸�):"); cin >> buffer5;
			if (buffer2.size() == 0)buffer2 = buffer1;
			if (buffer5.size() == 0) {
				printf("�������\n");
				break;
			}
			if (target->editStock(buffer1, buffer5, buffer2))
				printf("�ɹ�\n");
			else printf("�û����ǹ���Ա������ʧ��\n");
			break;
		case '8'://�л�״̬
			printf("��Ʊ����:"); cin >> buffer1;
			if (target->toggleStock(buffer1))
				printf("�ɹ�\n");
			else printf("�û����ǹ���Ա������ʧ��\n");
			break;
		}
		system("pause");
	}
}

void Interface::addUser() {
	string username, password;
	SuperUser inst;
	printf("�������û���:");
	cin >> username;
	printf("����������:");
	cin >> password;
	printf("�ǹ���Աô��(y/n)"); getchar(); char c = getchar(); getchar();
	if (c == 'y') {
		printf("su����:");
		string pwd = readPassword();
		if (pwd != "1234567890") {
			printf("su�������\n");
			return;
		}
	}
	inst.addUser(username, password, c == 'y' ? 1 : 0);
}

void Interface::query() {
	system("cls");
	printf("��ӭ������ѯϵͳ\n");
	string id, name;
	printf("�������Ʊ���루���Բ�������:"); cin >> id;
	vector<Stock*>list;
	for (unordered_map<std::string, Stock>::iterator i = stock_pool.pool.begin();
		i != stock_pool.pool.end(); i++)
		if (i->second.id.find(id) == 0)list.push_back(&i->second);//�ҳ����й�Ʊ������id��ͷ�Ĺ�Ʊ
	
	if (list.size() == 0) {
		printf("δ�ҵ��κι�Ʊ��Ϣ\n");
		return;
	}
	printf("�ҵ������й�Ʊ:\n");
	for (int i = 0; i < list.size(); i++) 
		printf("%d . %s\n", i + 1, list[i]->name.c_str());
	printf("��ѡ���Ʊ:");
	int n = 0; cin >> n;

	printTable(list[n - 1]);
}

void Interface::printTable(Stock *i){
	printf("---------------------------�۸�����ͼ-----------------------------\n");
	vector<float>temp = i->price_log;
	float max_price=0, min_price=99999999.9f;
	for (int i = 0; i < temp.size(); i++) {
		if (temp[i] < min_price)min_price = temp[i];
		if (temp[i] > max_price)max_price = temp[i];
	}
	int cnt = 0;
	for (float i = max_price; i >= min_price-0.3; i -= 0.1) {
		if (cnt++ % 4 == 0)cout << setiosflags(ios::right) << setw(3) << i << setw(1) << '|';
		else cout << setw(4) << '|';
		for (int j = 0; j < temp.size(); j++)
			if (temp[j] - i < 0.001&&temp[j]-i>-0.001)cout << setiosflags(ios::right) << setw(3 * j+1) << "*";
		cout << '\n';
	}
	printf("---");
	for (int i = 0; i < temp.size(); i++)printf("---");
	printf("\n");
	cout << "day 1";
	for (int i = 2; i <= temp.size(); i++)
		cout << setiosflags(ios::right) << setw(3) << i;
	printf("\n\n\n\n\n\n\n");
}

Interface::Interface() {
	char f = 0;
	system("cls");
	printf("\n\n\n\n\n**********************WELCOME!***********************\n\n\n\n\n\n");
	printf("*********TO STOCK EXCHANGE SIMULATION PROGRAM!***********\n\n\n\n");
	printf("��ѡ����:\n1.�����û���½\n2.��½�˻�\n3.ע���û�\n");
	printf("����������:");
	while (!isalnum(f))f = getchar();
	while (f<'1' || f>'3') { printf("��������Ч����:"); getchar(); f = getchar(); }
	getchar();
	switch (f) {
	case '1':suLogin(); break;
	case '2':userLogin(); break;
	case '3':addUser(); break;
	}
}

Interface::~Interface() {
	user_manager.fullUpdate();
	stock_pool.fullUpdate();
}
