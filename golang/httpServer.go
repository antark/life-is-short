package main

import (
	"fmt"
	"net/http"
)

func main() {
	http.ListenAndServe(":8080", http.HandlerFunc(httpHandler))
}

func httpHandler(response http.ResponseWriter, request *http.Request) {
	fmt.Fprintf(response, "%s\n", request.URL)
}
