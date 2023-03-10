#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

int main() {
	CURL* curl;
	CURLcode res;
	char* content = NULL;

	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if (!curl) {
		fprintf(stderr, "Error initializing curl.\n");
		return 1;
	}

	curl_easy_setopt(curl, CURLOPT_URL, "https://api.github.com/repos/cmus/cmus/releases/latest");
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl");
	/* curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL); */
	/* curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content); */
	res = curl_easy_perform(curl);
	if (res != CURLE_OK) {
		fprintf(stderr, "Error fetching URL: %s\n", curl_easy_strerror(res));
		curl_easy_cleanup(curl);
		free(content);
		return 1;
	}


	free(content);

	return 0;
}
