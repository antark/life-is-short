package main

import (
	"fmt"
	"math/rand"
	"time"
)

func main() {
	for i := 0; i < 100; i++ {
		fmt.Printf("% d", rand.Intn(10))
	}
	fmt.Println()
	gen := rand.New(rand.NewSource(time.Now().UnixNano()))
	for i := 0; i < 100; i++ {
		fmt.Printf("% d", gen.Intn(10))
	}
}

