
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

using namespace std;

char * buffer;
stringstream stream;

typedef struct {
	char *buf;
	int len;
	int pos;
} readarg_t;

static size_t write_data(char *ptr, size_t size, size_t nmemb, void *userdata){
	stringstream *ss = (stringstream*) userdata;
	size_t count = size * nmemb;
	ss->write(ptr, count);
	return count;
}

size_t readcb(void *ptr, size_t size, size_t nitems, void *stream)
{
	//readarg_t *rarg = (readarg_t *)stream;
	//int len = rarg->len - rarg->pos;
	//if (len > size * nitems)
	//	len = size * nitems;
	//memcpy(ptr, rarg->buf + rarg->pos, len);
	//rarg->pos += len;
	//printf("readcb: %d bytes\n", len);
	//return len;
}

void pretty_print (string jsontext){

	Json::Value root;
	Json::Reader reader;
	bool parsed = reader.parse(jsontext, root, false);
	if(not parsed){
		cout<<"Failed to parse correctly, but y?"
				//<<reader.getFormattedErrorMessage()
				<<endl;
	}
	//cout<< count_num << endl<<endl;
	cout<<"Now printing all of Json in pretty print" <<endl<<root.toStyledString();

}


Json::Value json_code(string jsontext, string query_text)
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


Json::Value json_code(string jsontext, string query_text)
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
	for (int index = 0; index < plugins.size(); ++index )  // Iterates over the sequence elements.
	  loadPlugIn( plugins[index].asString());

	return count_num;
	//cout<< count_num << endl<<endl;
	//cout<<"Now printing all of Json in pretty print" <<endl<<root.toStyledString();
}


void curl_code (string sub_url) {
	CURL *curl;
	string url = "https://redmine-test.spice.spiceworks.com/"+ sub_url;
	struct curl_slist* headers=NULL;
	struct curl_httppost* post = NULL;
	struct curl_httppost* last = NULL;
	string [] community_versions;
  long http_code;
  curl = curl_easy_init();
	
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
		
		printf("http code: %lu\n", http_code);
		//Json::Value t_count =	json_code(stream.str(),"total_count");
		pretty_print(stream.str());
//		cout << t_count;		
    
    curl_easy_cleanup(curl);
	}
}


int main(int argc, char *argv[]) {
//	string default_url = "issues.json";
	string project_url = "projects/community/versions.json";
	curl_code(project_url);	
}	
	

