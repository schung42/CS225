/**
 * @file btree.cpp
 * Implementation of a B-tree class which can be used as a generic dictionary
 * (insert-only). Designed to take advantage of caching to be faster than
 * standard balanced binary search trees.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

using std::vector;

/**
 * Finds the value associated with a given key.
 * @param key The key to look up.
 * @return The value (if found), the default V if not.
 */
template <class K, class V>
V BTree<K, V>::find(const K& key) const
{
    return root == nullptr ? V() : find(root, key);
}

/**
 * Private recursive version of the find function.
 * @param subroot A reference of a pointer to the current BTreeNode.
 * @param key The key we are looking up.
 * @return The value (if found), the default V if not.
 */
template <class K, class V>
V BTree<K, V>::find(const BTreeNode* subroot, const K& key) const
{
    /* TODO Your code goes here! */
    /* If first_larger_idx is a valid index and the key there is the key we
     * are looking for, we are done. */

    /* Otherwise, we need to figure out which child to explore. For this we
     * can actually just use first_larger_idx directly. E.g.
     * | 1 | 5 | 7 | 8 |
     * Suppose we are looking for 6. first_larger_idx is 2. This means we want to
     * explore the child between 5 and 7. The children vector has a pointer for
     * each of the horizontal bars. The index of the horizontal bar we want is
     * 2, which is conveniently the same as first_larger_idx. If the subroot is
     * a leaf and we didn't find the key in it, then we have failed to find it
     * anywhere in the tree and return the default V.
     */
    while(subroot != NULL)
    {
        size_t retVal = insertion_idx(subroot->elements, key);

        if(subroot->elements[retVal] == key)
        {
            return subroot->elements[retVal].val();
        }
        if(subroot->elements[retVal] < key)
        {
            if(subroot->is_leaf)
            {
                return V();
            }
            find(subroot->children, key);
        }
        if(subroot->elements[retVal] > key)
        {
            if(subroot->is_leaf)
            {
                return V();
            }
            find(subroot->children, key);
        }
    }
    //didnt find it; return default V();
    return V();
}

/**
 * Inserts a key and value into the BTree. If the key is already in the
 * tree do nothing.
 * @param key The key to insert.
 * @param value The value to insert.
 */
template <class K, class V>
void BTree<K, V>::insert(const K& key, const V& value)
{
    /* Make the root node if the tree is empty. */
    if(root == nullptr)
    {
        root = new BTreeNode(true, order);
    }
    insert(root, DataPair(key, value));
    /* Increase height by one by tossing up one element from the old
     * root node. */
    if(root->elements.size() >= order)
    {
        BTreeNode* new_root = new BTreeNode(false, order);
        new_root->children.push_back(root);
        split_child(new_root, 0);
        root = new_root;
    }
}

/**
 * Splits a child node of a BTreeNode. Called if the child became too 
 * large.
 * @param parent The parent whose child we are trying to split.
 * @param child_idx The index of the child in its parent's children
 * vector.
 */
template <class K, class V>
void BTree<K, V>::split_child(BTreeNode* parent, size_t child_idx)
{

    /* TODO Your code goes here! */

    /* Assume we are splitting the 3 6 8 child.
     * We want the following to happen.
     *     | 2 | 
     *    /     \
     * | 1 |   | 3 | 6 | 8 |
     *
     *
     * Insert a pointer into parent's children which will point to the 
     * new right node. The new right node is empty at this point.
     *     | 2 |   | 
     *    /     \
     * | 1 |   | 3 | 6 | 8 |
     *
     * Insert the mid element from the child into its new position in the
     * parent's elements. At this point the median is still in the child.
     *     | 2 | 6 | 
     *    /     \
     * | 1 |   | 3 | 6 | 8 |
     *
     * Now we want to copy over the elements (and children) to the right
     * of the child median into the new right node, and make sure the left
     * node only has the elements (and children) to the left of the child 
     * median.
     *     | 2 | 6 | 
     *    /   /     \
     * | 1 | | 3 | | 8 |
     *
     */
    BTreeNode* newChild = new BTreeNode(parent->children->order, parent->is_leaf);
    newChild->children.size()= order -1;

    for(int j = 0; j< (order-1); j++)
    {
        newChild->children[j] = parent->children[j+order];
    }

    if(parent->is_leaf == false)
    {
        for(int j = 0; j< order; j++)
        {
            newChild->elements[j] = parent->elements[j+order];
        }
    }

    parent->children.size() = order - 1;

    for(int j = parent->children.size(); j >= child_idx+1; j--)
    {
        parent->elements[j+1] = parent->elements[j];
    }

    parent->elements[child_idx + 1] = newChild;

    for(int j = parent->children.size()-1; j>= child_idx; j--)
    {
        parent->children[j+1] = parent->children[j];
    }

    parent->children[child_idx] = parent->children[order-1];

    parent->children.size() = parent->children.size()+1;
}

/**
 * Private recursive version of the insert function.
 * @param subroot A reference of a pointer to the current BTreeNode.
 * @param pair The DataPair to be inserted.
 * Note: Original solution used std::lower_bound, but making the students
 * write an equivalent seemed more instructive.
 */
template <class K, class V>
void BTree<K, V>::insert(BTreeNode* subroot, const DataPair& pair)
{
    /* There are two cases to consider. 
     * If the subroot is a leaf node and the key doesn't exist subroot, we 
     * should simply insert the pair into subroot.
     * Otherwise (subroot is not a leaf and the key doesn't exist in subroot)
     * we need to figure out which child to insert into and call insert on it.
     * After this call returns we need to check if the child became too large
     * and thus needs to be split to maintain order. 
     */

    /* TODO Your code goes here! */
}

