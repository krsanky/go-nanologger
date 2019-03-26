package main

import (
	"fmt"
	"os"
)

func main() {
	fmt.Printf("nanologger\n")
	for i, a := range os.Args[1:] {
		fmt.Printf("%d:%s ", i, a)
	}
	fmt.Println()

	if len(os.Args) >= 2 {
		switch arg1 := os.Args[1]; arg1 {
		case "web":
			fmt.Printf("do this ...\n")
		case "db":
			fmt.Printf("do that ...\n")
		default:
			usage()
		}
	} else {
		usage()
	}

}

func usage() {
	fmt.Println()
	fmt.Println(`nanologger [web|db]`)
	fmt.Println()
}
