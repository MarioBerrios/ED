#pragma once

#include "avltree.hpp"

#ifdef assert
//We undefined this macro to not shadow our implementation of assert.
#undef assert
#endif

/**
 * @brief Check an assertion.
 * In Debug mode, if the assertion is not met, a segfault is generated.
 * @param assertion
 */
inline void assert(bool assertion)
{
#ifndef NDEBUG
    (void)((assertion) || (__assert ("Assert violation!", __FILE__, __LINE__),0));
#endif
}

/****
 * AVLTNode class implementation.
 ****/


template <class T>
AVLTNode<T>::AVLTNode (T const& it, AVLTNode<T>::Ref parent,
                       AVLTNode<T>::Ref left, AVLTNode<T>::Ref right):
    item_(it), parent_(parent), left_(left), right_(right), height_(0)
{
    //TODO
    compute_height();

    //
    assert(check_height_invariant());
}

template <class T>
typename AVLTNode<T>::Ref AVLTNode<T>::create(T const& it,
                                              AVLTNode<T>::Ref parent,
                                              AVLTNode<T>::Ref left,
                                              AVLTNode<T>::Ref right)
{
    return std::make_shared< AVLTNode<T> > (it, parent, left, right);
}

template <class T>
const T& AVLTNode<T>::item() const
{
    //TODO
    return item_;
}

template <class T>
int AVLTNode<T>::height() const
{
    //TODO
    return height_;
}

template <class T>
int AVLTNode<T>::balance_factor() const
{
    int bf = 0;
    //TODO
    int left = -1, right = -1;
    
    if(left_ != nullptr)
        left = left_ -> height();
    if(right_ != nullptr)
        right = right_ -> height();

    bf = right - left;

    //
    return bf;
}

template <class T>
bool AVLTNode<T>::has_parent() const
{
    //TODO
    return parent_ != nullptr;
}

template <class T>
typename AVLTNode<T>::Ref AVLTNode<T>::parent() const
{
    //TODO
    return parent_;
}

template <class T>
bool AVLTNode<T>::has_left() const
{
    //TODO
    return left_ != nullptr;
}

template <class T>
typename AVLTNode<T>::Ref AVLTNode<T>::left() const
{
    //TODO
    return left_;
}

template <class T>
bool AVLTNode<T>::has_right() const
{
    //TODO
    return right_ != nullptr;
}

template <class T>
typename AVLTNode<T>::Ref AVLTNode<T>::right() const
{
    //TODO
    return right_;
}

template <class T>
bool AVLTNode<T>::check_height_invariant () const
{
    bool ret_val = false;
    //TODO

    int max = -1;
    if (left_ != nullptr)
        max = left_ -> height();

    if (right_ != nullptr && right_ -> height() > max)
        max = right_ -> height();

    if (height_ == 1 + max)
        ret_val = true;

    //
    return ret_val;
}

template <class T>
void AVLTNode<T>::set_item(const T& new_it)
{
    //TODO
    item_ = new_it;
    //
    assert(item()==new_it);
}

template <class T>
void AVLTNode<T>::set_parent(AVLTNode<T>::Ref const& new_parent)
{
    //TODO
    parent_ = new_parent;
    //
    assert(parent()==new_parent);
}

template <class T>
void AVLTNode<T>::remove_parent()
{
    //TODO
    parent_ = nullptr;
    //
    assert(!has_parent());
}

template <class T>
void AVLTNode<T>::set_left(AVLTNode<T>::Ref const& new_child)
{
    //TODO
    left_ = new_child;
    compute_height();
    //
    assert(check_height_invariant());
    assert(left()==new_child);
}

template <class T>
void AVLTNode<T>::remove_left()
{
    //TODO
    left_ = nullptr;
    compute_height();
    //
    assert(check_height_invariant());
    assert(!has_left());
}

template <class T>
void AVLTNode<T>::set_right(AVLTNode<T>::Ref const& new_child)
{
    //TODO
    right_ = new_child;
    compute_height();
    //
    assert(check_height_invariant());
    assert(right()==new_child);
}

