/*
[
12,
12.34,
true,
"tom",
["jack", "ace", "robin"],
{"sex":"man", "girlfriend":"lucy"}
]
*/

#include<iostream>
#include<json/json.h>
#include <fstream>

using namespace std;
using namespace Json;

void writeJson()
{
	// �����������鿴��һ��Value
	// ������Value���󴴽�
	Value root;
	// Value��һ������Ϊint �еĹ��캯��
	root.append(12);	// ����������ʽ����ת��
	root.append(12.34);
	root.append(true);
	root.append("tom");

	// ��������ʼ��һ��������
	Value subArray;
	subArray.append("jack");
	subArray.append("ace");
	subArray.append("robin");
	root.append(subArray);

	// ��������ʼ���Ӷ���
	Value subObj;
	subObj["sex"] = "woman";  // ��Ӽ�ֵ��
	subObj["girlfriend"] = "lucy";
	root.append(subObj);

	// ���л�
#if 1
	// �и�ʽ���ַ���
	string str = root.toStyledString();
#else
	FastWriter f;
	string str = f.write(root);
#endif
	// �����л����ַ���д�����ļ�
	ofstream ofs("test.json");
	ofs << str;
	ofs.close();
}

void readJson()
{
	// 1. �������ļ��е�json�ַ������������ļ�
	ifstream ifs("test.json");
	// 2. �����л� -> value����
	Value root;
	Reader r;
	r.parse(ifs, root);
	// 3. ��value�����н��������ζ���
	if (root.isArray())
	{
		// ����, ��������
		for (int i = 0; i < root.size(); ++i)
		{
			// ����ȡ������Ԫ��, ������value����
			Value item = root[i];
			// �ж�item�д洢�����ݵ�����
			if (item.isString())
			{
				cout << item.asString() << ", ";
			}
			else if (item.isInt())
			{
				cout << item.asInt() << ", ";
			}
			else if (item.isBool())
			{
				cout << item.asBool() << ", ";
			}
			else if (item.isDouble())
			{
				cout << item.asFloat() << ", ";
			}
			else if (item.isArray())
			{
				for (int j = 0; j < item.size(); ++j)
				{
					cout << item[j].asString() << ", ";
				}
			}
			else if (item.isObject())
			{
				// ����
				// �õ����е�key
				Value::Members keys = item.getMemberNames();
				for (int k = 0; k < keys.size(); ++k)
				{
					cout << keys.at(k) << ":" << item[keys[k]] << ", ";
				}
			}
		}
		cout << endl;
	}
}


int main()
{
	writeJson();
	readJson();
}
