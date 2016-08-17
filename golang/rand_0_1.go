package main

import (
	"fmt"
)

func main() {
	ch := make(chan int)
	go func(ch chan<- int) {
		for {
			select {
			case ch <- 0:
			case ch <- 1:
			}
		}
	}(ch)

	for i := 0; i < 10; i++ {
		fmt.Printf("% d", <-ch)
	}
}