template <class T>
void AVLTNode<T>::remove_right()
{
    //TODO
    right_ = nullptr;
    compute_height();
    //
    assert(check_height_invariant());
    assert(!has_right());
}

template <class T>
void AVLTNode<T>::compute_height()
{
    //TODO
    if (right_ == nullptr && left_ == nullptr){
        height_ = 0;
    }
    else{
        int aux = 0;
        if (left_ != nullptr){
            left_ -> compute_height();
            if (left_ -> height() > aux)
                aux = left_ -> height();
        }
        if (right_ != nullptr){
            right_ -> compute_height();
            if (right_ -> height() > aux)
                aux = right_ -> height();
        }
        height_ = 1 + aux;
    }
    //
    assert(check_height_invariant());
}

/***
 * AVLTree class implementation.
 ***/

template <class T>
AVLTree<T>::AVLTree ()
{
    //TODO
    root_ = nullptr;
    curr_ = nullptr;
    prev_ = nullptr;
    
    //
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());
}

template <class T>
AVLTree<T>::AVLTree (T const& item)
{
    //TODO
    root_ = AVLTNode<T>::create(item);
    curr_ = root_;
    prev_ = nullptr;
    //
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());
}

template <class T>
typename AVLTree<T>::Ref AVLTree<T>::create ()
{
    return std::make_shared< AVLTree<T> >();
}

template <class T>
typename AVLTree<T>::Ref AVLTree<T>::create (T const& item)
{
    return std::make_shared<AVLTree<T>> (item);
}

template <class T>
typename AVLTree<T>::Ref AVLTree<T>::create(std::istream& in) noexcept(false)
{
    auto tree = AVLTree<T>::create();
    std::string token;
    in >> token;
    if (!in)
        throw std::runtime_error("Wrong input format");

    //TODO

    T new_item;

    if(token == "["){
        in >> token;
        std::istringstream str(token);
        str >> new_item;
        tree -> create_root(new_item);

        typename AVLTree<T>::Ref l_aux= AVLTree<T>::create(in);
        tree -> set_left(l_aux);

        typename AVLTree<T>::Ref r_aux = AVLTree<T>::create(in);
        tree -> set_right(r_aux);

        in >> token;
        if(token != "]")
            throw std::runtime_error("Wrong input format");
    }
    else if (token != "[]"){
        throw std::runtime_error("Wrong input format");
    }

    //

    if (! tree->is_a_binary_search_tree())
        throw std::runtime_error("It is not a binary search tree");
    if (! tree->is_a_balanced_tree())
        throw std::runtime_error("It is not an avl bstree");
    return tree;
}

#ifdef __ONLY_BSTREE__
/**
 * @brief Create a BSTree by inserting the median of an ordered sequence.
 * @param data is an ordered sequence of keys.
 * @param begin,
 * @param end specify a [begin, end) indexing interval of data to use.
 * @pre data values are in order.
 * @pre 0 <= begin <= end <=data.size()
 */
template<class T>
void create_inserting_median(std::vector<T> const& data,
                             size_t begin,
                             size_t end,
                             typename AVLTree<T>::Ref& tree)
{
    assert(begin<=end);
    assert(end<=data.size());

    //TODO
    //Hint: use a recursive design by inserting the median of input
    // (begin, end] interval
    //and recursively, apply to each sub-interval [begin, median),
    //[median+1, end).

    int median = data.size() / 2;
    int next = median + 1;

    if(data.size() > 0){
        tree -> insert(data[median]);
        create_inserting_median(std::vector<T>(data.begin(),data.begin() + median), 0, 0, tree);
        create_inserting_median(std::vector<T>(data.begin() + next, data.end()), 0, 0, tree);
    }

}

template<class T>
typename AVLTree<T>::Ref AVLTree<T>::create(std::vector<T> & data)
{
    assert(data.size()>0);
    auto tree = AVLTree<T>::create();
    std::sort(data.begin(), data.end());
    create_inserting_median(data, 0, data.size(), tree);
    return tree;
}
#endif //#ifdef __ONLY_BSTREE__

template <class T>
bool AVLTree<T>::is_empty () const
{
    //TODO
    return root_ == nullptr;
}

