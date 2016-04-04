// sorted_list.go
package sort_ext

import (
	"container/list"
	"sort"
)

type sortedList struct {
	list *list.List
	data []*list.Element
	cmp  func(a, b *interface{}) bool
}

func (slist *sortedList) init() {
	for ele := slist.list.Front(); ele != nil; ele = ele.Next() {
		slist.data = append(slist.data, ele)
	}
}

func (slist *sortedList) post() {
	slist.list.Init()
	for _, value := range slist.data {
		slist.list.PushBack(value.Value)
	}
}

func (slist sortedList) Len() int {
	return len(slist.data)
}

func (slist sortedList) Swap(i, j int) {
	slist.data[i], slist.data[j] = slist.data[j], slist.data[i]
}

func (slist sortedList) Less(i, j int) bool {
	return slist.cmp(&slist.data[i].Value, &slist.data[j].Value)
}

func SortList(data *list.List, cmp func(a, b *interface{}) bool) {
	if data == nil {
		panic("error: input list is nil")
	}
	if cmp == nil {
		panic("error: cmp is nil")
	}
	var slist sortedList = sortedList{list: data, cmp: cmp}
	slist.init()
	sort.Sort(slist)
	slist.post()
}
