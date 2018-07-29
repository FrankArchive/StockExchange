#pragma once
#include<cstdlib>
#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<conio.h>
#include<iomanip>

//=======================tools============================

//��������Ƿ����Ҫ��
bool examPwd(std::string);
//�ָ�ַ���
std::vector<std::string> parse(char a, std::string word);
//�޻��Զ�����
std::string readPassword();
//base64����������
static const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";


static inline bool is_base64(unsigned char c);
std::string base64_encode(char const* bytes_to_encode, unsigned int in_len);
std::string base64_decode(std::string const& encoded_string);

//���ļ�����������
std::string readAll(FILE *f);