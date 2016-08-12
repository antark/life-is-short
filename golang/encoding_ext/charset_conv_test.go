package encoding_ext

import (
	"fmt"
	"testing"
)

func TestCharsetConv(t *testing.T) {
	origin := []byte("你好，世界!")
	fmt.Println(string(origin))

	gbk, err := PutBytes(origin, "GB18030")
	if err != nil {
		fmt.Println(err)
	}
	fmt.Println(string(gbk))

	utf8, err := GetBytes(gbk, "GBK")
	if err != nil {
		fmt.Println(err)
	}
	fmt.Println(string(utf8))
}