template <class T>
T const& AVLTree<T>::item() const
{
    return root_ -> item();
}

template <class T>
std::ostream& AVLTree<T>::fold(std::ostream& out) const
{
    //TODO
    if(this -> is_empty())
        out << "[]";

    else {
        out << "[ ";
        out << root_ -> item() << " ";
        this -> left() -> fold(out);
        out << " ";
        this -> right() -> fold(out);
        out << " ]";
        
    }
    //
    return out;
}

template <class T>
bool AVLTree<T>::current_exists() const
{
    //TODO
    return curr_ != nullptr;
}

template <class T>
T const& AVLTree<T>::current() const
{
    assert(current_exists());
    //TODO    
    return curr_ -> item();
}

template <class T>
int AVLTree<T>::current_level() const
{
    assert(current_exists());
    int level = 0;
    //TODO
    typename AVLTNode<T>::Ref aux = curr_;
    while (aux != root_){
        aux = aux -> parent();
        level++;
    }
    //
    return level;
}

template <class T>
typename AVLTree<T>::Ref AVLTree<T>::left() const
{
    assert(!is_empty());
    //TODO
    typename AVLTree<T>::Ref l_subtree;
    l_subtree = l_subtree -> create();
    l_subtree -> root_ = root_ -> left();
    return l_subtree;
}

template <class T>
typename AVLTree<T>::Ref AVLTree<T>::right() const
{
    assert(!is_empty());
    //TODO
    typename AVLTree<T>::Ref r_subtree;
    r_subtree = r_subtree -> create();
    r_subtree -> root_ = root_ -> right();
    return r_subtree;
}

template <class T>
int AVLTree<T>::size() const
{
    int s = 0;
    //TODO
    if (!is_empty())
        s = 1 + left()->size() + right()->size();
    return s;
}

template <class T>
int AVLTree<T>::height() const
{
    int h = -1;
    //TODO
    h = root_ -> height();
    //
    return h;
}

template <class T>
int AVLTree<T>::balance_factor() const
{
#ifdef __ONLY_BSTREE__
    return 0;
#else
    int bf = 0;
    //TODO
    bf = root_ -> balance_factor();
    //
    return bf;
#endif
}

template <class T>
bool AVLTree<T>::has(const T& k) const
{
#ifndef NDEBUG
  bool old_current_exists = current_exists();
  T old_current;
  if (old_current_exists)
      old_current = current();
#endif

  bool found = true;

  //TODO
    found = false;
    if(!this->is_empty()){
        if(k < this -> item())
            found = this -> left() -> has(k);
        else if (k > this -> item())
            found = this -> right() -> has(k);
        else if (k == this -> item())
            found = true;
    }

  //
#ifndef NDEBUG
  assert (!old_current_exists || old_current == current());
#endif
  return found;
}

template <class T>
bool AVLTree<T>::is_a_binary_search_tree() const
{
    bool is_bst = true;
    //TODO

    if (root_ == nullptr)
        return is_bst;

    if (root_ -> has_right()){
        if (root_ -> right() -> item() < root_ -> item()){
            is_bst = false;
            return is_bst;
        }
        is_bst = this -> right() -> is_a_binary_search_tree();
        if (!is_bst)
            return is_bst;
    }

    if (root_ -> has_left()){
        if (root_ -> left() -> item() > root_ -> item()){
            is_bst = false;
            return is_bst;
        }
        is_bst = this -> left() -> is_a_binary_search_tree();
        if (!is_bst)
            return is_bst;
    }

    //
    return is_bst;
}

template <class T>
bool AVLTree<T>::is_a_balanced_tree() const
{
#ifdef __ONLY_BSTREE__
    return true;
#else
    bool is_balanced = true;
    //TODO
    if(root_ == nullptr){
        return is_balanced;
    }
    
    root_ -> compute_height();
    if (root_ -> balance_factor() != 0 &&
        root_ -> balance_factor() != 1 &&
        root_ -> balance_factor() != -1){
        is_balanced = false;
        return is_balanced;
    }                

    if (root_ -> has_right()){
        is_balanced = this -> right() -> is_a_balanced_tree();
        if(!is_balanced)
            return is_balanced;
    }

    if (root_ -> has_left()){
        is_balanced = this -> left() -> is_a_balanced_tree();
        if(!is_balanced)
            return is_balanced;
    }
    //
    return is_balanced;
#endif
}

