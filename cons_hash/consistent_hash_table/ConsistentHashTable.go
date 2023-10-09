/**
ConsistentHashTable:
  Maintains data across separate nodes, using consistent hashing and
  an identifier circle to maintain the data.
*/

package consistent_hash_table

import (
	"fmt"
	"log"
	"github.com/spaolacci/murmur3"
)

type Id uint32

// Returns the identifier for a given key.
func GetIdentifier(key []byte) Id {
	hash := murmur3.New32()
	hash.Write(key)
	return Id(hash.Sum32())
}

type ConsistentHashTable struct {
	nodeIds []Id // Sorted list of all nodes
	nodes map[Id](*Node) // Associative array of all nodes
}

func NewConsistentHashTable() *ConsistentHashTable {
	return &ConsistentHashTable{
		make([]Id, 0),
		make(map[Id](*Node), 0),
	}
}

func (ht *ConsistentHashTable) AddNode(node *Node) {
	nodeId := GetIdentifier([]byte(node.Address))
	if _, exists := ht.nodes[nodeId]; exists {
		panic("AddNode: Node is already in table.")
	}
	
	// Invariant: ConsistentHashTable.nodeIds is sorted.	
	for i, id := range(ht.nodeIds) {
		if nodeId > id {
			continue
		}
		ht.nodeIds = append(ht.nodeIds, 0)
		copy(ht.nodeIds[i+1:], ht.nodeIds[i:])
		ht.nodeIds[i] = nodeId
		ht.nodes[nodeId] = node
		return
	}

	// Here, no id in the hash table is greater.
	ht.nodeIds = append(ht.nodeIds, nodeId)
	ht.nodes[nodeId] = node
}

func (ht *ConsistentHashTable) Get(key string) (string, bool) {
	if len(ht.nodeIds) == 0 {
		return "", false
	}

	dataId := GetIdentifier([]byte(key))

	// Find the nodeId responsible for dataId
	nodeId := ht.nodeIds[0]
	for _, nid := range(ht.nodeIds) {
		if nid >= dataId {
			nodeId = nid
			break
		}
	}

	node := ht.nodes[nodeId]

	log.Printf("Get: Key %s is in node %s\n", key, node.Address)
	return node.Get(key)
}

func (ht *ConsistentHashTable) Set(key, value string) {
	if len(ht.nodeIds) == 0 {
		panic("ConsistentHashTable.Set: No nodes in hash table.")
	}

	dataId := GetIdentifier([]byte(key))

	// Find the nodeId responsible for dataId
	nodeId := ht.nodeIds[0]
	for _, nid := range(ht.nodeIds) {
		if nid >= dataId {
			nodeId = nid
			break
		}
	}

	node := ht.nodes[nodeId]

	log.Printf("Set: Key %s is in node %s\n", key, node.Address)
	node.Set(key, value)
}

func (ht *ConsistentHashTable) String() string {
	ret := ""
	for nodeId, node := range(ht.nodes) {
		ret += fmt.Sprintf("%08x: %s\n", nodeId, node.Address)
	}
	return ret
}
