package encoding_ext

import (
	"fmt"
	"testing"
)

func TestCharsetConv(t *testing.T) {
	origin := []byte("你好，世界!")

	gbk, err := PutBytes(origin, "GB18030")
	if err != nil {
		fmt.Println(err)
	}
	fmt.Println(string(origin))
	fmt.Println(string(gbk))

	utf8, err := GetBytes(gbk, "GBK")
	fmt.Println(string(utf8))
}
