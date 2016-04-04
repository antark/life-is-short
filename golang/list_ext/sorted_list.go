// sorted_list.go
package sort_ext

import (
	"container/list"
	"sort"
)

type SortedList struct {
	list *list.List
	data []*list.Element
	cmp  func(a, b *interface{}) bool
}

func (slist *SortedList) init() {
	for ele := slist.list.Front(); ele != nil; ele = ele.Next() {
		slist.data = append(slist.data, ele)
	}
}

func (slist *SortedList) post() {
	slist.list.Init()
	for _, value := range slist.data {
		slist.list.PushBack(value.Value)
	}
}

func (slist SortedList) Len() int {
	return len(slist.data)
}

func (slist SortedList) Swap(i, j int) {
	slist.data[i], slist.data[j] = slist.data[j], slist.data[i]
}

func (slist SortedList) Less(i, j int) bool {
	return slist.cmp(&slist.data[i].Value, &slist.data[j].Value)
}

func SortList(data *list.List, cmp func(a, b *interface{}) bool) {
	if data == nil {
		panic("error: input list is nil")
	}
	if cmp == nil {
		panic("error: cmp is nil")
	}
	var slist SortedList = SortedList{list: data, cmp: cmp}
	slist.init()
	sort.Sort(slist)
	slist.post()
}
