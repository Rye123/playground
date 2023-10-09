package consistent_hash_table

import "testing"

func isIdSliceSorted(slice []Id) bool {
	for i := range slice {
		if i == 0 {
			continue
		}
		if slice[i-1] > slice[i] {
			return false
		}
	}
	return true
}

func TestAddNodeSorted(t *testing.T) {
	ht := NewConsistentHashTable()
	ht.AddNode(NewNode("a"))
	if !isIdSliceSorted(ht.nodeIds) {
		t.Fatalf("ht.nodeIds with one node not sorted")
	}
	ht.AddNode(NewNode("b"))
	if !isIdSliceSorted(ht.nodeIds) {
		t.Fatalf("ht.nodeIds not sorted, %v", ht.nodeIds)
	}
	ht.AddNode(NewNode("c"))
	if !isIdSliceSorted(ht.nodeIds) {
		t.Fatalf("ht.nodeIds not sorted, %v", ht.nodeIds)
	}
	ht.AddNode(NewNode("d"))
	if !isIdSliceSorted(ht.nodeIds) {
		t.Fatalf("ht.nodeIds not sorted, %v", ht.nodeIds)
	}
	ht.AddNode(NewNode("e"))
	if !isIdSliceSorted(ht.nodeIds) {
		t.Fatalf("ht.nodeIds not sorted, %v", ht.nodeIds)
	}
	ht.AddNode(NewNode("f"))
	if !isIdSliceSorted(ht.nodeIds) {
		t.Fatalf("ht.nodeIds not sorted, %v", ht.nodeIds)
	}
}
