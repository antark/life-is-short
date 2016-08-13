package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"regexp"
	//"strings"
)

type WordCount int

func (wc *WordCount) Write(b []byte) (n int, err error) {
	// string split, bad !
	//var s = string(b)
	//*wc += WordCount(len(strings.Split(s, " ")))

	// regexp word
	reg := regexp.MustCompile(`[a-zA-Z\x{4E00}-\x{9FA5}]+`)
	*wc += WordCount(len(reg.FindAll(b, -1)))
	return len(b), nil
}

func main() {
	file, _ := os.Open("names.txt")
	data, _ := ioutil.ReadAll(file)

	var wc WordCount
	wc.Write(data)

	fmt.Println(wc)
}
