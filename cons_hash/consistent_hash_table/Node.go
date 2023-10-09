package consistent_hash_table

// A node associates an address (e.g. IPv4 address) with data.
type Node struct {
	Address string
	Data    map[string]string
}

func NewNode(address string) *Node {
	return &Node{address, make(map[string]string, 0)}
}

func (node *Node) Get(key string) (string, bool) {
	value, ok := node.Data[key]
	if !ok {
		return "", false
	}
	return value, true
}

func (node *Node) Set(key string, value string) {
	node.Data[key] = value
}
