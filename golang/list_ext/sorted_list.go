// sorted_list_test.go
package sort_ext

import (
	"container/list"
	"fmt"
	"testing"
)

func TestSortedList(t *testing.T) {
	origin := [...]uint64{1, 7, 3, 5, 2, 8, 6, 4, 9}
	var data list.List
	for _, value := range origin {
		data.PushBack(value)
	}
	SortList(&data, func(a, b *interface{}) bool {
		return (*a).(uint64) < (*b).(uint64)
	})
	for ele := data.Front(); ele != nil; ele = ele.Next() {
		fmt.Printf("%d ", ele.Value) // ele.Value ==> (*ele).Value
	}
	fmt.Println()
}
