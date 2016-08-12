package encoding_ext

import (
	"golang.org/x/text/encoding"
	"golang.org/x/text/encoding/japanese"
	"golang.org/x/text/encoding/simplifiedchinese"
	"golang.org/x/text/encoding/traditionalchinese"
)

var table map[string]encoding.Encoding = make(map[string]encoding.Encoding)

func init() {
	table["GB18030"] = simplifiedchinese.GB18030
	table["GBK"] = simplifiedchinese.GBK
	table["GB2312"] = simplifiedchinese.HZGB2312
	table["BIG5"] = traditionalchinese.Big5
	table["ShiftJIS"] = japanese.ShiftJIS
}

func GetBytes(data []byte, charset string) ([]byte, error) {
	encoding, ok := table[charset]
	if !ok {
		panic("not supported charset: " + charset)
	}
	return encoding.NewDecoder().Bytes(data)
}

func PutBytes(data []byte, charset string) ([]byte, error) {
	encoding, ok := table[charset]
	if !ok {
		panic("not supported charset: " + charset)
	}
	return encoding.NewEncoder().Bytes(data)
}
