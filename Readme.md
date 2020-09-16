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

### 1、第一种格式

写入如下格式的json文件：

```json
{
    "answer": {
        "everything": 42
    },
    "happy": true,
    "list": [
        1,
        2,
        3
    ],
    "name": "Niels",
    "nothing": 0,
    "object": {
        "currency": "USD",
        "value": 42.99
    },
    "pi": 3.14
}
```

代码如下：

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
	js["answer"]["everything"] = 42;
	js["happy"] = true;
	js["list"] = {1, 2, 3};
	js["name"] = "Niels";
	js["nothing"] = NULL;
	js["object"]["currency"] = "USD";
	js["object"]["value"] = 42.99;
	js["pi"] = 3.14;
	
	ofstream out("write_1.json");
	if(!out.is_open())
	{
		cout<<"open write file failed"<<endl;
		return -1;
	}
	
	out<<setw(4)<<js;
	out.close();
	
	return 0;	
}
```

保存如下：

```json
root@ubuntu:/code/json# cat write_1.json 
{
    "answer": {
        "everything": 42
    },
    "happy": true,
    "list": [
        1,
        2,
        3
    ],
    "name": "Niels",
    "nothing": 0,
    "object": {
        "currency": "USD",
        "value": 42.99
    },
    "pi": 3.14
}
```



### 2、第二种格式

写入如下json格式的文件：

```json
{
    "devices": [
        {
            "appVerifiCode": "",
            "appVersion": "",
            "bindInfo": "1234567890",
            "bsn": "",
            "checkVersion": "V2.0005.0870737.0.R",
            "macAddress": "",
            "sn": "snsnsnsnsnns",
            "versionList": [
                {
                    "keyId": "1111111111",
                    "version": "1554"
                }
            ]
        }
    ]
}
```

代码如下：

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
	js["devices"][0]["appVerifiCode"] = "";
	js["devices"][0]["appVersion"] = "";
	js["devices"][0]["bindInfo"] = "1234567890";
	js["devices"][0]["bsn"] = "";
	js["devices"][0]["checkVersion"] = "V2.0005.0870737.0.R";
	js["devices"][0]["macAddress"] = "";
	js["devices"][0]["sn"] = "snsnsnsnsnns";
	js["devices"][0]["versionList"][0] = {{"keyId", "1111111111"}, {"version", "1554"}};
	
	ofstream out("write_2.json");
	if(!out.is_open())
	{
		cout<<"open write file failed"<<endl;
		return -1;
	}
	
	out<<setw(4)<<js;
	
	return 0;
}
```

保存的文件结果：

```json
root@ubuntu:/code/json# cat write_2.json 
{
    "devices": [
        {
            "appVerifiCode": "",
            "appVersion": "",
            "bindInfo": "1234567890",
            "bsn": "",
            "checkVersion": "V2.0005.0870737.0.R",
            "macAddress": "",
            "sn": "snsnsnsnsnns",
            "versionList": [
                {
                    "keyId": "1111111111",
                    "version": "1554"
                }
            ]
        }
    ]
}
```



### 3、第三种方法

写入如下文件：

```json
{
    "detect_area": {
        "point_num": 4,
        "points": [
            [
                1,
                1
            ],
            [
                1023,
                1
            ],
            [
                1023,
                1023
            ],
            [
                1,
                1023
            ]
        ]
    },
    "fps": 12,
    "pic_info": {
        "height": 480,
        "width": 640
    },
    "sensith": 90,
    "video_file": {
        "video_name": [
            "640_480.yuv",
            "a.yuv",
            "b.yuv"
        ],
        "video_num": 3
    }
}
```

代码如下：

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
	js["detect_area"]["point_num"] = 4;
	js["detect_area"]["points"][0] = {1, 1};
	js["detect_area"]["points"][1] = {1023, 1};
	js["detect_area"]["points"][2] = {1023, 1023};
	js["detect_area"]["points"][3] = {1, 1023};
	js["fps"] = 12;
	js["pic_info"]["height"] = 480;
	js["pic_info"]["width"] = 640;
	js["sensith"] = 90;
	js["video_file"]["video_num"] = 3;
	js["video_file"]["video_name"] = {"640_480.yuv", "a.yuv", "b.yuv"};
	
	
	ofstream out("write_3.json");
	if(!out.is_open())
	{
		cout<<"open write file failed"<<endl;
		return -1;
	}
	
	out<<setw(4)<<js;
	
	return 0;
}
```

文件保存如下：

```json
root@ubuntu:/code/json# cat write_3.json 
{
    "detect_area": {
        "point_num": 4,
        "points": [
            [
                1,
                1
            ],
            [
                1023,
                1
            ],
            [
                1023,
                1023
            ],
            [
                1,
                1023
            ]
        ]
    },
    "fps": 12,
    "pic_info": {
        "height": 480,
        "width": 640
    },
    "sensith": 90,
    "video_file": {
        "video_name": [
            "640_480.yuv",
            "a.yuv",
            "b.yuv"
        ],
        "video_num": 3
    }
}
```