template <class T>
void AVLTree<T>::create_root(T const& item)
{
    assert(is_empty());
    //TODO
    root_ = AVLTNode<T>::create(item);
    //
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());
    assert(!is_empty());
    assert(this -> item()==item);
    

}

template <class T>
bool AVLTree<T>::search(T const& k)
{
    bool found = false;
    //TODO
    curr_ = root_;
    prev_ = nullptr;

    while (curr_ != nullptr && !found){
        if (curr_ -> item() == k){
            found = true;
        }
        else{
            prev_ = curr_;
            if (curr_ -> item() > k)
                curr_ = curr_ -> left();
            else
                curr_ = curr_ -> right();    
        }
    }
    //
    assert(!found || current()==k);
    assert(found || !current_exists());
    return found;
}

template <class T>
void AVLTree<T>::insert(T const& k)
{
    if (!search(k))
    {
        //TODO
        if (this -> is_empty()){
            curr_ = AVLTNode<T>::create(k);
            root_ = curr_;
        }
        else {
            curr_ = AVLTNode<T>::create(k);
            if (prev_ -> item() > k)
                prev_ -> set_left(curr_);
            else
                prev_ -> set_right(curr_);

            curr_ -> set_parent(prev_);
        }

        //
#ifdef __ONLY_BSTREE__
        assert(is_a_binary_search_tree());
#else
        assert(is_a_binary_search_tree());
        make_balanced();
        assert(is_a_balanced_tree());
#endif
    }

    //check postconditions.
    assert(current_exists());
    assert(current()==k);
}

template <class T>
void AVLTree<T>::remove ()
{
    //check preconditions.
    assert(current_exists());

    bool replace_with_subtree = true;
    typename AVLTNode<T>::Ref subtree;

    //TODO
    // Check which of cases 0,1,2,3 we have.
    if (!curr_ -> has_left() && !curr_ -> has_right()){
        subtree = nullptr;
    }
    else if (!curr_ -> has_right())
        subtree = curr_ -> left();
    else if (!curr_ -> has_left())
        subtree = curr_ -> right();
    else
        replace_with_subtree = false;
    
    //

    if (replace_with_subtree)
    {
        //TODO
        //Manage cases 0,1,2
        if(prev_ == nullptr){
            root_ = subtree;
        }
        else if (prev_ -> right() == curr_){
            prev_ -> set_right(subtree);
        }
        else{
            prev_ -> set_left(subtree);
        }

        curr_ = nullptr;
        //
#ifdef __ONLY_BSTREE__
        assert(is_a_binary_search_tree());
        assert(!current_exists());
#else
        assert(is_a_binary_search_tree());
        make_balanced();
        assert(is_a_balanced_tree());
        assert(! current_exists());
#endif
    }
    else
    {
        //TODO
        //Manage case 3.
        
        typename AVLTNode<T>::Ref tmp = curr_;
        find_inorder_sucessor();
        tmp -> set_item(curr_ -> item());
        remove();

        //
    }
}

template <class T>
AVLTree<T>::AVLTree (typename AVLTNode<T>::Ref root_node)
{
    //TODO
    root_ = root_node;
    curr_ = root_node;
    prev_ = nullptr;
}

template <class T>
typename AVLTree<T>::Ref  AVLTree<T>::create (typename AVLTNode<T>::Ref root)
{
     AVLTree<T>::Ref ret_v (new AVLTree<T>(root));
     return ret_v;
}

template <class T>
typename AVLTNode<T>::Ref const&  AVLTree<T>::root() const
{
    //TODO
    return root_;
}

template <class T>
void AVLTree<T>::set_left(typename AVLTree<T>::Ref& subtree)
{
    assert(!is_empty());
    //TODO
    //Remenber to set parent's link of the subtree root to this.

    root_ -> set_left(subtree -> root_);

    if (!subtree -> is_empty())
        subtree -> root_ -> set_parent(root_);
    

    //
    assert(subtree->is_empty() || left()->item()==subtree->item());
    assert(!subtree->is_empty() || left()->is_empty());
}

