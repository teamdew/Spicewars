#ifndef REST_QUERY_H
#define REST_QUERY_H

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <curl/curl.h>
#include <iostream>
#include <sstream>
#include <ctime>
#include <jsoncpp/json/json.h>
#include <fstream>
#include <cstring>
#include <ctime>
#include <boost/algorithm/string.hpp>
#include <vector>

#define COMMUNITY 4
#define DESKTOP 6

using namespace std;

typedef struct {
	char *buf;
	int len;
	int pos;
} readarg_t;

struct version_data{
	int id;
	string name;
	string due_date;
	string status;
	string updated_on;
	version_data():id(0),name("")
	{}
} ;

class Rest{

       
			public:
								Rest();
								~Rest();
								int rest_query(int project_num);    

								string community_count;
								string desktop_count;
                
       private:
                CURL *curl;

								void pretty_print (string jsontext);
								//static size_t write_data(char *ptr, size_t size, size_t nmemb, void *userdata);
								Json::Value json_code(string jsontext, string query_text);
								void get_versions(string jsontext,string* version_names);
								
};
#endif
