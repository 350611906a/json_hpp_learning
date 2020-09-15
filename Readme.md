# json.hpp版本json的读与写的学习  

## 1、使用方法

在linux下，要求gcc版本大于4.8.使用时，直接include"json.hpp"即可，不用包含任何库文件。使用起来及其方便。



## 2、读取文件方法  

要读的文件如下：

json_read.json:

```json
{
	"name":"zhangsan",
	"age":20,
	"happy":true,
	"persons":
	[
		"AAA",
		"BBB",
		"CCC"
	],
	"book":
	[
		"English",
		60
	],
	"student":
	{
		"name":"Bob",
		"ID":"123456",
		"age":18
	},
	"array":
	[
		{
			"weather": "hot"
		},
		{
			"name":"bill",
			"age":60
		},
		{
			"num":2,
			"points":
			[
				[1,2],
				[3,4]
			]
		}
	],
	"array1":
	{
		"www":
		{
			"Test": "test"
		}
	}

}
```

读取的方法：

```c++
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
```

读取结果的打印：

```shell
root@ubuntu:/code/json# ./main
name: zhangsan
age: 20
happy: 1
persons:
AAA
BBB
CCC
book: English  60

================对象===============
name: Bob
ID: 123456
age: 18

================数组对象===============
weather: hot
name: "bill"   age: 60
num: 2   points: 1  2  3  4
root@ubuntu:/code/json# g++ main.cpp -o main -std=c++11 -g
root@ubuntu:/code/json# ./main
name: zhangsan
age: 20
happy: 1
persons:
AAA
BBB
CCC
book: English  60

================对象===============
name: Bob
ID: 123456
age: 18

================数组对象===============
weather: hot
name: "bill"   age: 60
num: 2   points: 1  2  3  4

================对象对象===============
Test: "test"
```



## 3、写文件的方法

