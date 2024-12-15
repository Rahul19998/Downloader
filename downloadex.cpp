#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

size_t got_data(char *buffer, size_t itemsize, size_t nitems, void* ignorethis) {
    size_t bytes = itemsize * nitems;
    int linenumber = 1;
    std::cout << "New chunk size : " << bytes << std::endl;
    std::cout << linenumber << std::endl;
    for (int i=0; i<bytes;i++) {
        std::cout << buffer[i];
        if(buffer[i] == '\n') {
            linenumber++;
            std::cout << linenumber << ": ";
        }
    }
    std::cout << std::endl;
    std::cout << std::endl;
    return bytes;
}

int main(void) {
    CURL *curl = curl_easy_init();

    if(!curl) {
        std::cerr << "init failed" << std::endl;
        return EXIT_FAILURE;
    }

    //set options
    // curl_easy_setopt(curl, CURLOPT_URL, "https://www.jacobsorber.com/");
    curl_easy_setopt(curl, CURLOPT_URL, "ftp://demo:password@test.rebex.net/readme.txt");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, got_data);

    //perform out action
    CURLcode result = curl_easy_perform(curl);
    if(result != CURLE_OK) {
        std::cerr << "download problem: " << curl_easy_strerror(result) << std::endl;
    }

    curl_easy_cleanup(curl);
    return EXIT_SUCCESS;
}