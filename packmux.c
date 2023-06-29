#include <stdio.h>
#include <curl/curl.h>

int
main (void)
{
	CURL *curl;
	CURLcode res;

	curl_global_init(CURL_GLOBAL_DEFAULT);

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "https://api.github.com/repos/cmus/cmus/releases/latest");

		struct curl_slist *headers = NULL;
		headers = curl_slist_append(headers, "User-Agent: My-User-Agent");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

		res = curl_easy_perform(curl);

		if(res != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));
		}

		curl_easy_cleanup(curl);
	}

	curl_global_cleanup();

	return 0;
}
