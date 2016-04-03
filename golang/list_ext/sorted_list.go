// sorted_list.go
package sort_ext

import (
	"container/list"
	"sort"
)

type SortedList struct {
	Value *list.List
	data  []*list.Element
	Cmp   func(a, b *interface{}) bool
}

func (slist *SortedList) Init() {
	for ele := slist.Value.Front(); ele != nil; ele = ele.Next() {
		slist.data = append(slist.data, ele)
	}
}

func (slist *SortedList) Post() {
	slist.Value.Init()
	for _, value := range slist.data {
		slist.Value.PushBack(value.Value)
	}
}

func (slist SortedList) Len() int {
	return len(slist.data)
}

func (slist SortedList) Swap(i, j int) {
	slist.data[i], slist.data[j] = slist.data[j], slist.data[i]
}

func (slist SortedList) Less(i, j int) bool {
	return slist.Cmp(&slist.data[i].Value, &slist.data[j].Value)
}

func SortList(data *list.List, cmp func(a, b *interface{}) bool) {
	if data == nil || cmp == nil {
		panic("error: input list is nil, or cmp is nil")
	}
	var slist SortedList = SortedList{Value: data, Cmp: cmp}
	slist.Init()
	sort.Sort(slist)
	slist.Post()
}
