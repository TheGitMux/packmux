#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

size_t write_callback(char* ptr, size_t size, size_t nmemb, void* userdata)
{
	size_t realsize = (size * nmemb);
	FILE *fp = (FILE *)userdata;
	fwrite(ptr, size, nmemb, fp);
	return realsize;
}

int main() {
	CURL* curl;
	CURLcode res;
	FILE* fp;

	fp = fopen("output.txt", "wb");

	if(!fp) {
		fprintf(stderr, "Failed to open file.\n");
		exit(-1);
	}

	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if (!curl) {
		fprintf(stderr, "Error initializing curl.\n");
		return 1;
	}

	curl_easy_setopt(curl, CURLOPT_URL, "https://api.github.com/repos/cmus/cmus/releases/latest");
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl");
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

	res = curl_easy_perform(curl);

	if (res != CURLE_OK) {
		fprintf(stderr, "Error fetching URL: %s\n", curl_easy_strerror(res));
		curl_easy_cleanup(curl);
		return 1;
	}

	curl_global_cleanup();
	fclose(fp);

	return 0;
}
