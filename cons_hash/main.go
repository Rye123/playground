package main

import (
	"fmt"
	cht "github.com/Rye123/playground/cons_hash/consistent_hash_table"
)



func main() {
	cHT := cht.NewConsistentHashTable()
	node1 := cht.NewNode("192.168.0.1")
	node2 := cht.NewNode("192.168.0.2")
	node3 := cht.NewNode("192.168.0.3")
	cHT.AddNode(node1)
	cHT.AddNode(node2)
	cHT.AddNode(node3)
	fmt.Printf("Nodes: \n\tNode 1: %s, %08x\n\tNode 2: %s, %08x\n\tNode 3: %s, %08x\n",
		node1.Address, cht.GetIdentifier([]byte(node1.Address)),
		node2.Address, cht.GetIdentifier([]byte(node2.Address)),
		node3.Address, cht.GetIdentifier([]byte(node3.Address)),
	)
	
	data, ok := cHT.Get("key1")
	if !ok {
		fmt.Println("key1 not found.")
	} else {
		fmt.Printf("key1: %s\n", data)
	}

	cHT.Set("key1", "value1")
	
	data, ok = cHT.Get("key1")
	if !ok {
		fmt.Println("key1 not found.")
	} else {
		fmt.Printf("key1: %s\n", data)
	}

	cHT.Set("The quick brown fox", "value2")
	
	data, ok = cHT.Get("The quick brown fox")
	if !ok {
		fmt.Println("Tqbf not found.")
	} else {
		fmt.Printf("Tqbf: %s\n", data)
	}
}
