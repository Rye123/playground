package main

import (
	"fmt"
	"sort"

	"github.com/spaolacci/murmur3"
)

type HashTable interface {
	Get(key any) (any, bool)
	Set(key any, value any)
}

type Node struct {
	address string
	data map[string]string
}

func NewNode(address string) *Node {
	return &Node{address, make(map[string]string, 0)}
}

func (node *Node) Get(key string) (string, bool) {
	value, ok := node.data[key]
	return value, ok
}

func (node *Node) Set(key string, value string) {
	node.data[key] = value
}

type CHashTable struct {
	nodeIds []uint32  // sorted list of all nodes
	nodes map[uint32](*Node)
}

func NewCHashTable() *CHashTable {
	return &CHashTable{make([]uint32, 0), make(map[uint32](*Node), 0)}
}


func (ht *CHashTable) AddNode(node *Node) {
	nodeId := GetIdentifier([]byte(node.address))
	ht.nodeIds = append(ht.nodeIds, nodeId)

	// Invariant: nodeIds is sorted
	sort.Slice(ht.nodeIds, func(i, j int) bool {
		return ht.nodeIds[i] < ht.nodeIds[j]
	})

	ht.nodes[nodeId] = node
}

func (ht *CHashTable) Get(key string) (string, bool) {
	if len(ht.nodeIds) == 0 {
		return "", false
	}
	
	identifier := GetIdentifier([]byte(key))
	nodeId := ht.nodeIds[0]

	// Find the nodeId responsible
	for _, nId := range(ht.nodeIds) {
		if nId >= identifier {
			nodeId = nId
			break
		}
	}

	fmt.Printf("Got key %s from node %s\n", key, ht.nodes[nodeId].address)
	return ht.nodes[nodeId].Get(key)
}

func (ht *CHashTable) Set(key string, value string) {
	if len(ht.nodeIds) == 0 {
		panic("No nodes in CHashTable")
	}
	
	identifier := GetIdentifier([]byte(key))
	nodeId := ht.nodeIds[0]

	// Find the nodeId responsible
	for _, nId := range(ht.nodeIds) {
		if nId >= identifier {
			nodeId = nId
			break
		}
	}
	
	ht.nodes[nodeId].Set(key, value)
	fmt.Printf("Key %s set at address %s\n", key, ht.nodes[nodeId].address)
}



// Returns the identifier for a given key
func GetIdentifier(key []byte) uint32 {
	hash := murmur3.New32()
	hash.Write(key)
	return hash.Sum32()
}


func main() {
	cHT := NewCHashTable()
	node1 := NewNode("192.168.0.1")
	node2 := NewNode("192.168.0.2")
	node3 := NewNode("192.168.0.3")
	cHT.AddNode(node1)
	cHT.AddNode(node2)
	cHT.AddNode(node3)
	fmt.Printf("Nodes: \n\tNode 1: %s, %08x\n\tNode 2: %s, %08x\n\tNode 3: %s, %08x\n",
		node1.address, GetIdentifier([]byte(node1.address)),
		node2.address, GetIdentifier([]byte(node2.address)),
		node3.address, GetIdentifier([]byte(node3.address)),
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
