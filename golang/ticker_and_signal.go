package main

import (
	"fmt"
	"os"
	"os/signal"
	"syscall"
	"time"
)

func main() {
	go func() {
		var timer = time.NewTicker(time.Second * 1)
		for {
			fmt.Println(<-timer.C)
		}
	}()
	var sch = make(chan os.Signal, 1)
	signal.Notify(sch, syscall.SIGINT, syscall.SIGTERM, syscall.SIGSTOP)
	<-sch
	fmt.Println("exit peaceful...")
}
