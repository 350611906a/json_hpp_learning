#include<iostream>
#include<fstream>
#include "json.hpp"
#include<iomanip>

using namespace std;
using json=nlohmann::json;

int main()
{
	json js;
	ifstream ifs("./json_read.json");
	if(!ifs.is_open())
	{
		cout<<"open json failed"<<endl;
		return -1;
	}
	ifs>>js;
	ifs.close();
	string str = js["name"].get<string>();
	cout<<"name: "<<str<<endl;
	int age = js["age"].get<int>();
	cout<<"age: "<<age<<endl;
	bool happy = js["happy"].get<bool>();
	cout<<"happy: "<<happy<<endl;
	
	//数组1
	cout<<"persons:"<<endl;
	for(int i = 0; i < js["persons"].size(); ++i)
	{
		cout<<js["persons"][i].get<string>()<<endl;		
	}
	
	//数组2
	cout<<"book: "<<js["book"][0].get<string>()<<"  "<<js["book"][1].get<int>()<<endl;
	
	//对象
	cout<<"\n================对象==============="<<endl;
	str = js["student"]["name"].get<string>();
	cout<<"name: "<<str<<endl;
	str = js["student"]["ID"].get<string>();
	cout<<"ID: "<<str<<endl;
	age = js["student"]["age"].get<int>();
	cout<<"age: "<<age<<endl;
	
	//数组对象
	cout<<"\n================数组对象==============="<<endl;
	str = js["array"][0]["weather"].get<string>();
	cout<<"weather: "<<str<<endl;
	cout<<"name: "<<js["array"][1]["name"]<<"   "<<"age: "<<js["array"][1]["age"]<<endl;
	cout<<"num: "<<js["array"][2]["num"]<<"   "<<"points: "<<js["array"][2]["points"][0][0]<<"  "<<js["array"][2]["points"][0][1]<<"  "<<js["array"][2]["points"][1][0]<<"  "<<js["array"][2]["points"][1][1]<<endl;
	
	//对象对象
	cout<<"\n================对象对象==============="<<endl;
	json obj = js.at("array1").at("www");   //使用at的方式求取，上面的也可以进行这样的修改。
	cout<<"Test: "<<obj["Test"]<<endl;
	
	return 0;
}