template <class T>
void AVLTree<T>::set_right(typename AVLTree<T>::Ref& subtree)
{
    assert(!is_empty());
    //TODO
    //Remenber to set parent's link of the subtree root to this.

    root_ -> set_right(subtree -> root());
    if (!subtree -> is_empty())
        subtree -> root_ -> set_parent(this -> root_);
    
    //
    assert(subtree->is_empty()|| right()->item()==subtree->item());
    assert(!subtree->is_empty()|| right()->is_empty());
}

template <class T>
void AVLTree<T>::find_inorder_sucessor()
{
    assert(current_exists());
#ifndef NDEBUG
    T old_curr = current();
#endif
    //TODO
    prev_ = curr_;
    curr_ = curr_ -> right();
    
    while(curr_ -> has_left()){
        prev_ = curr_;
        curr_ = curr_ -> left();        
    }
    //
    assert(current_exists());
#ifndef NDEBUG
    assert(current()>old_curr);
#endif
}

template <class T>
void AVLTree<T>::rotate_left(typename AVLTNode<T>::Ref node)
{
    //TODO
    //Remenber when set a node A as child of a node B, also is needed set
    // node B as parent of node A.
    typename AVLTNode<T>::Ref aux = node -> left();
    if (!node -> has_parent()){
        root_ = aux;
    }
    else if (node -> parent() -> right() == node){
        node -> parent() -> set_right(aux);
    }
    else{
        node -> parent() -> set_left(aux);
    }
    
    aux -> set_parent(node -> parent());

    if (aux -> has_right()){
        node -> set_left(aux -> right());
        aux -> right() -> set_parent(node);
    }
    else{
        node -> remove_left();
    }

    aux -> set_right(node);
    node -> set_parent(aux);

    node -> compute_height();
    aux -> compute_height();

    //
}

template <class T>
void AVLTree<T>::rotate_right(typename AVLTNode<T>::Ref node)
{
    //TODO
    //Remenber when set a node A as child of a node B, also is needed set
    // node B as parent of node A.

    typename AVLTNode<T>::Ref aux = node -> right();
    if (!node -> has_parent()){
        root_ = aux;
    }
    else if (node -> parent() -> right() == node){
        node -> parent() -> set_right(aux);
    }
    else{
        node -> parent() -> set_left(aux);
    }
    
    aux -> set_parent(node -> parent());

    if (aux -> has_left()){
        node -> set_right(aux -> left());
        aux -> left() -> set_parent(node);
    }
    else{
        node -> remove_right();
    }

    aux -> set_left(node);
    node -> set_parent(aux);

    node -> compute_height();
    aux -> compute_height();

    //
}

template <class T>
void AVLTree<T>::make_balanced()
{
#ifdef __ONLY_BSTREE__
    return;
#else
    //TODO
    //From current position, go up until root's node is achieved.
    //In each step, check if the current subtree is balanced and balance it
    // if not.
    
    int bfp, bfc;
    typename AVLTNode<T>::Ref child;
    
    while(prev_ != nullptr){
        prev_ -> compute_height();
        bfp = prev_ -> balance_factor();
        
        if (bfp < -1){
            child = prev_ -> left();
            bfc = child -> balance_factor();
            
            if (bfc <= 0){
                rotate_left(prev_);
            }
            else {
                rotate_right(child);
                rotate_left(prev_);
            }
        }
        else if (bfp > 1){
            child = prev_ -> right();
            bfc = child -> balance_factor();
            
            if (bfc >= 0){
                rotate_right(prev_);
            }
            else {
                rotate_left(child);
                rotate_right(prev_);
            }
        }
        prev_ = prev_ -> parent();
    }

    //

    if (current_exists())
    {
        //TODO
        // Remember that due to the rotations, the state of attributes curr and prev
        // may be inconsistent, so we need to force that "previous of current" is the
        // parent of "current" when current_exists().


        //
    }

#endif //__ONLY_BSTREE__
}
