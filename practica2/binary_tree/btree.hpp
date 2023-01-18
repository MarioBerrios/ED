#ifndef __ED_BTree_HPP__
#define __ED_BTree_HPP__

#include <cassert>
#include <exception>
#include <memory>
#include <iostream>
#include <sstream>

/** @brief a BTree's Node.*/
template <class T>
class BTNode
{
public:

    /** @brief Define a shared reference to a BTNode.
     * Manages the storage of a pointer, providing a limited garbage-collection
     * facility, possibly sharing that management with other objects.
     * @see http://www.cplusplus.com/reference/memory/shared_ptr/
     */
    typedef std::shared_ptr< BTNode<T> > Ref;

    /** @name Life cicle.*/
    /** @{*/

    /** @brief Create a BTNode.
     * @post n_children() == 0
     */
    BTNode (T const& it=T(), BTNode<T>::Ref left=nullptr, BTNode<T>::Ref right=nullptr)
    {
        //TODO
        _item = it;
        _left = left;
        _right = right;
    }

    /**
     * @brief Create a BTNode using dynamic memory.
     * @param it the value save in the node.
     * @param left links to the left child.
     * @param right links to the right child.
     * @return a shared referente to the new node.
     */
    static typename BTNode<T>::Ref create(T const& it, BTNode<T>::Ref left=nullptr, BTNode<T>::Ref right=nullptr)
    {
        return std::make_shared<BTNode<T>> (it, left, right);
    }

    /** @brief Destroy a BTNode. **/
    ~BTNode()
    {}

    /** @}*/

    /** @name Observers.*/
    /** @{*/

    /** @brief Get the data item.*/
    const T& item() const
    {
        //TODO
        return _item;
    }

    /** @brief Has it a left child?*/
    bool has_left() const
    {
        //TODO
        return _left != nullptr;
    }

    /** @brief get the left child.*/
    BTNode<T>::Ref left() const
    {
        //TODO
        return _left;
    }

    /** @brief Has it a right child? */
    bool has_right() const
    {
        //TODO
        return _right != nullptr;
    }

    /** @brief get the right child.*/
    BTNode<T>::Ref right() const
    {
        //TODO
        return _right;
    }
    /** @}*/

    /** @name Modifiers.*/
    /** @{*/

    /** @brief Set the data item.*/
    void set_item(const T& new_it)
    {
        //TODO
        _item = new_it;
    }

    /** @brief Set the left child.*/
    void set_left(BTNode<T>::Ref new_child)
    {
        //TODO
        _left = new_child;
    }

    /** @brief Remove link to the left child. */
    void remove_left()
    {
        //TODO: hint see std::share_ptr doc.
        _left.reset();
    }

    /** @brief Set the right child.*/
    void set_right(BTNode<T>::Ref new_child)
    {
        //TODO
        _right = new_child;
    }

    /** @brief Remove linkt to the right child. */
    void remove_right()
    {
        //TODO: hint see std::share_ptr doc.
        _right.reset();
    }

protected:
    //TODO
    //Hint: use typename SNode<T>::Ref for the link to other nodes.
    T _item;
    typename BTNode<T>::Ref _left;
    typename BTNode<T>::Ref _right;
};

/**
 * @brief ADT BTree.
 * Models a BTree of T.
 */
template<class T>
class BTree
{
  public:

    /** @brief Define a shared reference to a BTNode.
     * Manages the storage of a pointer, providing a limited garbage-collection
     * facility, possibly sharing that management with other objects.
     * @see http://www.cplusplus.com/reference/memory/shared_ptr/
     */
    typedef std::shared_ptr< BTree<T> > Ref;

  /** @name Life cicle.*/
  /** @{*/

    /** @brief Create an empty BTree.
     * @post is_empty()
     */
    BTree ()
    {
        //TODO
        _root = nullptr;
        _curr = nullptr;
        _prev = nullptr;
    }

  /** @brief Create Leaf BTree.
   * @post not is_empty()
   */
  BTree (const T& item)
  {
      //TODO
        create_root(item);
        
  }

  /**
   * @brief Create an empty BTree.
   * @return a shared referente to the new tree.
   */
  static typename BTree<T>::Ref create()
  {
      return std::make_shared<BTree<T>> ();
  }

  /**
   * @brief Create a leaf BTree.
   * @param item is the root's item.
   * @return a shared referente to the new tree.
   */
  static typename BTree<T>::Ref create(T const& item)
  {
      return std::make_shared<BTree<T>>(item);
  }

