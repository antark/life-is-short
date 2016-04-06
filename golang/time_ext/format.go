package time_ext

import (
	"fmt"
	"time"
)

type TimeWrapper struct {
	time.Time
}

// format 仅支持正常的 年: y/yy/yyy/yyyy  月: M/MM 日: d/dd 小时: H/HH h/hh 分钟: m/mm 秒钟: s/ss 和其他字符的组合模式
// 不支持类似于 yyyyy  MMMM 的非常规格式， 这些可能会有非预期结果哟~
func Parse(format, value string) (time.Time, error) {
	layout := get_std_format(format)
	return time.Parse(layout, value)
}

func (t TimeWrapper) Format(format string) string {
	layout := get_std_format(format)
	return t.Time.Format(layout)
}

func inner_parse(format string) string {
	format = format + "\u0000"
	var inner_format []byte = make([]byte, 0)
	var i, j int

	for ; j < len(format); j++ {
		if format[j] == format[i] {
			continue
		}
		if format[i] == 'y' || format[i] == 'M' || format[i] == 'd' || format[i] == 'H' || format[i] == 'h' || format[i] == 'm' || format[i] == 's' {
			inner_format = append(inner_format, format[i])
			inner_format = append(inner_format, byte('0'+j-i))
		} else {
			inner_format = append(inner_format, format[i:j]...)
		}
		i = j
	}
	return string(inner_format)
}

func get_std_format(format string) string {
	var f = inner_parse(format) // 获取 yyyyMMddHHmmss 格式 --> y4M2d2H2m2s2
	var inner_format []byte = make([]byte, 0)

	base := map[byte]int{
		'y': 2006, 'M': 01, 'd': 02, 'H': 15, 'h': 03, 'm': 04, 's': 05,
	}
	pow := map[byte]int{
		'1': 10, '2': 100, '3': 1000, '4': 10000,
	}

	// 从 2016年01月02号15点04分05秒时间中按照 y4M2d2H2m2s2 生成诸如 20160102150405 的字符串
	for i := 0; i < len(f); i++ {
		switch f[i] {
		case 'y', 'M', 'd', 'H', 'h', 'm', 's':
			if pow[f[i+1]] == 0 {
				panic("format invalid, format:" + format)
			}
			inner_format = append(inner_format, fmt.Sprintf("%0"+string(f[i+1])+"d", base[f[i]]%pow[f[i+1]])...)
			i++
		default:
			inner_format = append(inner_format, f[i])
		}
	}
	return string(inner_format)
}
