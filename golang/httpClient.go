package main

import (
    "io/ioutil"
    "log"
    "net/http"
    "os"

    "github.com/antark/golang-x/encoding_ext"
)

func errCheck(err error) {
    if err != nil {
        log.Fatal(err)
    }
}

func main() {
    // do request
    url := "http://www.szse.cn/szseWeb/common/szse/files/text/jy/jy160811.txt"
    req, err := http.NewRequest("GET", url, nil)
    errCheck(err)

    client := http.DefaultClient
    resp, err := client.Do(req)
    errCheck(err)

    // process response body
    text, err := ioutil.ReadAll(resp.Body)
    errCheck(err)

    // charset conversion: GBK --> UTF-8
    utfText, err := encoding_ext.GetBytes(text, "GBK")
    errCheck(err)

    log.Print(string(utfText))

    // store
    file, err := os.Create("sz-jy-160811.txt")
    errCheck(err)

    _, err = file.Write(utfText)
    errCheck(err)

    return
}