  /**
   * @brief Load a tree from a input stream.
   *
   * The input format will be:
   * '[]' for the empty tree.
   * '[ <item> <left-subtree> <right-subtree> ']'
   *
   * For example a tree with three nodes:
   * "[ 2 [ 1 [] [] ] [ 3 [] [] ] ]"
   *
   * @return a reference to the tree created.
   * @warning runtime_error will throw if worng input format was found.
   */
  static typename BTree<T>::Ref create (std::istream& in) noexcept(false)
  {
      auto tree = BTree<T>::create();
      std::string token;
      in >> token;
      if (!in)
          throw std::runtime_error("Wrong input format.");

      //TODO
        T new_item;

        if (token == "[]")
            return tree;

        if(token != "[")
            throw std::runtime_error("Wrong input format.");

        if(token == "["){
            in >> token;
            std::istringstream str(token);
            str >> new_item;
            
            tree -> create_root(new_item);
            tree -> set_left(BTree<T>::create(in));
            tree -> set_right(BTree<T>::create(in));

            in >> token;
            if(token != "]")
                throw std::runtime_error("Wrong input format.");
        }

      return tree;
  }

  /** @brief Destroy a BTree.**/
  ~BTree()
  {}

  /** @}*/

  /** @name Observers*/

  /** @{*/

  /** @brief is the list empty?.*/
  bool is_empty () const
  {
      //TODO
      return _root == nullptr;
  }

  /** @brief Get the root item.
   * @pre not is_empty();
   */
  T const& item() const
  {
      assert(!is_empty());
      //TODO
      return _root -> item();
  }

  /**
   * @brief Get the left subtree.
   * @return a reference to the left subtree.
   * @pre !is_empty()
   */
  typename BTree<T>::Ref left() const
  {
      assert(!is_empty());
      BTree<T>::Ref l_subtree;

      //TODO
        l_subtree = l_subtree -> create();
        l_subtree -> _root = _root -> left();
      //

      return l_subtree;
  }

  /**
   * @brief Get the right subtree.
   * @return a reference to the right subtree.
   * @pre !is_empty()   
   */
  typename BTree<T>::Ref right() const
  {
      assert(!is_empty());
      BTree<T>::Ref r_subtree;

      //TODO
        r_subtree = r_subtree -> create();
        r_subtree -> _root = _root -> right();

      //

      return r_subtree;
  }

  /**
   * @brief Fold a binary tree.
   *
   * The output format will be:
   * '[]' for the empty tree.
   * '[ <item> <left-subtree> <right-subtree> ']'
   *
   * For example a tree with three nodes:
   * "[ 2 [ 1 [] [] ] [ 3 [] [] ] ]"
   *
   * @param out is the output stream.
   * @param tree is the tree.
   * @return the output stream.
   * @pre tree!=nullptr
   */
  std::ostream& fold(std::ostream& out) const
  {
      //TODO
        if(this -> is_empty())
            out << "[]";

        else {
            out << "[ ";
            out << _root -> item() << " ";
            this -> left() -> fold(out);
            out << " ";
            this -> right() -> fold(out);
            out << " ]";
            
        }
      //
      return out;
  }

  /** @}*/

  /** @name Modifiers*/

  /** @{*/

  /**
   * @brief set the roor's item.
   * @pre not is_empty()
   */
  void set_item(const T& new_it)
  {
      assert(!is_empty());
      //TODO
        _root -> set_item(new_it);
  }

  /**
   * @brief Create the root node.
   * item is the new root item.
   * @post !is_empty()
   */
  void create_root(T const& item)
  {
      //TODO
        _root = BTNode<T>::create(item, nullptr, nullptr);
  }

  /**
   * @brief Remove the link to the root node.
   * @post is_empty()
   */
  void remove_root()
  {
      //TODO
        _root = nullptr;
      assert(is_empty());
  }

  /**
   * @brief Attach a new subtree as left child of root.
   * @param new_left is the new left subtree.
   * @pre !is_empty()
   */
  void set_left(typename BTree<T>::Ref new_left)
  {
      assert(!is_empty());
      //TODO
        _root -> set_left(new_left -> _root);
  }

  /**
   * @brief Detach the left child of root.
   * @pre !is_empty()
   */
  void remove_left()
  {
      assert(!is_empty());
      //TODO
        _root -> set_left(nullptr);
  }

  /**
   * @brief Attach a new subtree as right child of root.
   * @param t is the new right subtree.
   */
  void set_right(typename BTree<T>::Ref t)
  {
      assert(!is_empty());
      //TODO
        _root -> set_right(t -> _root);
  }

  /**
   * @brief Detach the right child of root.
   * @pre !is_empty()
   */
  void remove_right()
  {
      assert(!is_empty());
      //TODO
        _root -> set_right(nullptr);
  }

  /** @}*/

protected:

  //TODO
    
    typename BTNode<T>::Ref _root;
    typename BTNode<T>::Ref _curr;
    typename BTNode<T>::Ref _prev;

};
#endif
