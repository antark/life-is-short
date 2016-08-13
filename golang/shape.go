package main

import (
    "fmt"
    "math"
)

type Shape interface {
    area() float64
}

type Square struct {
    r float64
}

func (s Square) area() float64 {
    return s.r * s.r
}

type Circle struct {
    r float64
}

func (s Circle) area() float64 {
    return math.Pi * s.r * s.r
}

func main() {
    shapes := [2]Shape{Square{4}, Circle{4}}

    for _, shape := range shapes {
        fmt.Println(shape.area())
    }
}
