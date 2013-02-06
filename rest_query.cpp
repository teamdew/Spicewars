#include "rest_query.h"

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <curl/curl.h>
#include <iostream>
#include <sstream>
#include <ctime>
#include <jsoncpp/json.h>
#include <fstream>
#include <cstring>
#include <ctime>
#include <boost/algorithm/string.hpp>
#include <vector>



using namespace std;

char * buffer;
stringstream stream;

static size_t write_data(char *ptr, size_t size, size_t nmemb, void *userdata){
	stringstream *ss = (stringstream*) userdata;
	size_t count = size * nmemb;
	ss->write(ptr, count);
	return count;
}

Rest::Rest(){
	  curl = curl_easy_init();	
		 community_count = "issues.json?project_id=3&&status_id=open";
		 desktop_count = "issues.json?project_id=6&&status_id=open";
       
}

Rest::~Rest(){
	curl_easy_cleanup(curl);	
}


void Rest::pretty_print (string jsontext){
	Json::Value root;
	Json::Reader reader;
	bool parsed = reader.parse(jsontext, root, false);
	if(not parsed){
		cout<<"Failed to parse correctly, no pretty print."<<endl;
	}
	cout<<"Now printing all of Json in pretty print:" <<endl<<root.toStyledString();

}


Json::Value Rest::json_code(string jsontext, string query_text)
{
	Json::Value root;
	Json::Reader reader;

	//ifstream myfile;
	//myfile.open("output.text")
	bool parsed = reader.parse(jsontext, root, false);
	if(not parsed){
		cout<<"Failed to parse correctly, never!"
				//<<reader.getFormattedErrorMessage()
				<<endl;
	}
	Json::Value count_num = root[query_text];
	return count_num;
	//cout<< count_num << endl<<endl;
	//cout<<"Now printing all of Json in pretty print" <<endl<<root.toStyledString();
}


void Rest::get_versions(string jsontext,string* version_names){
	Json::Value root;
	Json::Reader reader;
	time_t sec;
	time(&sec);
	tm* ptr=localtime(&sec);
	version_data vers;
	//int month = (short) ptr->tm_mon +1;
	//int day = (short) ptr->tm_mday;
	//int year = (short) ptr->tm_year + 1900;

	int month = 10;
	int day = 8;
	int year = 2012;
	int vers_month,vers_day,vers_year;
	int begin_month, end_month;
	bool parsed = reader.parse(jsontext, root, false);
	if(!parsed){
		cout<<"Failed to parse correctly, never!"	<<endl;
	}		

	Json::Value versions = root["versions"];
	vector<string> splitstr;
	vector<version_data> valid_dates;
	version_names = new string[versions.size()];

	for (int index = 0; index < versions.size(); ++index )  {// Iterates over the sequence elements.
		if (versions[index]["status"].asString().compare("closed")!=0) {
			if(versions[index]["due_date"].asString().length()!=0){
				string vers_due_date = versions[index]["due_date"].asString();
		    boost::split(splitstr, vers_due_date, boost::is_any_of("-"));
				vers_month = atoi(splitstr[1].c_str());
				vers_day = atoi(splitstr[2].c_str());
				vers_year = atoi(splitstr[0].c_str());
				if(vers_year==year || vers_year==year+1){
					if(month==11||month==12) {
						begin_month = month;
						end_month = month-10;
						if((vers_month>=begin_month && vers_month<=12) || (vers_month>=1 && vers_month<=end_month)){
							version_data vers;
							
							vers.due_date = versions[index]["due_date"].asString(); //<<---- here!
							vers.name = versions[index]["name"].asString();
							vers.id = versions[index]["id"].asInt();
							vers.status = versions[index]["status"].asString();

							valid_dates.push_back(vers);
						}
					}
				else {
						begin_month = month;
						end_month = month+2;
						if(begin_month <= vers_month && end_month >= vers_month) {
							version_data vers;
							vers.due_date = versions[index]["due_date"].asString(); //<<---- here!
							vers.name = versions[index]["name"].asString();
							vers.id = versions[index]["id"].asInt();
							vers.status = versions[index]["status"].asString();
							valid_dates.push_back(vers);
						}
					
				}
			}
			

//			cout<<versions[index]["due_date"].asString()<<" "<< versions[index]["status"]<<versions[index]["name"]<<endl;
			}

		}
	}		
		for(vector<version_data>::size_type i=0 ;i < valid_dates.size(); ++i) {
			cout<<valid_dates.at(i).id<<endl;
		}
//			int begin_month,end_month;
//			int vers_month = atoi(parsed[1].c_str());
//			int vers_year = atoi(parsed[0].c_str());
//			int vers_day = atoi(parsed[2].c_str());

}

int Rest::rest_query(int project_num) {
	string url = "https://redmine-test.spice.spiceworks.com/";
	string sub_url;
	struct curl_slist* headers = NULL;
	struct curl_httppost* post = NULL;
	struct curl_httppost* last = NULL;
	struct tm *ptr;
	

	if (project_num == DESKTOP) sub_url = Rest::desktop_count;
	if (project_num == COMMUNITY) sub_url = Rest::community_count;
	url=url+sub_url;
	cout<< Rest::desktop_count;

	string* community_versions;
  long http_code;
	time_t rawtime;
	time (&rawtime);
	ctime(&rawtime);

	
  if(curl) {
		curl_easy_setopt(curl,CURLOPT_SSL_VERIFYPEER, 0);
   	curl_easy_setopt(curl,CURLOPT_HTTPGET,1);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &stream);
		//curl_easy_setopt(curl, CURLOPT_READFUNCTION, readcb);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		headers=curl_slist_append(headers, "Content-Type: application/json");
		headers=curl_slist_append(headers, "X-Redmine-API-Key:715a92bb9424b9c422dad6662482b6540aff4eed");
		curl_formadd(&post,&last,
		CURLFORM_CONTENTHEADER,headers,CURLFORM_END);
		curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
		
		cout<<"http code:"<< http_code<<"!!"<<endl;
		Json::Value t_count =	json_code(stream.str(),"total_count");
//		pretty_print(stream.str());
//    cout << t_count;		
//		get_versions(stream.str(),community_versions);
    
		return t_count.asInt();
	}
}


int main(int argc, char *argv[]) {
  //string default_url = "issues.json";
	string project_url = "projects/desktop/versions.json";
	string community_count = "issues.json?project_id=3&&status_id=open";
	string desktop_count = "issues.json?project_id=3&&status_id=open";
	Rest rest_q;
	//rest_q.curl_code(project_url);
	
	cout<<rest_q.rest_query(DESKTOP)<<endl;
}
	

